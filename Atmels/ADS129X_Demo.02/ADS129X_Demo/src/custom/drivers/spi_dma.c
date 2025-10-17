#include "string.h"
#include "spi_dma.h"
#include "user_board.h"
#include "sysclk.h"
#include "spi.h"
#include "pdc.h"
#include "ioport.h"
#include <asf.h>

/* @cond 0 */
#ifdef __cplusplus
extern "C" {
#endif
/* @endcond */

/**
* \weakgroup spi_dma_group SPI driver with DMA support
* \brief SPI driver with DMA support
* \ingroup Drivers
* @{
*/

/* SPI clock setting (Hz). */
static uint32_t gs_ul_spi_clock = SPI_CLOCK;

/* PDC buffer us_size. */
#define PDC_SPI_BUFFER_SIZE       800

/* Max number of following reads. */
#define MAX_NUM_READ_RX_COUNTER    10

/* PDC Receive buffer */
static uint8_t gs_spi_rx_buffer[PDC_SPI_BUFFER_SIZE];
/* PDC Transmission buffer */
static uint8_t gs_spi_tx_buffer[PDC_SPI_BUFFER_SIZE];
/* PDC RX data packet */
pdc_packet_t g_spi_rx_packet;
/* PDC TX data packet */
pdc_packet_t g_spi_tx_packet;
/* Pointer to PDC register base */
Pdc *g_spi_pdc;

/* SPI busy indication */
static uint8_t uc_spi_is_busy;

/* PPLC chip select config value */
#define SPI_PCS    spi_get_pcs(SPI_CHIP_ID_0)

/**
* \brief Initialize SPI_DMA interface
*
*/
void spi_dma_init(void) {
    uint32_t ul_cpuhz;
    uint8_t uc_div;
    pio_configure(PIOA, PINS_ADS_SPI_TYPE, PINS_ADS_SPI_PA_MASK, PINS_ADS_SPI_PA_ATTR);
    pio_configure(PIOB, PINS_ADS_SPI_TYPE, PINS_ADS_SPI_PB_MASK, PINS_ADS_SPI_PB_ATTR);

    ul_cpuhz = sysclk_get_cpu_hz();
    uc_div = ul_cpuhz / gs_ul_spi_clock;

    /* Enable SPI peripheral. */
    spi_enable_clock(SPI_MODULE);

    /* Reset SPI */
    spi_disable(SPI_MODULE);
    spi_reset(SPI_MODULE);

    /* Configure SPI */
    spi_set_master_mode(SPI_MODULE);
    spi_disable_mode_fault_detect(SPI_MODULE);
    spi_disable_loopback(SPI_MODULE);
    spi_set_peripheral_chip_select_value(SPI_MODULE, SPI_PCS);
    spi_set_clock_polarity(SPI_MODULE, SPI_CHIP_ID_0, 0);
    spi_set_clock_phase(SPI_MODULE, SPI_CHIP_ID_0, 0);
    spi_set_bits_per_transfer(SPI_MODULE, SPI_CHIP_ID_0, SPI_CSR_BITS_8_BIT);
    spi_set_fixed_peripheral_select(SPI_MODULE);
    spi_set_baudrate_div(SPI_MODULE, SPI_CHIP_ID_0, uc_div);
    spi_set_transfer_delay(SPI_MODULE, SPI_CHIP_ID_0, SPI_DLYBS, SPI_DLYBCT);
    spi_configure_cs_behavior(SPI_MODULE, SPI_CHIP_ID_0, SPI_CS_RISE_NO_TX);

#ifdef SPI_CHIP_ID_1
    /* CS1 stuff */
    spi_set_peripheral_chip_select_value(SPI_MODULE, spi_get_pcs(SPI_CHIP_ID_1));
    spi_set_clock_polarity(SPI_MODULE, SPI_CHIP_ID_1, 0);
    spi_set_clock_phase(SPI_MODULE, SPI_CHIP_ID_1, 0);
    spi_set_bits_per_transfer(SPI_MODULE, SPI_CHIP_ID_1, SPI_CSR_BITS_8_BIT);
    spi_set_baudrate_div(SPI_MODULE, SPI_CHIP_ID_1, uc_div);
    spi_set_transfer_delay(SPI_MODULE, SPI_CHIP_ID_1, SPI_DLYBS, SPI_DLYBCT);
    spi_configure_cs_behavior(SPI_MODULE, SPI_CHIP_ID_1, SPI_CS_RISE_NO_TX);
#endif

    spi_enable_interrupt(SPI_MODULE, SPI_IER_RXBUFF);
    // Configure and enable interrupt of spi.
    NVIC_EnableIRQ((IRQn_Type)ID_SPI);
    NVIC_SetPriority((IRQn_Type)ID_SPI, 10);

    /* SPI PDC base address and enable receiver and transmitter */
    g_spi_pdc = spi_get_pdc_base(SPI_MODULE);
    spi_enable(SPI_MODULE);
}

static SPIEventHandler_t spiEventHandlers[2] = {NULL};

void RegisterSpiEvent(SPIEventHandler_t func, enum SPIEvent_t eventtype) {
    spiEventHandlers[eventtype] = func;
}

void UnregisterSpiEvent(SPIEventHandler_t func, enum SPIEvent_t eventtype) {
    UNUSED(func);
    spiEventHandlers[eventtype] = NULL;
}

void SPI_Handler(void) {
    const uint32_t status = SPI_MODULE->SPI_SR;
    if (status & (SPI_SR_ENDTX|SPI_SR_RXBUFF)) {
        spi_disable_interrupt(SPI_MODULE, SPI_IER_RXBUFF);
        uc_spi_is_busy = false;
        if(status & SPI_SR_ENDTX) {
            if(spiEventHandlers[spiEvTxDone] != NULL) {
                spiEventHandlers[spiEvTxDone]();
            }
            if(spiEventHandlers[spiEvRxDone] != NULL) {
                spiEventHandlers[spiEvRxDone]();
            }
        }
    }
}

bool spi_dma_done(void) {
    bool result;
    Disable_global_interrupt();
    result = !uc_spi_is_busy;
    Enable_global_interrupt();
    return result;
}

bool spi_dma_transfer(uint8_t *txBuf, uint8_t *rxBuf, uint16_t us_len, uint8_t csPin) {
    Disable_global_interrupt();
    if (!uc_spi_is_busy) {
        uc_spi_is_busy = true;
        /* Fill tx data */
        if (txBuf != NULL) {
            memcpy(gs_spi_tx_buffer, txBuf, us_len);
        } else {
            memset(gs_spi_tx_buffer, 0xff, us_len);
        }

        if(csPin == 0) {
            spi_set_peripheral_chip_select_value(SPI_MODULE, spi_get_pcs(SPI_CHIP_ID_0));    // use the right cs
        } 
#ifdef SPI_CHIP_ID_1
        else {
            spi_set_peripheral_chip_select_value(SPI_MODULE, spi_get_pcs(SPI_CHIP_ID_1));    // use the right cs
        }
#endif

        /* Configure DMA channels */
        g_spi_rx_packet.ul_addr = (rxBuf!=NULL)?(uint32_t)(rxBuf):(uint32_t)gs_spi_rx_buffer;
        g_spi_rx_packet.ul_size = us_len;
        pdc_rx_init(g_spi_pdc, &g_spi_rx_packet, NULL);

        g_spi_tx_packet.ul_addr = (uint32_t)gs_spi_tx_buffer;
        g_spi_tx_packet.ul_size = us_len;
        pdc_tx_init(g_spi_pdc, &g_spi_tx_packet, NULL);

        pdc_enable_transfer(g_spi_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);
        spi_enable_interrupt(SPI_MODULE,  SPI_IER_RXBUFF);
        Enable_global_interrupt();
        return true;
    } else {
        Enable_global_interrupt();
        return false;
    }
}

/* @} */

/* @cond 0 */
#ifdef __cplusplus
}
#endif
/* @endcond */