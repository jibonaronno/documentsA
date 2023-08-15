# Initial test firmware.
* Most of the uuids are not applied. <br>
I tried to make a characteristics for accel data. For accel data I made a uuid constant as accel_char_uuid, Then use this uuid to make the characteristic as below: <br>

```C
BT_GATT_SERVICE_DEFINE(stsensor_svc,
BT_GATT_PRIMARY_SERVICE(&st_service_uuid),
BT_GATT_CHARACTERISTIC(&but_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY,
		       BT_GATT_PERM_READ, NULL, NULL, &but_val),
BT_GATT_CHARACTERISTIC(&accel_char_uuid.uuid,
		       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE, // BT_GATT_CHRC_WRITE_WITHOUT_RESP,
		       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, write_cb, recv, &accel_value),
BT_GATT_CCC(mpu_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);
```

Mark the stsensor_svc is the service, inside this service there are 4 elements. Along these elements, 2 of them are characteristics. One is but_notify_uuid and another is our accel_char_uuid . See these macros are helping to create BLE data structures. Observe that the accel_value is a global variable that reflects the accel value. We use another function called accel_notify() which eventually called bt_gatt_notify(...) <br>
I am calling this function at a regular interval by using an OS timer at every 4/5 seconds interval. May be this function sends data over BLE. <br>

This main.c file has many function that has not been used yet. Device also get hanged when I tried to reconnect on BLE. 
<br><br>
At this stage of development you can see that proj.conf is much smaller as below: <br>
```C
CONFIG_STDOUT_CONSOLE=y
CONFIG_USB_DEVICE_STACK=y
CONFIG_USB_DEVICE_PRODUCT="Zephyr CDC ACM sample"
CONFIG_GPIO=y
CONFIG_BT=y
CONFIG_BT_DEBUG_LOG=y
CONFIG_BT_PERIPHERAL=y
CONFIG_BT_DEVICE_NAME="TIC-V1.00"
CONFIG_BT_GATT_CLIENT=y
CONFIG_LOG=y
CONFIG_LOG_BUFFER_SIZE=2048
CONFIG_SERIAL=y
CONFIG_UART_INTERRUPT_DRIVEN=y
CONFIG_UART_LINE_CTRL=y
```
<br>
