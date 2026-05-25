#include "tucoio.h"

int scompare(char* s1, char* s2) // strcmp, compara duas strings retorna 0 se forem iguais
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int clear(int cursor) // comando para limpar a tela
{
    char* memoria_video = (char*) 0xb8000; // variavel com ponteiro para a posição da memoria de video de texto
    for (int i = 0; i < 80 * 25 * 2; i += 2) // tela em modo vga 80x25
    {
        memoria_video[i] = ' ';
        memoria_video[i + 1] = 0x0f;
    }
    return 0;
}

void echo(char* mensagem, int cursor) // comando para imprimir um texto em verde
{
    char* memoria_video = (char*) 0xb8000;
    int i = 0;
    while (mensagem[i] != 0)
    {
        memoria_video[cursor + (i * 2)] = mensagem[i]; 
        memoria_video[cursor + ((i * 2) + 1)] = 0x02;
        i++;
    }
}

int bgststr(char* s1, char* s2) // testa qual a maior string
{
    int first_count = 0;
    int second_count = 0;

    for (int i = 0; s1[i] != '\0'; i++)
    {
        first_count++;
    }

    for (int i = 0; s2[i] != '\0'; i++)
    {
        second_count++;
    }

    if (first_count > second_count)
        return 1;
    else if (first_count < second_count)
        return 2;
    else if (first_count == second_count)
        return 0;
    return -1;
}

// funçao get size
int get_size_of(char* word)
{
    int size = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        size++;
    }

    return size;
}

int fs_filename_compare(unsigned char* disk_name, char* input_name) {
    for (int i = 0; i < 8; i++) {
        char c = input_name[i];
        
        if (c == '\0') {
            for (int j = i; j < 8; j++) {
                if (disk_name[j] != 0x20 && disk_name[j] != 0x00) return 0;
            }
            return 1;
        }

        if ((unsigned char)c != disk_name[i]) {
            return 0;
        }
    }
    return 1;
}


//inline
void outb(unsigned short port, unsigned char val)
{
    __asm__ __volatile__("outb %0,%1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port)
{
    unsigned char ret;
    __asm__ __volatile__("inb %1,%0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void inw_string(unsigned short port, void* addr, unsigned long count)
{
    __asm__ __volatile__("cld; rep; insw" : "+D"(addr), "+c"(count): "d"(port) : "memory");
}

void outw_string(unsigned short port, void* addr, unsigned long count)
{
    __asm__ __volatile__("cld; rep; outsw" : "+S"(addr), "+c"(count) : "d"(port) : "memory");
}