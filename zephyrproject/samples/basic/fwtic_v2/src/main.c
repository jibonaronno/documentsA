/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"


#include "button_svc.h"
#include "led_svc.h"

/* Custom Service Variables */
#define BT_UUID_CUSTOM_SERVICE_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)

static struct bt_uuid_128 vnd_uuid = BT_UUID_INIT_128(BT_UUID_CUSTOM_SERVICE_VAL);

static struct bt_uuid_128 vnd_enc_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1));

static struct bt_uuid_128 vnd_auth_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2));

static const struct bt_uuid_128 vnd_long_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3));

#define VND_MAX_LEN 20

static uint8_t vnd_value[VND_MAX_LEN + 1] = { 'T', 'I', 'C', '-', 'V', '1', '.', '0', '0'};
static uint8_t vnd_auth_value[VND_MAX_LEN + 1] = { 'T', 'I', 'C', '-', 'V', '1', '.', '0', '0'};
static uint8_t vnd_wwr_value[VND_MAX_LEN + 1] = { 'T', 'I', 'C', '-', 'V', '1', '.', '0', '0'};

#define VND_LONG_MAX_LEN 74
static uint8_t vnd_long_value[VND_LONG_MAX_LEN + 1] = {
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '1',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '2',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '3',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '4',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '5',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '6',
		  '.', ' ' };

#define E0_STACK_SIZE 500
#define E0_PRIORITY 5

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

/* The devicetree node identifier for the "led0" alias. */
//#define LED0_NODE DT_ALIAS(led0)

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart), "Console device is not ACM CDC UART device");

K_THREAD_STACK_DEFINE(e0_stack, E0_STACK_SIZE);
struct k_thread e0_thread;

#define RING_BUF_SIZE 1024
uint8_t ring_buffer[RING_BUF_SIZE];
struct ring_buf ringbuf;

int flag_a = 0;
int flag_b = 0;
int flag_c = 0;
int flag_d = 0;

int flag_x = 0;
int flag_y = 0;
int flag_v = 0;
int flag_w = 0;
int flag_z = 0;
int flag_u = 0;

int x_global = 0;
int y_global = 0;

int ret, p0, p1, p2, p3, p4, p5, t1pwm, t2pwm;

uint16_t accel_value = 0;

volatile int run_duration_limit = 0;

void uartSend(const struct device *dev, char *usrData)
{

	int lent = strlen(usrData);
	int send_len = 0;


	while (uart_irq_update(dev) && uart_irq_is_pending(dev))
	{
		k_sleep(K_MSEC(100));
	}


	/*************************
	 * Functin below has no effect here. 
	 * I copied this function from interrup handler.
	 * Transmitting data over uart 
	 * here does not perform as
	 * from inside interrupt handler.
	 * *********************/
	//uart_irq_tx_enable(dev);

	/**********************************************
	 * If this if state is enabled then data does not transmit.
	 * But it works inside interrupt_handler
	 * ******************************************/
	//if (uart_irq_tx_ready(dev)) 
	{
		send_len = uart_fifo_fill(dev, (uint8_t *)usrData, lent);
	}
}

static void interrupt_handler(const struct device *dev, void *user_data)
{
	ARG_UNUSED(user_data);

	while (uart_irq_update(dev) && uart_irq_is_pending(dev)) 
	{
		if (uart_irq_rx_ready(dev)) 
		{
			int recv_len, rb_len;
			uint8_t buffer[64];
			size_t len = MIN(ring_buf_space_get(&ringbuf), sizeof(buffer));

			recv_len = uart_fifo_read(dev, buffer, len);
			
			if (recv_len < 0) 
			{
				//LOG_ERR("Failed to read UART FIFO");
				recv_len = 0;
			}

			

			if(buffer[0] == 'd')
			{
				flag_d = 1;
			}

			rb_len = ring_buf_put(&ringbuf, buffer, recv_len);

			if (rb_len < recv_len) 
			{
				;//LOG_ERR("Drop %u bytes", recv_len - rb_len);
			}

			//LOG_DBG("tty fifo -> ringbuf %d bytes", rb_len);
			if (rb_len) 
			{
				uart_irq_tx_enable(dev);
			}
		}

		/* As mentioned earlier, it works here. */
		if (uart_irq_tx_ready(dev)) 
		{
			uint8_t buffer[64];
			int rb_len, send_len;

			rb_len = ring_buf_get(&ringbuf, buffer, sizeof(buffer));

			if (!rb_len) 
			{
				//LOG_DBG("Ring buffer empty, disable TX IRQ");
				uart_irq_tx_disable(dev);
				continue;
			}

			send_len = uart_fifo_fill(dev, buffer, rb_len);

			if (send_len < rb_len) 
			{
				;
				//LOG_ERR("Drop %d bytes", rb_len - send_len);
			}

			//LOG_DBG("ringbuf -> tty fifo %d bytes", send_len);
		}
	}
}


