/*
 * Task.h
 *
 * Created: 2023-05-15 오전 10:23:19
 *  Author: Ronny
 */


#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>

typedef enum {
    taskStarting, taskWorking, taskDone, taskCancel
} taksStatus_t;

typedef struct {
    taksStatus_t status;
    uint8_t stage;
} taskDescriptor_t;

typedef enum {
    ms_None,        /* media is not present (no Bluetooth module / no SD card)*/
    ms_Disabled,    /* media is turned off (Bluetooth is Off to save energy / SD card is Off to save energy) */
    ms_Enabled,     /* media is operational (Bluetooth ON waiting or connection / SD card ready) */
    ms_Active       /* media is in use (sending data over Bluetooth / writing to SD card) */
} mediaStatus_t;

#endif /* TASK_H_ */