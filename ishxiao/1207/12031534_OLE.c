//1207
#include <stdio.h>

//Find the cycle length of integer n
int findCycleLength(int n);

//Find the maximum cycle-length for integers between and including i and j
int findMaxCycleLength(int i, int j);

int main()
{
	int i,j;
	do{
		scanf("%d %d",&i,&j);
		printf("%d %d %d\n",i,j,findMaxCycleLength(i,j));
	}while(1);//while(!(i == 1&& j == 1));
	
	return 0;
}

int findCycleLength(int n)
{
	int count = 1;//the cycle-length
	while(n != 1)
	{
		if(n%2 == 1)
			n = 3*n+1;
		else
			n = n/2;
		count++;
	}
	return count;
}

int findMaxCycleLength(int i, int j)
{
	int maxCycleLength = 0;//the maximum cycle-length
	int temCycleLength = 0;//the temporary cycle-length
	int curNumber = i;//the current number
	
	if(i > j)
	{
		curNumber = j;
		j = i;
	}
	
	for(curNumber;curNumber < j+1; curNumber++)
	{
		temCycleLength = findCycleLength(curNumber);
		if(maxCycleLength < temCycleLength)
			maxCycleLength = temCycleLength;
	}
	
	return maxCycleLength;
}