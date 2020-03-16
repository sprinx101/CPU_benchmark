#include<iostream>
using namespace std;


void main()
{
	int item;
	cout<<"Please item which item do you want test:"<<endl;
	cout<<"1.CPU Zlib "<<endl;
	cout<<"2.CPU Blowfish "<<endl;
	cout<<"3.CPU CryptoHash "<<endl;
	cout<<"4.CPU Fibnocci "<<endl;
	cout<<"5.CPU N-Queen "<<endl;
	cout<<"Please Check:(Input 'q' to exit)";
	while(1)
	{
		cin>>item;
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
