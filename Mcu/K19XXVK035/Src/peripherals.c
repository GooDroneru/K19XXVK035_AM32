/*
 * peripherals.c
 *
 * */
#include "peripherals.h"
#include "targets.h"
#include "serial_telemetry.h"

extern uint16_t counter;
extern uint16_t deadTime;

void initCorePeripherals(void)
{
  ALL_GPIO_Init( );   //gpio clock
  ALL_DMA_Init( );    //IC DMA and ADC DMA
  PWM_TIM1_Init( );   //6 channels PWM
  ZC_TIM4_Init( );    //zero cross timer
  ALL_COMP_Init( );   //ALL comparer
  COM_TIM3_Init( );   //
  TENKHz_SysTick_Init( );
  MX_TIM16_Init( );
  UN_TIM2_Init( );
  #ifdef USE_SERIAL_TELEMETRY
  telem_UART_Init();
  #endif
}

void initAfterJump(void)
{
    //don't need
}

void SystemClock_Config(void)
{
    SystemCoreClockUpdate();
}

void setAutoReloadPWM(uint16_t relval)
{
  PWM0->TBPRD = relval;
  PWM1->TBPRD = relval;
  PWM2->TBPRD = relval;
}

void setPrescalerPWM(uint16_t presc){
  if(presc == 0) {  
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;        //48 KHz
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div1; //48 KHz
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;        //48 KHz
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div1; //48 KHz
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;        //48 KHz
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div1; //48 KHz
  }
  if(presc == 10) {  
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
  }
  else if(presc == 20) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
  }
  else if(presc == 25) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12;
  }
  else if(presc == 30) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14;
  }
  else if(presc == 40) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
  }
  else if(presc == 50) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12;
  }
  else if(presc == 55) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div4;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14;
  }
  else if(presc == 60) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div8; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div8;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div8;
  }
  else if(presc == 60) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div8; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div8;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div8;
  }
  else if(presc == 70) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div10;
  }
  else if(presc == 80) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div12;
  }
  else if(presc == 90) {
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;    
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div8;   
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14; 
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14;
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div14;
  }
}

void setDutyCycleAll(uint16_t newdc){
  PWM0->CMPA_bit.CMPA = newdc;
  PWM0->CMPB_bit.CMPB = TIM1_AUTORELOAD - newdc;
  PWM1->CMPA_bit.CMPA = newdc;
  PWM1->CMPB_bit.CMPB = TIM1_AUTORELOAD - newdc;
  PWM2->CMPA_bit.CMPA = newdc;
  PWM2->CMPB_bit.CMPB = TIM1_AUTORELOAD - newdc;
}

void resetInputCaptureTimer()
{
  ECAP2->ECCTL0_bit.CAPLDEN = 0;
  ECAP2->TSCTR = 0;
  ECAP2->ECCTL1_bit.REARM = 1;
  counter = 0;
  ECAP2->ECCTL0_bit.CAPLDEN = 1;
}

void setPWMCompare1(uint16_t compareone)
{
  PWM0->CMPA_bit.CMPA = compareone;
  PWM0->CMPB_bit.CMPB = compareone;
}
void setPWMCompare2(uint16_t comparetwo)
{
  PWM1->CMPA_bit.CMPA = comparetwo;
  PWM1->CMPB_bit.CMPB = comparetwo;
}
void setPWMCompare3(uint16_t comparethree)
{
  PWM2->CMPA_bit.CMPA = comparethree;
  PWM2->CMPB_bit.CMPB = comparethree;
}

void enableCorePeripherals(){
    COM_TIMER->CTRL_bit.INTEN = 0;
    COM_TIMER->CTRL_bit.ON = 1;
    COM_TIMER->CTRL_bit.ON = 1;

#ifdef USE_ADC
    ADCInit();
    enableADC_DMA();
    activateADC();
#endif
}

void generatePwmTimerEvent(){
}