/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
int err;
struct bt_conn *default_conn;
static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpioa));
static const struct device *portb = DEVICE_DT_GET(DT_NODELABEL(gpiob));

static uint16_t but_val;

static uint16_t counterA = 0;

/* Prototype */
static ssize_t recv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
		    uint16_t len, uint16_t offset, uint8_t flags);

/* ST Custom Service  */
static struct bt_uuid_128 st_service_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x0000fe40, 0xcc7a, 0x482a, 0x984a, 0x7f2ed5b3e58f));

/* ST LED service */
static struct bt_uuid_128 led_char_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x0000fe41, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19));

/* ST Notify button service */
static struct bt_uuid_128 but_notif_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x0000fe42, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19));

/* ST LED service */
static struct bt_uuid_128 accel_char_uuid = BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x0000fe43, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed21));

static ssize_t write_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, /*sizeof(ct)*/ 2 );
}

static ssize_t read_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

static ssize_t write_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (offset + len > VND_MAX_LEN) 
	{
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	value[offset + len] = 0;

	return len;
}

static ssize_t write_long_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (flags & BT_GATT_WRITE_FLAG_PREPARE) 
	{
		return 0;
	}

	if (offset + len > VND_LONG_MAX_LEN) 
	{
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	value[offset + len] = 0;

	return len;
}

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
#define ADV_LEN 12

/* Advertising data */
static uint8_t manuf_data[ADV_LEN] = {
	0x01 /*SKD version */,
	0x83 /* STM32WB - P2P Server 1 */,
	0x00 /* GROUP A Feature  */,
	0x00 /* GROUP A Feature */,
	0x00 /* GROUP B Feature */,
	0x00 /* GROUP B Feature */,
	0x00, /* BLE MAC start -MSB */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, /* BLE MAC stop */
};

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
	BT_DATA(BT_DATA_MANUFACTURER_DATA, manuf_data, ADV_LEN)
};

/* BLE connection */
struct bt_conn *conn;
/* Notification state */
volatile bool notify_enable;

static void mpu_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	ARG_UNUSED(attr);
	notify_enable = (value == BT_GATT_CCC_NOTIFY);
	//LOG_INF("Notification %s", notify_enable ? "enabled" : "disabled");
}

/* The embedded board is acting as GATT server.
 * The ST BLE Android app is the BLE GATT client.
 */

 /* ST BLE Sensor GATT services and characteristic */

BT_GATT_SERVICE_DEFINE(stsensor_svc,
BT_GATT_PRIMARY_SERVICE(&st_service_uuid),
BT_GATT_CHARACTERISTIC(&but_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY,
		       BT_GATT_PERM_READ, NULL, NULL, &but_val),
BT_GATT_CHARACTERISTIC(&accel_char_uuid.uuid,
		       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE, // BT_GATT_CHRC_WRITE_WITHOUT_RESP,
		       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, write_cb, recv, &accel_value),
BT_GATT_CCC(mpu_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);

void accel_notify(void)
{	/* Current Time Service updates only when time is changed 
	if (!ct_update) {
		return;
	}
	ct_update = 0U;
	*/
	accel_value++;

	bt_gatt_notify(NULL, &stsensor_svc.attrs[2], &accel_value, /*sizeof(ct)*/ 2);
}

/*
BT_GATT_SERVICE_DEFINE(stsensor_svc,
BT_GATT_PRIMARY_SERVICE(&st_service_uuid),
BT_GATT_CHARACTERISTIC(&led_char_uuid.uuid,
		       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
		       BT_GATT_PERM_WRITE, NULL, recv, (void *)1),
BT_GATT_CHARACTERISTIC(&but_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY,
		       BT_GATT_PERM_READ, NULL, NULL, &but_val),
BT_GATT_CCC(mpu_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);
*/

static ssize_t recv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
	//led_update();
	printk("recv() called \r\n");
	printk("Data count: %d Data: %s\r\n", len, (unsigned char *)buf);
	return 0;
}

static void manual_bt_notify(void)
{
	if (conn) 
	{
		if (notify_enable) 
		{
			err = bt_gatt_notify(NULL, &stsensor_svc.attrs[4], &but_val, sizeof(but_val));
			if (err) 
			{
				; //LOG_ERR("Notify error: %d", err);
			}
			if(but_val < 32767)
			{
				but_val++;
			}
			else
			{
				but_val = 1;
			}
			printk(":");
		}
	}
}

static void bt_ready(int err)
{
	if (err) 
	{
		//LOG_ERR("Bluetooth init failed (err %d)", err);
		return;
	}
	//LOG_INF("Bluetooth initialized");
	/* Start advertising */
	err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
	
	if (err) 
	{
		//LOG_ERR("Advertising failed to start (err %d)", err);
		return;
	}

	//LOG_INF("Configuration mode: waiting connections...");
}

