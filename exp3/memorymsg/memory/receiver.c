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
         int shmid = shmget((key_t)8888, 50, IPC_CREAT | 0666);
         sem_t *mutex1 = sem_open("mutex1", O_CREAT | O_RDWR, 0666, 0);
         sem_t *mutex2 = sem_open("mutex2", O_CREAT | O_RDWR, 0666, 0);

         sem_wait(mutex1);

         char *m =(char *)shmat(shmid, NULL, 0);
         printf("receive: %s \n",m);
         strcpy(buf, "over");
         memcpy(m,buf,sizeof(buf));

         shmdt(shmid);
         sem_post(mutex2);

         return 0;

}
