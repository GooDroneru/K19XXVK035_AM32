/*
 * comparator.h
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#ifndef COMPARATOR_H_
#define COMPARATOR_H_
#include "main.h"
#include "plib035_gpio.h"

#define PHASE_A_COMP PIN4
#define PHASE_B_COMP PIN5
#define PHASE_C_COMP PIN6

#define PHASE_A_COMP_PIN GPIO_Pin_4
#define PHASE_B_COMP_PIN GPIO_Pin_5
#define PHASE_C_COMP_PIN GPIO_Pin_6

#define COMPARATOR_REGISTER GPIOB

void maskPhaseInterrupts();
void changeCompInput();
void enableCompInterrupts();
uint8_t getCompOutputLevel();
extern char rising;
extern char step;


#endif /* COMPARATOR_H_ */


