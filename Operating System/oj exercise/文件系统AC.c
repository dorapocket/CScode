/*
文件系统程序设计
题目描述
请编写一个模拟文件系统管理的C语言程序，实现文件系统的基本功能模块，具体需要实现以下几部分功能：
1. pwd：输出当前目录（初始的根目录名为"...",输出为".../")，如根目录下xxx目录为”…/xxx/”；
2. ls：按创建顺序输出当前目录下的文件及文件夹，为空则输出空行；
3. cat filename：查看某个文件中内容，filename格式（严格）为"./XXX/....."代表当前目录下的XXX目录下级文件，或者".../XXX/...."代表根目录下XXX目录下级文件。如果找到了目标且目标是一个文件输出其内容，内容为空则输出空行;否则输出"error"；
4. makdir filename：在当前目录下创建目录，filename为字母型字符串；
5. touch filename：在当前目录下创建文件，filename为字母型字符串；
6. tac filename content：打开文件并且将其中内容替换为content filename格式同cat,并且找到了目标且是一个文件才进行（替换式）写入（注意有可能出现空格），否则输出"error"；
7. cd dirname：进入dirname目录中，dirname格式为字母字符串或者".."或者".../XXX..."或为空（注意没有"./…"型)，分别代表本目录下dirname目录，上一级目录，根目录下XXX目录下级目录，根目录。当目标不存在（根目录的上一级仍然为根目录，是存在的）或者目标为文件时输出error；
8.输入不正确的命令，输出"error"；
利用脚本程序测试系统的功能，输入信息：第一行有一个数字n代表输入的命令数；后面n行分别根据描述中的格式输入命令，特别注意这里文件名和目录名都没有重名的存在其文件名中不会有’/’和’.’，测试用例不会输入非法输入。
 
输入描述
输入信息：
    第一行有一个数字n代表输入的命令数；后面n行分别根据描述中的格式输入命令，特别注意这里文件名和目录名都没有重名的存在其文件名中不会有’/’和’.’，测试用例不会输入非法输入。
 
输出描述
输出信息：
    目录、路径和文件内容等信息，每项为一行，命令执行时没有输出信息系统不显示。
 
输入样例
输入信息：
4
ls
makdir aaa
pwd
ls
 
输出样例
输出信息：
…/
aaa
*/

#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include <malloc.h>
#define DIR 1
#define FILE 2

