#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
sem_t *w,*r;
int main(){
	int filedis[2];
	pipe(filedis);
	char buf[256];
	char *name1="writer";
	char *name2="reader";
	int x,y;
	w=sem_open(name1,O_CREAT,0666,1);//写信号量
	r=sem_open(name2,O_CREAT,0666,0);//读信号量
	//sem_getvalue(w,&x);
	//if(x==0) sem_post(w);
	pid_t pid1,pid2,pid3;
	pid1=1;pid2=1;pid3=1;//初始化pid
	pid1=fork();
	if(pid1>0) pid2=fork();
	if(pid1>0&&pid2>0) pid3=fork();//连续创建三个子进程
	if(pid1==0){
		close(filedis[0]);//0为读管道
		sem_wait(w);//写管道阻塞
		printf("This is child 1\n");
		write(filedis[1],"Hey I am Child 1 ",strlen("Hey I am Child 1 "));
		sem_post(w);
		sem_post(r);//写好了
		exit(0);
	}
	if(pid2==0){
		close(filedis[0]);
		sem_wait(w);
		printf("This is child 2\n");
		write(filedis[1],"Hey I am Child 2 ",strlen("Hey I am Child 2 "));
		sem_post(w);
		sem_post(r);
		exit(0);
	}		
	if(pid3==0){
		close(filedis[0]);
		sem_wait(w);
		printf("This is child 3\n");
		write(filedis[1],"Hey I am Child 3 ",strlen("Hey I am Child 3 "));
		sem_post(w);
		sem_post(r);
		exit(0);
	}
	if(pid1>0&&pid2>0&&pid3>0){
		sem_wait(r);//三个都好了
		sem_wait(r);
		sem_wait(r);
		sem_wait(w);
		printf("This is father ,I got child messages:");
		close(filedis[1]);//1为写
		read(filedis[0],buf,sizeof(buf));
		printf("%s\n",buf);
		sem_post(w);
	}	
}
