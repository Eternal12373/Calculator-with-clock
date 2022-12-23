#include "main.h"
#include <reg52.h>
#include "bsp_lcd1603.h"
#include "bsp_board.h"
#include "bsp_computer.h"
#include "bsp_clock.h"

uint8_t hour;
uint8_t min;
uint8_t sec;
int count = 0;

uint8_t disp_table[32];
uint8_t exp_table[32];
int disp_index = 0;
int exp_index = 0;
double result;

sbit LED = P3 ^ 7;

control_mode control; // 状态机

Data_Stack data_stack;
Symbol_Stack symbol_stack;
void delay(int ms);
char key;
void main()
{
    clock_init();

#if 1
    mode_init();
    lcd_computer_init();

#endif
#if 1

    while (1)
    {
        key = scan_board();
        set_mode();

        if (control.mode == COMPUTER)
        {
            computer_mode_behavior();
        }
        else if (control.mode == CLOCK)
        {
            clock_mode_behavior();
        }
        change_mode();
    }
#endif
}
void delay(int ms)
{
    int i, j;
    for (i = 0; i < 112; i++)
    {
        for (j = 0; j < ms; j++)
        {
            ;
        }
    }
}

void mode_init(void)
{
    control.mode = COMPUTER;
    control.com_mode = INPUT;
    control.clk_mode = RUN;
    control.com_next_mode = INPUT;
    control.clk_next_mode = RUN;
}
void set_mode(void)
{

    if (control.mode == CLOCK)
    {
        if (key == '=')
        {
            control.next_mode = COMPUTER;
        }
        else
        {
            control.next_mode = control.mode;
        }
    }
    else if (control.mode == COMPUTER)
    {
        static computer_flag = 1;
        if (computer_flag)
        {
            computer_flag=0;
            clear_screen();
            disp_index = 0;
            exp_index = 0;
        }
        write_com(0x0f); // 0x0f 用于计算器，0x0c用于时钟 光标和闪烁
        if (key == 'm')
        {
            computer_flag=1;
            control.next_mode = CLOCK;
        }
        else
        {
            control.next_mode = control.mode;
        }
    }
}
void clock_mode_behavior(void)
{

    if (control.clk_mode == RUN)
    {
        static int run_flag = 1;
        write_com(0x0c);
        if (run_flag)
        {
            clear_screen();

            write_address(0x48);
            write_date('R');
            write_date('U');
            write_date('N');
            run_flag = 0;
        }

        display_clock();
        if (key == '/')
        {
            control.clk_next_mode = PAUSE;
            run_flag = 1;
        }
        else
        {
            control.clk_next_mode = control.clk_mode;
        }
    }
    else if (control.clk_mode == PAUSE)
    {
        static int pause_flag = 1;
        if (pause_flag)
        {
            write_com(0x0c);

            write_address(0x48);
            write_date('P');
            write_date('A');
            write_date('U');
            write_date('S');
            write_date('E');
            pause_flag = 0;
        }

        if (key == '/')
        {
            control.clk_next_mode = RUN;
            pause_flag = 1;
        }
        else if (key == '*')
        {
            control.clk_next_mode = CLEAR;
            pause_flag = 1;
        }
        else if (key == '-')
        {
            control.clk_next_mode = SETNUM;
            pause_flag = 1;
        }
        else
        {
            control.clk_next_mode = control.clk_mode;
        }
    }
    else if (control.clk_mode == CLEAR)
    {
        sec = min = hour = 0;
        display_clock();
        control.clk_next_mode = PAUSE;
    }
    else if (control.clk_mode == SETNUM)
    {
        static int a, b, c, d, e, f;
        static int cursor = 1;
        static int set_flag = 1;
        if (set_flag) // 第一次进入 保存数据
        {
            clear_screen();

            a = hour / 10;
            b = hour % 10;
            c = min / 10;
            d = min % 10;
            e = sec / 10;
            f = sec % 10;

            cursor = 1;
            set_flag = 0;

            display_set_clock(a, b, c, d, e, f);
            write_address(0x48);
            write_date('S');
            write_date('E');
            write_date('T');

            write_com(0x0f);
            back_home();
        }

        if (key == '(')
        {
            if (cursor % 2 != 0) // 多移动一个：
            {
                move_cursor_left(2);
            }
            else
            {
                move_cursor_left(1);
            }
            cursor -= 1;
        }
        if (key == ')')
        {
            if (cursor % 2 == 0)
            {
                move_cursor_right(2);
            }
            else
            {
                move_cursor_right(1);
            }
            cursor += 1;
        }

        if (key >= '0' && key <= '9')
        {
            switch (cursor)
            {
            case 1:
                a = key - '0';
                break;
            case 2:
                b = key - '0';
                break;
            case 3:
                c = key - '0';
                break;
            case 4:
                d = key - '0';
                break;
            case 5:
                e = key - '0';
                break;
            case 6:
                f = key - '0';
                break;
            }
            display_set_clock(a, b, c, d, e, f);

            back_home();
            delay(10); // 这里要加延时，否则move无效，且有报警
            if (cursor <= 2)
                move_cursor_right(cursor - 1);
            else if (cursor >= 3 && cursor <= 4)
                move_cursor_right(cursor);
            else
                move_cursor_right(cursor + 1);
        }

        // mode change
        if (key == '-')
        {
            hour = a * 10 + b;
            min = c * 10 + d;
            sec = e * 10 + f;
            set_flag = 1;
            control.clk_next_mode = PAUSE;
        }
        else
        {
            control.clk_next_mode = control.clk_mode;
        }
        LED = 0;
    }
}
void computer_mode_behavior(void)
{
    if (control.com_mode == INPUT)
    {
        if (key != '\0' && key != '=' && key != 'd')
        {
            disp_table[disp_index++] = key;
            disp_table[disp_index] = '\0';
            display(disp_table, sizeof(disp_table));
            control.com_next_mode = control.com_mode;
        }
        else if (key == 'd')
        {
            disp_index--;
            disp_table[disp_index] = '\0';
            display(disp_table, sizeof(disp_table));
        }
        else if (key == '=') // 状态转换
        {
            control.com_next_mode = CALCULATE;
        }
    }
    else if (control.com_mode == CALCULATE)
    {
        init_data_stack(&data_stack); // init the stack
        init_symbol_stack(&symbol_stack);
        result = intoresult(disp_table, &data_stack, &symbol_stack);
        sprintf(exp_table, "%.3f", result);
        clear_screen();
        display(exp_table, 7);
        control.com_next_mode = CALEND;
    }
    else if (control.com_mode == CALEND)
    {
        if (key == '=')
        {
            clear_screen();
            disp_index = 0;
            exp_index = 0;

            control.com_next_mode = INPUT;
        }
        else
        {
            control.com_next_mode = control.com_mode;
        }
    }
}

void change_mode()
{
    control.mode = control.next_mode;
    control.com_mode = control.com_next_mode;
    control.clk_mode = control.clk_next_mode;
}

void Timer0() interrupt 1
{
    TH0 = (65536 - 60000) / 256;
    TL0 = (65536 - 60000) % 256;
    TR0 = 1;
    count++;
    if (count >= 15)
    {
        count = 0;
        if (control.mode == CLOCK && control.clk_mode == RUN) // control.mode == CLOCK && control.clk_mode == RUN
        {

            sec++;
            if (sec >= 60)
            {
                sec = 0;
                min++;
                if (min >= 60)
                {
                    min = 0;
                    hour++;
                    if (hour >= 24)
                    {
                        hour = 0;
                    }
                }
            }
        }
    }
}