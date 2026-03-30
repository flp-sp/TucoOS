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
    char* comandos[4] = {
        "echo - imprime uma mensagem na tela",
        "clear - limpa a tela",
        "help - exibe os comandos na tela",
        "shutdown - desliga o computador"
    };

    for (int i = 0; i <= 3; i++)
    {
        cursor = ((cursor / 160) + 1) * 160;
        echo(comandos[i], cursor);
    }
    
    return cursor;
}

#endif