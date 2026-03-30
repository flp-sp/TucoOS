#include "stdlibs/tucoio.h"
#include "core/video.h"
#include "core/shell.h"

int cursor = 0;

void main()
{
    cursor = clear(cursor);
    echo("Seja bem vindo ao TucoOS - Kernel carregado!", cursor);

    cursor = print_char('\n', 0x07, cursor);
    shell(cursor);
    while (1);
}
