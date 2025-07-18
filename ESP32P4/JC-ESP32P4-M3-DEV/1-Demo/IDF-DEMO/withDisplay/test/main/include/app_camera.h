#ifndef __APP_CAMERA_H
#define __APP_CAMERA_H


#include <stdint.h>
#include "esp_cam_sensor_types.h"
#include "ov5647_types.h"
#include "bsp/esp-bsp.h"

#include "lvgl.h"

extern lv_obj_t *label;

void app_camera(void);

#define OV5647_IDI_CLOCK_RATE_800x800_50FPS        (100000000ULL)
#define OV5647_8BIT_MODE                           (0x18)
#define OV5647_REG_END              0xffff


static const ov5647_reginfo_t ov5647_raw8_800x800_50fps[] = {
    {0x3034, OV5647_8BIT_MODE}, // set RAW format
    {0x3035, 0x41}, // system clk div
    {0x3036, ((OV5647_IDI_CLOCK_RATE_800x800_50FPS * 8 * 4) / 25000000)},
    {0x303c, 0x11},
    {0x3106, 0xf5},
    {0x3821, 0x03},
    {0x3820, 0x41},
    {0x3827, 0xec},
    {0x370c, 0x0f},
    {0x3612, 0x59},
    {0x3618, 0x00},
    {0x5000, 0xff},

    {0x583e, 0xf0}, // LSC max gain
    {0x583f, 0x20}, // LSC min gain

    {0x5002, 0x41},
    {0x5003, 0x08},
    {0x5a00, 0x08},
    {0x3000, 0x00},
    {0x3001, 0x00},
    {0x3002, 0x00},
    {0x3016, 0x08},
    {0x3017, 0xe0},
    {0x3018, 0x44},
    {0x301c, 0xf8},
    {0x301d, 0xf0},
    {0x3a18, 0x00},
    {0x3a19, 0xf8},
    {0x3c01, 0x80},
    {0x3c00, 0x40},
    {0x3b07, 0x0c},
    //HTS line exposure time in # of pixels
    {0x380c, (1896 >> 8) & 0x1F},
    {0x380d, 1896 & 0xFF},
    //VTS frame exposure time in # lines
    {0x380e, (984 >> 8) & 0xFF},
    {0x380f, 984 & 0xFF},
    {0x3814, 0x31},
    {0x3815, 0x31},
    {0x3708, 0x64},
    {0x3709, 0x52},
    //[3:0]=0 X address start high byte
    {0x3800, (500 >> 8) & 0x0F},
    //[7:0]=0 X address start low byte
    {0x3801, 500 & 0xFF},
    //[2:0]=0 Y address start high byte
    {0x3802, (0 >> 8) & 0x07},
    //[7:0]=0 Y address start low byte
    {0x3803, 0 & 0xFF},
    //[3:0] X address end high byte
    {0x3804, ((2624 - 1) >> 8) & 0x0F},
    //[7:0] X address end low byte
    {0x3805, (2624 - 1) & 0xFF},
    //[2:0] Y address end high byte
    {0x3806, ((1954 - 1) >> 8) & 0x07},
    //[7:0] Y address end low byte
    {0x3807, (1954 - 1) & 0xFF},
    //[3:0] Output horizontal width high byte
    {0x3808, (800 >> 8) & 0x0F},
    //[7:0] Output horizontal width low byte
    {0x3809, 800 & 0xFF},
    //[2:0] Output vertical height high byte
    {0x380a, (800 >> 8) & 0x7F},
    //[7:0] Output vertical height low byte
    {0x380b, 800 & 0xFF},
    //[3:0]=0 timing hoffset high byte
    {0x3810, (8 >> 8) & 0x0F},
    //[7:0]=0 timing hoffset low byte
    {0x3811, 8 & 0xFF},
    //[2:0]=0 timing voffset high byte
    {0x3812, (0 >> 8) & 0x07},
    //[7:0]=0 timing voffset low byte
    {0x3813, 0 & 0xFF},
    {0x3630, 0x2e},
    {0x3632, 0xe2},
    {0x3633, 0x23},
    {0x3634, 0x44},
    {0x3636, 0x06},
    {0x3620, 0x64},
    {0x3621, 0xe0},
    {0x3600, 0x37},
    {0x3704, 0xa0},
    {0x3703, 0x5a},
    {0x3715, 0x78},
    {0x3717, 0x01},
    {0x3731, 0x02},
    {0x370b, 0x60},
    {0x3705, 0x1a},
    {0x3f05, 0x02},
    {0x3f06, 0x10},
    {0x3f01, 0x0a},
    {0x3a08, 0x01},
    {0x3a09, 0x27},
    {0x3a0a, 0x00},
    {0x3a0b, 0xf6},
    {0x3a0d, 0x04},
    {0x3a0e, 0x03},
    {0x3a0f, 0x58},
    {0x3a10, 0x50},
    {0x3a1b, 0x58},
    {0x3a1e, 0x50},
    {0x3a11, 0x60},
    {0x3a1f, 0x28},
    {0x4001, 0x02},
    {0x4004, 0x02},
    {0x4000, 0x09},
    {0x4837, (1000000000 / OV5647_IDI_CLOCK_RATE_800x800_50FPS) * 2},
    {0x4050, 0x6e},
    {0x4051, 0x8f},
    {OV5647_REG_END, 0x00},
};

static const esp_cam_sensor_isp_info_t custom_isp_info = {
    .isp_v1_info = {
        .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
        .pclk = 81666700,
        .vts = 1896,
        .hts = 984,
        .bayer_type = ESP_CAM_SENSOR_BAYER_GBRG,
    }
};


static const esp_cam_sensor_format_t custom_format_info = {
    .name = "MIPI_2lane_24Minput_RAW8_800x800_50fps",
    .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
    .port = ESP_CAM_SENSOR_MIPI_CSI,
    .xclk = 24000000,
    .width = 800,
    .height = 800,
    .regs = ov5647_raw8_800x800_50fps,
    .regs_size = ARRAY_SIZE(ov5647_raw8_800x800_50fps),
    .fps = 50,
    .isp_info = &custom_isp_info,
    .mipi_info = {
        .mipi_clk = 400000000,
        .lane_num = 2,
        .line_sync_en = false,
    },
    .reserved = NULL,
};

#endif