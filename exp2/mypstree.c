#include <stddef.h>
#include <linux/vmalloc.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched/signal.h>
static int spid;
module_param(spid,int,0644);

char* print_process(struct task_struct *p,int depth,char* buffer_pointer, int *indenti,int *isnewline);
char* visit(struct task_struct *p,int depth,char* buffer_pointer,int* isnewline);

void sys_mypstree(char *buffer2copy){
	int depth = 0;
	int isnewline = 1;
	struct task_struct *p = current;
	char* buffer = (char*)vmalloc(64*1024);
	while(p -> pid != 1)
		p = p -> parent;
	for_each_process(p){
		if(p->pid==spid){
			//p=p->parent;
			visit(p->real_parent,depth,buffer,&isnewline);
		}
	}
	printk(buffer);
	//copy_to_user(buffer2copy,buffer,64*1024);			
}
char* print_process(struct task_struct *p,int depth,char* buffer_pointer,int *indent,int* isnewline){
	//printk("print_process 0 : depth : %d  indent : %d isnewline: %d \n",depth,*indent,*isnewline);
	char* ptr = buffer_pointer;
	int i = 0;
	if(p == NULL){
		*ptr = '\n';
		ptr++;
		return ptr;
	}
	if(*isnewline == 1){
		*indent = 0;
		while(i < depth){
			*ptr = ' ';
			ptr++;
			i ++;
			(*indent) ++;
		}
	}
	*isnewline = 0;
	if(depth != 0){
		*ptr = '-';
		ptr ++;
		*ptr = '-';
		ptr ++;
		*ptr = '|';
		ptr++;
		*ptr = '-';
		ptr++;
		*ptr = '-';
		ptr ++;
		(*indent) += 5;
	}
	memcpy(ptr,p->comm,strlen(p->comm));
	ptr += strlen(p->comm);
	(*indent) += strlen(p->comm);
	return ptr;
}
char* visit(struct task_struct *p,int depth,char* buffer_pointer,int* isnewline){
	struct list_head *pos;
	struct task_struct *childTask;
	char* ptr = NULL;
	int indent = depth;
	ptr =  print_process(p,depth,buffer_pointer,&indent,isnewline);

	if(p -> pid == 1)
		depth = 4;
	else
		depth = indent;
	if((&(p -> children))->next == &(p->children)){
		*ptr = '\n';
		ptr ++;
		*isnewline = 1;
		return ptr;
	}
	list_for_each(pos,&(p -> children)){
		childTask = list_entry(pos,struct task_struct,sibling);
		ptr = visit(childTask,depth,ptr,isnewline);
			//printk("%s",ptr);
	}
	return ptr;
}
static int __init init_pstree(void){
	printk("HI!");
	char* a = (char*)vmalloc(64*1024);
	sys_mypstree(a);
	printk(a);
return 0;
}
static void __exit exit_pstree(void){
	
}
MODULE_LICENSE("GPL");
module_init(init_pstree);
module_exit(exit_pstree);
