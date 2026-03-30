int cursor = 0;

void clear()
{
    char* memoria_video = (char*) 0xb8000; // variavel com ponteiro para a posição da memoria de video de texto
    for (int i = 0; i < 80 * 25 * 2; i += 2) // tela em modo vga 80x25
    {
        memoria_video[i] = ' ';
        memoria_video[i + 1] = 0x0f;
    }
    cursor = 0;
}

void echo(char* mensagem)
{
    char* memoria_video = (char*) 0xb8000;
    int i = 0;
    cursor = ((cursor / 160) + 1) * 160;
    while (mensagem[i] != 0)
    {
        memoria_video[cursor + (i * 2)] = mensagem[i]; 
        memoria_video[cursor + ((i * 2) + 1)] = 0x02;
        i++;
    }
}

void print_char(char c, char color) {
    char* memoria_video = (char*) 0xb8000;
    if (c == '\n') {
        cursor = ((cursor / 160) + 1) * 160;
    } else {
        memoria_video[cursor] = c;
        memoria_video[cursor + 1] = color;
        cursor += 2;
    }
}

int scompare(char* s1, char* s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

unsigned char inb(unsigned short porta)
{
    unsigned char ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(porta));
    return ret;
}

char get_key() {
    unsigned char scancode = 0;
    
    while (!(inb(0x64) & 1)); 
    
    scancode = inb(0x60);

    switch(scancode) {
        case 0x1E: return 'a';
        case 0x30: return 'b';
        case 0x2E: return 'c';
        case 0x20: return 'd';
        case 0x12: return 'e';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x17: return 'i';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x32: return 'm';
        case 0x31: return 'n';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x10: return 'q';
        case 0x13: return 'r';
        case 0x1F: return 's';
        case 0x14: return 't';
        case 0x16: return 'u';
        case 0x2F: return 'v';
        case 0x11: return 'w';
        case 0x2D: return 'x';
        case 0x15: return 'y';
        case 0x2C: return 'z';
        case 0x1C: return '\n';
        case 0x39: return ' ';
        case 0x0e: return '\b'; 
        default: return 0;  
    }
}

void shell()
{
    char buffer[128];
    int pos = 0;

    while (1)
    {
        char words[2][64];
        int word_index = 0;
        int char_index = 0;

        char c = get_key();
        if (c != 0)
        {
            if (c == '\n')
            {
                buffer[pos] = '\0';

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

                if (scompare(words[0], "echo") == 0)
                {
                    echo(words[1]);
                }
                if (scompare(buffer, "clear") == 0)
                {
                    clear();
                }
                pos = 0;
                print_char(c, 0x07);
            }
            else if (c == '\b')
            {
                if (pos > 0)
                {
                    pos--;
                    cursor -= 2;
                    print_char(' ', 0x07);
                    cursor -= 2;
                }
            }
            else
            {
                buffer[pos++] = c;
                print_char(c, 0x07);
            }
        }
    }
}

void main()
{
    clear();
    echo("Seja bem vindo ao TucoOS - Kernel carregado!");
    cursor = 160;
    shell();
    while (1);
}