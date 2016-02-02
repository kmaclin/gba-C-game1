//Kelsey Maclin

#include "mylib.h"
#include "text.h"
#include <stdio.h>

//create enemy struct
typedef struct  
{
	volatile int r;
	volatile int c;
	volatile int oldR;
	volatile int oldC;
	volatile int check;

} Enemy;

//creat main player struct
typedef struct  
{
	volatile int r;
	volatile int c;
	volatile int oldR;
	volatile int oldC;
	volatile int check;

} Hero;

//create coin struct
typedef struct
{
	int r;
	int c;
	int collected;
}Coin;

//prototypes
int inbounds(int r, int c);
int inbounds2(int r, int c);
int isColliding(Enemy enemy, Hero hero);
void drawCoins(Coin coins[], int size);
int allCollected(Coin coins[], int size);
int isCoinColliding(Coin coin, Hero hero);
Enemy sideTosideMovement(Enemy red);
Enemy upDownMovement(Enemy red);
Enemy upDownMovementWithBounds(Enemy red, int boundR);
Enemy upDownMovementWithBounds2(Enemy red, int boundR);
Enemy upDownMovement2(Enemy red);
Enemy sideTosideMovement2(Enemy red);


void intro() {
	//intro/rules to game
	drawString(30,	30, "Welcome to my game", BLUE);
	delay(50);
	drawString(30,	30, "Welcome to my game", BLACK);
	delay(50);
	drawString(40,	40, "Here are the rules:", BLUE);
	delay(50);
	drawString(50,	50, "You are the blue square", RED);
	delay(50);
	drawString(60,	50, "Gather the yellow, square coins",RED);
	delay(50);
	drawString(70,	50, "Avoid the red squares", RED);
	delay(50);
	drawString(80,	50, "Use the arrow keys to move.", RED);
	delay(50);
	drawString(90,	50, "Clear the level by collecting", RED);
	drawString(100,	50, "all of the coins.", RED);
	delay(50);
	drawString(110,	50, "Good Luck.", RED);

	while(!KEY_DOWN_NOW(A)) 
	{
		drawRect(140, 220, 10, 10, WHITE);
		delay(20);
		drawRect(140, 220, 10, 10, BLACK);
		delay(20);
		drawString(140,	50, "hold A (Z) to start", BLUE);
		delay(10);
	}
	for (int i = 0; i < 240; i++) {
		for(int j = 0; j < 160; j ++) {
			setPixel(j,i, RGB(0,0,0));
		}
	}
}

