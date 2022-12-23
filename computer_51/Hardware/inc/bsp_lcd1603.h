#ifndef BSP_LCD1603_H
#define BSP_LCD1603_H

#include "main.h"
#include <reg52.h>
#include <intrins.h>

#define Data_Port P2

#define uint8_t unsigned char

sbit rs = P1 ^ 0;
sbit rw = P1 ^ 1;
sbit lcden = P1 ^ 2;
sbit bf = P2 ^ 7;

static void lcd_delay(uint8_t x);
void write_com(uint8_t com);
void write_date(uint8_t date);
void lcd_computer_init();
void write_address(uint8_t x);
int BusyTest(void);
/**
 * @brief 封装指令
 * 
 */
void back_home();//光标返回初始位置
void clear_screen();//清屏
void display(char *str,int len); //计算器显示字符串 自动换行
void move_cursor_left(int x);
void move_cursor_right(int x);
#endif