/*server.c*/
#include"unistd.h"
#include"fcntl.h"
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
int main()
{
printf("******exp3-2 FIFO MSG Server******\n");
int ret;
       ret=mkfifo("./fifo",0777);
       if(ret<0)
       {
              printf("creat fifo failure\n");
       }
       printf("Creat fifo sucess\n");
       int fd;
       char rdbuf[128]={0};
       fd=open("./fifo",O_RDONLY);
       if(fd<0)
       {
              printf("Do not have fifo files! Generate first!\n");
       }
	printf("Server Ready!");
       while(1)
       {
              read(fd,rdbuf,128);
              printf("recive:%s",rdbuf);
              if(!strcmp(rdbuf,"quit\n"))
              break;
              memset(rdbuf,0,128);
       }
       sleep(1);
       close(fd);
       return 0;
}
