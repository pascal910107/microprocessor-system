#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "Scankey.h"

int main(void)
{
    int i = 0;
    int j = 0;

    SYS_Init();
    init_LCD();
    clear_LCD();
    OpenKeyPad();
    GPIO_SetMode(PB, BIT0, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT1, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT2, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT3, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT4, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT5, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT6, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, BIT7, GPIO_MODE_QUASI);

    PD14 = 0;
    PB0 = PB1 = 1;
    while (1)
    {

        i = j = ScanKey();
        PC12 = PC13 = PC14 = PC15 = PB0 = PB2 = PB4 = PB6 = 1;
        // if(i==0)continue;
        if (i / 8 >= 1 || PB7 == 0)
        {
            PC12 = 0;
            i -= 8;
            PB6 = 0;
        }
        if (i / 4 >= 1 || PB5 == 0)
        {
            PC13 = 0;
            i -= 4;
            PB4 = 0;
        }
        if (i / 2 >= 1 || PB3 == 0)
        {
            PC14 = 0;
            i -= 2;
            PB2 = 0;
        }
        if (i == 1 || PB1 == 0)
        {
            PC15 = 0;
            PB0 = 0;
        }
    }
}