struct MyFile {
	const char* filename;
	char* content;
	const char* fullname;
	int dir;
};
struct MyDir {
	int father;
	const char* dirname;
	const char* fullname;
};
struct MyDir* root;
int now = 0;
struct MyDir* initDir(char* dirname, char* fullname, int father);
struct MyFile* initFile(char* filename, char* fullname, int dir);
struct MyFile* allfile[100];
struct MyDir* alldir[100];
int alldirn = 0;
char rn[10] = { ".../" };
char rn1[10] = { "..." };
int allfilen = 0;
int main() {
	int commandcnt, i, k;
	int lsn;
	char* temp;
	char* buffer;
	char* para;
	char* para2;
	char* para3;
	char* para4;
	char full[100] = { '\0' };
	int flag1 = 0;
	int flag2 = 0;
	char readall[100] = { '\0' };
	int ia = 0;
	char* a;
	root = initDir(rn1, rn, 0);
	now = 0;
	scanf("%d", &commandcnt);
	getchar();
	while (commandcnt--) {
		scanf("%[^\n]", &readall);
		getchar();
		buffer = strtok(readall, " ");
		para = strtok(NULL, " ");
		para2 = strtok(NULL, " ");
		para3 = strtok(NULL, " ");
		para4 = strtok(NULL, " ");
		if (strcmp(buffer, "pwd") == 0) {
			printf(alldir[now]->fullname);
			printf("\n");
			flag1 = 1;
		}
		else
			if (strcmp(buffer, "ls") == 0) {
				lsn = alldirn;
				for (i = 0; i < lsn; i++) {
					if (alldir[i]->father == now && i != 0)
						printf("%s ", alldir[i]->dirname);
				}
				lsn = allfilen;
				for (i = 0; i < lsn; i++) {
					if (allfile[i]->dir == now)
						printf("%s ", allfile[i]->filename);
				}
				printf("\n");
				flag1 = 1;
			}
			else
				if (strcmp(buffer, "cat") == 0) {
					flag2 = 0;
					if (para[1] == '/') {
						strcpy(full, alldir[now]->fullname);
						for (i = 2; para[i - 1] != '\0'; i++) {
							para[i - 2] = para[i];
						}
						strcat(full, para);
					}
					else {
						strcpy(full, "");
						strcat(full, para);
					}
					for (i = 0; i < allfilen; i++) {
						if (strcmp(full, allfile[i]->fullname) == 0) {
							flag2 = 1;
							if (allfile[i]->content == NULL) {
								printf("\n");
							}
							else
								printf("%s\n", allfile[i]->content);
						}
					}
					if (flag2 == 0) {
						printf("error\n");
					}
					flag1 = 1;
				}
				else
					if (strcmp(buffer, "makdir") == 0) {
						temp = (char*)malloc(50 * sizeof(char));
						strcpy(temp, alldir[now]->fullname);
						strcat(temp, para);
						strcat(temp, "/");
						initDir(para, temp, now);
						flag1 = 1;
					}
					else
						if (strcmp(buffer, "touch") == 0) {
							temp = (char*)malloc(50 * sizeof(char));
							strcpy(temp, alldir[now]->fullname);
							strcat(temp, para);
							initFile(para, temp, now);
							flag1 = 1;
						}
						else
							if (strcmp(buffer, "tac") == 0) {
								flag2 = 0;
								if (para[1] == '/') {
									strcpy(full, alldir[now]->fullname);
									for (i = 2; para[i - 1] != '\0'; i++) {
										para[i - 2] = para[i];
									}
									strcat(full, para);
								}
								else {
									strcpy(full, "");
									strcat(full, para);
								}
								if (para3 != NULL) {
									ia = 0;
									a = (char*)malloc(sizeof(char) * 100);
									while (para3[ia] != '\0') {
										a[ia] = para3[ia];
										ia++;
									}
									a[ia] = '\0';

									strcat(para2, " ");
									strcat(para2, a);
								}
								if (para4 != NULL) {
									strcat(para2, " ");
									strcat(para2, para4);
								}
								for (i = 0; i < allfilen; i++) {
									if (strcmp(full, allfile[i]->fullname) == 0) {
										ia = 0;
										a = (char*)malloc(sizeof(char) * 100);
										while (para2[ia] != '\0') {
											a[ia] = para2[ia];
											ia++;
										}
										a[ia] = '\0';

										allfile[i]->content = a;
										flag2 = 1;
									}
								}
								if (flag2 == 0) {
									printf("error\n");
								}
								flag1 = 1;
							}
							else
								if (strcmp(buffer, "cd") == 0) {
									flag2 = 0;
									if (para == NULL) {
										flag2 = 1;
										now = 0;
									}
									else
										if (strcmp(para, "..") == 0) {
											now = alldir[now]->father;
											flag2 = 1;
										}
										else
											if (para[0] == '.' && para[1] == '.' && para[2] == '.') {
												strcat(para,"/");
												for (i = 0; i < alldirn; i++) {
													if (strcmp(para, alldir[i]->fullname) == 0) {
														now = i;
														flag2 = 1;
													}
												}
											}
											else
												if (para[0] != '.') {
													strcpy(full, alldir[now]->fullname);
													strcat(full, para);
													strcat(full, "/");
													for (i = 0; i < alldirn; i++) {
														if (strcmp(full, alldir[i]->fullname) == 0) {
															now = i;
															flag2 = 1;
														}
													}
										
												}
									if (flag2 == 0) {
										printf("error\n");
									}
									flag1 = 1;
								}
		if (flag1 == 0) {
			printf("error\n");
		}
	}
}

struct MyDir* initDir(char* dirname, char* fullname, int father) {
	struct MyDir* temp = (struct MyDir*)malloc(sizeof(struct MyDir));
	int ia = 0;
	char* name = (char*)malloc(sizeof(char) * 20);
	while (dirname[ia] != '\0') {
		name[ia] = dirname[ia];
		ia++;
	}
	name[ia] = '\0';
	temp->dirname = name;
	temp->fullname = fullname;
	temp->father = father;
	alldir[alldirn] = temp;
	alldirn++;
	return temp;
}
struct MyFile* initFile(char* filename, char* fullname, int dir) {
	struct MyFile* temp = (struct MyFile*)malloc(sizeof(struct MyFile));

	int ia = 0;
	char* name = (char*)malloc(sizeof(char) * 20);
	while (filename[ia] != '\0') {
		name[ia] = filename[ia];
		ia++;
	}
	name[ia] = '\0';


	temp->filename = name;
	temp->content = NULL;
	temp->fullname = fullname;
	temp->dir = dir;
	allfile[allfilen] = temp;
	allfilen++;
	return temp;
}