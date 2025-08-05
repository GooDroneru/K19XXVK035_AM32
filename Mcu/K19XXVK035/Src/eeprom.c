#include "eeprom.h"
#include "string.h"

#define page_size 0x400                 

void save_flash_nolib(uint8_t *data, uint16_t length, uint32_t add)
{   
    volatile uint32_t start_addr
    uint32_t data_to_FLASH[2];

    if(length < 8) {
        length = 8;
    }
    if(length > 1024) {
        length = 1024;
    }

    start_addr = add;
    if(add % 0x400 == 0) {
        MFLASH_ErasePage(start_addr, MFLASH_Region_Main);
    }

    MFLASH_ErasePage(start_addr, MFLASH_Region_Main);

    for(uint32_t i = 0; i < length; i += 4) {
        data_to_FLASH[0] = *((uint32_t*) &data[i * 2]);
        data_to_FLASH[1] = *((uint32_t*) &data[4 + (i * 2)]);
        MFLASH_WriteData(start_addr + (i * 2), data_to_FLASH, MFLASH_Region_Main);
    }
}

void read_flash_bin(uint8_t* data , uint32_t add , int out_buff_len)
{
    uint32_t rawData[2] = {0};
    uint32_t j = 0;

    for(uint32_t i = 0; i < out_buff_len; i += 8) {
        MFLASH_ReadData(add + (j * 8), rawData, MFLASH_Region_Main);
        data[i] = (uint8_t)rawData[0];
        data[i + 1] = (uint8_t)(rawData[0]>>8);
        data[i + 2] = (uint8_t)(rawData[0]>>16);
        data[i + 3] = (uint8_t)(rawData[0]>>24);

        data[i + 4] = (uint8_t)rawData[1];
        data[i + 5] = (uint8_t)(rawData[1]>>8);
        data[i + 6] = (uint8_t)(rawData[1]>>16);
        data[i + 7] = (uint8_t)(rawData[1]>>24);
        
        j++;
    }
}
