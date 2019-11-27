/*client.c*/
#include"unistd.h"
#include"fcntl.h"
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
int main()
{
printf("******EXP3-2 FIFO MSG Client******");
int fd;
char wrbuf[128];
fd=open("./fifo",O_WRONLY);
if(fd<0)
{
       printf("open fifo failure\n");
       return -1;
}
while(1)
{
       memset(wrbuf,0,sizeof(wrbuf));
       fgets(wrbuf,128,stdin);
       write(fd,wrbuf,strlen(wrbuf));
       if(!strcmp(wrbuf,"quit\n"))
       {
              break;
       }
}
sleep(1);
close(fd);
return 0;
}
