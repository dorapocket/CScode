#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include <fcntl.h>
int main(){

         char buf[50];
         int shmid1 = shmget((key_t)8890, 50, IPC_CREAT | 0666);//打开共享内存
	 int shmid2 = shmget((key_t)8891, 50, IPC_CREAT | 0666);//打开共享内存
         sem_t *mutex1 = sem_open("mutex1", O_CREAT | O_RDWR, 0666, 0);//打开信号量
         sem_t *mutex2 = sem_open("mutex2", O_CREAT | O_RDWR, 0666, 0);
	 sem_t *mutex3 = sem_open("mutex3", O_CREAT | O_RDWR, 0666, 0);
	 sem_t *mutex4 = sem_open("mutex4", O_CREAT | O_RDWR, 0666, 0);
pid_t pid2=fork();
	if(pid2==0){
while(1){
		sem_wait(mutex1)；//等待发送过来
		char *m = (char *)shmat(shmid1, NULL, 0);//启动对共享内存访问 拉到当前地址空间
         	printf("\nreceive: %s \n",m);
         	strcpy(buf, "over");
         	memcpy(m,buf,sizeof(buf));
		shmdt(shmid1);
	 	sem_post(mutex2);//回传
}
	}
if(pid2>0){while(1){
	char *n = (char *)shmat(shmid2, NULL, 0);//启动对共享内存访问 拉到当前地址空间
        printf("\nwriting:");
        scanf("%s", buf);
        memcpy(n,buf,sizeof(buf));
	shmdt(shmid2);
        sem_post(mutex3);
        sem_wait(mutex4);
	n = (char *)shmat(shmid2, NULL, 0);//启动对共享内存访问 拉到当前地址空间
	printf("\nreturn:%s\n", n);//返回的信息
	shmdt(shmid2);}
}
         return 0;
}
