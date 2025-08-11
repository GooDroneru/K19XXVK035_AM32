#include "main.h"
#include "K19xxVK035_it.h"
#include "targets.h"
#include "ADC.h"
#include "comparator.h"
#include "functions.h"

extern void transfercomplete();
extern void PeriodElapsedCallback();
extern void interruptRoutine();
extern void tenKhzRoutine();
extern void sendDshotDma();
extern void receiveDshotDma();

extern char send_telemetry;
extern char telemetry_done;
extern char servoPwm;
extern char dshot;
extern char inputSet;
extern char running;
extern uint16_t ADCDataDMA[3];
extern uint32_t dma_buffer[64];
volatile uint16_t counter = 0;
extern uint8_t buffersize;
char input_ready = 0;
extern uint32_t gcr[37];
extern uint8_t buffer_padding;

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
    while (1)
    {
    }
}


__RAMFUNC void SysTick_Handler(void)
{
    tenKhzRoutine();
}

__RAMFUNC void ADC_SEQ0_IRQHandler()
{   
    ADC_SEQ_ITStatusClear(ADC_SEQ_Num_0);
    while (ADC_SEQ_GetFIFOLoad(ADC_SEQ_Num_0)) {
        for(volatile uint32_t i = 0; i < 10; i++) {
            asm("nop");
            //delay
        }
        ADCDataDMA[0] = ADC_SEQ_GetFIFOData(ADC_SEQ_Num_0);
        ADCDataDMA[1] = ADC_SEQ_GetFIFOData(ADC_SEQ_Num_0);
        ADCDataDMA[2] = ADC_SEQ_GetFIFOData(ADC_SEQ_Num_0);
        //ADCDataDMA[3] = ADC_SEQ_GetFIFOData(ADC_SEQ_Num_0);
    }
}

__RAMFUNC void GPIOB_IRQHandler()
{
    if (step == 1 || step == 4)
    {   // c floating
        if(GPIOB->INTSTATUS_bit.PHASE_C_COMP && COMPARATOR_REGISTER->DENSET_bit.PHASE_C_COMP && COMPARATOR_REGISTER->INTENSET_bit.PHASE_C_COMP) {
            GPIOB->INTSTATUS_bit.PHASE_C_COMP = 1;
            interruptRoutine();
        }
    }
    if (step == 2 || step == 5)
    {   // a floating
        if(GPIOB->INTSTATUS_bit.PHASE_A_COMP && COMPARATOR_REGISTER->DENSET_bit.PHASE_A_COMP && COMPARATOR_REGISTER->INTENSET_bit.PHASE_C_COMP) {
            GPIOB->INTSTATUS_bit.PHASE_A_COMP = 1;
            interruptRoutine();
        }

    }
    if (step == 3 || step == 6)
    {   // b floating
        if(GPIOB->INTSTATUS_bit.PHASE_B_COMP && COMPARATOR_REGISTER->DENSET_bit.PHASE_B_COMP && COMPARATOR_REGISTER->INTENSET_bit.PHASE_C_COMP) {
            GPIOB->INTSTATUS_bit.PHASE_B_COMP = 1;
            interruptRoutine();
        }
    }
}

__RAMFUNC void TMR0_IRQHandler(void)
{
    if(COM_TIMER->INTSTATUS_bit.INT && COM_TIMER->CTRL_bit.INTEN) {
        COM_TIMER->INTSTATUS_bit.INT = 1;
        PeriodElapsedCallback( );
    }
}

__RAMFUNC void ECAP1_IRQHandler()
{
    if(IC_TIMER_REGISTER->ECFLG_bit.CEVT1 && IC_TIMER_REGISTER->ECEINT_bit.CEVT1) {
        dma_buffer[counter++] = IC_TIMER_REGISTER->CAP0;
        dma_buffer[counter++] = IC_TIMER_REGISTER->CAP1;
        // *(uint32_t*)(&dma_buffer[counter]) = *(uint32_t*)&IC_TIMER_REGISTER->CAP0;
        // counter += 2;
        // memcpy(&dma_buffer[counter], &IC_TIMER_REGISTER->CAP0, 2*sizeof(uint16_t));
        // counter += 2;
        IC_TIMER_REGISTER->ECCLR_bit.INT = 1;
        IC_TIMER_REGISTER->PEINT_bit.PEINT = 1;
        IC_TIMER_REGISTER->ECCLR_bit.CEVT1 = 1;
    }
    if(IC_TIMER_REGISTER->ECFLG_bit.CEVT3 && IC_TIMER_REGISTER->ECEINT_bit.CEVT3) {
        dma_buffer[counter++] = IC_TIMER_REGISTER->CAP2;
        dma_buffer[counter++] = IC_TIMER_REGISTER->CAP3;
        IC_TIMER_REGISTER->ECCLR_bit.INT = 1;
        IC_TIMER_REGISTER->PEINT_bit.PEINT = 1; 
        IC_TIMER_REGISTER->ECCLR_bit.CEVT3 = 1;

        if(counter >= buffersize) {
            IC_TIMER_REGISTER->ECCTL0_bit.CAPLDEN = 0;
            IC_TIMER_REGISTER->ECEINT_bit.CEVT3 = 0;
            IC_TIMER_REGISTER->ECCTL1_bit.TSCTRSTOP = 0;
            NVIC_DisableIRQ(IC_TIMER_INT_VECTOR);
            counter = 0;
            transfercomplete();
            input_ready = 1;
        }     
    }
    if(IC_TIMER_REGISTER->ECFLG_bit.CTRPRD && IC_TIMER_REGISTER->ECEINT_bit.CTRPRD) {
        IC_TIMER_REGISTER->ECCLR_bit.INT = 1;
        IC_TIMER_REGISTER->PEINT_bit.PEINT = 1;
        IC_TIMER_REGISTER->ECCLR_bit.CTRPRD = 1;
        if(counter < (37)) {
            IC_TIMER_REGISTER->CMPSHDW = gcr[counter];
            counter++;
        }
        else {
            counter = 0;
            NVIC_DisableIRQ(IC_TIMER_INT_VECTOR);
            transfercomplete();
        }
    }
    IC_TIMER_REGISTER->ECCLR_bit.INT = 1;
    IC_TIMER_REGISTER->PEINT_bit.PEINT = 1;
}