void ALL_COMP_Init(void)
{
    RCU->HCLKCFG_bit.GPIOBEN = 1;
    RCU->HRSTCFG_bit.GPIOBEN = 1;
    GPIOB->DENSET_bit.PIN4 = 1;
    GPIOB->DENSET_bit.PIN5 = 1;
    GPIOB->DENSET_bit.PIN6 = 1;
    GPIOB->PULLMODE_bit.PIN4 = 0x01;
    GPIOB->PULLMODE_bit.PIN5 = 0x01;
    GPIOB->PULLMODE_bit.PIN6 = 0x01;
    GPIOB->INTTYPESET_bit.PIN4 = 1;
    GPIOB->INTTYPESET_bit.PIN5 = 1;
    GPIOB->INTTYPESET_bit.PIN6 = 1;
}

void MX_IWDG_Init(void)
{
    RCU->WDTCFG_bit.CLKEN = 1;
    RCU->WDTCFG_bit.RSTDIS = 1;
    WDT->LOAD = 200000;
    WDT->CTRL_bit.INTEN = 1;
    WDT->CTRL_bit.RESEN = 1;
}

void PWM_TIM1_Init(void)  //PWM
{     
    SIU->PWMSYNC_bit.PRESCRST = 0x07;
    GPIOA->DENSET |= GPIO_DENSET_PIN8_Msk | GPIO_DENSET_PIN9_Msk | GPIO_DENSET_PIN10_Msk | GPIO_DENSET_PIN11_Msk | GPIO_DENSET_PIN12_Msk | GPIO_DENSET_PIN13_Msk;

    RCU->PCLKCFG_bit.PWM0EN = 1;
    RCU->PRSTCFG_bit.PWM0EN = 1;
    RCU->PCLKCFG_bit.PWM1EN = 1;
    RCU->PRSTCFG_bit.PWM1EN = 1;
    RCU->PCLKCFG_bit.PWM2EN = 1;
    RCU->PRSTCFG_bit.PWM2EN = 1;
    PWM0->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;        //48 KHz
    PWM0->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div1; //48 KHz
    PWM1->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;        //48 KHz
    PWM1->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div1; //48 KHz
    PWM2->TBCTL_bit.CLKDIV = PWM_TBCTL_CLKDIV_Div2;        //48 KHz
    PWM2->TBCTL_bit.HSPCLKDIV = PWM_TBCTL_HSPCLKDIV_Div1; //48 KHz 
    PWM0->ETSEL_bit.SOCAEN = 1; 
    PWM0->ETSEL_bit.SOCASEL = PWM_ETSEL_INTSEL_CTREqZero; 
    PWM0->TBCTL_bit.SYNCOSEL = PWM_TBCTL_SYNCOSEL_CTREqZero;    
    PWM0->TBPRD = TIM1_AUTORELOAD; //24 KHz
    PWM0->AQCTLA_bit.PRD = PWM_AQCTLA_PRD_Set;
    PWM0->AQCTLA_bit.CAU = PWM_AQCTLA_CAU_Clear;
    PWM0->AQCTLB_bit.PRD = PWM_AQCTLB_PRD_Clear;
    PWM0->AQCTLB_bit.CBU = PWM_AQCTLB_CBU_Set;
    PWM1->TBPRD = TIM1_AUTORELOAD; //24 KHz
    PWM1->AQCTLA_bit.PRD = PWM_AQCTLA_PRD_Set;
    PWM1->AQCTLA_bit.CAU = PWM_AQCTLA_CAU_Clear;
    PWM1->AQCTLB_bit.PRD = PWM_AQCTLB_PRD_Clear;
    PWM1->AQCTLB_bit.CBU = PWM_AQCTLB_CBU_Set;
    PWM2->TBPRD = TIM1_AUTORELOAD; //24 KHz
    PWM2->AQCTLA_bit.PRD = PWM_AQCTLA_PRD_Set;
    PWM2->AQCTLA_bit.CAU = PWM_AQCTLA_CAU_Clear;
    PWM2->AQCTLB_bit.PRD = PWM_AQCTLB_PRD_Clear;
    PWM2->AQCTLB_bit.CBU = PWM_AQCTLB_CBU_Set;
    PWM0->DBRED = deadTime;
    PWM0->DBFED = deadTime;
    PWM0->DBCTL_bit.OUTMODE = 0x03;
    PWM0->DBCTL_bit.POLSEL = 0x02;
    PWM1->DBRED = deadTime;
    PWM1->DBFED = deadTime;
    PWM1->DBCTL_bit.OUTMODE = 0x03;
    PWM1->DBCTL_bit.POLSEL = 0x02;
    PWM2->DBRED = deadTime;
    PWM2->DBFED = deadTime;
    PWM2->DBCTL_bit.OUTMODE = 0x03;
    PWM2->DBCTL_bit.POLSEL = 0x02;
    PWM0->DBCTL_bit.INMODE =  0;
    PWM1->DBCTL_bit.INMODE =  0;
    PWM2->DBCTL_bit.INMODE =  0;
}

