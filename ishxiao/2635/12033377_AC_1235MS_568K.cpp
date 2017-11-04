//2635 

#include<iostream>
#include<string.h>
using namespace std;

const int Range=1000100;  //打表不能只打到100W，素数表中最大的素数必须大于10^6

int Kt[10000];  //千进制的K
int L;
int prime[Range+1];

/*素数组打表*/
void PrimeTable(void)
{
	int pNum=0;
	prime[pNum++]=2;

	for(int i=3;i<=Range;i+=2)  //奇偶法
	{
		bool flag=true;
		for(int j=0;prime[j]*prime[j]<=i;j++)  //根号法+递归法
			if(!(i%prime[j]))
			{
				flag=false;
				break;
			}
		if(flag)
			prime[pNum++]=i;
	}
	return;
}

/*高精度K对p求模，因数检查(整除)*/
bool mod(const int* K,const int p,const int len)
{
	int sq=0;
	for(int i=len-1;i>=0;i--)  //千进制K是逆序存放
		sq=(sq*1000+K[i])%p;  //同余模定理

	if(!sq)   //K被整除
		return false;
	return true;
}

int main(void)
{
	PrimeTable();

	char K[10000];
	while(cin>>K>>L && L)
	{
		memset(Kt,0,sizeof(Kt));
		int lenK=strlen(K);
		for(int i=0;i<lenK;i++)  //把K转换为千进制Kt，其中Kt局部顺序，全局倒序
		{                      //如K=1234567=[  1][234][567] ，则Kt=[567][234][1  ]
			int pKt=(lenK+2-i)/3-1;
			Kt[pKt]=Kt[pKt]*10+(K[i]-'0');
		}
		int lenKt=(lenK+2)/3;

		bool flag=true;
		int pMin=0;  //能整除K且比L小的在prime中的最小素数下标
		while(prime[pMin]<L)  //枚举prime中比L小的素数
		{
			if(!mod(Kt,prime[pMin],lenKt))
			{
				flag=false;
				cout<<"BAD "<<prime[pMin]<<endl;
				break;
			}
			pMin++;
		}
		if(flag)
			cout<<"GOOD"<<endl;
	}
	return 0;
}