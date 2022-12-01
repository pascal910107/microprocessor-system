//
// UART0_RX : UART0 RX recieve and display Text
//
// Board : Nu-LB-NUC140
// MCU : NUC140VE3CN (LQFP100)
// UART0 : baudrate=115200, databit=8, stopbit=1, paritybit=0, flowcontrol=None

#include #include #include #include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"

void Init_UART(void)
{
    UART_Open(UART0, 9600); // set UART0 baud rate
}

void show(char *num)
{
    if (*num == '1')
    {
        PC15 = 0;
        PC14 = 1;
        PC13 = 1;
        PC12 = 1;
    }
    else if (*num == '2')
    {
        PC15 = 1;
        PC14 = 0;
        PC13 = 1;
        PC12 = 1;
    }
    else if (*num == '3')
    {
        PC15 = 0;
        PC14 = 0;
        PC13 = 1;
        PC12 = 1;
    }
    else if (*num == '4')
    {
        PC15 = 1;
        PC14 = 1;
        PC13 = 0;
        PC12 = 1;
    }
    else if (*num == '5')
    {
        PC15 = 0;
        PC14 = 1;
        PC13 = 0;
        PC12 = 1;
    }
    else if (*num == '6')
    {
        PC15 = 1;
        PC14 = 0;
        PC13 = 0;
        PC12 = 1;
    }
    else if (*num == '7')
    {
        PC15 = 0;
        PC14 = 0;
        PC13 = 0;
        PC12 = 1;
    }
    else if (*num == '8')
    {
        PC15 = 1;
        PC14 = 1;
        PC13 = 0;
        PC12 = 0;
    }
    else if (*num == '9')
    {
        PC15 = 0;
        PC14 = 1;
        PC13 = 1;
        PC12 = 0;
    }
    CLK_SysTickDelay(10000);
}

int32_t main()
{
    char TX_Buffer[16];
    char RX_Buffer[16];
    uint32_t keyin = 0;

    SYS_Init();
    init_LCD();
    clear_LCD();

    Init_UART();

    PD14 = 0;

    print_Line(0, "test TX and RX:");

    while (1)
    {
        UART_Read(UART0, RX_Buffer, 1);
        print_Line(1, RX_Buffer);
        show(RX_Buffer);
    }
}