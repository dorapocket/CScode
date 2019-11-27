#include<stdio.h>
#include"function/api.h"
#include"global/var.h"
#include"util/disk.h"
#include"shell/shell.h"
#include"util/time.h"
char sysname[20]="FS";
char pwd[80];
//int BLOCK_SIZE=1024;
//int BLOCK_NUMS=1024;
FILE * DISK;
BLOCK0 block0;
FATitem FAT1[FAT_ITEM_NUM];
FATitem FAT2[FAT_ITEM_NUM];
FCB presentFCB;
useropen uopenlist[MAX_FD_NUM];
char * type[2]={"file","directory"};
int main()
{
    startsys();
    go();
    return 0;
}
