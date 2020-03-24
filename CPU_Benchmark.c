#include "CPU_Benchmark.h"

void BenchMark_Result(int _item)
{
	switch(_item)
	{
		case 'q':
			return;break;
		case 5:
			benchmark_nqueens();break;
		defalut:
			printf("还没实现\n");
			return;break;
	}
}

