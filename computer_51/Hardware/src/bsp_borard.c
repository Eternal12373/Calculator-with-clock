#include "bsp_board.h"

char scan_board(void)
{
    int flag = 0;
    char ch;
    uint8_t temp;

    P1 &= 0x0F; // 其他拉低
    P1 |= 0x08; // row1拉高
    temp = P0;
    temp &= 0x0F; // 掩去高四位
    switch (temp)
    {
    case 0x01:
        flag = 1;
        ch = '0';
        break;
    case 0x02:
        flag = 1;
        ch = '1';
        break;
    case 0x04:
        flag = 1;
        ch = '4';
        break;
    case 0x08:
        flag = 1;
        ch = '7';
        break;
    }
    if (flag == 1) // 减少一次循环
    {
        do
        {
            temp = P0;
            temp &= 0x0F;
        } while (temp != 0x00);

        return ch;
    }
#if 1
    P1 &= 0x17; // 其他拉低
    P1 |= 0x10; // row2拉高
    temp = P0;
    temp &= 0x0F; // 掩去高四位
    switch (temp)
    {
    case 0x01:
        flag = 2;
        ch = '.';
        break;
    case 0x02:
        flag = 2;
        ch = '2';
        break;
    case 0x04:
        flag = 2;
        ch = '5';
        break;
    case 0x08:
        flag = 2;
        ch = '8';
        break;
    }
    if (flag == 2) // 减少一次循环
    {
        do
        {
            temp = P0;
            temp &= 0x0F;
        } while (temp != 0x00);

        return ch;
    }

    P1 &= 0x27; // 其他拉低
    P1 |= 0x20; // row3拉高
    temp = P0;
    temp &= 0x0F; // 掩去高四位
    switch (temp)
    {
    case 0x01:
        flag = 3;
        ch = '=';
        break;
    case 0x02:
        flag = 3;
        ch = '4';
        break;
    case 0x04:
        flag = 3;
        ch = '6';
        break;
    case 0x08:
        flag = 3;
        ch = '9';
        break;
    }
    if (flag == 3) // 减少一次循环
    {
        do
        {
            temp = P0;
            temp &= 0x0F;
        } while (temp != 0x00);

        return ch;
    }

    P1 &= 0x47; // 其他拉低
    P1 |= 0x40; // row4拉高
    temp = P0;
    temp &= 0x0F; // 掩去高四位
    switch (temp)
    {
    case 0x01:
        flag = 4;
        ch = '+';
        break;
    case 0x02:
        flag = 4;
        ch = '-';
        break;
    case 0x04:
        flag = 4;
        ch = '*';
        break;
    case 0x08:
        flag = 4;
        ch = '/';
        break;
    }
    if (flag == 4) // 减少一次循环
    {
        do
        {
            temp = P0;
            temp &= 0x0F;
        } while (temp != 0x00);

        return ch;
    }

    P1 &= 0x87; // 其他拉低
    P1 |= 0x80; // row5拉高
    temp = P0;
    temp &= 0x0F; // 掩去高四位
    switch (temp)
    {
    case 0x01:
        flag = 5;
        ch = 'd';
        break;
    case 0x02:
        flag = 5;
        ch = 'm';
        break;
    case 0x04:
        flag = 5;
        ch = ')';
        break;
    case 0x08:
        flag = 5;
        ch = '(';
        break;
    }
    if (flag == 5) // 减少一次循环
    {
        do
        {
            temp = P0;
            temp &= 0x0F;
        } while (temp != 0x00);

        return ch;
    }
#endif
    if (flag == 0)
    {
        return '\0';
    }
}