void ZC_TIM4_Init(void)
{
    RCU->PCLKCFG_bit.INTERVAL_TIMER_EN = 1;
    RCU->PRSTCFG_bit.INTERVAL_TIMER_EN = 1;
    INTERVAL_TIMER->VALUE = 0xFFFFFFFF;
    INTERVAL_TIMER->LOAD = 0;
    INTERVAL_TIMER->CTRL_bit.ON = 1;
}

void disableComTimerInt() 
{
    COM_TIMER->CTRL_bit.INTEN = 0;
}

void enableComTimerInt() 
{
    COM_TIMER->CTRL_bit.INTEN = 1;
}

uint16_t getintervaTimerCount()
{
  uint16_t temp = (0xFFFFFFFF - INTERVAL_TIMER->VALUE) / 50;
  return temp;
}

void setintervaTimerCount(uint16_t intertime)
{
    INTERVAL_TIMER->VALUE = (0xFFFFFFFF - (intertime * 50));
}

void setAndEnableComInt(uint16_t time)
{
    COM_TIMER->VALUE = time * 50;
    COM_TIMER->INTSTATUS_bit.INT = 1;
    COM_TIMER->CTRL_bit.INTEN = 1;
}

void TENKHz_SysTick_Init(void) 
{
    SysTick_Config(5000 - 1);
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_SetPriority(SysTick_IRQn, 0xF);
}

void reloadWatchDogCounter()
{
    WDT->INTCLR = 1; 
}

void COM_TIM3_Init(void)
{
    RCU->PCLKCFG_bit.COM_TIMER_EN = 1;
    RCU->PRSTCFG_bit.COM_TIMER_EN = 1;
    COM_TIMER->VALUE = 0xFFFFFFFF;
    COM_TIMER->LOAD = 0;
    COM_TIMER->CTRL_bit.INTEN = 1;
    __NVIC_EnableIRQ(COM_TIMER_IRQ);  
    NVIC_SetPriority(COM_TIMER_IRQ, 0x1);
}

void MX_TIM16_Init(void)
{
    RCU->PCLKCFG_bit.DELAY_TIMER_EN = 1;
    RCU->PRSTCFG_bit.DELAY_TIMER_EN = 1;
    DELAY_TIMER->LOAD = 0;
}

void MX_TIM17_Init(void) 
{
}

void ALL_DMA_Init(void)
{
}

void ALL_GPIO_Init(void)
{
    RCU->HCLKCFG_bit.GPIOBEN = 1;
    RCU->HRSTCFG_bit.GPIOBEN = 1;
    RCU->HCLKCFG_bit.GPIOAEN = 1;
    RCU->HRSTCFG_bit.GPIOAEN = 1;
    NVIC_EnableIRQ(GPIOB_IRQn);
    NVIC_SetPriority(GPIOB_IRQn, 0x2);
}

void UN_TIM2_Init(void) 
{
    RCU->OSICFG_bit.CAL = 588;
    RCU->PCLKCFG_bit.ECAP1EN = 1;
    RCU->PRSTCFG_bit.ECAP1EN = 1;
    RCU->HCLKCFG_bit.GPIOAEN = 1;
    RCU->HRSTCFG_bit.GPIOAEN = 1;
    SIU->REMAPAF_bit.ECAP1EN = 1;
    GPIOA->DENSET_bit.PIN5 = 1;
    GPIOA->ALTFUNCSET_bit.PIN5 = 1;
    IC_TIMER_REGISTER->ECCTL0_bit.CAPLDEN = 0;
    IC_TIMER_REGISTER->ECCTL0_bit.CAP1POL = 1;
    IC_TIMER_REGISTER->ECCTL0_bit.CAP3POL = 1;
    IC_TIMER_REGISTER->ECCTL1_bit.CONTOST = 0;
    IC_TIMER_REGISTER->ECCTL1_bit.STOPWRAP = 3;
}



