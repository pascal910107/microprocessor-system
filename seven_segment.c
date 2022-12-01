#include <stdio.h>
#include "NUC100Series.h"
#include "GPIO.h"
#include "SYS.h"
#include "Seven_Segment.h"
#define SEG_N0 0x82
#define SEG_N1 0xEE
#define SEG_N2 0x07
#define SEG_N3 0x46
#define SEG_N4 0x6A
#define SEG_N5 0x52
#define SEG_N6 0x12
#define SEG_N7 0xE6
#define SEG_N8 0x02
#define SEG_N9 0x62
#define SEG_N10 0x22
#define SEG_N11 0x1A
#define SEG_N12 0x93
#define SEG_N13 0x0E
#define SEG_N14 0x13
#define SEG_N15 0x33

uint8_t SEG_BUF[16] = {SEG_N0, SEG_N1, SEG_N2, SEG_N3, SEG_N4, SEG_N5, SEG_N6, SEG_N7, SEG_N8, SEG_N9, SEG_N10, SEG_N11, SEG_N12, SEG_N13, SEG_N14, SEG_N15};
void OpenSevenSegment(void)
{
    GPIO_SetMode(PC, BIT4, GPIO_PMD_OUTPUT);
    GPIO_SetMode(PC, BIT5, GPIO_PMD_OUTPUT);
    GPIO_SetMode(PC, BIT6, GPIO_PMD_OUTPUT);
    GPIO_SetMode(PC, BIT7, GPIO_PMD_OUTPUT);
    PC4 = 0;
    PC5 = 0;
    PC6 = 0;
    PC7 = 0;
    GPIO_SetMode(PE, BIT0, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT1, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT2, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT3, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT4, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT5, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT6, GPIO_PMD_QUASI);
    GPIO_SetMode(PE, BIT7, GPIO_PMD_QUASI);
    PE0 = 1;
    PE1 = 1;
    PE2 = 1;
    PE3 = 1;
    PE4 = 1;
    PE5 = 1;
    PE6 = 1;
    PE7 = 1;
}

void CloseSevenSegment(void)
{
    PC4 = 0;
    PC5 = 0;
    PC6 = 0;
    PC7 = 0;
}
