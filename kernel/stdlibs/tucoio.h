#ifndef TUCOIO
#define TUCOIO

int scompare(char* s1, char* s2); // strcmp, compara duas strings retorna 0 se forem iguais

int clear(int cursor); // comando para limpar a tela

void echo(char* mensagem, int cursor); // comando para imprimir um texto em verde

int bgststr(char* s1, char* s2); // testa qual a maior string

int get_size_of(char* word);

// inline asm
void outb(unsigned short port, unsigned char val);

unsigned char inb(unsigned short port);

void inw_string(unsigned short port, void* addr, unsigned long count);

void outw_string(unsigned short port, void* addr, unsigned long count);

#endif