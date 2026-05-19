#ifndef DISK_H
#define DISK_H

void read_disk_sector(unsigned int lba, unsigned char* buffer);

void write_disk_sector(unsigned int lba, unsigned char* buffer);

#endif