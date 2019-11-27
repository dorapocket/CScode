/*
银行家算法程序设计
题目描述
请编写一个实现银行家算法的程序，输入进程需要的最大资源需求，进程已经拥有的系统资源和还预留的系统资源，再输入T0时刻Pi申请的系统资源数，请用银行家算法进行安全性检查，如果系统安全，则输出进程运行的安全序列，如果系统不安全，输出unsafe。要求：按资源需求量最小优先的原则选取进程的运行顺序。
 
输入描述
请编写一个实现银行家算法的程序，输入进程需要的最大资源需求，进程已经拥有的系统资源和还预留的系统资源，再输入T0时刻Pi申请的系统资源数。
2 5  // 资源数  进程数
2 4  // 进程需要最大资源数
10 2
5 4
3 1
4 2
2 0   // 进程已拥有的资源数
3 2
1 4
2 1
0 0
2 7   // 系统预留的资源数
0 0 4  // 进程编号 申请数 0进程申请(0,4)
 
输出描述
如果存在安全序列输出：
safe order:P00 P03 P02 P04 P01
如果不存在安全序列输出：
unsafe
 
输入样例
2 5  
2 4
10 2
5 4
3 1
4 2
2 0
3 2
1 4
2 1
0 0
2 7
0 0 4
 
输出样例
safe order:P00 P03 P02 P04 P01
*/
#include<stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;
int* available;
int** max;
int** allocation;
int** need;
int* finish;
int* safe;
int* request;
int resourceNum;
int processNum;
int requestProcess;
int* torder;
int* forder;
void init() {
	int i = 0;
	int j = 0;
	int temp;
	scanf("%d %d", &resourceNum, &processNum);
	max = (int**)malloc(processNum * sizeof(int*));
	for (i = 0; i < processNum; i++) {
		max[i] = (int*)malloc(resourceNum * sizeof(int));
		for (j = 0; j < resourceNum; j++) {
			scanf("%d", &temp);
			max[i][j] = temp;
		}
	}
	allocation = (int**)malloc(processNum * sizeof(int*));
	for (i = 0; i < processNum; i++) {
		allocation[i] = (int*)malloc(resourceNum * sizeof(int));
		for (j = 0; j < resourceNum; j++) {
			scanf("%d", &temp);
			allocation[i][j] = temp;
		}
	}
	available = (int*)malloc(resourceNum * sizeof(int));
	for (i= 0; i < resourceNum; i++) {
		scanf("%d", &temp);
		available[i] = temp;
	}

	scanf("%d", &requestProcess);

	request = (int*)malloc(resourceNum * sizeof(int));
	for (i = 0; i < resourceNum; i++) {
		scanf("%d", &temp);
		request[i] = temp;
	}

	need = (int**)malloc(processNum * sizeof(int*));
	for (i = 0; i < processNum; i++) {
		need[i] = (int*)malloc(resourceNum * sizeof(int));
		for (j = 0; j < resourceNum; j++) {
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	finish = (int*)malloc(processNum * sizeof(int));
	safe = (int*)malloc(processNum * sizeof(int));
}
bool safeCheck() {
	int i, j, k;
	int trueFinished = 0;
	int test = 0;
	int temp = 0;

	int* work = (int*)calloc(resourceNum ,sizeof(int));
	for (i = 0; i < resourceNum; i++) {
		work[i] = available[i];
	}

	for (i = 0; i < processNum; i++) {
		finish[i] = false;
	}
	i = 0;
	while (trueFinished != processNum) {
		test++;
		j = 0;
		if (finish[forder[i]] != true) {
			for (j = 0; j < resourceNum; j++) {
				if (need[forder[i]][j] > work[j]) { break; }
			}
		}
		if (j == resourceNum) {
			finish[forder[i]] = true;
			for (k = 0; k < resourceNum; k++) {
				work[k] += allocation[forder[i]][k];
			}
			safe[trueFinished++] = forder[i];
		}
		i++;
		if (i >= processNum)
		{
			i = i % processNum;
			if (test > 300) break;
		}
		temp = trueFinished;
	}
	if (trueFinished == processNum) {
		printf("safe order:");
		for (i = 0; i < processNum; i++) {
			printf("P%02d ", safe[i]);
		}
		return true;
	}
	printf("unsafe");
	return false;
}
int main() {
	int i,j;

	int hh = 0;
	int q = 0;
	int k = 0;
	int tempmax, tempindex;
    int* order;
	init();
	for (j = 0; j < resourceNum; j++) {
		if (request[j] <= need[requestProcess][j])continue;
		else { printf("unsafe"); break; }
	}

	if (j == resourceNum) {
		for (j = 0; j < resourceNum; j++) {
			available[j] -= request[j];
			allocation[requestProcess][j] += request[j];
			need[requestProcess][j] -= request[j];
		}
		order = (int*)malloc(processNum * sizeof(int));
		torder = (int*)malloc(processNum * sizeof(int));
		forder = (int*)malloc(processNum * sizeof(int));
		for (i = 0; i < processNum; i++) {
			order[i] = 0;
			for (j = 0; j < resourceNum; j++) {
				order[i] += need[i][j];
			}
		}

		for (q = 0; q < processNum; q++) {
			tempmax = order[0];
			tempindex = 0;
			for (k = 0; k < processNum; k++)
			{
				if (order[k] < tempmax) {
					tempmax = order[k];
					tempindex = k;
				}
			}
			torder[tempindex] = hh;
			forder[hh] = tempindex;
			hh++;
			order[tempindex] = 9999;
		}
		safeCheck();
	}
}
