/*
 * serial_telemetry.c
 *
 *  Created on: May 13, 2020
 *      Author: Alka
 */

#include "plib035_uart.h"
#include "targets.h"

uint8_t aTxBuffer[10];
uint8_t nbDataToTransmit = sizeof(aTxBuffer);

void telem_UART_Init(void)
{
    UART_Init_TypeDef UART_InitStruct;
    RCU_AHBClkCmd(RCU_AHBClk_GPIOB, ENABLE);
    RCU_AHBRstCmd(RCU_AHBRst_GPIOB, ENABLE);
    GPIO_AltFuncCmd(GPIOB, GPIO_Pin_10, ENABLE);
    GPIO_DigitalCmd(GPIOB, GPIO_Pin_10, ENABLE);
    RCU_UARTClkConfig(UART0_Num, RCU_PeriphClk_PLLClk, 0, DISABLE);
    RCU_UARTClkCmd(UART0_Num, ENABLE);
    RCU_UARTRstCmd(UART0_Num, ENABLE);
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 115200;
    UART_InitStruct.Tx = ENABLE;
    UART_Init(UART0, &UART_InitStruct);
    UART0->LCRH_bit.FEN = 1;
    UART_Cmd(UART0, ENABLE);
}

void send_telem_DMA()
{
    for(uint8_t i = 0; i < nbDataToTransmit; i++) {
        UART0->DR = aTxBuffer[i];
    }
}

uint8_t update_crc8(uint8_t crc, uint8_t crc_seed)
{
    uint8_t crc_u, i;
    crc_u = crc;
    crc_u ^= crc_seed;
    for ( i=0; i<8; i++) {
        crc_u = ( crc_u & 0x80 ) ? 0x7 ^ ( crc_u << 1 ) : ( crc_u << 1 );
    }
    return (crc_u);
}

uint8_t get_crc8(uint8_t *Buf, uint8_t BufLen)
{
    uint8_t crc = 0, i;
    for( i=0; i<BufLen; i++) {
        crc = update_crc8(Buf[i], crc);
    } 
    return (crc);
}


void makeTelemPackage(uint8_t temp, uint16_t voltage, uint16_t current, uint16_t consumption, uint16_t e_rpm)
{
    aTxBuffer[0] = temp; // temperature

    aTxBuffer[1] = (voltage >> 8) & 0xFF; // voltage hB
    aTxBuffer[2] = voltage & 0xFF; // voltage   lowB

    aTxBuffer[3] = (current >> 8) & 0xFF; // current
    aTxBuffer[4] = current & 0xFF; // divide by 10 for Amps

    aTxBuffer[5] = (consumption >> 8) & 0xFF; // consumption
    aTxBuffer[6] = consumption & 0xFF; //  in mah

    aTxBuffer[7] = (e_rpm >> 8) & 0xFF; //
    aTxBuffer[8] = e_rpm & 0xFF; // eRpM *100

    aTxBuffer[9] = get_crc8(aTxBuffer,9);
}




