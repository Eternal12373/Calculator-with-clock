#include "bsp_clock.h"

extern uint8_t sec;
extern uint8_t min;
extern uint8_t hour;

extern control_mode control;
sbit led = P0 ^ 6;
void clock_init()
{
    TMOD = 0x01;
    TH0 = (65536 - 60000) / 256;
    TL0 = (65536 - 60000) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void display_clock(void)
{
    char str[15];
    str[0] = '0' + hour / 10;
    str[1] = '0' + hour % 10;
    str[2] = ':';
    str[3] = '0' + min / 10;
    str[4] = '0' + min % 10;
    str[5] = ':';
    str[6] = '0' + sec / 10;
    str[7] = '0' + sec % 10;
    str[8] = '\0';
    display(str, 15);
}
void display_set_clock(int a, int b, int c, int d, int e, int f)
{
    int i = 0;
    char str[15];
    str[0] = '0' + a;
    str[1] = '0' + b;
    str[2] = ':';
    str[3] = '0' + c;
    str[4] = '0' + d;
    str[5] = ':';
    str[6] = '0' + e;
    str[7] = '0' + f;
    str[8] = '\0';
    
    write_address(0x00);
    while (str[i] != '\0')
    {
        if (i == 16)
            write_address(0x40);
        write_date(str[i]);
        i++;
    }

}
