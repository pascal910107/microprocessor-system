//
// GPIO_7seg_keypad : 3x3 keypad inpt and display on 7-segment LEDs
//
#include #include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "Seven_Segment.h"
#include "Scankey.h"

// display an integer on four 7-segment LEDs
void left()
{
    if (!PE4)
    {
        PE4 = 1;
        PE2 = 0;
    }
    else if (!PE0)
    {
        PE0 = 1;
        PE6 = 0;
    }
    else if (!PE5)
    {
        PE5 = 1;
        PE6 = 0;
    }
    else if (!PE7)
    {
        PE7 = 1;
        PE2 = 0;
    }
    else if (!PE3)
    {
        PE3 = 1;
        PE2 = 0;
    }
    else if (!PE2)
    {
        PE2 = 1;
        PE4 = 0;
        if (PC4)
        {
            PC4 = 0;
            PC5 = 1;
        }
        else if (PC5)
        {
            PC5 = 0;
            PC6 = 1;
        }
        else if (PC6)
        {
            PC6 = 0;
            PC7 = 1;
        }
        else if (PC7)
        {
            PC7 = 0;
            PC4 = 1;
        }
    }
    else if (!PE6)
    {
        PE6 = 1;
        PE0 = 0;
        if (PC4)
        {
            PC4 = 0;
            PC5 = 1;
        }
        else if (PC5)
        {
            PC5 = 0;
            PC6 = 1;
        }
        else if (PC6)
        {
            PC6 = 0;
            PC7 = 1;
        }
        else if (PC7)
        {
            PC7 = 0;
            PC4 = 1;
        }
    }
}
void right()
{
    if (!PE2)
    {
        PE2 = 1;
        PE4 = 0;
    }
    else if (!PE6)
    {
        PE6 = 1;
        PE0 = 0;
    }
    else if (!PE5)
    {
        PE5 = 1;
        PE0 = 0;
    }
    else if (!PE7)
    {
        PE7 = 1;
        PE4 = 0;
    }
    else if (!PE3)
    {
        PE3 = 1;
        PE4 = 0;
    }
    else if (!PE4)
    {
        PE4 = 1;
        PE2 = 0;
        if (PC4)
        {
            PC4 = 0;
            PC7 = 1;
        }
        else if (PC5)
        {
            PC5 = 0;
            PC4 = 1;
        }
        else if (PC6)
        {
            PC6 = 0;
            PC5 = 1;
        }
        else if (PC7)
        {
            PC7 = 0;
            PC6 = 1;
        }
    }
    else if (!PE0)
    {
        PE0 = 1;
        PE6 = 0;
        if (PC4)
        {
            PC4 = 0;
            PC7 = 1;
        }
        else if (PC5)
        {
            PC5 = 0;
            PC4 = 1;
        }
        else if (PC6)
        {
            PC6 = 0;
            PC5 = 1;
        }
        else if (PC7)
        {
            PC7 = 0;
            PC6 = 1;
        }
    }
}
void up()
{
    if (!PE4)
    {
        PE4 = 1;
        PE3 = 0;
    }
    else if (!PE0)
    {
        PE0 = 1;
        PE4 = 0;
    }
    else if (!PE5)
    {
        PE5 = 1;
        PE7 = 0;
    }
    else if (!PE7)
    {
        PE7 = 1;
        PE3 = 0;
    }
    else if (!PE6)
    {
        PE6 = 1;
        PE2 = 0;
    }
    else if (!PE2)
    {
        PE2 = 1;
        PE3 = 0;
    }
    else if (!PE3)
    {
        PE3 = 1;
        PE5 = 0;
    }
}
void down()
{
    if (!PE4)
    {
        PE4 = 1;
        PE0 = 0;
    }
    else if (!PE0)
    {
        PE0 = 1;
        PE5 = 0;
    }
    else if (!PE3)
    {
        PE3 = 1;
        PE7 = 0;
    }
    else if (!PE7)
    {
        PE7 = 1;
        PE5 = 0;
    }
    else if (!PE6)
    {
        PE6 = 1;
        PE5 = 0;
    }
    else if (!PE2)
    {
        PE2 = 1;
        PE6 = 0;
    }
    else if (!PE5)
    {
        PE5 = 1;
        PE3 = 0;
    }
}

int main(void)
{
    uint16_t i = 0;

    SYS_Init();

    OpenSevenSegment();
    OpenKeyPad();
    PC4 = 0;
    PC5 = 0;
    PC6 = 0;
    PC7 = 0;
    PC4 = 1;
    PE0 = 0;

    while (1)
    {
        i = ScanKey();
        if (i == 2 || i == 4 || i == 8 || i == 6)
        {
            CLK_SysTickDelay(1000000);
            if (i == 2)
            {
                up();
            }
            else if (i == 4)
            {
                left();
            }
            else if (i == 8)
            {
                down();
            }
            else if (i == 6)
            {
                right();
            }
        }
    }
}