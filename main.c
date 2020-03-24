#include <stdio.h>



void main()
{
	int item;
	printf("Please item which item do you want test:\n");
	printf("1.CPU Zlib \n");
	printf("2.CPU Blowfish \n");
	printf("3.CPU CryptoHash \n");
	printf("4.CPU Fibnocci \n");
	printf("5.CPU N-Queen \n");
	printf("Please Check(Input 'q' to exit):");
	while(1)
	{
		scanf("%d",&item);
		if(item == 'q'){
			cout<<"Quit test."<<endl;
			return;
		}else if(item > 0 && item < 6)
		{
			//创建对象，调用方法
		}else{
			break;
		}
	}
}
