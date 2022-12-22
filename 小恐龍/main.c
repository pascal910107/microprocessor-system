
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
unsigned char bmp16x16[32] = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
    0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF};
unsigned char dinosaur[32] = {
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xFE, 0xFE, 0x3E, 0x0E, 0x0E, 0x0E, 0x00,
    0x00, 0x03, 0x07, 0x0E, 0x1E, 0x3F, 0x1F, 0x1F, 0x3F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char dinosaur_down[] = {
    0x02, 0x06, 0x0C, 0x1C, 0x3E, 0x1E, 0x3E, 0x1E, 0x3E, 0x0C, 0x0E, 0x1C, 0x1E, 0x0E, 0x0E, 0x06};

unsigned char one[] = {
    0xF7, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFE, 0x7F,
    0x00, 0x03, 0x0F, 0x0E, 0x0C, 0x18, 0x18, 0xFF, 0x3F, 0x18, 0x18, 0x08, 0x0C, 0x07, 0x01, 0x00};

unsigned char two1[] = {
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3C, 0xF3, 0xCE, 0x3C, 0x00, 0x00, 0x00, 0xE0, 0xFF,
    0x2E, 0x7F, 0x7E, 0x70, 0xE0, 0xE0, 0xFF, 0xC0, 0xFF, 0xEF, 0x70, 0x78, 0x3C, 0x1F, 0x0F, 0x0E};
unsigned char two2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char three[] = {
    0xF0, 0xF8, 0xFC, 0xDC, 0xDE, 0xFF, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xDF, 0x3F, 0x1F, 0x0F, 0x06, 0x04, 0x06, 0x06, 0x06, 0x04};
void init()
{
    PC4 = PC5 = PC6 = PC7 = 0;
    PE0 = PE7 = PE2 = PE3 = PE4 = PE5 = PE6 = 1;
}
void Show(uint16_t x)
{
    if (x < 10)
    {
    }
    else if (x > 9 && x < 100)
    {
        Show(x % 10);
				init();
        PC5 = 1;
        x = x / 10;
    }
    else if (x > 99 && x < 1000)
    {

        Show(x % 10);
				init();
        PC5 = 1;
        x = x / 10;
        Show(x % 10);
				init();
        PC6 = 1;
        x = x / 10;
    }
    else if (x > 999 && x < 10000)
    {
        Show(x % 10);
				init();
        PC5 = 1;
        x = x / 10;
        Show(x % 10);
				init();
        PC6 = 1;
        x = x / 10;
        Show(x % 10);
				init();
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
    CLK_SysTickDelay(5000);
		//init();
}
int judge(int x, int y, int oby_top, int oby_down)
{
    if (x >= 12 && x <= 28)
    {
        if (y <= oby_top && y > oby_down)
        {
            return 1;
        }
        return 0;
    }
    return 0;
}
void showSeven(int obstacle)
{
    int j;
    if (obstacle >= 10)
    {
        int j = 10;
    }
    else
    {
        j = 30;
    }
    init();
    while (j--)
    {
        PC4 = 1;
        Show(obstacle);
				if (obstacle >= 10)
				{
						init();
				}
        
    }
}
int randomObstacle(int n, int dnum, int y, int obstacle)
{
    int j = 0;
    if (n == 0)
    {
        j = judge(90 - dnum, y, 16, 0) || judge(107 - dnum, y, 16, 0);
        draw_Bmp16x16(90 - dnum, 48, FG_COLOR, BG_COLOR, one);
        draw_Bmp16x16(107 - dnum, 48, FG_COLOR, BG_COLOR, one);
    }
    else if (n == 1)
    {
        j = judge(100 - dnum, y, 24, 8);
        draw_Bmp16x16(100 - dnum, 40, FG_COLOR, BG_COLOR, three);
    }
    else if (n == 2)
    {
        j = judge(100 - dnum, y, 24, 16) || judge(100 - dnum, y, 16, 0);
        draw_Bmp16x16(100 - dnum, 40, FG_COLOR, BG_COLOR, two1);
        draw_Bmp16x16(100 - dnum, 48, FG_COLOR, BG_COLOR, two2);
    }
    else if (n == 3)
    {
        j = judge(90 - dnum, y, 16, 0) || judge(100 - dnum, y, 24, 16) || judge(100 - dnum, y, 16, 0);
        draw_Bmp16x16(90 - dnum, 48, FG_COLOR, BG_COLOR, one);
        draw_Bmp16x16(100 - dnum, 40, FG_COLOR, BG_COLOR, two1);
        draw_Bmp16x16(100 - dnum, 48, FG_COLOR, BG_COLOR, two2);
    }
    else if (n == 4)
    {
        j = judge(100 - dnum, y, 24, 8) || judge(85 - dnum, y, 24, 16) || judge(85 - dnum, y, 16, 0);
        draw_Bmp16x16(85 - dnum, 40, FG_COLOR, BG_COLOR, two1);
        draw_Bmp16x16(85 - dnum, 48, FG_COLOR, BG_COLOR, two2);
        draw_Bmp16x16(100 - dnum, 40, FG_COLOR, BG_COLOR, three);
    }
    else if (n == 5)
    {
        j = judge(100 - dnum, y, 28, 12);
        draw_Bmp16x16(100 - dnum, 36, FG_COLOR, BG_COLOR, three);
    }
    else if (n == 6)
    {
        j = judge(90 - dnum, y, 16, 0) || judge(107 - dnum, y, 28, 12);
        draw_Bmp16x16(90 - dnum, 48, FG_COLOR, BG_COLOR, one);
        draw_Bmp16x16(107 - dnum, 36, FG_COLOR, BG_COLOR, three);
    }
    return j;
}

int jump(int n, int dnum, int obstacle)
{
    int y = 48;
    while (1)
    {
        showSeven(obstacle);
        clear_LCD();
        if (y <= 4)
        {
            break;
        }
        draw_Bmp16x16(12, y, FG_COLOR, BG_COLOR, dinosaur);
        y -= 12;
        if (randomObstacle(n, dnum, 64 - y, obstacle))
        {
            return -1;
        }
        dnum += 8;
    }
    while (1)
    {
        showSeven(obstacle);
        clear_LCD();
        if (y >= 48)
        {
            return dnum;
        }
        y += 6;
        draw_Bmp16x16(12, y, FG_COLOR, BG_COLOR, dinosaur);
        if (randomObstacle(n, dnum, 64 - y, obstacle))
        {
            return -1;
        }
        dnum += 8;
    }
}

void showLED(int num)
{
    PC12 = 1;
    PC13 = 1;
    PC14 = 1;
    PC15 = 1;
    if (num == 4)
    {
        PC12 = 0;
        PC13 = 0;
        PC14 = 0;
        PC15 = 0;
    }
    else if (num == 3)
    {
        PC13 = 0;
        PC14 = 0;
        PC15 = 0;
    }
    else if (num == 2)
    {
        PC14 = 0;
        PC15 = 0;
    }
    else if (num == 1)
    {
        PC15 = 0;
    }
}

int32_t main(void)
{
    uint32_t y, z;
    int n = 0, dnum = 0, i = 4, obstacle = 0;
    SYS_Init();
    init_LCD();
    Init_ADC();
    clear_LCD();
    OpenSevenSegment();
    GPIO_SetMode(PB, BIT0, GPIO_MODE_QUASI);
    PB0 = 1;
    ADC_START_CONV(ADC);

    PD14 = 0;

    for (i = 4; i > 0; i--)
    {
        showSeven(obstacle);
        n = 0, dnum = 0;
        clear_LCD();
        showLED(i);
        while (1)
        {
            y = ADC_GET_CONVERSION_DATA(ADC, 1);
            if (dnum >= 110)
            {
                dnum = 0;
                n = (n + 8) % 7;
                obstacle++;
            }
            if (y < 2000)
            {
                dnum = jump(n, dnum, obstacle);
                if (dnum == -1)
                {
                    break;
                }
            }
            else if (y > 4000)
            {
                clear_LCD();
                draw_Bmp16x8(12, 56, FG_COLOR, BG_COLOR, dinosaur_down);
                if (randomObstacle(n, dnum, 8, obstacle))
                {
                    break;
                }

                dnum += 8;
                showSeven(obstacle);
            }
            else
            {
                clear_LCD();
                draw_Bmp16x16(12, 48, FG_COLOR, BG_COLOR, dinosaur);
                if (randomObstacle(n, dnum, 16, obstacle))
                {
                    break;
                }
                dnum += 8;
                showSeven(obstacle);
            }
        }
    }
    showLED(0);
}