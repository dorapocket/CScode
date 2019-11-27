/*

进程调度程序设计
题目描述
请编写一个C语言程序，模拟若干进程调度执行的情况。假设进程的状态分为执行和就绪两种。每个进程以其PCB为代表即可，无需创建真正的进程。以链表的方式组织PCB，分为二个队列：readyQueue就绪队列和runningQueue执行队列。
程序开始运行时，用户输入进程调度方式：先来先服务（FCFS）或短进程优先（SPF），进程数量n，以及每个进程需要运行的时间t0/t1/…/tn，先创建进程PCB，然后插入到readyQueue队列中。
程序先从就绪队列中按FCFS或SPF选择一个进程投入运行（注：需要将该PCB中的状态变量赋值为“运行”）。相应的修改其所在队列，再将原来处于运行态的进程需要转变为“就绪”态，插入readyQueue队列。
假设时间片是2，进程每次调度运行后，其还需运行的时间应该减少2，直至为0，即表示该进程执行完毕。
示例片段代码：
#define READY         0x01
#define RUNNING    0x02
#define TIMESLICE  0x02 
typedef struct _PCB
{   int pid;    
int state;  
int time;  
    struct _PCB *next; 
} PCB, *pPCB;

输出信息:
FCFS/SPF order: P00 P01 P02 P00 P01 P02 P00 P01 P02
上述信息表示为FCFS/SPF调度时进程运行顺序。
 
输入描述
程序开始运行时，用户输入进程调度方式：先来先服务（FCFS）或短进程优先（SPF），进程数量n，以及每个进程需要运行的时间t0/t1/…/tn
 
输出描述
FCFS/SPF order: P00 P01 P02 P00 P01 P02 P00 P01 P02
上述信息表示为FCFS/SPF调度时进程运行顺序。
 
输入样例
fcfs 3
12 6 8
 
输出样例
fcfs order:P00 P01 P02 P00 P01 P02 P00 P01 P02 P00 P02 P00 P00
*/

#define READY      1
#define RUNNING    2
#define TIMESLICE  2
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
typedef struct _PCB
{   
    int pid;    
    int state;  
    int time;  
    struct _PCB *next; 
} PCB, *pPCB;
void doFCFS(pPCB head);
void doSPF(pPCB head);
void appendin(int apno,int aprotime, pPCB ahefcfsad);
void deleteone(pPCB head);
int main(){
    pPCB head= (pPCB)malloc(sizeof(PCB));
    int a;
    int nowpro=0;
    char type[10];
    int protime;
    head->next = NULL;
    scanf("%s %d",type,&a);
    while(a--){
        scanf("%d",&protime);
        appendin(nowpro,protime,head);
        nowpro++;
    }
    if(strcmp(type,"fcfs")==0||strcmp(type,"FCFS")==0){
        printf("%s order:",type);
        doFCFS(head);
    }else if(strcmp(type,"spf")==0||strcmp(type,"SPF")==0){
        printf("%s order:",type);
        doSPF(head);
    }
}
void appendin(int apno,int aprotime, pPCB ahead) {
    pPCB p;
	pPCB q;
	q = ahead;
	while (q->next != NULL) { q = q->next; }
	p = (pPCB)malloc(sizeof(PCB));
	p->pid = apno;
	p->time = aprotime;
    p->state=READY;
	p->next = NULL;
	q->next = p;
}
void deleteone(pPCB head) {
    pPCB n=head->next->next;
    free(head->next);
    head->next=n;
}
void sortList(pPCB a) {
    int i=0;
	pPCB head = a;
	pPCB prev = a;
	pPCB p = prev->next;
    if(a==NULL || a->next==NULL) return;
	for (i = 0; i < 200; i++) {
		prev = a;
		p = prev->next;
		while (p->next != NULL) {
			if (p->time > p->next->time) {
				prev->next = p->next;
				p->next = p->next->next;
				prev->next->next = p;
			}
			prev = prev->next;
			p = prev->next;
		}
	}
}
void doFCFS(pPCB head){
    PCB now;
	while (head->next != NULL) {
        now.pid=head->next->pid;
        now.state=RUNNING;
        now.time=head->next->time-TIMESLICE;
        now.next=head->next->next;
        deleteone(head);
        printf(" P%02d",now.pid);
        if(now.time>0){
            appendin(now.pid,now.time,head); 
        }
	}
}
void doSPF(pPCB head){
    PCB now;
    sortList(head);
	while (head->next != NULL) {
        now.pid=head->next->pid;
        now.state=RUNNING;
        now.time=head->next->time-TIMESLICE;
        now.next=head->next->next;
        if(now.next!=NULL){
            deleteone(head);
        }else{
            printf(" P%02d",now.pid);
            while(now.time>0){
                printf(" P%02d",now.pid);
                now.time-=2;
            }
            break;
        }
        sortList(head);
        printf(" P%02d",now.pid);
        if(now.time>0){
            appendin(now.pid,now.time,head); 
        }
	}
}