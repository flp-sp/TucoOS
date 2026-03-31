#ifndef SHELL 
#define SHELL

#include "../drivers/keyboard_handdle.h"
#include "../stdlibs/tucoio.h"
#include "video.h"
#include "comands.h"

static void shell(int cursor)
{
    char buffer[128]; // armazena as entradas do usuario
    int pos = 0; // guarda a posicao atual do buffer

    while (1)
    {
        // permite multiplas palavras por linha para flags
        char words[3][64] = {{},{},{}};
        int word_index = 0;
        int char_index = 0;

        char c = get_key();
        if (c != 0)
        {
            if (c == '\n') // checa se o usuario apertou enter
            {
                buffer[pos] = '\0'; // adiciona o fim ao buffer

                for (int i = 0; buffer[i] != '\0'; i++)
                {
                    if (buffer[i] == ' ')
                    {
                        words[word_index][char_index] = '\0';
                        word_index++;
                        char_index = 0;
                    }
                    else  
                    {
                        words[word_index][char_index] = buffer[i];
                        char_index++;
                    }
                }
                
                words[word_index][char_index] = '\0';

                if (scompare(words[0], "echo") == 0) //comando echo
                {
                    cursor = ((cursor / 160) + 1) * 160;
                    echo(words[1], cursor);
                }
                else if (scompare(buffer, "clear") == 0) // comando clear
                {
                    cursor = clear(cursor);
                }
                else if (scompare(buffer, "help") == 0)
                {
                    cursor = help(cursor);
                }
                else if (scompare(buffer, "shutdown") == 0)
                {
                    shutdown();
                }
                else if (scompare(words[0], "sum") == 0)
                {
                    cursor = ((cursor / 160) + 1) * 160;
                    echo(sum(words[1], words[2]), cursor);
                }
                else  
                {
                    cursor = ((cursor / 160) + 1) * 160;
                    echo("comando nao encontrado", cursor);
                }
                pos = 0;
                cursor = print_char(c, 0x07, cursor);
            }
            else if (c == '\b') // backspace
            {
                if (pos > 0)
                {
                    pos--;
                    cursor -= 2;
                    cursor = print_char(' ', 0x07, cursor);
                    cursor -= 2;
                }
            }
            else
            {
                buffer[pos++] = c;
                cursor = print_char(c, 0x07, cursor);
            }
        }
    }
}

#endif