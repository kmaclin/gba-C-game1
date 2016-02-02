//Kelsey Maclin
#include <stdio.h>

#define REG_DISPCTL *(unsigned short *)0x4000000
#define BG2_ENABLE (1<<10)
#define MODE3 3

typedef unsigned short u16;
extern u16 *videoBuffer;

#define OFFSET(row, col, rLength) ((row)*(rLength)+(col))
#define RGB(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED RGB(31,0,0)
#define GREEN RGB(0, 31,0)
#define BLUE RGB(0, 0, 31)
#define CYAN RGB(0, 31, 31)
#define MAGENTA RGB(31, 0, 31)
#define YELLOW RGB(31, 31, 0)
#define WHITE RGB(31, 31, 31)
#define BLACK RGB(0, 0, 0)


#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define BUTTONS *(volatile unsigned int *)0x4000130

#define A		(1<<0)
#define B		(1<<1)
#define SELECT	(1<<2)
#define START	(1<<3)
#define RIGHT	(1<<4)
#define LEFT	(1<<5)
#define UP		(1<<6)
#define DOWN	(1<<7)
#define R		(1<<8)
#define L		(1<<9)


#define SCANLINECOUNTER *(volatile u16 *)0x4000006



void setPixel(int row, int col, u16 color);
void drawRect(int row, int col, int height, int width, u16 color);
void drawHollowRect(int row, int col, int height, int width, u16 color);
void plotLine(int y0, int x0, int y1, int x1, u16 color);
void waitForVblank();
void delay(int n);