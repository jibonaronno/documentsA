#include "filter.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define AMP_IN_LEADS    8

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II
 * Numerator Length    : 3
 * Denominator Length  : 3
 * Stable              : Yes
 * Linear Phase        : No
 * Notch 60Hz at Sample Frequency 500Hz
 */
#define MWSPT_NSEC60 1

long double x60[AMP_IN_LEADS][MWSPT_NSEC60][3];
long double y60[AMP_IN_LEADS][MWSPT_NSEC60][3];

const int NL_AC60[MWSPT_NSEC60] = {3};
const float NUM_AC60[MWSPT_NSEC60][3] = {
    { 0.9936459339824,               0,              -0.9936459339824 }
};
const int DL_AC60[MWSPT_NSEC60] = {3};
const float DEN_AC60[MWSPT_NSEC60][3] = {
    { 1,                             0,              -0.9872918679647 }
};

void AC60_Filter(int32_t *_data) {
#if 0
    _data[0]-=199818;
    _data[1]-=199818;
    _data[2]-=199818;
#else
    int Lead = 0;
    float w;
    while (Lead < AMP_IN_LEADS) {
        for(int i=0; i<MWSPT_NSEC60; i++) {
            x60[Lead][i][2] = x60[Lead][i][1];
            x60[Lead][i][1] = x60[Lead][i][0];
            x60[Lead][i][0] = _data[Lead];
            w=0;
            y60[Lead][i][2] = y60[Lead][i][1];
            y60[Lead][i][1] = y60[Lead][i][0];
            for ( int j=0; j<NL_AC60[i]; j++) w+= NUM_AC60[i][j]*x60[Lead][i][j];
            for ( int j=1; j<DL_AC60[i]; j++) w-= DEN_AC60[i][j]*y60[Lead][i][j];
            w/= DEN_AC60[i][0];
            _data[Lead] = (int32_t)w;
            y60[Lead][i][0] = _data[Lead];
        }
        Lead++;
    }
#endif
}

#define SAMPLES_TO_STABLE 500u

static uint32_t wasOff[8] = {SAMPLES_TO_STABLE, SAMPLES_TO_STABLE, SAMPLES_TO_STABLE, SAMPLES_TO_STABLE, SAMPLES_TO_STABLE, SAMPLES_TO_STABLE, SAMPLES_TO_STABLE, SAMPLES_TO_STABLE};

/** First order high-pass filter 0.045 Hz
*   Yn = Xn - Xn-1 + 0.99939 Yn-1
*/
static void Filter005_InitLead(int lead, double value);
static double x[AMP_IN_LEADS];
static double y[AMP_IN_LEADS];

void Filter005_Init(void) {
    for(int i=0; i<AMP_IN_LEADS; i++) {
        x[i] = 0.0;
        y[i] = 0.0;
        wasOff[i] = SAMPLES_TO_STABLE;
    }
}

static void Filter005_InitLead(int lead, double value) {
    x[lead] = value;
    y[lead] = 0.0;
}

volatile uint8_t resetLead[AMP_IN_LEADS] = {0u};

void Filter005_SetLeadReset(int lead) {
    resetLead[lead] = 1u;
}

/*#define JUST_DIVIDE_THE_SIGNAL_TO_SEE_DC_BEHAVIOR*/
#define ZERO_SAMPLES_AFTER_STEP         12u

void Filter005_Filter(ADS1298_Frame *sample, bool isCalibration) {
    const uint32_t ch_flags[] = {
        ADS_LA|ADS_RA,
        ADS_LL|ADS_RA,
        ADS_V1|ADS_LL|ADS_RA|ADS_LA,
        ADS_V2|ADS_LL|ADS_RA|ADS_LA,
        ADS_V3|ADS_LL|ADS_RA|ADS_LA,
        ADS_V4|ADS_LL|ADS_RA|ADS_LA,
        ADS_V5|ADS_LL|ADS_RA|ADS_LA,
        ADS_V6|ADS_LL|ADS_RA|ADS_LA,
    };
#ifdef JUST_DIVIDE_THE_SIGNAL_TO_SEE_DC_BEHAVIOR
    for (int lead = 0; lead < AMP_IN_LEADS; lead++) {
        sample->Leads[lead] /= 20;
    }
#else
    static const double coeff = 0.99939;
    if(sample->Status & OFFSET_DETECTED) {
        for (int lead = 0; lead < AMP_IN_LEADS; lead++) {
            if(resetLead[lead]!=0u && wasOff[lead] < ZERO_SAMPLES_AFTER_STEP) {
                wasOff[lead] = ZERO_SAMPLES_AFTER_STEP;
                resetLead[lead] = 0u;
            }
        }
    }
    for (int lead = 0; lead < AMP_IN_LEADS; lead++) {
        if(((sample->Status&ch_flags[lead])==0u) || isCalibration) {
            if(wasOff[lead]) {
                if(--wasOff[lead]==0u) {
                    Filter005_InitLead(lead, (double) sample->Leads[lead]);
                }
                sample->Leads[lead] = 0;
            } else {
                double tmpX = (double) sample->Leads[lead];
                double w = tmpX - x[lead] + coeff * y[lead];
                x[lead] = tmpX;
                y[lead] = w;
                sample->Leads[lead] = (int32_t)w;
            }
        } else {
            wasOff[lead] = SAMPLES_TO_STABLE;
            sample->Leads[lead] = 0;
        }
    }
#endif
}
