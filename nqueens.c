#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "/opt/CPU_benchmark/include/benchmark.h"

#define BENCH_REVISION 0
#define QUEENS 11

int row[QUEENS];

bool safe(int x,int y)
{
	int i;
	for(i=1;i<=y;++i)
	{
		if(row[y-i] == x || row[y-i]==x-i || row[y-i]==x+j)
			return false;
	}
	return true;
}

int nquees(int y)
{
	int x;
	for(x=0;x<QUEENS;x++)
	{
		if(safe((row[y-1]=x),y-1)){
			if(y < QUEENS){
				nqueens(y+1);
			}else{

				break;
			}
		}
	}
	return 0;
}

static gpointer nqueens_for(unsigned int start,unsigned int end,void *data,gint thread_number)
{
	unsigned int i;
	for(i = start;i <= end;++i)
	{
		nqueens(0);
	}
	return NULL;
}

void benchmark_nqueens(void)
{
	bench_value r = EMPTY_BENCH_VALUE;
	r=benchmark_parallel_for(0,0,10.nqueens_for,NULL);
	r.result = r.elapsed_time;
	r.revision=BENCH_REVISION;
	//先做一个打印的处理，后面需要集合了再改
	printf("CPU N-Queens test result:%d \n",r.result);
	//保存到统一的结构体中??
}
