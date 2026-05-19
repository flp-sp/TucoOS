#include "fs.h"

unsigned int cluster_to_lba(unsigned short cluster)
{
    //regiao de inicio de dados + (primeira cluster - 2) * setores por cluster
    return DATA_LBA + (cluster - 2) * CLUSTER_PER_SECTORS; 
}