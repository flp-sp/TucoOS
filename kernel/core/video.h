#ifndef VIDEO
#define VIDEO

// imprimir inputs
static int print_char(char c, char color, int cursor) {
    char* memoria_video = (char*) 0xb8000;
    const char* shell_bash = "tuco-OS~$ ";

    if (c == '\n') {
        cursor = ((cursor / 160) + 1) * 160; // passa para a proxima linha
        for (int i = 0; i <= 9; i++)
            {
                memoria_video[cursor] = shell_bash[i];
                memoria_video[cursor + 1] = 0x02;
                cursor += 2;
            }
    } else {
        memoria_video[cursor] = c;
        memoria_video[cursor + 1] = color;
        cursor += 2;
    }
    return cursor;
}

#endif