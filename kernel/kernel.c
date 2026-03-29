void clear()
{
    char* memoria_video = (char*) 0xb8000; // variavel com ponteiro para a posição da memoria de video de texto
    for (int i = 0; i < 80 * 25 * 2; i += 2) // tela em modo vga 80x25
    {
        memoria_video[i] = ' ';
        memoria_video[i + 1] = 0x0f;
    }
}

void echo(char* mensagem)
{
    char* memoria_video = (char*) 0xb8000;
    int i = 0;
    while (mensagem[i] != 0)
    {
        memoria_video[i * 2] = mensagem[i]; 
        memoria_video[(i * 2) + 1] = 0x02;
        i++;
    }
}

void main()
{
    clear();
    echo("Seja bem vindo ao TucoOS - Kernel carregado!");
    while (1);
}