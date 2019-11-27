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

        int shmid1 = shmget((key_t)8890, 50, IPC_CREAT | 0666); //创建共享内存8888
	int shmid2 = shmget((key_t)8891, 50, IPC_CREAT | 0666); //创建共享内存8889
        shmctl((key_t)8890, IPC_RMID, NULL);//控制 写null
	shmctl((key_t)8891, IPC_RMID, NULL);//控制 写null
        sem_unlink("mutex1");//删除两个信号量
        sem_unlink("mutex2");
	sem_unlink("mutex3");
	sem_unlink("mutex4");
        sem_t *mutex1 = sem_open("mutex1", O_CREAT | O_RDWR, 0666, 0);//创建信号量
        sem_t *mutex2 = sem_open("mutex2", O_CREAT | O_RDWR, 0666, 0);
	sem_t *mutex3 = sem_open("mutex3", O_CREAT | O_RDWR, 0666, 0);
	sem_t *mutex4 = sem_open("mutex4", O_CREAT | O_RDWR, 0666, 0);
        shmid1 = shmget((key_t)8890, 50, IPC_CREAT | 0666);//创建
	shmid2 = shmget((key_t)8891, 50, IPC_CREAT | 0666);//创建

        if( shmid1 == -1 || shmid2==-1){
            printf("create failed");
            exit(-1);
        }
	pid_t pid1=fork();
	if(pid1==0){
while(1){
		sem_wait(mutex3);
		char *n = (char *)shmat(shmid2, NULL, 0);//启动对共享内存访问 拉到当前地址空间
		printf("\nreceive:%s\n",n);
		strcpy(buf, "over");
        	memcpy(n,buf,sizeof(buf));
		shmdt(shmid2);//分离共享内存
		sem_post(mutex4);
}
	}
	if(pid1>0){
while(1){
		char *m = (char *)shmat(shmid1, NULL, 0);//启动对共享内存访问 拉到当前地址空间
        	printf("\nwriting:");
        	scanf("%s", buf);
        	memcpy(m,buf,sizeof(buf));
		shmdt(shmid1);//分离共享内存
        	sem_post(mutex1); //m1标志1已经发送

		sem_wait(mutex2);
		m = (char *)shmat(shmid1, NULL, 0);//启动对共享内存访问 拉到当前地址空间
		printf("\nreturn:%s\n", m);//返回的信息
		shmdt(shmid1);
}
	}
        shmctl((key_t)8890, IPC_RMID, NULL);//删除共享内存
	shmctl((key_t)8891, IPC_RMID, NULL);//删除共享内存
        sem_unlink("mutex1");//删除信号量
        sem_unlink("mutex2");
	sem_unlink("mutex3");
	sem_unlink("mutex4");
        return 0;
}
