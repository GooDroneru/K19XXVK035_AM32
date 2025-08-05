/*
 * phaseouts.c
 *
 *  Created on: Apr 22, 2020
 *      Author: Alka
 */
#include "phaseouts.h"
#include "targets.h"

extern char comp_pwm;
extern char prop_brake_active;

#define PHASE_C_HIGH PIN8
#define PHASE_C_LOW PIN9
#define PHASE_B_HIGH PIN10
#define PHASE_B_LOW PIN11
#define PHASE_A_HIGH PIN12
#define PHASE_A_LOW PIN13

void proportionalBrake()
{
	GPIOA->ALTFUNCSET_bit.PHASE_A_HIGH = 0;
	GPIOA->DATAOUTCLR_bit.PHASE_A_HIGH = 1;
	GPIOA->ALTFUNCSET_bit.PHASE_B_HIGH = 0;
	GPIOA->DATAOUTCLR_bit.PHASE_B_HIGH = 1;
	GPIOA->ALTFUNCSET_bit.PHASE_C_HIGH = 0;
	GPIOA->DATAOUTCLR_bit.PHASE_C_HIGH = 1;
	GPIOA->ALTFUNCSET_bit.PHASE_A_LOW = 1;
	GPIOA->ALTFUNCSET_bit.PHASE_B_LOW = 1;
	GPIOA->ALTFUNCSET_bit.PHASE_C_LOW = 1;
}
 
void phaseBPWM() 
{
	if(!eepromBuffer.comp_pwm){  // for future
		GPIOA->ALTFUNCCLR_bit.PHASE_B_LOW = 1;
		GPIOA->DATAOUTCLR_bit.PHASE_B_LOW = 1;
		GPIOA->OUTENSET_bit.PHASE_B_LOW = 1;
	}else{
		GPIOA->ALTFUNCSET_bit.PHASE_B_LOW = 1;
		GPIOA->OUTENCLR_bit.PHASE_B_LOW = 1;
	}
	GPIOA->ALTFUNCSET_bit.PHASE_B_HIGH = 1;
	GPIOA->OUTENCLR_bit.PHASE_B_HIGH = 1;   
}

void phaseBFLOAT()
{
	GPIOA->ALTFUNCCLR_bit.PHASE_B_LOW = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_B_LOW = 1;
	GPIOA->OUTENSET_bit.PHASE_B_LOW = 1;
	GPIOA->ALTFUNCCLR_bit.PHASE_B_HIGH = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_B_HIGH = 1;
	GPIOA->OUTENSET_bit.PHASE_B_HIGH = 1;
}

void phaseBLOW()
{
	GPIOA->ALTFUNCCLR_bit.PHASE_B_LOW = 1;
	GPIOA->DATAOUTSET_bit.PHASE_B_LOW = 1;
	GPIOA->OUTENSET_bit.PHASE_B_LOW = 1;
	GPIOA->ALTFUNCCLR_bit.PHASE_B_HIGH = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_B_HIGH = 1;
	GPIOA->OUTENSET_bit.PHASE_B_HIGH = 1;
}

//////////////////////////////PHASE 2//////////////////////////////////////////////////
void phaseAPWM()
{
	if (!eepromBuffer.comp_pwm)
	{
		GPIOA->ALTFUNCCLR_bit.PHASE_A_LOW = 1;
		GPIOA->DATAOUTCLR_bit.PHASE_A_LOW = 1;
		GPIOA->OUTENSET_bit.PHASE_A_LOW = 1;
	}
	else
	{
		GPIOA->ALTFUNCSET_bit.PHASE_A_LOW = 1;
		GPIOA->OUTENCLR_bit.PHASE_A_LOW = 1;
	}
	GPIOA->ALTFUNCSET_bit.PHASE_A_HIGH = 1;
	GPIOA->OUTENCLR_bit.PHASE_A_HIGH = 1;    
}

