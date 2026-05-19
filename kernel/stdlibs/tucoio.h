#ifndef TUCOIO
#define TUCOIO

int scompare(char* s1, char* s2); // strcmp, compara duas strings retorna 0 se forem iguais

int clear(int cursor); // comando para limpar a tela

void echo(char* mensagem, int cursor); // comando para imprimir um texto em verde

int bgststr(char* s1, char* s2); // testa qual a maior string

inline void outb(unsigned short port, unsigned char val);

inline unsigned char inb(unsigned short port);

inline void inw_string(unsigned short port, void* addr, unsigned long count);

#endif