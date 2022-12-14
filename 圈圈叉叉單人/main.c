//
// LCD_Bmp : display Logo Bitmap on LCD
//
// Bitmap Creation:
// Step 1. use Paint to draw 128x64 bitmap 
// Step 2. use bmp2asm to convert bitmap into hex
// Step 3. cut hex code paste into char array Bitmap[128*8]
// Step 4. build & download code to learning board, then bitmap will be displayed on LCD
//
#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"

unsigned char cross[32] = {
0x06, 0x0f, 0x1f, 0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x0f, 0x06, 
0x60, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x1f, 0x3e, 0x7c, 0xf8, 0xf0, 0x60
};

unsigned char circle[32] = {
0xe0, 0xf8, 0x1c, 0x0e, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x0e, 0x1c, 0xf8, 0xe0, 
0x07, 0x1f, 0x38, 0x70, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x60, 0x70, 0x38, 0x1f, 0x07
};

unsigned char mapleft[1024] = {
// 'pngwing', 64x64px
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 

0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,



};
unsigned char mapright[1024] = {
// 'pngwing', 64x64px
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,

0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
};


unsigned char o[] = {
0x00,0xC0,0xE0,0xF0,0xF8,0xF8,0xF8,0x7C,0x7C,0xFC,0xFC,0xFC,0xF8,0xF0,0x00,0x00,
0x00,0x07,0x1F,0x3F,0x3F,0x7F,0x7C,0x7C,0x7E,0x3F,0x3F,0x1F,0x1F,0x07,0x00,0x00
};

unsigned char x[] = {
0x00,0x00,0x38,0x7C,0xFC,0xFC,0xF8,0xF0,0xF0,0xF0,0xF8,0xFC,0xFC,0x7C,0x38,0x00,
0x00,0x00,0x30,0x7C,0x7E,0x7F,0x7F,0x1F,0x1F,0x1F,0x7F,0x7F,0x7E,0x7C,0x00,0x00
};


void rgb(int i)
{
	if(i%3==0)
	{
		PA12 = 0; PA13 = 1; PA14 = 1;
	}
	else if(i%3==1)
	{
		PA12 = 1; PA13 = 0; PA14 = 1;
	}
	else
	{
		PA12 = 1; PA13 = 1; PA14 = 0;
	}
}

int checkwin(int* square){
	if (square[0] != 0 && square[0] == square[1] && square[1] == square[2])
			return 1;
			
	else if (square[3] != 0 && square[3] == square[4] && square[4] == square[5])
			return 1;
			
	else if (square[6] != 0 && square[6] == square[7] && square[7] == square[8])
			return 1;
			
	else if (square[0] != 0 && square[0] == square[3] && square[3] == square[6])
			return 1;
			
	else if (square[1] != 0 && square[1] == square[4] && square[4] == square[7])
			return 1;
			
	else if (square[2] != 0 && square[2] == square[5] && square[5] == square[8])
			return 1;
			
	else if (square[0] != 0 && square[0] == square[4] && square[4] == square[8])
			return 1;
			
	else if (square[2] != 0 && square[2] == square[4] && square[4] == square[6])
			return 1;
			
	else if (square[0] != 0 && square[1] != 0 && square[2] != 0 &&
			square[3] != 0 && square[4] != 0 && square[5] != 0 && square[6] 
			!= 0 && square[7] != 0 && square[8] != 0)

			return 0;
	else
			return  - 1;
}

int main(void)
{
	
	while(1) {
		int i = 0;
		int j = 0;
		int flag[9] = {0};
		int square[9] = {0};
		int f = 0;
		int temp;
		SYS_Init();	  
		init_LCD();
		clear_LCD();
		
		PD14 = 0;
		draw_Bmp64x64(0,0,FG_COLOR,BG_COLOR,mapleft);
		draw_Bmp64x64(64,0,FG_COLOR,BG_COLOR,mapright);
		while(1) {
			if (checkwin(square) >= 0) {
				break;
			}
			
			i = ScanKey();
			while(i == 0){
				i = ScanKey();
			}
			temp = i;
			while(i != 0) {
				i = ScanKey();
			}
			
			if (!flag[temp-1]) {
				switch(temp) {
					case 1:
						draw_Bmp16x16(0,0,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[0] = 1;
						square[0] = f?1:2;
						break;
					case 2:
						draw_Bmp16x16(16,0,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[1] = 1;
						square[1] = f?1:2;
						break;
					case 3:
						draw_Bmp16x16(32,0,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[2] = 1;
						square[2] = f?1:2;
						break;
					case 4:
						draw_Bmp16x16(0,16,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[3] = 1;
						square[3] = f?1:2;
						break;
					case 5:
						draw_Bmp16x16(16,16,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[4] = 1;
					square[4] = f?1:2;
						break;
					case 6:
						draw_Bmp16x16(32,16,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[5] = 1;
					square[5] = f?1:2;
						break;
					case 7:
						draw_Bmp16x16(0,32,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[6] = 1;
					square[6] = f?1:2;
						break;
					case 8:
						draw_Bmp16x16(16,32,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[7] = 1;
					square[7] = f?1:2;
						break;
					case 9:
						draw_Bmp16x16(32,32,FG_COLOR,BG_COLOR,f?o:x);
						f=!f;
						flag[8] = 1;
					square[8] = f?1:2;
						break;
					default:
						break;
				}
				PB11 = 0;
				CLK_SysTickDelay(500000);
				PB11 = 1;
				CLK_SysTickDelay(500000);
			} else {
				PC12 = 0;
				CLK_SysTickDelay(500000);
				PC12 = 1;
				PC13 = 0;
				CLK_SysTickDelay(500000);
				PC13 = 1;
				PC14 = 0;
				CLK_SysTickDelay(500000);
				PC14 = 1;
				PC15 = 0;
				CLK_SysTickDelay(500000);
				PC15 = 1;
				PC12 = 0;
				CLK_SysTickDelay(500000);
				PC12 = 1;
				PC13 = 0;
				CLK_SysTickDelay(500000);
				PC13 = 1;
				PC14 = 0;
				CLK_SysTickDelay(500000);
				PC14 = 1;
				PC15 = 0;
				CLK_SysTickDelay(500000);
				PC15 = 1;
			}
			
			
			
			
		}
		if(!checkwin(square)){
			print_Line(3, "Tie");
			rgb(0);
		} else {
			if(f) {
					print_Line(3, "X Win");
				rgb(2);
			} else {
					print_Line(3, "O Win");
				rgb(1);
			}
		}
		PB11 = 0;
		CLK_SysTickDelay(1000000);
		while(1) {
			if(ScanKey()) {
				PB11 = 1;
				CLK_SysTickDelay(1000000);
				break;
			}
		}
		
	}
	
}