void phaseAFLOAT()
{
	GPIOA->ALTFUNCCLR_bit.PHASE_A_LOW = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_A_LOW = 1;
	GPIOA->OUTENSET_bit.PHASE_A_LOW = 1;
	GPIOA->ALTFUNCCLR_bit.PHASE_A_HIGH = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_A_HIGH = 1;
	GPIOA->OUTENSET_bit.PHASE_A_HIGH = 1;
}

void phaseALOW() 
{
	GPIOA->ALTFUNCCLR_bit.PHASE_A_LOW = 1;
	GPIOA->DATAOUTSET_bit.PHASE_A_LOW = 1;
	GPIOA->OUTENSET_bit.PHASE_A_LOW = 1;
	GPIOA->ALTFUNCCLR_bit.PHASE_A_HIGH = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_A_HIGH = 1;
	GPIOA->OUTENSET_bit.PHASE_A_HIGH = 1;
}

///////////////////////////////////////////////PHASE 3 /////////////////////////////////////////////////

void phaseCPWM()
{
	if (!eepromBuffer.comp_pwm){
		GPIOA->ALTFUNCCLR_bit.PHASE_C_LOW = 1;
		GPIOA->DATAOUTCLR_bit.PHASE_C_LOW = 1;
		GPIOA->OUTENSET_bit.PHASE_C_LOW = 1;
	}else{
		GPIOA->ALTFUNCSET_bit.PHASE_C_LOW = 1;
		GPIOA->OUTENCLR_bit.PHASE_C_LOW = 1;
	}
	GPIOA->ALTFUNCSET_bit.PHASE_C_HIGH = 1;
	GPIOA->OUTENCLR_bit.PHASE_C_HIGH = 1;    
}

void phaseCFLOAT() 
{
	GPIOA->ALTFUNCCLR_bit.PHASE_C_LOW = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_C_LOW = 1;
	GPIOA->OUTENSET_bit.PHASE_C_LOW = 1;
	GPIOA->ALTFUNCCLR_bit.PHASE_C_HIGH = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_C_HIGH = 1;
	GPIOA->OUTENSET_bit.PHASE_C_HIGH = 1;
}

void phaseCLOW() 
{
	GPIOA->ALTFUNCCLR_bit.PHASE_C_LOW = 1;
	GPIOA->DATAOUTSET_bit.PHASE_C_LOW = 1;
	GPIOA->OUTENSET_bit.PHASE_C_LOW = 1;
	GPIOA->ALTFUNCCLR_bit.PHASE_C_HIGH = 1;
	GPIOA->DATAOUTCLR_bit.PHASE_C_HIGH = 1;
	GPIOA->OUTENSET_bit.PHASE_C_HIGH = 1;
}

void allOff()
{
	phaseAFLOAT();
	phaseBFLOAT();
	phaseCFLOAT();
}

void comStep(int newStep)
{
    switch (newStep) {
    case 1: // A-B
        phaseAPWM();
        phaseBLOW();
        phaseCFLOAT();
        break;

    case 2: // C-B
        phaseAFLOAT();
        phaseBLOW();
        phaseCPWM();
        break;

    case 3: // C-A
        phaseALOW();
        phaseBFLOAT();
        phaseCPWM();
        break;

    case 4: // B-A
        phaseALOW();
        phaseBPWM();
        phaseCFLOAT();
        break;

    case 5: // B-C
        phaseAFLOAT();
        phaseBPWM();
        phaseCLOW();
        break;

    case 6: // A-C
        phaseAPWM();
        phaseBFLOAT();
        phaseCLOW();
        break;
    }
}

void fullBrake()
{ // full braking shorting all low sides
    phaseALOW();
    phaseBLOW();
    phaseCLOW();
}

void allpwm()
{ // for stepper_sine
    phaseAPWM();
    phaseBPWM();
    phaseCPWM();
}

void twoChannelForward()
{
    phaseAPWM();
    phaseBLOW();
    phaseCPWM();
}

void twoChannelReverse()
{
    phaseALOW();
    phaseBPWM();
    phaseCLOW();
}

