| Supported ESP SoCs | ESP32 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 | ESP32-P4 |
| ------------------ | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# LVGL (v8) Porting Example

## Overview

This example demonstrates how to port `LVGL v8`. And it runs LVGL's internal demos include `Music Player`, `Widgets`, `Stress` and `Benchmark`.

This example also shows three methods to avoid tearing effect when using `RGB/MIPI-DSI` interface LCD. It uses two or more frame buffers based on LVGL **buffering modes**. For more information about this, please refer to [LVGL documents](https://docs.lvgl.io/8.4/porting/display.html?highlight=buffering%20mode#buffering-modes).

## How to use

### ESP-IDF Required

* This demo was made and tested with ESP-IDF `v5.4.1`.
* Please follow the [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html) to set up the development environment.

### Hardware Required

* Olimex [ESP32-P4-DevKit](https://www.olimex.com/Products/IoT/ESP32-P4/ESP32-P4-DevKit/open-source-hardware)
* Display - Olimex [MIPI-LCD2.8-640x480](https://www.olimex.com/Products/RaspberryPi/MIPI-LCD2.8-640x480/)
* USB cable

### Configurations

The demo is already configured, but if you wish you can check the menuconfig settigns the following way:

- Run `idf.py menuconfig`
- Go to `Example Configurations`:

  - `Avoid Tearing Mode`: Select the avoid tearing mode you want to use. Only valid for `RGB/MIPI-DSI` interface LCDs.
  - `Rotation Degree`: Select the rotation degree you want to use. Only valid when `Avoid Tearing Mode` is not `None`.

- Go to `ESP Display Panel Configurations`:

  - See [Configuration Guide](../../../docs/envs/use_with_idf.md#configuration-guide) for more details.

### Build and Flash

Run `idf.py -p <PORT> build flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type `Ctrl-]`.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.
