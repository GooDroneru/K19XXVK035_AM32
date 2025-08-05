/*
 * ADC.h
 *
 *  Created on: May 20, 2020
 *      Author: Alka
 */

#include "main.h"
#include "targets.h"
#include "plib035_adc.h"

#ifndef ADC_H_
#define ADC_H_

void ADC_DMA_Callback(void);
void enableADC_DMA(void);
void activateADC(void);
void ADCInit(void);
uint16_t getConvertedDegrees(void);

#endif /* ADC_H_ */

