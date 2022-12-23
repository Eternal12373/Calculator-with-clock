#ifndef MAIN_H
#define MAIN_H

typedef enum
{
    CLOCK,
    COMPUTER,
} bsp_mode;
typedef enum
{
    INPUT,
    OUTPUT,
    CALCULATE,
    CALEND
} com_sub_mode;
typedef enum
{
    PAUSE,
    RUN,
    SETNUM,
    CLEAR
} clk_sub_mode;

typedef struct control__
{
    bsp_mode mode;
    bsp_mode next_mode;
    com_sub_mode com_mode;
    com_sub_mode com_next_mode;
    clk_sub_mode clk_mode;
    clk_sub_mode clk_next_mode;
} control_mode;

void mode_init(void);
void set_mode(void);
void clock_mode_behavior(void);
void computer_mode_behavior(void);
void change_mode(void);
#endif