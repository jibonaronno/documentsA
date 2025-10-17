/*
 * HolterCfgFileFormat.h
 *
 * Created: 2023-05-15 오후 2:27:12
 *  Author: Ronny
 */


#ifndef HOLTERCFGFILEFORMAT_H_
#define HOLTERCFGFILEFORMAT_H_

#include <stdbool.h>
#include <stdint.h>
#include <asf.h>

#pragma pack(push, 1)
typedef struct {
    char signatureArray[3];
    uint8_t pacemakerType;      // None = 0, Atrial = 1, Ventricular = 2, Double = 3
    uint8_t channels;
    uint8_t leadPlacement;      // 0 -->> Standard; 1 -->> Frank
    uint8_t specifiedDuration;  // hours 0 -->> Ignore
    char patientId[13];
    uint8_t recordMode;
    uint8_t already_used;
} THTConfigFile;
#pragma pack(pop)

typedef struct  {
    THTConfigFile Data;
    char isValid;
} THT_ConfigFile_RAM;

extern THT_ConfigFile_RAM HT_ConfigFile;

void ReadConfigFile(void);
void WriteConfigFile(bool _useCurrentValues);

#endif /* HOLTERCFGFILEFORMAT_H_ */