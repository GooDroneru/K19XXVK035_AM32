/*
 * functions.c
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#include "functions.h"
#include "targets.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    if (x >= in_max)
        return out_max;
		if (x <= in_min)
        return out_min;
    if (in_min > in_max)
        return map(x, in_max, in_min, out_max, out_min);
    if (out_min == out_max)
        return out_min;
    const long in_mid = (in_min + in_max) >> 1;
    const long out_mid = (out_min + out_max) >> 1;
    if (in_min == in_mid)
        return out_mid;
    if (x <= in_mid)
        return map(x, in_min, in_mid, out_min, out_mid);
    else
        return map(x, in_mid + 1, in_max, out_mid, out_max);
}

uint32_t getAbsDif(int number1, int number2)
{
	int result = number1 - number2;
	if (result < 0) {
	    result = -result;
	}
    return (uint32_t)result;
}

void delayMicros(uint32_t micros)
{
    DELAY_TIMER->VALUE = micros * 100;
    DELAY_TIMER->CTRL_bit.ON = 1;
    while(DELAY_TIMER->VALUE != 0) {
        asm("nop");
    }
    DELAY_TIMER->CTRL_bit.ON = 0;
}

void delayMillis(uint32_t millis)
{
    do
    {
        delayMicros(1000);
    }while( --millis );

}
