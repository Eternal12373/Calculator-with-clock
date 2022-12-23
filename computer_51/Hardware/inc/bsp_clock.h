#ifndef BSP_CLOCK_H
#define BSP_CLOCK_H

#include <reg52.h>
#include "bsp_lcd1603.h"

void display_clock(void);
void display_set_clock(int a, int b, int c, int d, int e, int f);
void clock_init();

#endif