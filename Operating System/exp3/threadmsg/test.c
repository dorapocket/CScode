#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <fcntl.h>
#define MSG_MAX 100

struct my_msgbuf{
      long int mtype;
      char mtext[MSG_MAX];
};


void *sender1(){
       int n;
       struct my_msgbuf message;
       char buf[MSG_MAX];
       sem_t *mutex = sem_open("mutex", O_CREAT | O_RDWR, 0666, 0);
       sem_t *sender1_over = sem_open("sender1_over", O_CREAT | O_RDWR, 0666, 0);
       sem_t *receive1_over = sem_open("receive1_over", O_CREAT | O_RDWR, 0666, 0);
       int msqid = msgget((key_t)8088, 0666 | IPC_CREAT);
       if( msqid == -1){
             printf("create failed");
             exit(-1);
       }

       while(1){
             sem_wait(mutex);
             printf("sender1:");
             scanf("%s", &buf);
             printf("\n");
             message.mtype = 1;
             if(strcmp(buf,"exit") == 0){
                     strcpy(message.mtext,"end1");
                     n = msgsnd(msqid, (void *)&message, 100, 0);
                     sem_wait(receive1_over);
                     n = msgrcv(msqid, (void *)&message, 100, 2, 0);
                     printf("%s\n", message.mtext);

                     sem_post(sender1_over);
                     sem_post(mutex);
                     sleep(1);
                     return 0;
             }
             else{
                     strcpy(message.mtext,buf);
                     n = msgsnd(msqid, (void *)&message, 100, 0);
                     sem_post(mutex);
                     sleep(1);
             }

       }

}


void *sender2(){
       int n;
       struct my_msgbuf message;
       char buf[MSG_MAX];
       sem_t *mutex = sem_open("mutex", O_CREAT | O_RDWR, 0666, 0);
       sem_t *sender2_over = sem_open("sender2_over", O_CREAT | O_RDWR, 0666, 0);
       sem_t *receive2_over = sem_open("receive2_over", O_CREAT | O_RDWR, 0666, 0);
       int msqid = msgget((key_t)8088, 0666 | IPC_CREAT);
       if( msqid == -1){
             printf("msq create failed");
             exit(-1);
       }

       while(1){
             sem_wait(mutex);
             printf("sender2:");
             scanf("%s", &buf);
             printf("\n");
             message.mtype = 1;
             if(strcmp(buf,"exit") == 0){
                     strcpy(message.mtext,"end2");
                     n = msgsnd(msqid, (void *)&message, 100, 0);
                     sem_wait(receive2_over);
                     n = msgrcv(msqid, (void *)&message, 100, 3, 0);
                     printf("%s\n", message.mtext);
                     sem_post(sender2_over);
                     sem_post(mutex);
                     sleep(1);
                     return 0;
             }
             else{
                     strcpy(message.mtext,buf);
                     n = msgsnd(msqid, (void *)&message, 100, 0);
                     sem_post(mutex);
                   sleep(1);
             }
       }

}


void *receive(){
           int n;
           int over1=0;
           int over2=0;
           struct my_msgbuf message;
           char buf[MSG_MAX];
           sem_t *sender1_over = sem_open("sender1_over", O_CREAT | O_RDWR, 0666, 0);
           sem_t *receive1_over = sem_open("receive1_over", O_CREAT | O_RDWR, 0666, 0);
           sem_t *sender2_over = sem_open("sender2_over", O_CREAT | O_RDWR, 0644, 0);
           sem_t *receive2_over = sem_open("receive2_over", O_CREAT | O_RDWR, 0666, 0);
           int msqid = msgget((key_t)8088, 0666 | IPC_CREAT);

           if( msqid == -1){
               printf("create failed");
               exit(-1);
           }

           while(1){
                   n = msgrcv(msqid, (void *)&message, 100, 0, 0);
                   if(n > 0){
                         printf("\n*************\nreceive:%s\n*************\n", message.mtext);
                         if( strcmp(message.mtext,"end1") == 0 ){
                               message.mtype = 2;
                               strcpy(message.mtext,"over1");
                               n = msgsnd(msqid, (void *)&message, 100, 0);
                               if( n == 0 ){
                                   sem_post(receive1_over);

                                   sem_wait(sender1_over);

                               }
                               over1 = 1;
                         }else if( strcmp(message.mtext,"end2") == 0 ){
                               message.mtype = 3;
                               strcpy(message.mtext,"over2");
                               n = msgsnd(msqid, (void *)&message, 100, 0);
                               if( n == 0 ){
                                   sem_post(receive2_over);
                                   sem_wait(sender2_over);
                               }
                               over2 = 1;
                         }

                   }
                   if(over1==1 && over2==1){
                       msgctl(msqid, IPC_RMID, 0);
                       exit(0);
                   }
                   sleep(1);
           }

}





int main(){
           int msqid = msgget((key_t)8088, 0666 | IPC_CREAT);
           msgctl(msqid, IPC_RMID, 0);
           sem_unlink("mutex");
           sem_unlink("sender1_over");
           sem_unlink("sender2_over");
           sem_unlink("receive1_over");
           sem_unlink("receive2_over");

           sem_t *mutex = sem_open("mutex", O_CREAT | O_RDWR, 0666, 0);
           sem_t *sender1_over = sem_open("sender1_over", O_CREAT | O_RDWR, 0666, 0);
           sem_t *receive1_over = sem_open("receive1_over", O_CREAT | O_RDWR, 0666, 0);
           sem_t *sender2_over = sem_open("sender2_over", O_CREAT | O_RDWR, 0666, 0);
           sem_t *receive2_over = sem_open("receive2_over", O_CREAT | O_RDWR, 0666, 0);

           pthread_t pt1,pt2,pt3;
           pthread_create(&pt1, NULL, sender1, NULL);
           pthread_create(&pt2, NULL, sender2, NULL);
           pthread_create(&pt3, NULL, receive, NULL);
           sem_post(mutex);
           pthread_join(pt1, NULL);
           pthread_join(pt2, NULL);
           pthread_join(pt3, NULL);
           return 0;
}
