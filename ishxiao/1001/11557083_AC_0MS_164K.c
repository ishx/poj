#include <stdio.h>
#include <string.h>
#define NUNMAX 150
int main()
{
	char s[6+1];
	int a[5]={0},b[NUNMAX]={0},c[NUNMAX]={0};
	int i=0,j=0,k=0,m=0,n=0,ki=0,flag = 0;
	while(scanf("%s%d",s,&n)==2)
	{
		i=0,j=0,k=0,m=0,ki=0,flag = 0;
		for(i = 0;i<NUNMAX;i++)
		{
			b[i] = c[i] = 0;
		}
		for(i = 5; i >= 0;i--)
		{
			if('.' == s[i])
			{
				m = 5 - i;
			}
			else
			{
				a[j] = s[i] -'0';
				b[j++] = a[j];
			}
		}
		for(k = 2;k < n+1;k++)
		{
			for(i = 0;i < 5;i++)
			{
				for(j = 0; j < 5*k; j++)
				{
					c[i+j] += a[i]*b[j];
					c[i+j+1] += (int) c[i+j]/10;
					c[i+j] %= 10; 
				}
			}
			for(ki = 0; ki < i+j-1; ki++)
			{
				b[ki] = c[ki];
				c[ki] = 0;
			}
		}
		m = m*n;
		for(i = 0;i < NUNMAX-1;i++)
		{
			if(0 != b[i]||i==m)
			{
				j = i;
				break;
			}
		}
		for(i = NUNMAX-1;i>=j;i--)
		{
			if(0 != b[i])
				flag = 1;
			if(1 == flag)
			{
				printf("%d",b[i]);
			}
			if(m == i&&m!=j)
			{
				printf(".");
				flag = 1;
			}
		}
		printf("\n");
	}
	return 1;
}