//Memory Time 
//260K  141MS 

#include<iostream>
using namespace std;

bool judge_prime(int temp)
{
	int k,flag=1;
	int num=2;
	if(temp==2)
		return true;
	else if(temp==1||temp%2==0)
		return false;
	else
	{
		for(k=3;k*k<=temp;k+=2)
			if(temp%k==0)
			{
				flag=0;
				break;
			}
	}		
	if(flag)
		return true;
	else
		return false;	
}

int main(void)
{
	int a,b,n,i,temp;
	for(;;)
	{
		int flag=0;
		cin>>a>>b>>n;
		if(b==0&&n==0||a==0||a>9307||b>346||n>210)
			break;
		if(b==0&&judge_prime(a)==false)
			break;
		for(i=0;flag!=n;i++)
		{
			temp=a+i*b;
			if(judge_prime(temp))
				flag++;
		}
		cout<<temp<<endl;
	}
	return 0;
}
