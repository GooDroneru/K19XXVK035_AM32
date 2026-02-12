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
extern uint16_t periodTime;
extern uint16_t bitShift;

__RAMFUNC void changeToInput()
{
    GPIOA->ALTFUNCCLR_bit.PIN5 = 1;
    updateDma();
    TMR3->DMAREQ_bit.EN = 0;
    SIU->REMAPAF_bit.ECAP1EN = 0;
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
{   
    if(servoPwm == 1) {
        //GPIOA->INTEDGECLR_bit.PIN5 = 1;
        //GPIOA->INTPOLSET_bit.PIN5 = 1;
    }
    //setDmaCnt(buffersize);
    out_put = 0;
    changeToInput();

}

__RAMFUNC void changeToOutput()
{
    updateDmaTransmit();
    TMR3->CTRL_bit.ON = 0;
    TMR3->VALUE = periodTime / 2;
    TMR3->LOAD = periodTime;
    TMR3->DMAREQ_bit.EN = 1;
    IC_TIMER_REGISTER->TSCTR = 0;
    // counter++;
    IC_TIMER_REGISTER->CMP = 0;
    IC_TIMER_REGISTER->ECCTL1_bit.CONTOST = 1;
    IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 1;
    SIU->REMAPAF_bit.ECAP1EN = 1;
    GPIOA->ALTFUNCSET_bit.PIN5 = 1;
    GPIOA->DMAREQCLR_bit.PIN5 = 1;
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
