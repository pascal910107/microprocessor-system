//
// UART0_RX : UART0 RX recieve and display Text
//
// Board : Nu-LB-NUC140
// MCU : NUC140VE3CN (LQFP100)
// UART0 : baudrate=115200, databit=8, stopbit=1, paritybit=0, flowcontrol=None

#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "ScanKey.h"

void Init_UART(void)
{
    UART_Open(UART0, 9600); // set UART0 baud rate
}

int32_t main()
{
    char TX_Buffer[16];
    char RX_Buffer[16];
    uint32_t keyin = 0;

    GPIO_SetMode(PB, BIT0, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT1, GPIO_MODE_QUASI);

    SYS_Init();
    init_LCD();
    clear_LCD();
    Init_UART();

    PB0 = 1;
    PB1 = 1;
    PD14 = 0;
    print_Line(0, "test TX and RX:");

    while (1)
    {
        keyin = ScanKey();
        switch (keyin)
        {
        case 1:
            print_Line(1, "send!!!");
            UART_Write(UART0, "1", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 2:
            print_Line(1, "send!!!");
            UART_Write(UART0, "2", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 3:
            print_Line(1, "send!!!");
            UART_Write(UART0, "3", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 4:
            print_Line(1, "send!!!");
            UART_Write(UART0, "4", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 5:
            print_Line(1, "send!!!");
            UART_Write(UART0, "5", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 6:
            print_Line(1, "send!!!");
            UART_Write(UART0, "6", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 7:
            print_Line(1, "send!!!");
            UART_Write(UART0, "7", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 8:
            print_Line(1, "send!!!");
            UART_Write(UART0, "8", 1);
            CLK_SysTickDelay(1000000);
            break;
        case 9:
            print_Line(1, "send!!!");
            UART_Write(UART0, "9", 1);
            CLK_SysTickDelay(1000000);
            break;
        }
    }
}