#include "bsp_lcd1603.h"

void write_com(uint8_t com)
{
    while (BusyTest() == 1)
        ;
    rs = 0;
    rw = 0;
    lcden = 0;
    _nop_();
    _nop_();
    Data_Port = com;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    lcden = 1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    lcden = 0;
}
void write_date(uint8_t date)
{
    while (BusyTest() == 1)
        ;

    rs = 1;
    rw = 0;
    lcden = 0;

    Data_Port = date; // 将数据送入 P0 口，即将数据写入液晶模块
    _nop_();
    _nop_();
    _nop_();
    _nop_();   // 空操作四个机器周期，给硬件反应时间
    lcden = 1; // lcden 置高电平
    _nop_();
    _nop_();
    _nop_();
    _nop_();   // 空操作四个机器周期，给硬件反应时间
    lcden = 0; // 当 lcden 由高电平跳变成低电平时，液晶模块开始执行命令
}

void lcd_computer_init()
{
    while (BusyTest())
        ;
    write_com(0x38); // 0x38 用于计算器 两行  0x34用于时钟 一行
    while (BusyTest())
        ;
    write_com(0x0f); // 0x0f 用于计算器，0x0c用于时钟 光标和闪烁
    while (BusyTest())
        ;
    write_com(0x06); // 自动增加 不平移
    while (BusyTest())
        ;
    write_com(0x01); // 清屏
}

static void lcd_delay(uint8_t x)
{
    uint8_t a, b;
    for (a = x; a > 0; a--)
        for (b = 10; b > 0; b--)
            ;
}
int BusyTest(void)
{
    int result;
    rs = 0;
    rw = 1;    // 此时才可以读状态
    lcden = 1; // 此时才允许读写
    _nop_();
    _nop_();
    _nop_();
    _nop_();     // 四个空操作，给硬件反应时间
    result = bf; // 将忙碌标值赋值给result
    lcden = 0;
    return result;
}

void write_address(uint8_t x)
{

    write_com(x | 0x80);

}

void back_home()
{
    write_com(0x02);
}
void clear_screen()
{
    write_com(0x01);
}

void move_cursor_left(int x)
{
    int i;
    for (i = 1; i <= x; i++)
    {
        write_com(0x10);
    }
}
void move_cursor_right(int x)
{
    int i;
    for (i = 1; i <= x; i++)
    {
        write_com(0x14);
    }
}

void display(char *str, int len)
{
    if (len <= 33) //'\0'也在其中
    {
        int i = 0;
        write_address(0x00);
        while (str[i] != '\0')
        {
            if (i == 16)
                write_address(0x40);
            write_date(str[i]);
            i++;
        }
    }
}