static void connected(struct bt_conn *connected, uint8_t err)
{
	if (err) 
	{
		printk("Connection failed (err %u) \r\n", err); //LOG_ERR("Connection failed (err %u)", err);
	} 
	else 
	{
		//LOG_INF("Connected");
		printk("BLE Connected \r\n");
		if (!conn) 
		{
			conn = bt_conn_ref(connected);
		}
	}
}

static void disconnected(struct bt_conn *disconn, uint8_t reason)
{
	if (conn) 
	{
		bt_conn_unref(conn);
		conn = NULL;
		printk("BLE Disconnected \r\n");
	}

	//LOG_INF("Disconnected (reason %u)", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

void timer_handler(struct k_timer *timer)
{
    printk(".");
	if (conn) 
	{
		//manual_bt_notify();
		accel_notify();
	}
}

K_TIMER_DEFINE(e0_timer, timer_handler, NULL);

void e0_thread_entry(void *p1, void *p2, void *p3)
{
    printk("Starting timer...\n");
    k_timer_start(&e0_timer, K_SECONDS(5), K_SECONDS(5));

    while (1) {
        //printk("Doing other work...\n");
        k_sleep(K_SECONDS(1));
    }
}

void main(void)
{
	
	/// @brief USB
	/// @param None
	//const struct device *dev;
	uint32_t baudrate, dtr = 0U;
	// END USB

	if (!device_is_ready(gpio_ct_dev)) {
		return;
	}

	p0 = gpio_pin_configure(gpio_ct_dev, 1, GPIO_OUTPUT_ACTIVE);
	p1 = gpio_pin_configure(gpio_ct_dev, 7, GPIO_OUTPUT_ACTIVE);
	t1pwm = gpio_pin_configure(gpio_ct_dev, 8, GPIO_OUTPUT_ACTIVE);
	t2pwm = gpio_pin_configure(gpio_ct_dev, 5, GPIO_OUTPUT_ACTIVE);
	p2 = gpio_pin_configure(gpio_ct_dev, 6, GPIO_OUTPUT_ACTIVE);
	p3 = gpio_pin_configure(portb, 2, GPIO_OUTPUT_ACTIVE);
	p4 = gpio_pin_configure(gpio_ct_dev, 14, GPIO_OUTPUT_ACTIVE);
	p5 = gpio_pin_configure(gpio_ct_dev, 13, GPIO_OUTPUT_ACTIVE);
	//ret = gpio_pin_configure(gpio_ct_dev, 0, GPIO_OUTPUT_ACTIVE);

	k_thread_create(&e0_thread, e0_stack, E0_STACK_SIZE, e0_thread_entry, NULL, NULL, NULL, E0_PRIORITY, 0, K_NO_WAIT);

	
	const struct device *const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

	//dev = DEVICE_DT_GET_ONE(zephyr_cdc_acm_uart);

	if (!device_is_ready(dev)) {
		//LOG_ERR("CDC ACM device not ready");
		return;
	}

	ret = usb_enable(NULL);
	if (ret != 0) {
		//LOG_ERR("Failed to enable USB");
		return;
	}

	ring_buf_init(&ringbuf, sizeof(ring_buffer), ring_buffer);

	//LOG_INF("Wait for DTR");
	while (true) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
		if (dtr) {
			break;
		} else {
			/* Give CPU resources to low priority threads. */
			k_sleep(K_MSEC(100));
		}
	}

	//LOG_INF("DTR set");

	/* They are optional, we use them to test the interrupt endpoint */
	ret = uart_line_ctrl_set(dev, UART_LINE_CTRL_DCD, 1);
	if (ret) {
		;//LOG_WRN("Failed to set DCD, ret code %d", ret);
	}

	ret = uart_line_ctrl_set(dev, UART_LINE_CTRL_DSR, 1);
	if (ret) {
		;//LOG_WRN("Failed to set DSR, ret code %d", ret);
	}

	/* Wait 1 sec for the host to do all settings */
	k_busy_wait(1000000);

	ret = uart_line_ctrl_get(dev, UART_LINE_CTRL_BAUD_RATE, &baudrate);
	if (ret) {
		;//LOG_WRN("Failed to get baudrate, ret code %d", ret);
	} else {
		;//LOG_INF("Baudrate detected: %d", baudrate);
	}

	uart_irq_callback_set(dev, interrupt_handler);

	/* Enable rx interrupts */
	uart_irq_rx_enable(dev);

	uartSend(dev, "Command Interface From Uart \r\n");

    /**************************************
	if(gap_init() == 0)
	{
		printk("GAP INIT .............");
	}
	else
	{
		printk("GAP INIT ERROR ........");
	}
    ****************************************/

	bt_enable(bt_ready);

	while (1) 
	{
		
		k_msleep(100);
	}
}
