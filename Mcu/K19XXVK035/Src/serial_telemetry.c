/*
 * serial_telemetry.c
 *
 *  Created on: May 13, 2020
 *      Author: Alka
 *      modified by TempersLee June 21, 2024
 */

#include "plib035_uart.h"
#include "serial_telemetry.h"
#include "common.h"
#include "kiss_telemetry.h"
#include "functions.h"

UART_Init_TypeDef UART_InitStruct;

void send_telem_DMA(uint8_t bytes)
{   
    GPIO_AltFuncCmd(GPIOB, GPIO_Pin_10, ENABLE);
    for(uint8_t i = 0; i < bytes; i++) {
        UART0->DR = aTxBuffer[i];
    }
}

void telem_UART_Init(void)
{
    RCU_AHBClkCmd(RCU_AHBClk_GPIOB, ENABLE);
    RCU_AHBRstCmd(RCU_AHBRst_GPIOB, ENABLE);
    GPIO_DigitalCmd(GPIOB, GPIO_Pin_10, ENABLE);
    GPIOB->PULLMODE_bit.PIN10 = 1;
    RCU_UARTClkConfig(UART0_Num, RCU_PeriphClk_PLLClk, 0, DISABLE);
    RCU_UARTClkCmd(UART0_Num, ENABLE);
    RCU_UARTRstCmd(UART0_Num, ENABLE);
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 115200;
    UART_InitStruct.Tx = ENABLE;
    UART_Init(UART0, &UART_InitStruct);
    UART0->LCRH_bit.FEN = 1;
    UART0->IMSC_bit.TDIM = 1;
    //UART0->IMSC_bit.TXIM = 1;
    UART_AutoBaudConfig(UART0, 115200);
    UART_Cmd(UART0, ENABLE);
    __NVIC_EnableIRQ(UART0_TD_IRQn);  
    NVIC_SetPriority(UART0_TD_IRQn, 0x6);
}