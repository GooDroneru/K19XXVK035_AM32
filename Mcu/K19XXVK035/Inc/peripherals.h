/*
 * peripherals.h
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "main.h"
#include "ADC.h"

void initAfterJump(void);
void initCorePeripherals(void);
void SystemClock_Config(void);
void ALL_GPIO_Init(void);
void ALL_DMA_Init(void);
//static void MX_ADC_Init(void);
void ALL_COMP_Init(void);
void PWM_TIM1_Init(void);
void ZC_TIM4_Init(void);
void MX_IWDG_Init(void);
void MX_TIM16_Init(void);
void COM_TIM3_Init(void);
void TENKHz_SysTick_Init(void);
void MX_TIM17_Init(void);
void UN_TIM2_Init(void);
void LED_GPIO_init(void);
void disableComTimerInt(void);
void enableComTimerInt(void);
void setAndEnableComInt(uint16_t time);
uint16_t getintervaTimerCount();
void setintervaTimerCount(uint16_t intertime);
void setAutoReloadPWM(uint16_t relval);
void setDutyCycleAll(uint16_t newdc);
void resetInputCaptureTimer();
void setPWMCompare1(uint16_t compareone);
void setPWMCompare2(uint16_t comparetwo);
void setPWMCompare3(uint16_t comparethree);
void enableCorePeripherals(void);
void reloadWatchDogCounter(void);
void generatePwmTimerEvent(void);
void setPrescalerPWM(uint16_t presc);

#define INTERVAL_TIMER_COUNT (getintervaTimerCount())
#define RELOAD_WATCHDOG_COUNTER() (WDT_ITStatusClear())
#define DISABLE_COM_TIMER_INT() (COM_TIMER->CTRL_bit.INTEN = 0)
#define ENABLE_COM_TIMER_INT() (COM_TIMER->CTRL_bit.INTEN = 1)
#define SET_AND_ENABLE_COM_INT(time) (setAndEnableComInt(time))
#define SET_INTERVAL_TIMER_COUNT(intertime) (setintervaTimerCount(intertime))
#define SET_PRESCALER_PWM(presc) (setPrescalerPWM(presc))
#define SET_AUTO_RELOAD_PWM(relval)             \
            (PWM0->TBPRD = relval,              \
            PWM1->TBPRD = relval,               \
            PWM2->TBPRD = relval)
#define SET_DUTY_CYCLE_ALL(newdc)               \
            (PWM0->CMPA_bit.CMPA = newdc,       \
            PWM0->CMPB_bit.CMPB = newdc,        \
            PWM1->CMPA_bit.CMPA = newdc,        \
            PWM1->CMPB_bit.CMPB = newdc,        \
            PWM2->CMPA_bit.CMPA = newdc,        \
            PWM2->CMPB_bit.CMPB =  newdc)

#endif /* PERIPHERALS_H_ */







