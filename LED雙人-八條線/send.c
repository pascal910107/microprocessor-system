//
// GPIO_LED : GPIO output to control an on-board red LED
//
// EVB : Nu-LB-NUC140
// MCU : NUC140VE3CN

// low-active output control by GPC12

#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "Scankey.h"

int main(void)
{
    int keyin = 0;

    GPIO_SetMode(PB, BIT0, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT2, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT4, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT6, GPIO_MODE_QUASI);

    GPIO_SetMode(PB, BIT1, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT3, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT5, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT7, GPIO_MODE_QUASI);

    PB0 = 1;
    PB1 = 1;
    SYS_Init();
    PD14 = 0;

    while (1)
    {

        keyin = ScanKey();
        PB0 = PB2 = PB4 = PB6 = 1;
        PC12 = PC13 = PC14 = PC15 = 1;
        // if(!keyin)continue;

        PC15 = !((keyin % 2) || !PB1);
        PB0 = !(keyin % 2);
        keyin /= 2;

        PC14 = !((keyin % 2) || !PB3);
        PB2 = !(keyin % 2);
        keyin /= 2;

        PC13 = !((keyin % 2) || !PB5);
        PB4 = !(keyin % 2);
        keyin /= 2;

        PC12 = !((keyin % 2) || !PB7);
        PB6 = !(keyin % 2);
    }
}