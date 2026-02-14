#include "main.h"
#include "K19xxVK035_it.h"
#include "targets.h"
#include "ADC.h"
#include "string.h"
#include "comparator.h"
#include "functions.h"
#include "peripherals.h"
#include "IO.h"

extern void transfercomplete();
extern void PeriodElapsedCallback();
extern void interruptRoutine();
extern void tenKhzRoutine();
extern void sendDshotDma();
extern void receiveDshotDma();
extern void processDshot();

extern char send_telemetry;
extern char telemetry_done;
extern char servoPwm;
extern char dshot;
extern char inputSet;
extern char running;
extern uint16_t ADCDataDMA[3];
extern uint32_t dma_buffer[64];
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

__RAMFUNC void UART0_TD_IRQHandler(void)
{      
    if(UART0->RIS_bit.TDRIS) {
        UART0->ICR_bit.TDIC = 1;
        GPIOB->PULLMODE_bit.PIN10 = 1;
        GPIO_AltFuncCmd(GPIOB, GPIO_Pin_10, DISABLE);
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
        if(GPIOB->INTSTATUS_bit.PHASE_C_COMP) {
            GPIOB->INTSTATUS = 0xFFFFFFFF;
            if(COMPARATOR_REGISTER->INTENSET_bit.PHASE_C_COMP) {
                interruptRoutine();
            }
        }
        return;
    }
    if (step == 2 || step == 5)
    {   // a floating
    if(GPIOB->INTSTATUS_bit.PHASE_A_COMP) {
        GPIOB->INTSTATUS = 0xFFFFFFFF;
            if(COMPARATOR_REGISTER->INTENSET_bit.PHASE_A_COMP) {
                interruptRoutine();
            }
        }
        return;
    }
    if (step == 3 || step == 6)
    {   // b floating
    if(GPIOB->INTSTATUS_bit.PHASE_B_COMP) {
        GPIOB->INTSTATUS = 0xFFFFFFFF;
            if(COMPARATOR_REGISTER->INTENSET_bit.PHASE_B_COMP) {
                interruptRoutine();
            }
        }
    }
    return;
}

__RAMFUNC void TMR0_IRQHandler(void)
{
    //if(COM_TIMER->INTSTATUS_bit.INT && COM_TIMER->CTRL_bit.INTEN) {
        COM_TIMER->INTSTATUS_bit.INT = 1;
        PeriodElapsedCallback();
    //}
}


__RAMFUNC void DMA_CH8_IRQHandler()
{   
    TMR3->VALUE = 0xFFFFFFFF;
    reverseBuffer();
    transfercomplete();
    input_ready = 1;
    //processDshot();
    __NVIC_SetPendingIRQ(ADC_SEQ1_IRQn);
}

__RAMFUNC void DMA_CH12_IRQHandler()
{   
    IC_TIMER_REGISTER->CMPSHDW = 0;
    transfercomplete();
}

__RAMFUNC void ADC_SEQ1_IRQHandler() {
    ADC_SEQ_ITStatusClear(ADC_SEQ_Num_1);
    processDshot();
}
