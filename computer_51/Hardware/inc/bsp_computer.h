#ifndef BSP_COMPUTER_H
#define BSP_COMPUTER_H

#include <string.h>
#include <stdio.h>
#include <reg52.h>

#define Data_Type double
#define MAX_DOUBLE_DATA 20
#define MAD_EXP_LEN 32



typedef struct Data_and_Symbol__
{
    double bsp_data;
    char sym;
    int flag; // 0->data   1->sym
} DAS;
typedef struct Data_Stack__
{
    Data_Type bsp_data[32];
    int top;
} Data_Stack;

typedef struct Symbol_Stack__
{
    char symbol[32];
    int top;
} Symbol_Stack;

void init_data_stack(Data_Stack *ptr); // init the stack
void init_symbol_stack(Symbol_Stack *ptr);
void push_data_stack(Data_Stack *ptr, Data_Type num);
Data_Type pop_data_stack(Data_Stack *ptr);
void push_symbol_stack(Symbol_Stack *ptr, char symbol);
char pop_symbol_stack(Symbol_Stack *ptr);
char check_symbol_stack(Symbol_Stack *ptr);
int judge(char ch);
double compute(double a, double b, char sign);
double intoresult(char *exp, Data_Stack *data_stack, Symbol_Stack *symbol_stack);


#endif