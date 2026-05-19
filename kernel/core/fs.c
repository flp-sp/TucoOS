#include "fs.h"
#include "../drivers/disk.h"

unsigned int cluster_to_lba(unsigned short cluster)
{
    //regiao de inicio de dados + (primeira cluster - 2) * setores por cluster
    return DATA_LBA + (cluster - 2) * CLUSTER_PER_SECTORS; 
}

void copy_filename(char* dest, char* src)
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
int fs_cat(char* file_name, char* out_buffer)
{
    unsigned char sector[512];
    TOFS_DirEntry* entry;

    for (int sec = 0; sec < ROOT_DIR_SECTORS; sec++)
    {

        read_disk_sector(ROOT_DIR_LBA + sec, sector);
        for (int i = 0; i < 512; i+= sizeof(TOFS_DirEntry))
        {
            entry = (TOFS_DirEntry*)&sector[i];
            if (entry->file_name[0] != 0x00 && entry->file_name[0] != 0xe5)
            {
                read_disk_sector(cluster_to_lba(entry->cluster_pointer), (unsigned char*)out_buffer);
                out_buffer[entry->file_size] = '\0';
                return 1;
            }
        }
    }
    return 0;
}