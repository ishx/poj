#include <stdio.h>

#define NMAX 1000
int testCase(float x);

int main()
{
	float temp = 0.00;
	int value[NMAX],i=0,iMax = 0;
	while((scanf("%f",&temp),temp != 0.00))
	{
		value[++iMax] = testCase(temp);
	}

	while(++i <= iMax)
	{
		printf("%d card(s)\n",value[i]);
	}
	return 1;
}

int testCase(float x)
{
	float sumMax=1.0/2,sumMin=0;
	int i = 1;
	while(!(x>=sumMin&&x<sumMax))
	{
		sumMin = sumMax;
		sumMax += (float)1.0/(i+2);
		i++;
	}
	return i;
}