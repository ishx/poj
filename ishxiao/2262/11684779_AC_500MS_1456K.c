// -2262-
#include <stdio.h>
#define NMAX 1000000
#define NPRIME 78498

int prim[NPRIME]={2,3};

//odd prime
void prime(void)
{
	int tally=2;
	int i,j,flag;
	for(i=5;i<NMAX;i+=2)
	{
		flag = 1;
		for(j=0;prim[j]*prim[j]<=i;j++)
		{
			if(i%prim[j]==0)
			{
				flag=0;
				break;
			}
		}
		//flag = IsPrime(i);
		if(flag)
		{
			prim[tally]=i;
		    tally++;
		}
	}
	return;
}

//judge the number is odd prime or not
int IsPrime(int num)
{
	int flag = 1;
	int i = 2;
	if(num > 1)
	{
		for(i = 2; i*i <= num;i++)
		{
			if(num % i == 0)
			{
				flag = 0;
				break;
			}
		}
	}
	else
	{
		flag = 0;
	}

	return flag;
}

int main(void)
{
	int i = 0, k = 0,num = 0;
	char buffer[NMAX];
	int nbuffer = 0;
	prime();

	scanf("%d",&num);
	while(num)
	{
		i = 3;
		while(prim[i] < num)
		{
			i++;
		}
		while(i--)
		{
			if(IsPrime(num - prim[i]))
				break;
			//i--;
		}
		i = i;
		nbuffer += sprintf(buffer + nbuffer,"%d = %d + %d\n",num,num - prim[i],prim[i]);
		scanf("%d",&num);
	}
	if(nbuffer)
		printf("%s",buffer);
	
	return 0;
} 