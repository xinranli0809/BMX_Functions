#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "timerInit.h"
#include "delay.h"
#include "pwmInit.h"
#include "adcInit.h"
#include "triangle.h"



/**
 * main.c
 */
int toggle = 0;

volatile uint32_t second = 0;
volatile uint32_t second2 = 0;

void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
void ISR(void)
{
    uint32_t status=0;

    status = TimerIntStatus(TIMER0_BASE,true);
    TimerIntClear(TIMER0_BASE,status);
    second++;

}

void ISR2(void)
{
    uint32_t status=0;

    status = TimerIntStatus(TIMER5_BASE,true);
    TimerIntClear(TIMER5_BASE,status);
    second2++;
}



int main(void)
{
    // MUST USE PLL CLOCK IF WANT TO USE ADC
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ );
    ConfigureTimerAndInterrupt(triangle,ISR2);

    ConfigureUART();

//    delayMs(3000);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

while(1)
{

//
//    //
//            // Trigger the ADC conversion.
//            //
//            ADCProcessorTrigger(ADC0_BASE, 1);
//
//            //
//            // Wait for conversion to be completed.
//            //
//            while(!ADCIntStatus(ADC0_BASE, 1, false))
//            {
//            }
//
//            //
//            // Clear the ADC interrupt flag.
//            //
//            ADCIntClear(ADC0_BASE, 1);
//
//            //
//            // Read ADC Value.
//            //
//            ADCSequenceDataGet(ADC0_BASE, 1, pui32ADC0Value);
//
//            //
//            // Display the AIN0 (PE3) digital value on the console.
//            //
//            div[0] = (pui32ADC0Value[0]/5.25128)+780;
//            width = ((div[0]*1000)/15600)*20;
//            distance = 27.726*pow(((double)pui32ADC0Value[2])/1241.21,-1.2045);
////                width =

                UARTprintf("sysF = %d   ", SysCtlClockGet());
                UARTprintf("pwm = %d   ", pwmOut);
                UARTprintf("swcond2 = %d  \r ", second2);
//                UARTprintf("AIN1 = %d   ", pui32ADC0Value[1]);
//                UARTprintf("AIN2 = %dCM   ",(int)distance );
//                UARTprintf("System Clock: %d    \r",SysCtlClockGet());
//                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, speed);
//                UARTprintf("PWM width = %4d\r\n", width);


}
}
