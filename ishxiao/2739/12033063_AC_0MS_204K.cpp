//Memory   Time 
//232K     16MS 


#include<iostream>
using namespace std;

int prim[1230]={2,3};
int count=0;

void prime(void)    //素数组打表
{

	int tally=2;
	int i,j,flag;
	for(i=5;i<10000;i+=2)
	{
		for(j=0,flag=1;prim[j]*prim[j]<=i;j++)
			if(i%prim[j]==0)flag=0;
		if(flag)
		{
			prim[tally]=i;
		    tally++;
		}
	}
	return;
}

void minus(int num,int i)            //寻找num的素数组合个数
{
	if(i<0)
		return;
	if(num-prim[i]==0)
		count++;
	else if(num-prim[i]>0)
		minus(num-prim[i],i-1);
	else
		return;
	return;
}

int main(void)
{
	prime();
	int num,i,k;
	for(;;)
	{
		cin>>num;
	    if(num==0)return 0;
	    for(i=0;i<1230;i++)
			if(num==prim[i])
			{
				count++;
				k=i-1;
				break;
			}
			else if(num<prim[i])
			{
				k=i-1;
				break;
			}
		for(i=k;i>=0;i--)
			minus(num,i);
		cout<<count<<endl;
		count=0;
	}
	return 0;
}
