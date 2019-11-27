#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/wait.h>

void do_execvp(int argc,char* argv[])
{
	int flag=0;
	if(strcmp(argv[0],"cmd1")==0){
		argv[0]="./cmd1";
		flag=1;
	}else if(strcmp(argv[0],"cmd2")==0){
		argv[0]="./cmd1";
		flag=1;
	}else if(strcmp(argv[0],"cmd3")==0){
		argv[0]="./cmd1";
		flag=1;
	}else if(strcmp(argv[0],"grep")==0){
		flag=1;
	}else if(strcmp(argv[0],"find")==0){
		flag=1;
	}
if(flag==1){
    if(fork() == 0)//子进程会进入if
    {
        execvp(argv[0],argv);//内存替换
        perror("execvp");
        exit(0);//perror报错并退出程序
    }
    wait(NULL);//防止父进程和子进程并发运行
}else{
	printf("exp3-1 shell>> Command not found\n");
}
}


void do_parse(char* buf)
{
    char* argv[8]={};
    int argc=0;
    int i=0;
    int status=0;

    for(i=0;buf[i]!=0;i++)
    {
        if(status == 0 && !isspace(buf[i]))
        {
            argv[argc++]=buf+i;
            status=1;
        }
        else if(isspace(buf[i]))
        {
            status=0;
            buf[i]=0;
        }
    }
    argv[argc]=NULL;
    do_execvp(argc,argv);
}

int main()
{
    char buf[1024];
    while(1)
    {
        printf("exp3-1 shell>>");
        memset(buf,0,sizeof(buf));
        while(scanf("%[^\n]%*c",buf) == 0)
        {
            while(getchar()!='\n');
            printf("exp3-1 shell>>");
        }
        if(strncmp(buf,"exit",4) == 0 )
        {
            exit(0);
        }
        do_parse(buf);
    }
}
