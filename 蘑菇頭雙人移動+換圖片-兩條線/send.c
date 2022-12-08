//
// TMR_Capture_SR04 : usi[ng Timer Capture to read Ultrasound Ranger SR-04
//
// EVB : Nu-LB-NUC140 (need to manually switch RSTCAPSEL)
// MCU : NUC140VE3CN
// Sensor: SR-04

// SR-04 connection
// Trig connected to PB8
// Echo connected to TC2/PB2 (TC0_PB15, TC1_PE5, TC2_PB2, TC3_PB3)

#include <stdio.h>
#include "NUC100Series.h"
#include "string.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"

unsigned char bmp16x16[32] = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
    0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF};

void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK);
    ADC_POWER_ON(ADC);
}
void Init_UART(void)
{
    UART_Open(UART0, 9600); // set UART0 baud rate
}
int32_t main(void)
{
    uint32_t x, y, z;
    char text[20];
    SYS_Init();
    Init_ADC();
    init_LCD();
    clear_LCD();
    Init_UART();
    GPIO_SetMode(PB, BIT0, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT1, GPIO_MODE_QUASI);
    PB0 = 1;
    PB1 = 1;

    PD14 = 0;

    // print_Line(0, "VR");

    while (1)
    {
        ADC_START_CONV(ADC);
        x = ADC_GET_CONVERSION_DATA(ADC, 0);
        y = ADC_GET_CONVERSION_DATA(ADC, 1);
        z = PB5;
        x *= 0.017;
        y *= 0.0075;
        if (x > 56)
            x += (x - 56) * 3.35;
        if (y > 24)
            y += (y - 24) * 3.1;

        sprintf(text, "%3d %3d %1d", x, y, z);

        UART_Write(UART0, text, 9);

        clear_LCD();
        draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, bmp16x16);
        CLK_SysTickDelay(100000);
    }
}