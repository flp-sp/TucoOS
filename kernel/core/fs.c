#include "fs.h"
#include "../stdlibs/tucoio.h"
#include "../drivers/disk.h"

unsigned int cluster_to_lba(unsigned short cluster)
{
    //regiao de inicio de dados + (primeira cluster - 2) * setores por cluster
    return DATA_LBA + (cluster - 2) * CLUSTER_PER_SECTORS; 
}

void copy_filename(unsigned char* dest, char* src)
{
    for (int i = 0; i < 8; i++)
    {
        if (*src)
        {
            dest[i] = *src;
            src++;
        }
        else
        {
            dest[i] = 0x20;
        }
    }
}

// comando de mostrar conteudo de arquivo (cat)
int fs_cat(char* filename, char* out_buffer)
{
    unsigned char sector[512];
    TOFS_DirEntry* entry;

    for (int sec = 0; sec < ROOT_DIR_SECTORS; sec++)
    {

        read_disk_sector(ROOT_DIR_LBA + sec, sector);
        for (int i = 0; i < 512; i+= sizeof(TOFS_DirEntry))
        {
            entry = (TOFS_DirEntry*)&sector[i];
            if (fs_filename_compare(entry->file_name, filename))
            {
                if (entry->file_name[0] != 0x00 && entry->file_name[0] != 0xe5)
                {
                    read_disk_sector(cluster_to_lba(entry->cluster_pointer), (unsigned char*)out_buffer);
                    out_buffer[entry->file_size] = '\0';
                    return 1;
                }
            }
        }
    }
    return 0;
}

// comando de criar arquivo
int fs_make(char* filename, char* content, int size)
{
    unsigned char sector[512];
    TOFS_DirEntry* entry;

    for (int sec = 0; sec < ROOT_DIR_SECTORS; sec++)
    {
        read_disk_sector(ROOT_DIR_LBA + sec, sector);
        for (int i = 0; i < 512; i += sizeof(TOFS_DirEntry))
        {
            entry = (TOFS_DirEntry*)&sector[i];

            if (entry->file_name[0] == 0x00 || entry->file_name[0] == 0xe5)
            {
                copy_filename(entry->file_name, filename);
                entry->cluster_pointer = 2;
                entry->file_size = size;
                entry->type = 0x20;

                entry->file_name[get_size_of((char*)entry->file_name)] = 0x20;

                write_disk_sector(ROOT_DIR_LBA + sec, sector);

                unsigned char data_sector[512];
                for (int d = 0; d < 512; d++)
                {
                    if (d < size)
                    {
                        data_sector[d] = content[d];
                    }
                    else 
                    {
                        data_sector[d] = 0;
                    }
                    
                }
                write_disk_sector(cluster_to_lba(2), data_sector);
                return 1;
            }
        }
    }
    
    return 0;
}

// comando de listar diretorio root ls
int fs_ls(int cursor)
{
    unsigned char sector[512];
    TOFS_DirEntry* entry;

    for (int sec = 0; sec < ROOT_DIR_SECTORS; sec++)
    {
        read_disk_sector(ROOT_DIR_LBA + sec, sector);
        for (int i = 0; i < 512; i += sizeof(TOFS_DirEntry))
        {
            entry = (TOFS_DirEntry*)&sector[i];

            if (entry->file_name[0] != 0x00 && entry->file_name[0] != 0xe5)
            {
                cursor = ((cursor / 160) + 1) * 160;
                echo((char*)entry->file_name, cursor);
            }
        }
    }
    return cursor;
}