//
// LCD_Bmp_Keypad: use 3x3 keypad to move bitmap on LCD
//
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"

unsigned char bmp16x16[32] = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
    0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF};

void Buzz(void)
{
    PB11 = 0;
    CLK_SysTickDelay(1000000);
    PB11 = 1;
    CLK_SysTickDelay(1000000);
}

int main(void)
{
    int8_t x = 0, y = 0, k = 0, s = 0;
    int8_t keyin = 0;

    SYS_Init();
    init_LCD();
    clear_LCD();
    OpenKeyPad();
    PD14 = 0;
    x = 64;
    y = 32;
    draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, bmp16x16);
    CLK_SysTickDelay(1000000);

    while (1)
    {
        keyin = ScanKey();
        if (keyin == 5)
        {
            if (k == 5)
            {
                k = s;
            }
            else
            {
                s = k;
                k = 5;
            }
        }
        else if (keyin == 6)
        {
            x += 3;
            k = 6;
        }
        else if (keyin == 4)
        {
            x -= 3;
            k = 4;
        }
        else if (keyin == 8)
        {
            y += 3;
            k = 8;
        }
        else if (keyin == 2)
        {
            y -= 3;
            k = 2;
        }
        else
        {
            if (k == 5)
            {
            }
            else if (k == 6)
            {
                x += 3;
                k = 6;
            }
            else if (k == 4)
            {
                x -= 3;
                k = 4;
            }
            else if (k == 8)
            {
                y += 3;
                k = 8;
            }
            else if (k == 2)
            {
                y -= 3;
                k = 2;
            }
            else
            {
                continue;
            }
        }
        if (x > 112)
        {
            k = 4;
            Buzz();
            continue;
        }
        else if (x < 0)
        {
            k = 6;
            Buzz();
            continue;
        }
        if (y > 47)
        {
            k = 2;
            Buzz();
            continue;
        }
        else if (y < 0)
        {
            k = 8;
            Buzz();
            continue;
        }
        clear_LCD();
        draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, bmp16x16);
        CLK_SysTickDelay(1000000);
    }
}