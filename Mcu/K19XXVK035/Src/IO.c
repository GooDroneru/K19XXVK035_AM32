/*
 * IO.c
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#include "IO.h"

#include "common.h"
#include "dshot.h"
#include "functions.h"
#include "serial_telemetry.h"
#include "targets.h"

uint8_t buffer_padding = 7;
char ic_timer_prescaler = CPU_FREQUENCY_MHZ / 5;
uint32_t dma_buffer[64] = { 0 };
char out_put = 0;
extern uint16_t counter;
extern uint16_t halfpulsetime;
extern char fallingEdgeTrigger;

void changeToInput()
{
    NVIC_DisableIRQ(IC_TIMER_INT_VECTOR);
    IC_TIMER_REGISTER->ECCTL0 = 0;
    IC_TIMER_REGISTER->ECCTL1 = 0;
    IC_TIMER_REGISTER->ECEINT = 0;
    IC_TIMER_REGISTER->TSCTR = 0;
    IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 1;
    
    if(fallingEdgeTrigger) {
        IC_TIMER_REGISTER->ECCTL0_bit.CAP0POL = 1;
        IC_TIMER_REGISTER->ECCTL0_bit.CAP2POL = 1;
    }
    else {
        IC_TIMER_REGISTER->ECCTL0_bit.CAP1POL = 1;
        IC_TIMER_REGISTER->ECCTL0_bit.CAP3POL = 1;
    }
    
    IC_TIMER_REGISTER->ECCTL1_bit.CONTOST = 0;
    IC_TIMER_REGISTER->ECCTL1_bit.STOPWRAP = 3;
    IC_TIMER_REGISTER->ECCTL1_bit.REARM = 1;
    IC_TIMER_REGISTER->ECEINT_bit.CEVT1 = 1;
    IC_TIMER_REGISTER->ECEINT_bit.CEVT3 = 1;
    IC_TIMER_REGISTER->ECCTL0_bit.CAPLDEN = 1;
    NVIC_EnableIRQ(IC_TIMER_INT_VECTOR);
    NVIC_SetPriority(IC_TIMER_INT_VECTOR, 0x00);

    if(servoPwm)
    {
    }
    else
    {
        buffersize = 32;
    }
}



void receiveDshotDma()
{
    changeToInput();
    out_put = 0;
}

void changeToOutput()
{
    NVIC_DisableIRQ(IC_TIMER_INT_VECTOR);
    IC_TIMER_REGISTER->ECCTL0 = 0;
    IC_TIMER_REGISTER->ECCTL1 = 0;
    IC_TIMER_REGISTER->ECEINT = 0;
    IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 0;
    IC_TIMER_REGISTER->ECCTL1 |= ECAP_ECCTL1_CAPAPWM_Msk | ECAP_ECCTL1_APWMPOL_Msk;
    IC_TIMER_REGISTER->PRD = 250;
    IC_TIMER_REGISTER->CMP = gcr[0];

    counter++;

    IC_TIMER_REGISTER->ECCTL1_bit.CONTOST = 1;
    IC_TIMER_REGISTER->ECEINT_bit.CTRPRD = 1;
    NVIC_EnableIRQ(IC_TIMER_INT_VECTOR);
    NVIC_SetPriority(IC_TIMER_INT_VECTOR, 0x00);
    IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 1;
    
    out_put = 1;
}

void sendDshotDma()
{
    changeToOutput();
}

uint8_t getInputPinState()
{
    return SET == GPIO_ReadBit(INPUT_PIN_PORT, INPUT_PIN);
}

void setInputPolarityRising()
{
}

void setInputPullDown()
{
}

void setInputPullUp()
{
}

void enableHalfTransferInt()
{
}
