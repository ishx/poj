#include<stdio.h>
int main()
{
	int p,e,i,k,d,t,r,x;
	x=0;

	while(scanf("%d %d %d %d",&p,&e,&i,&d) && p!=-1)
	{
		p=p%23; e=e%28; i=i%33;
		t=e-p;
		k=0;
		while(t%23!=0)
		{
			k++;
			t+=5;//28-23
		}
		t=e+k*28;

		r=t-i;
		k=0;
		while(r%33!=0)
		{
			k++;
			r+=611;//23*28-33
		}
		r=t+k*644;

		if(r > d)
			r = r-d;
		else
			r = r-d+21252;

		printf("Case %d: the next triple peak occurs in %d days.\n",++x,r);
	}

	return 0;
}