#include <LSM6DS3.h>
#include <bluefruit.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <Wire.h>
#include <malloc.h>


BLEService dataService("8cee49d4-f8cd-44b5-9986-9860eae25def");
BLECharacteristic protoCharacIn("f65a39c4-bf69-43e9-abf1-f23a4e0ec8d0");

TaskHandle_t taskHandle; 
Adafruit_NeoPixel pixels(10, 3, NEO_GRB + NEO_KHZ800);

enum { RID_KEYBOARD = 0, };
uint8_t const desc_hid_report[] = { TUD_HID_REPORT_DESC_KEYBOARD(), };
Adafruit_USBD_HID usbHID(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);

void loop() {
}

void setup() {
	dwt_enable();
	Wire.setClock(800000);
	NRF_I2S->ENABLE = 1;
	TinyUSB_Device_FlushCDC();
	malloc(10);
}
