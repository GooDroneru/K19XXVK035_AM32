/*
 * comparator.c
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#include "comparator.h"
#include "targets.h"

void maskPhaseInterrupts()
{
    COMPARATOR_REGISTER->INTENCLR_bit.PHASE_A_COMP = 1;
    COMPARATOR_REGISTER->INTENCLR_bit.PHASE_B_COMP = 1;
    COMPARATOR_REGISTER->INTENCLR_bit.PHASE_C_COMP = 1;
    COMPARATOR_REGISTER->INTSTATUS_bit.PHASE_A_COMP = 1;
    COMPARATOR_REGISTER->INTSTATUS_bit.PHASE_B_COMP = 1;
    COMPARATOR_REGISTER->INTSTATUS_bit.PHASE_C_COMP = 1;
}

void enableCompInterrupts()      //enable
{
    COMPARATOR_REGISTER->INTENSET_bit.PHASE_A_COMP = 1;
    COMPARATOR_REGISTER->INTENSET_bit.PHASE_B_COMP = 1;
    COMPARATOR_REGISTER->INTENSET_bit.PHASE_C_COMP = 1;
}
void changeCompInput()
{
    if (step == 1 || step == 4)
    {   // c floating
    }
    if (step == 2 || step == 5)
    {   // a floating
    }
    if (step == 3 || step == 6)
    {   // b floating
    }

#if defined INVERTED_COMPARATOR
    if (!rising)
#else
    if (rising)
#endif
    {
        COMPARATOR_REGISTER->INTPOLCLR_bit.PHASE_A_COMP = 1;
        COMPARATOR_REGISTER->INTPOLCLR_bit.PHASE_B_COMP = 1;
        COMPARATOR_REGISTER->INTPOLCLR_bit.PHASE_C_COMP = 1;
    }
    else
    {
        COMPARATOR_REGISTER->INTPOLSET_bit.PHASE_A_COMP = 1;
        COMPARATOR_REGISTER->INTPOLSET_bit.PHASE_B_COMP = 1;
        COMPARATOR_REGISTER->INTPOLSET_bit.PHASE_C_COMP = 1; 
    }
}

uint8_t getCompOutputLevel(){
    if (step == 1 || step == 4)
    {   // c floating
#if !defined INVERTED_COMPARATOR
        return SET == GPIO_ReadBit(COMPARATOR_REGISTER, PHASE_A_COMP_PIN);
#else
        return CLEAR == GPIO_ReadBit(COMPARATOR_REGISTER, PHASE_A_COMP_PIN);
#endif
    }
    if (step == 2 || step == 5)
    {   // a floating
#if !defined INVERTED_COMPARATOR
        return SET == GPIO_ReadBit(COMPARATOR_REGISTER, PHASE_C_COMP_PIN);
#else
        return CLEAR == GPIO_ReadBit(COMPARATOR_REGISTER, PHASE_C_COMP_PIN);
#endif
    }
    if (step == 3 || step == 6)
    {   // b floating
#if !defined INVERTED_COMPARATOR
        return SET == GPIO_ReadBit(COMPARATOR_REGISTER, PHASE_B_COMP_PIN);
#else
        return CLEAR == GPIO_ReadBit(COMPARATOR_REGISTER, PHASE_B_COMP_PIN);
#endif
    }
    return 0;
}




