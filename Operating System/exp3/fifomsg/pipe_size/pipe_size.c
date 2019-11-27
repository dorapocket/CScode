#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int _pipe[2];
    if(pipe(_pipe)==-1)
    {
        printf("create pipr error\n");
        return 1;
    }
    int ret;
    int count=0;
    int flag=fcntl(_pipe[1],F_GETFL);
    fcntl(_pipe[1],F_SETFL,flag|O_NONBLOCK);
    while(1)
    {
        ret=write(_pipe[1],"0",1);
        if(ret==-1)
        {
            printf("pipe full!\n");
            break;
        }
        count++;
    }
    printf("size=%d\n",count);
    return 0;
}
