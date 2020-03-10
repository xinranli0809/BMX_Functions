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

volatile uint32_t pwmOut = 9531;

// 0.025ms dead-band = 156 counts out of 125000
// Forward actual starting point = 9375 + 156 = 9531
// Reverse actual starting point = 9375 - 156 = 9219

int upFlag = 1;

void triangle(void)
{
    uint32_t status=0;
    status = TimerIntStatus(TIMER0_BASE,true);
    TimerIntClear(TIMER0_BASE,status);

    if (pwmOut == 12500)
    {
        upFlag = 0;
    }
    if (pwmOut == 6250)
    {
        upFlag = 1;
    }

    if (pwmOut > 9531 && pwmOut <= 12500 || pwmOut == 9531)
    {
        if (upFlag == 1)
        {
            pwmOut++;
        }
        else if (pwmOut == 9531 && upFlag == 0)
        {
            pwmOut = 9219;
        }
        else
        {
            pwmOut = pwmOut - 1;
        }

    }
    else if (pwmOut >= 6250 && pwmOut < 9219 || pwmOut == 9219)
    {
        if (upFlag == 0)
        {
            pwmOut = pwmOut - 1;
        }
        else if (pwmOut == 9219 && upFlag == 1)
        {
            pwmOut = 9531;
        }
        else
        {
            pwmOut++;
        }
    }

}
