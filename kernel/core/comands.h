#ifndef COMANDS
#define COMANDS

#include "../stdlibs/tucoio.h"

static inline void outw(unsigned short port, unsigned short val)
{
    __asm__ __volatile__ ("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline void shutdown()
{
    outw(0x604, 0x2000);
}

static int help(int cursor)
{
    char* comandos[5] = {
        "echo - imprime uma mensagem na tela",
        "clear - limpa a tela",
        "help - exibe os comandos na tela",
        "shutdown - desliga o computador",
        "sum - soma dois inputs inteiros do teclado"
    };

    for (int i = 0; i <= 4; i++)
    {
        cursor = ((cursor / 160) + 1) * 160;
        echo(comandos[i], cursor);
    }
    
    return cursor;
}

static char* sum(char* n1, char* n2)
{
    static char result[16];
    static char correct_result[16];
    int result_lenght = 0;

    int soma = 0;
    int int1 = 0;
    int int2 = 0;

    for (int i = 0; n1[i] != '\0'; i++)
    {
        if (i != 0)
        {
            int1 *= 10;
            int1 += n1[i] - '0';
        }
        else if (i == 0)
        {
            int1 += n1[i] - '0';
        }
    }
    for (int i = 0; n2[i] != '\0'; i++)
    {
        if (i != 0)
        {
            int2 *= 10;
            int2 += n2[i] - '0';
        }
        else if (i == 0)
        {
            int2 += n2[i] - '0';
        }
    }
    soma = int1 + int2;
    for (int i = 0; i > -1; i++)
    {
        if (soma % 10 == 0 && soma > 0)
        {
            result[i] = (soma % 10) + '0';
            soma /= 10;
        }
        else if (soma % 10 > 0)
        {
            result[i] = (soma % 10) + '0';
            soma /= 10;
        }
        else 
        {
            result[i] = '\0';
            break;
        }
    }
    for (int i = 0; result[i] != '\0'; i++)
    {
        result_lenght++;
    }
    for (int i = 0; i < result_lenght; i++)
    {
        correct_result[i] = result[result_lenght - i - 1];
    }
    correct_result[result_lenght] = '\0';
    return correct_result;
}

#endif