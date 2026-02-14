/*
 * ADC.c
 *
 *  Created on: May 20, 2020
 *      Author: Alka
 *      Modified by TempersLee June 21, 2024
 */
#include "ADC.h"
#include "ntc_tables.h"
#include "functions.h"
#include "math.h"
#ifdef USE_ADC
#ifdef USE_ADC_INPUT
uint16_t ADCDataDMA[4];
#else
uint16_t ADCDataDMA[3];
#endif

#define R_REF 10000.0
#define B 3380.0
#define T_REF 298.0
#define ADC_RESOLUTION 4095.0

#define V_IN 3.3
#define R_SERIES 10000.0

extern uint16_t ADC_raw_temp;
extern uint16_t ADC_raw_volts;
extern uint16_t ADC_raw_current;
extern uint16_t ADC_raw_input;
extern uint16_t ADC_raw_ntc;

void ADC_DMA_Callback()
{  // read dma buffer and set extern variables

#ifdef USE_ADC_INPUT
    ADC_raw_temp =    ADCDataDMA[3];
    ADC_raw_volts = ADCDataDMA[1] / 2;
    ADC_raw_current = ADCDataDMA[2];
    ADC_raw_input = ADCDataDMA[0];

#else
    ADC_raw_temp =    ADCDataDMA[2];
#ifdef PA6_VOLTAGE
    ADC_raw_volts = ADCDataDMA[1]; 
    ADC_raw_ntc = ADCDataDMA[0];
#else
    ADC_raw_volts = ADCDataDMA[0];
    ADC_raw_current = ADCDataDMA[1];
    ADC_raw_ntc = ADCDataDMA[2];
#endif
#endif
}

int16_t getConvertedDegrees(uint16_t adcrawtemp) {
    float v_out = (ADC_raw_ntc / ADC_RESOLUTION) * V_IN;
    float r_ntc = (R_SERIES * v_out) / (V_IN - v_out);
    float t_kelvin = 1.0 / ((1.0 / T_REF) + (1.0 / B) * log(r_ntc / R_REF));
    float t_celsius = t_kelvin - 273.15;
    return (int16_t)t_celsius;
}

#ifdef USE_NTC
int16_t getNTCDegrees(uint16_t ntcrawtemp){
  int p1,p2;
  p1 = NTC_table[ (ntcrawtemp >> 6)  ];
  p2 = NTC_table[ (ntcrawtemp >> 6)+1];
  return p1 - ( (p1-p2) * (ntcrawtemp & 0x003F) ) / 64;
}
#endif

//trigger ADC
void startADCConversion()
{
    ADC_SEQ_ITConfig(ADC_SEQ_Num_0, 1, DISABLE);
    ADC_SEQ_ITCmd(ADC_SEQ_Num_0, ENABLE);
    NVIC_EnableIRQ(ADC_SEQ0_IRQn);
    NVIC_SetPriority(ADC_SEQ0_IRQn, 6);
}

void ADCInit(void)
{
    RCU->ADCCFG_bit.CLKSEL = RCU_ADCCFG_CLKSEL_PLLCLK;
    RCU->ADCCFG_bit.DIVN = 0x1; // div4
    RCU->ADCCFG_bit.DIVEN = 0x1;
    RCU->ADCCFG_bit.CLKEN = 0x1;
    RCU->ADCCFG_bit.RSTDIS = 0x1;

    ADC->ACTL_bit.ADCEN = 0x1;
    ADC->EMUX_bit.EM0 = ADC_EMUX_EM0_PWM012A | ADC_EMUX_EM0_SwReq;
    //ADC->SEQSYNC = ADC_SEQSYNC_SYNC0_Msk;
    ADC->SEQ[0].SCCTL_bit.ICNT = 2;
    ADC->SEQ[0].SRQCTL_bit.RQMAX = 0x2;
    ADC->SEQ[0].SRQCTL_bit.QAVGVAL = ADC_SEQ_SRQCTL_QAVGVAL_Average64;
    ADC->SEQ[0].SRQCTL_bit.QAVGEN = 0;
    ADC->SEQ[0].SRQSEL_bit.RQ0 = 0x0;
    ADC->SEQ[0].SRQSEL_bit.RQ1 = 0x1;
    ADC->SEQ[0].SRQSEL_bit.RQ2 = 0x2;
    ADC_SEQ_SetRestartTimer(ADC_SEQ_Num_0, 50);
    //ADC->SEQ[0].SRQSEL_bit.RQ3 = 0x3;
    ADC->SEQEN_bit.SEQEN0 = 1;
    while (!ADC->ACTL_bit.ADCRDY) {
    };
    ADC->IM_bit.SEQIM0 = 1;
    NVIC_EnableIRQ(ADC_SEQ0_IRQn);
    NVIC_SetPriority(ADC_SEQ0_IRQn, 6);
}

#endif // USE_ADC
