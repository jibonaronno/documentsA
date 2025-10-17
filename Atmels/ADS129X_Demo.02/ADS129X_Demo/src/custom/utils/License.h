#ifndef LICENSE_H
#define LICENSE_H

#include <stdint.h>
#include <stdbool.h>
#include "trismed/gui/resources/HT_strings.h"

typedef enum {
    licRealtime,                /* 0 */ // str_Stress
    licHolter,                  /* 1 */ // str_Holter
    licFecturesCount            /* must always be the last in the enum */
} t_Option_Id;

typedef enum {
    licF_None,
    licF_Holter,
    licF_Realtime,
    licF_Holter_Realtime
} licFeaturesSet;

typedef struct {
    bool active;
    const HT_String *name;
} licFeatureStatus_t;

enum licenseUpdateResult_t {
    licUpdateNotFound,
    licInvalid,
    licImported
};

extern enum licenseUpdateResult_t LicenseCheckForUpdate(void);
extern bool LicenseCheckOption(t_Option_Id option);
extern void LoadLicenseFromFlash(void);
extern licFeaturesSet LicenseGetFeaturesSet(void);
extern licFeatureStatus_t* LicenseGetAllStatus(void);

#endif /* LICENSE_H */

