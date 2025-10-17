/**
 * @file spi_dma.h
 * @version 01.00
 * @brief SPI Interface Using DMA
 * @ingroup Drivers
 *
 * This module provides SPI communication functionality using Direct Memory Access (DMA)
 * for efficient data transfers. It supports asynchronous transmit/receive operations
 * and event-driven callbacks for transfer completion.
 *
 * Intended for use with Microchip MCUs and ASF-based firmware.
 */

#ifndef SPI_DMA_H_INCLUDED
#define SPI_DMA_H_INCLUDED

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup SpiDma SPI DMA Driver
 * @ingroup Drivers
 * @brief SPI data transfer using DMA for improved performance
 * @{
 */

/**
 * @brief Type for SPI transfer event callback functions.
 *
 * This function type is used to register callbacks that will be called when
 * a specific SPI transfer event occurs (e.g., transmission complete).
 */
typedef void (*SPIEventHandler_t)(void);

/**
 * @brief SPI transfer event types.
 *
 * These are used to indicate whether the registered event handler should be
 * triggered for a transmission or reception completion.
 */
enum SPIEvent_t {
    spiEvTxDone, /**< Transmission completed */
    spiEvRxDone  /**< Reception completed */
};

/**
 * @brief Registers a callback function for a specific SPI DMA event.
 *
 * The function will be invoked when the specified event occurs.
 *
 * @param func Pointer to the callback function to register.
 * @param eventtype Event type to associate with the callback.
 */
void RegisterSpiEvent(SPIEventHandler_t func, enum SPIEvent_t eventtype);

/**
 * @brief Unregisters a previously registered SPI DMA event callback.
 *
 * Prevents the callback from being called when the associated event occurs.
 *
 * @param func Pointer to the previously registered callback function.
 * @param eventtype Event type associated with the callback.
 */
void UnregisterSpiEvent(SPIEventHandler_t func, enum SPIEvent_t eventtype);

/**
 * @brief Initializes the SPI interface with DMA support.
 *
 * This function should be called once before performing any SPI transfers.
 * It sets up the SPI peripheral and configures DMA channels.
 */
void spi_dma_init(void);

/**
 * @brief Starts an SPI transfer using DMA.
 *
 * Initiates a full-duplex SPI transfer. Either `txBuf` or `rxBuf` may be `NULL`
 * if only transmitting or receiving data. Both buffers must have at least `us_len` bytes.
 *
 * @param txBuf Pointer to the transmit buffer. May be `NULL`.
 * @param rxBuf Pointer to the receive buffer. May be `NULL`.
 * @param us_len Number of bytes to transfer.
 * @param csPin Chip select pin index for the SPI slave.
 *
 * @return `true` if the transfer was successfully started, `false` otherwise.
 */
bool spi_dma_transfer(uint8_t *txBuf, uint8_t *rxBuf, uint16_t us_len, uint8_t csPin);

/**
 * @brief Checks whether the current SPI DMA transfer has completed.
 *
 * @return `true` if the transfer has finished, `false` if still in progress.
 */
bool spi_dma_done(void);

/** @} */ // end of SpiDma group

#ifdef __cplusplus
}
#endif

#endif /* SPI_DMA_H_INCLUDED */