void part2() {
	//draws level
	drawRect(10, 100, 100, 100, GREEN);
	drawHollowRect(9, 99, 100, 101, CYAN);
	drawRect(111, 30, 180, 30, GREEN);
	drawHollowRect(110, 29, 180, 31, CYAN);
	waitForVblank();
	drawRect(110, 100, 99, 1, GREEN);
	delay(30);

	//initialize hero

	Hero blue;
	blue.r = 123;
	blue.c = 30;
	blue.check = 1;
	int origR = 123;
	int origC = 30;
	blue.oldR = blue.r;
	blue.oldC = blue.c;

	u16 color = GREEN;

	//initialize enemies
	Enemy red1, red2, red3, red4, red5, red6, red7; 
	Enemy red8, red9, red10, red11, red12, red13;
	red1.r = 111;
	red1.c = 60;
	red1.check = 1;
	red1.oldR = 111;
	red1.oldC = 60;
	

	red2.r = 113;
	red2.c = 203;
	red2.check = 1;
	red2.oldR = 113;
	red2.oldC = 203;
	
	red3.r = 132;
	red3.c = 30;
	red3.check = 0;
	red3.oldR = 132;
	red3.oldC = 30;


	red4.r = 11;
	red4.c = 100;
	red4.check = 1;
	red4.oldR = 11;
	red4.oldC = 100;

	red5.r = 105;
	red5.c = 109;
	red5.check = 0;
	red5.oldR = 105;
	red5.oldC = 109;

	red6.r = 11;
	red6.c = 118;
	red6.check = 1;
	red6.oldR = 11;
	red6.oldC = 118;

	red7.r = 105;
	red7.c = 127;
	red7.check = 0;
	red7.oldR = 105;
	red7.oldC = 127;

	red8.r = 11;
	red8.c = 136;
	red8.check = 1;
	red8.oldR = 11;
	red8.oldC = 136;

	red9.r = 105;
	red9.c = 145;
	red9.check = 0;
	red9.oldR = 105;
	red9.oldC = 145;

	red10.r = 11;
	red10.c = 154;
	red10.check = 1;
	red10.oldR = 11;
	red10.oldC = 154;

	red11.r = 105;
	red11.c = 163;
	red11.check = 0;
	red11.oldR = 105;
	red11.oldC = 163;

	red12.r = 11;
	red12.c = 172;
	red12.check = 1;
	red12.oldR = 11;
	red12.oldC = 172;

	red13.r = 105;
	red13.c = 181;
	red13.check = 0;
	red13.oldR = 105;
	red13.oldC = 181;

	//initialized coins

	Coin coin1, coin2, coin3, coin4, coin5, coin6, coin7;

	coin1.r = 11;
	coin1.c = 115;
	coin1.collected = 0;

	coin2.r = 54;
	coin2.c = 150;
	coin2.collected = 0;

	coin3.r = 90;
	coin3.c = 178;
	coin3.collected = 0;

	coin4.r = 27;
	coin4.c = 133;
	coin4.collected = 0;

	coin5.r = 119;
	coin5.c = 68;
	coin5.collected = 0;

	coin6.r = 118;
	coin6.c = 203;
	coin6.collected = 0;

	coin7.r = 129;
	coin7.c = 203;
	coin7.collected = 0;
	//coins in array of Coin
	Coin coins[7];
	coins[0] = coin1;
	coins[1] = coin2;
	coins[2] = coin3;
	coins[3] = coin4;
	coins[4] = coin5;
	coins[5] = coin6;
	coins[6] = coin7;

	int count = 0;

	drawCoins(coins, 7);
	while(1) {
		//check if colliding with an enemy
		blue.oldR = blue.r;
		blue.oldC = blue.c;

		if (isColliding(red1, blue) || isColliding(red2, blue) || isColliding(red3, blue))
		{
			blue.oldR = blue.r;
			blue.oldC = blue.c;
			blue.r = origR;
			blue.c = origC;
			drawRect(blue.oldR, blue.oldC, 5, 5, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			drawRect(blue.r, blue.c, 5, 5, color);
			drawCoins(coins, 7);
		}

		if (isColliding(red4, blue) || isColliding(red5, blue) || isColliding(red6, blue))
		{
			blue.oldR = blue.r;
			blue.oldC = blue.c;
			blue.r = origR;
			blue.c = origC;
			drawRect(blue.oldR, blue.oldC, 5, 5, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			drawRect(blue.r, blue.c, 5, 5, color);
			drawCoins(coins, 7);
		}

		if (isColliding(red7, blue) || isColliding(red8, blue) || isColliding(red9, blue))
		{
			blue.oldR = blue.r;
			blue.oldC = blue.c;
			blue.r = origR;
			blue.c = origC;
			drawRect(blue.oldR, blue.oldC, 5, 5, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			drawRect(blue.r, blue.c, 5, 5, color);
			drawCoins(coins, 7);
		}

		if (isColliding(red10, blue) || isColliding(red11, blue) || isColliding(red12, blue) || isColliding(red13, blue))
		{
			blue.oldR = blue.r;
			blue.oldC = blue.c;
			blue.r = origR;
			blue.c = origC;
			drawRect(blue.oldR, blue.oldC, 5, 5, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			drawRect(blue.r, blue.c, 5, 5, color);
			drawCoins(coins, 7);
		}

		//dealing with coin collisions
		if (isCoinColliding(coin1, blue))
		{
			drawRect(coin1.r, coin1.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin1.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin2, blue))
		{
			drawRect(coin2.r, coin2.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin2.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin3, blue))
		{
			drawRect(coin3.r, coin3.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin3.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin4, blue))
		{
			drawRect(coin4.r, coin4.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin4.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin5, blue))
		{
			drawRect(coin5.r, coin5.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin5.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin6, blue))
		{
			drawRect(coin6.r, coin6.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin6.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin7, blue))
		{
			drawRect(coin7.r, coin7.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin7.collected = 1;
			count = count + 1;
		}

		//player movement
		if(KEY_DOWN_NOW(UP)) 
		{
			int r = blue.r - 1;
			int c = blue.c;
			if(inbounds(r,c)) 
			{
				blue.r = r;
			}	
		}
		if(KEY_DOWN_NOW(LEFT)) 
		{
			int r = blue.r;
			int c = blue.c - 1;
			if(inbounds(r,c)) 
			{
				blue.c = c;
			}
		}
		if(KEY_DOWN_NOW(DOWN)) 
		{
			int r = blue.r + 5;
			int c = blue.c;
			if(inbounds(r,c)) 
			{
				blue.r = blue.r + 1;
			}
		}
		if(KEY_DOWN_NOW(RIGHT)) 
		{
			int r = blue.r;
			int c = blue.c + 5;
			if(inbounds(r,c)) 
			{
				blue.c = blue.c + 1;
			}
		}


		//enemy movements


		Enemy red1rev = upDownMovement(red1);
		red1 = red1rev;
		Enemy red2rev = sideTosideMovement(red2);
		red2 = red2rev;
		Enemy red3rev = sideTosideMovement(red3);
		red3 = red3rev;
		Enemy red4rev = upDownMovementWithBounds(red4,105);
		red4 = red4rev;
		Enemy red5rev = upDownMovementWithBounds(red5,105);
		red5 = red5rev;
		Enemy red6rev = upDownMovementWithBounds(red6,105);
		red6 = red6rev;
		Enemy red7rev = upDownMovementWithBounds(red7, 105);
		red7 = red7rev;
		Enemy red8rev = upDownMovementWithBounds(red8, 105);
		red8 = red8rev;
		Enemy red9rev = upDownMovementWithBounds(red9, 105);
		red9 = red9rev;
		Enemy red10rev= upDownMovementWithBounds(red10, 105);
		red10= red10rev;
		Enemy red11rev= upDownMovementWithBounds(red11, 105);
		red11= red11rev;
		Enemy red12rev= upDownMovementWithBounds(red12, 105);
		red12= red12rev;
		Enemy red13rev = upDownMovementWithBounds(red13, 105);
		red13 = red13rev;

		//coins
		coins[0] = coin1;
		coins[1] = coin2;
		coins[2] = coin3;
		coins[3] = coin4;
		coins[4] = coin5;
		coins[5] = coin6;
		coins[6] = coin7;

		//ends loop if all coins are collected
		if (allCollected(coins, 7))
		{
			break;
		}

	
		//prepare for next loop
		waitForVblank();
		drawRect(blue.oldR, blue.oldC, 5, 5, color);
		drawRect(blue.r, blue.c, 5, 5, BLUE);
		blue.oldR = blue.r;
		blue.oldC = blue.c;
	}
	delay(50);
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			videoBuffer[OFFSET(j, i, 240)] = BLACK;
		}
	}
	delay(50);
	drawString(0, 0, "You collected all of the coins!", MAGENTA);
	delay(70);
	drawString(10, 0, "You won the game!", MAGENTA);
	delay(50);
	drawString(20, 0, "Thanks for playing", MAGENTA);
	delay(60);
	drawString(30, 0, "Game by: Kelsey Maclin", MAGENTA);
	delay(60);
	//close window to end the game
	while(1);
}
//checks if all coins have been collected
int allCollected(Coin coins[], int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (coins[i].collected == 1)
		{
			count++;
		}
	}
	return count == size;
}
//draws coins on level
void drawCoins(Coin coins[], int size) 
{
	for (int i = 0; i < size; i++)
	{
		drawRect(coins[i].r, coins[i].c, 3, 3, YELLOW);
	}
}
//enemy movement up and down
Enemy upDownMovement(Enemy red)
{
	int red_up, red_down;
	red_up = red.r - 1;
	red_down = red.r + 5;

	if (inbounds(red_down, red.c) && red.check) 
	{
		red.r = red.r + 1;
	} 
	else if (!inbounds(red_down, red.c) && red.check) 
	{
		red.check = 0;
		red.r = red.r - 1;
	}
	else if (inbounds(red_up, red.c) && !red.check) 
	{
		red.r = red.r - 1;
	}
	else if (!inbounds(red_up, red.c) && !red.check) 
	{
		red.check = 1;
		red.r = red.r + 1;
	}
	drawRect(red.oldR, red.oldC, 5, 5, GREEN);
	drawRect(red.r, red.c, 5, 5, RED);
	red.oldR = red.r;
	return red;
}
//enemy movement right to left
Enemy sideTosideMovement(Enemy red)
{
	
	int red_left, red_right;
		red_left = red.c - 2;
		red_right = red.c + 6;

	if (inbounds(red.r, red_left) && red.check) 
	{
		red.c = red_left;
	} 
	else if (!inbounds(red.r, red_left) && red.check) 
	{
		red.check = 0;
		red.c = red.c + 2;
	}
	else if (inbounds(red.r, red_right) && !red.check) 
	{
		red.c = red.c + 2;
	}
	else if (!inbounds(red.r, red_right) && !red.check) 
	{
		red.check = 1;
		red.c = red_left;
	}
	drawRect(red.oldR, red.oldC, 5, 5, GREEN);
	drawRect(red.r, red.c, 5, 5, RED);
	red.oldC = red.c;
	return red;
}
//enemy movement up and down with another bound on the rows
Enemy upDownMovementWithBounds(Enemy red, int boundR)
{
	int red_up, red_down;
	red_up = red.r - 2;
	red_down = red.r + 6;

	if ((inbounds(red_down, red.c) && red_down <= boundR) && red.check) 
	{
		red.r = red.r + 2;
	} 
	else if(!(inbounds(red_down, red.c) && red_down <= boundR) && red.check) 
	{
		red.check = 0;
		red.r = red.r - 2;
	}
	else if ((inbounds(red_up, red.c) && red_up <= boundR) && !red.check) 
	{
		red.r = red.r - 2;
	}
	else if (!(inbounds(red_up, red.c) && red_up <= boundR) && !red.check) 
	{
		red.check = 1;
		red.r = red.r + 2;
	}
	drawRect(red.oldR, red.oldC, 5, 5, GREEN);
	drawRect(red.r, red.c, 5, 5, RED);
	red.oldR = red.r;
	return red;
}
//checks for enemy collision
int isColliding(Enemy enemy, Hero hero) 
{
	if ((hero.r + 4) < enemy.r)
	{
		return 0;
	}
	if ((enemy.r + 4) < hero.r)
	{
		return 0;
	}
	if (hero.c > (enemy.c + 4))
	{
		return 0;
	}
	if (enemy.c > (hero.c + 4))
	{
		return 0;
	}
	
	return 1;
}
//checks for a player collision with a coin
int isCoinColliding(Coin coin, Hero hero) 
{
	if ((hero.r + 4) < coin.r)
	{
		return 0;
	}
	if ((coin.r + 2) < hero.r)
	{
		return 0;
	}
	if (hero.c > (coin.c + 2))
	{
		return 0;
	}
	if (coin.c > (hero.c + 4))
	{
		return 0;
	}
	
	return 1;
}
//checks if point is within level boundaries
int inbounds(int r, int c) {
	if ((r >= 10 && r <= 110) && (c >= 100 && c <= 198))
	{
		return 1;
	}
	else if ((r >= 111 && r <= 140) && (c >= 30 && c <= 208))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

//called part2, but is actually part
void part1() 
{
	//draws level
	drawRect(20, 60, 120, 120, GREEN);
	drawHollowRect(19, 59, 121, 121, CYAN);
	//initializes player
	Hero blue;
	blue.r = 61;
	blue.c = 61;
	blue.check = 1;
	int origR = 61;
	int origC = 61;
	blue.oldR = blue.r;
	blue.oldC = blue.c;

	u16 color = GREEN;
	//initializes enemies
	Enemy red1, red2, red3, red4, red5, red6;

	red1.r = 126;
	red1.c = 60;
	red1.check = 1;
	red1.oldR = 126;
	red1.oldC = 60;
	

	red2.r = 113;
	red2.c = 175;
	red2.check = 1;
	red2.oldR = 113;
	red2.oldC = 175;
	
	red3.r = 132;
	red3.c = 70;
	red3.check = 0;
	red3.oldR = 132;
	red3.oldC = 70;

	red4.r = 20;
	red4.c = 100;
	red4.check = 1;
	red4.oldR = 20;
	red4.oldC = 100;

	red5.r = 105;
	red5.c = 109;
	red5.check = 0;
	red5.oldR = 105;
	red5.oldC = 109;

	red6.r = 20;
	red6.c = 118;
	red6.check = 1;
	red6.oldR = 20;
	red6.oldC = 118;

	//coins

	Coin coin1, coin2, coin3, coin4;

	coin1.r = 20;
	coin1.c = 106;
	coin1.collected = 0;

	coin2.r = 20;
	coin2.c = 115;
	coin2.collected = 0;

	coin3.r = 118;
	coin3.c = 90;
	coin3.collected = 0;

	coin4.r = 80;
	coin4.c = 177;
	coin4.collected = 0;

	Coin coins[4];
	coins[0] = coin1;
	coins[1] = coin2;
	coins[2] = coin3;
	coins[3] = coin4;

	int count = 0;

	drawCoins(coins, 4);
	while(1) {
		//check if colliding with an enemy
		blue.oldR = blue.r;
		blue.oldC = blue.c;

		if (isColliding(red1, blue) || isColliding(red2, blue) || isColliding(red3, blue))
		{
			blue.oldR = blue.r;
			blue.oldC = blue.c;
			blue.r = origR;
			blue.c = origC;
			drawRect(blue.oldR, blue.oldC, 5, 5, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			drawRect(blue.r, blue.c, 5, 5, color);
			drawCoins(coins, 4);
		}

		if (isColliding(red4, blue) || isColliding(red5, blue) || isColliding(red6, blue))
		{
			blue.oldR = blue.r;
			blue.oldC = blue.c;
			blue.r = origR;
			blue.c = origC;
			drawRect(blue.oldR, blue.oldC, 5, 5, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			drawRect(blue.r, blue.c, 5, 5, color);
			drawCoins(coins, 4);
		}

		//dealing with player collisions with coins

		if (isCoinColliding(coin1, blue))
		{
			drawRect(coin1.r, coin1.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin1.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin2, blue))
		{
			drawRect(coin2.r, coin2.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin2.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin3, blue))
		{
			drawRect(coin3.r, coin3.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin3.collected = 1;
			count = count + 1;
		}
		if (isCoinColliding(coin4, blue))
		{
			drawRect(coin4.r, coin4.c, 3, 3, color);
			drawRect(blue.r, blue.c, 5, 5, BLUE);
			coin4.collected = 1;
			count = count + 1;
		}

		//player movement
		if(KEY_DOWN_NOW(UP)) 
		{
			int r = blue.r - 1;
			int c = blue.c;
			if(inbounds2(r,c)) 
			{
				blue.r = r;
			}	
		}
		if(KEY_DOWN_NOW(LEFT)) 
		{
			int r = blue.r;
			int c = blue.c - 1;
			if(inbounds2(r,c)) 
			{
				blue.c = c;
			}
		}
		if(KEY_DOWN_NOW(DOWN)) 
		{
			int r = blue.r + 5;
			int c = blue.c;
			if(inbounds2(r,c)) 
			{
				blue.r = blue.r + 1;
			}
		}
		if(KEY_DOWN_NOW(RIGHT)) 
		{
			int r = blue.r;
			int c = blue.c + 5;
			if(inbounds2(r,c)) 
			{
				blue.c = blue.c + 1;
			}
		}


		//enemy movements

		Enemy red1rev = sideTosideMovement2(red1);
		red1 = red1rev;
		Enemy red2rev = sideTosideMovement2(red2);
		red2 = red2rev;
		Enemy red3rev = sideTosideMovement2(red3);
		red3 = red3rev;
		Enemy red4rev = upDownMovementWithBounds2(red4,105);
		red4 = red4rev;
		Enemy red5rev = upDownMovementWithBounds2(red5,105);
		red5 = red5rev;
		Enemy red6rev = upDownMovementWithBounds2(red6,105);
		red6 = red6rev;
		
		//coin update
		coins[0] = coin1;
		coins[1] = coin2;
		coins[2] = coin3;
		coins[3] = coin4;

		//end game if all coins are collected
		if (allCollected(coins, 4))
		{
			waitForVblank();
			break;
		}

		//prepare for next loop
		waitForVblank();
		drawRect(blue.oldR, blue.oldC, 5, 5, color);
		drawRect(blue.r, blue.c, 5, 5, BLUE);
		blue.oldR = blue.r;
		blue.oldC = blue.c;
	}
	delay(50);
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			videoBuffer[OFFSET(j, i, 240)] = BLACK;
		}
	}
	delay(50);
	drawString(0, 0, "You collected all of the coins!", MAGENTA);
	delay(70);
	drawString(10, 0, "So, now you can play next level!", MAGENTA);
	delay(70);
	drawString(20, 0, "I hope you're ready...", MAGENTA);
	delay(60);
	drawString(30, 0, "This one is hard.", MAGENTA);
	delay(60);
	drawString(0, 0, "You collected all of the coins!", BLACK);
	drawString(10, 0, "So, now you can play next level!", BLACK);
	drawString(20, 0, "I hope you're ready...", BLACK);
	drawString(30, 0, "This one is hard.", BLACK);
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			videoBuffer[OFFSET(j, i, 240)] = BLACK;
		}
	}
	delay(50);
}
//calculates whether a point is within the level's boundary
int inbounds2(int r, int c) {
	if ((r > 20 && r < 140) && (c > 60 && c < 180))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
//makes enemies move up and down with a bound on the row
Enemy upDownMovementWithBounds2(Enemy red, int boundR)
{
	int red_up, red_down;
	red_up = red.r - 2;
	red_down = red.r + 6;

	if ((inbounds2(red_down, red.c) && red_down <= boundR) && red.check) 
	{
		red.r = red.r + 2;
	} 
	else if(!(inbounds2(red_down, red.c) && red_down <= boundR) && red.check) 
	{
		red.check = 0;
		red.r = red.r - 2;
	}
	else if ((inbounds2(red_up, red.c) && red_up <= boundR) && !red.check) 
	{
		red.r = red.r - 2;
	}
	else if (!(inbounds2(red_up, red.c) && red_up <= boundR) && !red.check) 
	{
		red.check = 1;
		red.r = red.r + 2;
	}
	drawRect(red.oldR, red.oldC, 5, 5, GREEN);
	drawRect(red.r, red.c, 5, 5, RED);
	red.oldR = red.r;
	return red;
}
//function that allows enemies to move up and down
Enemy upDownMovement2(Enemy red)
{
	int red_up, red_down;
	red_up = red.r - 1;
	red_down = red.r + 5;

	if (inbounds2(red_down, red.c) && red.check) 
	{
		red.r = red.r + 1;
	} 
	else if (!inbounds2(red_down, red.c) && red.check) 
	{
		red.check = 0;
		red.r = red.r - 1;
	}
	else if (inbounds2(red_up, red.c) && !red.check) 
	{
		red.r = red.r - 1;
	}
	else if (!inbounds2(red_up, red.c) && !red.check) 
	{
		red.check = 1;
		red.r = red.r + 1;
	}
	drawRect(red.oldR, red.oldC, 5, 5, GREEN);
	drawRect(red.r, red.c, 5, 5, RED);
	red.oldR = red.r;
	return red;
}
//function that allows enemies to move right to left
Enemy sideTosideMovement2(Enemy red)
{	
	int red_left, red_right;
		red_left = red.c - 2;
		red_right = red.c + 6;

	if (inbounds2(red.r, red_left) && red.check) 
	{
		red.c = red_left;
	} 
	else if (!inbounds2(red.r, red_left) && red.check) 
	{
		red.check = 0;
		red.c = red.c + 2;
	}
	else if (inbounds2(red.r, red_right) && !red.check) 
	{
		red.c = red.c + 2;
	}
	else if (!inbounds2(red.r, red_right) && !red.check) 
	{
		red.check = 1;
		red.c = red_left;
	}
	drawRect(red.oldR, red.oldC, 5, 5, GREEN);
	drawRect(red.r, red.c, 5, 5, RED);
	red.oldC = red.c;
	return red;
}

