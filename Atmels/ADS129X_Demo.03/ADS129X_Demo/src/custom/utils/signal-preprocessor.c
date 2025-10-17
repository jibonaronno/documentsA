/*
 * signal_preprocessor.c
 *
 * Created: 2023-05-24 오후 1:25:51
 *  Author: Ronny
 */
#include "signal-preprocessor.h"
#include "FIFO.h"
#include "filter.h"

#define ADS_FIFO_MAX_ELEMS   50u
static struct fifo_descriptor adsFifo;
static /*volatile */ADS1298_Frame adsFifoBuffer[ADS_FIFO_MAX_ELEMS];
static int activeChannels;

void SignalPreprocesorInit(int channels) {
    memset(adsFifoBuffer, 0, sizeof(adsFifoBuffer));
    fifo_create_static(&adsFifo, (void*) adsFifoBuffer, ADS_FIFO_MAX_ELEMS, sizeof(ADS1298_Frame));
    activeChannels = channels;
}

#define STEP_CLEAN_SAMPLES 6u

#define MINIMUM_STEP_AMP_TO_REMOVE_ADC        (MV_TO_ADC((double)290))       /* +/- 290mV steps will be removed */

static inline void FindStepInAllLeads(ADS1298_Frame *data) {
    if(activeChannels == 3) {
        uint32_t tmpVal = data->Leads[0];
        data->Leads[0] = data->Leads[1];
        data->Leads[1] = data->Leads[2];
        data->Leads[2] = tmpVal;
    }

    if(fifo_is_full(&adsFifo)) {
        ADS1298_Frame* stableSample = fifo_peek_ptr(&adsFifo, fifo_item_count(&adsFifo)-STEP_CLEAN_SAMPLES);
        bool step_IorII = false;
        for(int lead=0; lead<AMP_IN_LEADS; lead++) {
            if(abs(stableSample->Leads[lead]-data->Leads[lead]) > MINIMUM_STEP_AMP_TO_REMOVE_ADC) {
                /* All the cleanup will be done later in FilterIIR_HP005 base on ADS_GPIO3
                after the amplitude of the step is verified. Search for "ADS_GPIO3" to
                understand better */
                stableSample->Status |= OFFSET_DETECTED;   /* probably big step */
                if(lead <= 1) {
                    step_IorII = true;
                }
                Filter005_SetLeadReset(lead);  /* reset the filter for this lead */
            } else {
                if(step_IorII) {
                    Filter005_SetLeadReset(lead);  /* reset the filter for this lead */
                }
            }
        }
        if(step_IorII) {
            Filter005_SetLeadReset(0);
        }
    }
    fifo_add(&adsFifo, data);// TODO: we may need to use something like "tmpAdsFifo" in ATSAM4S-ACQ
}

bool SignalPreprocessorProcessSample(ADS1298_Frame *data) {
    FindStepInAllLeads(data);
    return fifo_is_full(&adsFifo);
}

bool SignalPreprocessorHasData(void) {
    return fifo_item_count(&adsFifo) > ADS_FIFO_MAX_ELEMS-(ADS_FIFO_MAX_ELEMS/2u)/*5u*/;
}

ADS1298_Frame SignalProcessorGetSample(void) {
    ADS1298_Frame data;
    fifo_get(&adsFifo, &data);
    return data;
}
