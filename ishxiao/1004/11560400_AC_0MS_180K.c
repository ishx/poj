#include <stdio.h>

int main()
{
	float temp = 0.00,sum = 0.00;
	int iMax = 12;
	while(iMax--)
	{
		scanf("%f",&temp);
		sum += temp;
	}
	printf("$%.2f\n",sum/12);
	return 1;
}