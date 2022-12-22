#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"
#include "Seven_Segment.h"

void init()
{
    PC4 = PC5 = PC6 = PC7 = 0;
    PE0 = PE7 = PE2 = PE3 = PE4 = PE5 = PE6 = 1;
}
void Show(uint16_t x, uint32_t u32ADCvalue)
{
    if (x < 10)
    {
    }
    else if (x > 9 && x < 100)
    {
        Show(x % 10, u32ADCvalue);
        PC5 = 1;
        x = x / 10;
    }
    else if (x > 99 && x < 1000)
    {

        Show(x % 10, u32ADCvalue);
        PC5 = 1;
        x = x / 10;
        Show(x % 10, u32ADCvalue);
        PC6 = 1;
        x = x / 10;
    }
    else if (x > 999 && x < 10000)
    {
        Show(x % 10, u32ADCvalue);
        PC5 = 1;
        x = x / 10;
        Show(x % 10, u32ADCvalue);
        PC6 = 1;
        x = x / 10;
        Show(x % 10, u32ADCvalue);
        PC7 = 1;
        x = x / 10;
    }
    switch (x)
    {
    case 0:
        PE0 = 0;
        PE3 = 0;
        PE4 = 0;
        PE2 = 0;
        PE6 = 0;
        PE5 = 0;
        break;
    case 1:
        PE0 = 0;
        PE4 = 0;
        break;
    case 2:
        PE3 = 0;
        PE4 = 0;
        PE7 = 0;
        PE6 = 0;
        PE5 = 0;
        break;
    case 3:
        PE0 = 0;
        PE3 = 0;
        PE4 = 0;
        PE7 = 0;
        PE5 = 0;
        break;
    case 4:
        PE0 = 0;
        PE4 = 0;
        PE2 = 0;
        PE7 = 0;
        break;
    case 5:
        PE0 = 0;
        PE3 = 0;
        PE7 = 0;
        PE2 = 0;
        PE5 = 0;
        break;
    case 6:
        PE0 = 0;
        PE3 = 0;
        PE7 = 0;
        PE2 = 0;
        PE6 = 0;
        PE5 = 0;
        break;
    case 7:
        PE0 = 0;
        PE3 = 0;
        PE4 = 0;
        PE2 = 0;
        break;
    case 8:
        PE0 = 0;
        PE3 = 0;
        PE4 = 0;
        PE2 = 0;
        PE6 = 0;
        PE5 = 0;
        PE7 = 0;
        break;
    case 9:
        PE0 = 0;
        PE3 = 0;
        PE4 = 0;
        PE2 = 0;
        PE7 = 0;
        break;
    defult:
        break;
    }
    //CLK_SysTickDelay(10 + u32ADCvalue / 10);
		CLK_SysTickDelay(1000);
    init();
}
void show1to9999()
{
    int i = 1;
    int j = 50;
    while (1)
    {
        j = 50;

        init();
        while (j--)
        {
            PC4 = 1;
            // Show(i);
            init();
        }

        i++;

        if (i == 9999)
        {
            i = 1;
        }
    }
}

char Text[16];

void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK);
    ADC_POWER_ON(ADC);
}

int32_t main(void)
{
    int i = 1;
    int j = 50;

    uint32_t u32ADCvalue;
    SYS_Init();
    Init_ADC();
    init_LCD();
    clear_LCD();
    OpenSevenSegment();

    PD14 = 0;

    while (1)
    {
        ADC_START_CONV(ADC);
        u32ADCvalue = ADC_GET_CONVERSION_DATA(ADC, 7);
        sprintf(Text, "T = %5d", u32ADCvalue);
        print_Line(1, Text);
        j = 50 - u32ADCvalue/200;
        init();
        while (j--)
        {
            PC4 = 1;
            Show(i, u32ADCvalue);
            init();
        }

        i++;

        if (i == 9999)
        {
            i = 1;
        }
    }
}