#ifndef BSP_BOARD_H
#define BSP_BOARD_H

#include <reg52.h>
#include "bsp_lcd1603.h"

sbit line1 = P0 ^ 0;
sbit line2 = P0 ^ 1;
sbit line3 = P0 ^ 2;
sbit line4 = P0 ^ 3;

sbit row1 = P1 ^ 3;
sbit row2 = P1 ^ 4;
sbit row3 = P1 ^ 5;
sbit row4 = P1 ^ 6;
sbit row5 = P1 ^ 7;

char scan_board(void);

#endif