#ifndef TUCOFS_H
#define TUCOFS_H

typedef struct __attribute__((packed)){
    unsigned char file_name[8];
    char format[3];
    unsigned char type;
    unsigned char reserved[14];
    unsigned short cluster_pointer;
    unsigned int file_size;
} TOFS_DirEntry;

#define RESERVED_SECTORS 31
#define FAT_SECTORS 9
#define ROOT_DIR_SECTORS 14

#define CLUSTER_PER_SECTORS 2

#define FAT_LBA RESERVED_SECTORS
#define ROOT_DIR_LBA (RESERVED_SECTORS + FAT_SECTORS)
#define DATA_LBA (ROOT_DIR_LBA + ROOT_DIR_SECTORS)

unsigned int cluster_to_lba(unsigned short cluster);

void copy_filename(unsigned char* dest, char* src);
int fs_cat(char* file_name, char* out_buffer);
int fs_make(char* filename, char* content, int size);
int fs_ls(int cursor);
int fs_filename_compare(unsigned char* disk_name, char* input_name);

#endif