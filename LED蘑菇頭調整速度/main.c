
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "Seven_Segment.h"
#include "Scankey.h"
#include "LCD.h"


void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK);
    ADC_POWER_ON(ADC);
}

int32_t main(void)
{
    uint32_t x, y, z;
	int flag = 0, change = 0;
    SYS_Init();
    Init_ADC();
    init_LCD();
    clear_LCD();

    PD14 = 0;

    // print_Line(0, "VR");

    while (1)
    {
				change = 0;
        ADC_START_CONV(ADC);
        x = ADC_GET_CONVERSION_DATA(ADC, 0);
        y = ADC_GET_CONVERSION_DATA(ADC, 1);
        z = PB0;
        x *= 0.017;
        y *= 0.0075;
        if (x > 56)
            x += (x - 56) * 3.35;
        if (y > 24)
            y += (y - 24) * 3.1;
        clear_LCD();
				
				flag = change||z ? flag : !flag, change = 1;
				PD14 = flag;
        PC12 = 0;
				CLK_SysTickDelay(500000-x*1000);
				PC12 = 1;
				flag = change||z ? flag : !flag, change = 1;
				PD14 = flag;
				PC13 = 0;
				CLK_SysTickDelay(500000-x*1000);
				PC13 = 1;
				flag = change||z ? flag : !flag, change = 1;
				PD14 = flag;
				PC14 = 0;
				CLK_SysTickDelay(500000-x*1000);
				PC14 = 1;
				flag = change||z ? flag : !flag, change = 1;
				PD14 = flag;
				PC15 = 0;
				CLK_SysTickDelay(500000-x*1000);
				PC15 = 1;
				flag = change||z ? flag : !flag, change = 1;
				PD14 = flag;
    }
}