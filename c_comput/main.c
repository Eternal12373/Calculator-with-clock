#include <stdio.h>
#include <string.h>
typedef unsigned char uint8_t;

#define Data_Type double
#define MAX_DOUBLE_DATA 20
#define MAD_EXP_LEN 100
typedef struct Data_and_Symbol__
{
    double data;
    char sym;
    int flag; // 0->data   1->sym
} DAS;
typedef struct Data_Stack__
{
    Data_Type data[100];
    int top;
} Data_Stack;

typedef struct Symbol_Stack__
{
    char symbol[100];
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
int main()
{
    // char test[] = "1.2*((1+2)*8)*6";
    // Data_Stack data_stack;
    // Symbol_Stack symbol_stack;

    // init_data_stack(&data_stack); // init the stack
    // init_symbol_stack(&symbol_stack);

    // intoresult(test, &data_stack, &symbol_stack);
    // printf("\n%d",sizeof("123456789123456789123456789123456789"));
    double x=1.35678;
    char c[30];
    sprintf(c,"%.2f",x);
    puts(c);


    return 0;
}

void init_data_stack(Data_Stack *ptr)
{
    ptr->top = -1;
}
void init_symbol_stack(Symbol_Stack *ptr)
{
    ptr->top = -1;
}
void push_data_stack(Data_Stack *ptr, Data_Type num)
{
    ptr->top++;
    ptr->data[ptr->top] = num;
}
Data_Type pop_data_stack(Data_Stack *ptr)
{
    Data_Type num;
    num = ptr->data[ptr->top];
    ptr->top--;
    return num;
}
void push_symbol_stack(Symbol_Stack *ptr, char symbol)
{
    ptr->top++;
    ptr->symbol[ptr->top] = symbol;
}
char pop_symbol_stack(Symbol_Stack *ptr)
{
    char symbol = ptr->symbol[ptr->top];
    ptr->top--;
    return symbol;
}
char check_symbol_stack(Symbol_Stack *ptr)
{
    char symbol = ptr->symbol[ptr->top];
    return symbol;
}

int judge(char ch)
{
    switch (ch)
    {
    case '(':
        return 1;
        break;
    case '+':
    case '-':
        return 2;
        break;
    case '*':
    case '/':
        return 3;
        break;
    }
}

double compute(double a, double b, char sign)
{
    if (sign == '+')
        return a + b;
    if (sign == '-')
        return b - a;
    if (sign == '*')
        return a * b;
    if (sign == '/')
        return b / a;
}

double stringToDouble(char a[])
{
    int i = 0;
    char p[MAX_DOUBLE_DATA];
    int top = 0;
    double sum = 0;
    double mul = 1;
    while (a[i] != '\0' && a[i] != '.')
    {
        p[top] = a[i];
        top++;
        i++;
    }
    while (top != 0)
    {
        top--;
        sum = sum + (p[top] - '0') * mul;
        mul = mul * 10;
    }
    if (a[i] == '.')
    {
        i++;
        mul = 0.1;
        while (a[i] != '\0')
        {
            sum = sum + (a[i] - 48) * mul;
            mul = mul / 10;
            i++;
        }
    }
    return sum;
}
double intoresult(char *exp, Data_Stack *data_stack, Symbol_Stack *symbol_stack)
{
    int str_read = 0, str_write = 0;
    int length = 0;
    int str_start = 0; // when cut string use it as start flag
    double str_temp_double;
    DAS L[MAD_EXP_LEN];
    int L_index = 0;
    int L_indexlast = 0;

    char str_temp[MAX_DOUBLE_DATA];
    while (exp[str_read] != '\0')
    {
        if (exp[str_read] >= '0' && exp[str_read] <= '9' || exp[str_read] == '.') // num
        {
            length = 0;
            str_start = str_read; // start pos
            while (exp[str_read] >= '0' && exp[str_read] <= '9' || exp[str_read] == '.')
            {
                str_read++;
                length++;
            }
            strncpy(str_temp, exp + str_start, length);
            str_temp[length] = '\0';
            str_temp_double = stringToDouble(str_temp);
            L[L_index].data = str_temp_double;
            L[L_index].flag = 0;
            L_index++;
            // push_data_stack(data_stack, str_temp_double);
        }
        else // symbol
        {
            if (symbol_stack->top == -1)
            {
                push_symbol_stack(symbol_stack, exp[str_read]);
            }
            else if (exp[str_read] == '(') // push!
            {
                push_symbol_stack(symbol_stack, exp[str_read]);
            }
            else if (exp[str_read] == ')')
            {
                while (check_symbol_stack(symbol_stack) != '(')
                {
                    char compare_temp = pop_symbol_stack(symbol_stack);
                    L[L_index].sym = compare_temp;
                    L[L_index].flag = 1;
                    L_index++;
                }
                pop_symbol_stack(symbol_stack); // pop (
            }
            else
            {
                while (judge(exp[str_read]) <= judge(check_symbol_stack(symbol_stack)))
                {
                    char compare_temp = pop_symbol_stack(symbol_stack);
                    L[L_index].sym = compare_temp;
                    L[L_index].flag = 1;
                    L_index++;
                }
                push_symbol_stack(symbol_stack, exp[str_read]);
            }
            str_read++;
        }
    }
    while (symbol_stack->top != -1)
    {
        char compare_temp = pop_symbol_stack(symbol_stack);
        L[L_index].sym = compare_temp;
        L[L_index].flag = 1;
        L_index++;
    }
    for (L_indexlast = 0; L_indexlast < L_index; L_indexlast++)
    {
        if (L[L_indexlast].flag == 1)
        {
            char sign = L[L_indexlast].sym;
            double a = pop_data_stack(data_stack);
            double b = pop_data_stack(data_stack);
            double c = compute(a, b, sign);
            push_data_stack(data_stack, c);
        }
        else
        {
            push_data_stack(data_stack, L[L_indexlast].data);
        }
    }

    printf("%f", pop_data_stack(data_stack));
}