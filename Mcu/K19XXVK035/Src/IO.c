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
#include "peripherals.h"

uint8_t buffer_padding = 7;
char ic_timer_prescaler = CPU_FREQUENCY_MHZ / 5;
uint32_t dma_buffer[64] __attribute__((section(".ram_section"))) __attribute__((aligned(4))) = { 0 };

char out_put = 0;
extern uint16_t counter;
extern uint16_t halfpulsetime;
extern char fallingEdgeTrigger;

__RAMFUNC void changeToInput()
{
    // NVIC_DisableIRQ(IC_TIMER_INT_VECTOR);
    // IC_TIMER_REGISTER->ECCTL0 = 0;
    // IC_TIMER_REGISTER->ECCTL1 = 0;
    // IC_TIMER_REGISTER->ECEINT = 0;
    // IC_TIMER_REGISTER->TSCTR = 0;
    // IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 1;
    // IC_TIMER_REGISTER->PEINT_bit.PEINT = 1; 
    // IC_TIMER_REGISTER->ECCLR_bit.INT = 1;
    
    // if(fallingEdgeTrigger) {
    //     IC_TIMER_REGISTER->ECCTL0_bit.CAP0POL = 1;
    //     IC_TIMER_REGISTER->ECCTL0_bit.CAP2POL = 1;
    // }
    // else {
    //     IC_TIMER_REGISTER->ECCTL0_bit.CAP1POL = 1;
    //     IC_TIMER_REGISTER->ECCTL0_bit.CAP3POL = 1;
    // }
    
    // IC_TIMER_REGISTER->ECCTL1_bit.CONTOST = 0;
    // IC_TIMER_REGISTER->ECCTL1_bit.STOPWRAP = 3;
    // IC_TIMER_REGISTER->ECCTL1_bit.REARM = 1;
    // //IC_TIMER_REGISTER->ECEINT_bit.CEVT1 = 1;
    // IC_TIMER_REGISTER->ECEINT_bit.CEVT3 = 1;
    // IC_TIMER_REGISTER->ECCTL0_bit.CAPLDEN = 1;
    // NVIC_EnableIRQ(IC_TIMER_INT_VECTOR);
    // NVIC_SetPriority(IC_TIMER_INT_VECTOR, 0x00);

    // if(servoPwm)
    // {
    // }
    // else
    // {
    //     buffersize = 32;
    // }
    GPIOA->ALTFUNCCLR_bit.PIN5 = 1;
    updateDma();
    TMR3->DMAREQ_bit.EN = 0;
    //DMA->ENSET_bit.CH12 = 0; //Включаем канала DMA 1 
    //DMA->CFG_bit.MASTEREN = 0; //Бит разрешения работы контролера DMA
    SIU->REMAPAF_bit.ECAP1EN = 0;
    // GPIOA->DENSET_bit.PIN5 = 1;
    gcr[0];
    TMR3->CTRL_bit.ON = 0;
    TMR3->VALUE = 0xFFFFFFFF;
    TMR3->LOAD = 0xFFFFFFFF;
    IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 0;
    IC_TIMER_REGISTER->TSCTR = 0;
    GPIOA->DMAREQSET_bit.PIN5 = 1;

    DMA->CFG_bit.MASTEREN = 1; //Бит разрешения работы контролера DMA
    TMR3->CTRL_bit.ON = 1;

}



__RAMFUNC void receiveDshotDma()
{    out_put = 0;
    changeToInput();

}

__RAMFUNC void changeToOutput()
{
    // NVIC_DisableIRQ(IC_TIMER_INT_VECTOR);
    // IC_TIMER_REGISTER->ECCTL0 = 0;
    // //IC_TIMER_REGISTER->ECCTL1 = 0;
    // IC_TIMER_REGISTER->ECEINT = 0;
    // IC_TIMER_REGISTER->ECCTL1 = ECAP_ECCTL1_CAPAPWM_Msk | ECAP_ECCTL1_APWMPOL_Msk;

    // IC_TIMER_REGISTER->PEINT_bit.PEINT = 1; 
    //IC_TIMER_REGISTER->ECCLR = 1;
    //DMA->ENSET_bit.CH8 = 0; //Включаем канала DMA 1 
    updateDmaTransmit();
    TMR3->CTRL_bit.ON = 0;
    TMR3->VALUE = 125;
    TMR3->LOAD = 255;
    TMR3->DMAREQ_bit.EN = 1;
    IC_TIMER_REGISTER->TSCTR = 0;
    // counter++;
    IC_TIMER_REGISTER->CMP = 0;
    IC_TIMER_REGISTER->ECCTL1_bit.CONTOST = 1;
    IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 1;
    SIU->REMAPAF_bit.ECAP1EN = 1;
    GPIOA->ALTFUNCSET_bit.PIN5 = 1;
    GPIOA->DMAREQCLR_bit.PIN5 = 1;
    //DMA->CFG_bit.MASTEREN = 0; //Бит разрешения работы контролера DMA

    DMA->CFG_bit.MASTEREN = 1; //Бит разрешения работы контролера DMA
    TMR3->CTRL_bit.ON = 1;
}

__RAMFUNC void sendDshotDma()
{
        out_put = 1;
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
