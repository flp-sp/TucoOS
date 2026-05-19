#include "../stdlibs/tucoio.h"

void read_disk_sector(unsigned int lba, unsigned char* buffer)
{
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20);

    while (!(inb(0x1F7) & 0x08));

    inw_string(0x1F0, buffer, 256);
}

void write_disk_sector(unsigned int lba, unsigned char* buffer)
{
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x30);

    while (!(inb(0x1F7) & 0x08));

    outw_string(0x1F0, buffer, 256);
}