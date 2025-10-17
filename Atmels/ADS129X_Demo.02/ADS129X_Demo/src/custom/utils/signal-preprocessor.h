/*
 * signal_preprocessor.h
 *
 * Created: 2023-05-24 오후 1:26:01
 *  Author: Ronny
 */


#ifndef SIGNAL_PREPROCESSOR_H_
#define SIGNAL_PREPROCESSOR_H_

#include "trismed/drivers/ADS129x.h"

void SignalPreprocesorInit(int channels);

bool SignalPreprocessorProcessSample(ADS1298_Frame *data);

ADS1298_Frame SignalProcessorGetSample(void);

bool SignalPreprocessorHasData(void);


#endif /* SIGNAL_PREPROCESSOR_H_ */