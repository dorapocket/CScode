/*
1.   (18分)

链表程序设计
题目描述
请用C语言编写一个管理程序，以链表的方式管理学生信息typedef struct _student
{      char no[10];
	char name[20];
	int  age;
	int  ranking;
	struct _student *next;
} student_t, *pstudent_t;。编程实现输入10位学生的信息，对于学生信息节点的查找find、排序sort、添加append、修改modify、删除delete和插入insert等功能。
 
输入描述
输入学生信息例子：
170210 tomy 20 3
170209 jone 22 6
170208 thomas 18 5 
170207 lily 18 7 
170206 amy 19 8 
170205 nice 21 2 
170204 ouot 19 1 
170203 sice 18 4
170202 davie 21 9 
170201 rash 22 10
 
输出描述
输出查找find、排序sort、添加append、修改modify、删除delete和插入insert命令处理后的学生学号列表。
命令：sort
输出：170204 170205 170210 170203 170208 170209 170207 170206 170202 170201
命令：find 3(排名)
输出：170210
命令：append 170211 gase 21 15
输出：170204 170205 170210 170203 170208 170209 170207 170206 170202 170201 170211
命令：modify 170203 5(排名)
输出：170203 5
命令：delete 170208(学号)
输出：170204 170205 170210 170203 170209 170207 170206 170202 170201
命令：insert 170209 170211 gase 21 15
输出：170204 170205 170210 170203 170208 170209 170211 170207 170206 170202 170201
 
输入样例
170210 tomy 20 3
170209 jone 22 6
170208 thomas 18 5 
170207 lily 18 7 
170206 amy 19 8 
170205 nice 21 2 
170204 ouot 19 1 
170203 sice 18 4
170202 davie 21 9 
170201 rash 22 10
sort
 
输出样例
170204 170205 170210 170203 170208 170209 170207 170206 170202 170201
*/


#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
typedef struct _student
{
	char no[10];
	char name[20];
	int  age;
	int  ranking;
	struct _student* next;
} student_t, * pstudent_t;
void appendin(const char *ano, const char * aname, int aage, int aranking, pstudent_t head);
void printList(pstudent_t head);
void sortList(pstudent_t a);
void find(int rank, pstudent_t head);
void modify(const char* stuno, int rank, pstudent_t head);
void deleteout(const char* stuno, pstudent_t head);
void insertin(const char* prev, const char* no, const char* name, int age, int rank, pstudent_t head);
int main() {
    int arg = 0;
	char tno[10]; char tname[10]; int tage; int trank;
	char mno[10]; int mrank;
	char qno[10];
	char wpre[10]; char wno[10]; char wname[10]; int wage; int wrank;
	char num[10];
	char name[10];
	int age;
	int rank;
    int i=0;
    char command[20];
    pstudent_t head= (pstudent_t)malloc(sizeof(student_t));
	head->next = NULL;
	for (i = 0; i < 10; i++) {
		scanf("%s %s %d %d",num,name,&age,&rank);
		appendin(num, name, age, rank, head);
	}
	scanf("%s", command);
	if (strcmp(command, "sort") == 0) {
		sortList(head);
		printList(head);
	}
	if (strcmp(command, "find") == 0) {
		scanf("%d", &arg);
		find(arg, head);
	}
	if (strcmp(command, "append") == 0) {
		scanf("%s %s %d %d",tno,tname,&tage,&trank);
		appendin(tno,tname, tage, trank, head);
		printList(head);
	}
	if (strcmp(command, "modify") == 0) {
		scanf("%s %d", mno, &mrank);
		modify(mno,mrank, head);
	}
	if (strcmp(command, "delete") == 0) {
		scanf("%s", qno);
		deleteout(qno, head);
		printList(head);
	}
	if (strcmp(command, "insert") == 0) {
		scanf("%s %s %s %d %d",wpre,wno,wname,&wage,&wrank);
		insertin(wpre,wno,wname, wage,wrank, head);
        printList(head);
	}
}
void appendin(const char * ano,const char * aname, int aage, int aranking, pstudent_t head) {
    pstudent_t p;
	pstudent_t q;
	q = head;
	while (q->next != NULL) { q = q->next; }
	p = (pstudent_t)malloc(sizeof(student_t));
	strcpy(p->no, ano);
	strcpy(p->name, aname);
	p->age = aage;
	p->ranking = aranking;
	p->next = NULL;
	q->next = p;
}
void printList(pstudent_t head) {
	pstudent_t p = head->next;
	while (p != NULL) {
		printf("%s ", p->no);
		p = p->next;
	}
}
void sortList(pstudent_t a) {
    int i=0;
	pstudent_t head = a;
	pstudent_t prev = a;
	pstudent_t p = prev->next;
	for (i = 0; i < 10; i++) {
		prev = a;
		p = prev->next;
		while (p->next != NULL) {
			if (p->ranking > p->next->ranking) {
				prev->next = p->next;
				p->next = p->next->next;
				prev->next->next = p;
			}
			prev = prev->next;
			p = prev->next;
		}
	}
}
void find(int rank, pstudent_t head) {
	pstudent_t p = head->next;
	while (p != NULL) {
		if (p->ranking == rank) {
			break;
		}
		p = p->next;
	}
	printf("%s",p->no);
}
void modify(const char* stuno, int rank, pstudent_t head) {
	pstudent_t p = head->next;
	while (p != NULL) {
		if (strcmp(stuno,p->no)==0) {
			break;
		}
		p = p->next;
	}
	p->ranking = rank;
	printf("%s %d", p->no, p->ranking);
}
void deleteout(const char* stuno, pstudent_t head) {
	pstudent_t prev = head;
	pstudent_t p = prev->next;
	while (p!=NULL)
	{
		if (strcmp(stuno, p->no) == 0) {
			break;
		}
		prev = prev->next;
		p = prev->next;
	}
	prev->next = p->next;
	p->next = NULL;
	free(p);
}
void insertin(const char* prev, const char* no,const char* name,int age,int rank, pstudent_t head) {
	pstudent_t p = head->next;
    pstudent_t news;
	while (p!=NULL)
	{
		if (strcmp(prev, p->no) == 0) {
			break;
		}
		p = p->next;
	}
	news = (pstudent_t)malloc(sizeof(student_t));
	strcpy(news->no, no);
	strcpy(news->name, name);
	news->age = age;
	news->ranking = rank;
	news->next = p->next;
	p->next = news;
}