#include <stdio.h>

#define NMAX 50
#define MMAX 100

int CalcUnsortedness(char DNA[],int n);

void InsertSort(int iarray[],int n);

int main()
{
	char strDNA[MMAX][NMAX+1];
	int iDNA[MMAX] = {0};
	int n = 0; //length of the strings
	int m = 0; //number of strings
	int i = 0; //number of loop

	scanf("%d %d",&n,&m);//input n and m

	while(i < m)
	{
		scanf("%s",&strDNA[i]);
		iDNA[i] = CalcUnsortedness(strDNA[i],n);
		i++;
	}
	InsertSort(iDNA,m);
	for(i = 0; i < m; i++)
	{
		printf("%s\n",strDNA[iDNA[i]]);
	}

	return 0;
}

int CalcUnsortedness(char DNA[],int n)
{
	int i = 0;
	int j = 0;
	int iUnsortedness = 0;

	for(i = 0; i < n-1; i++)
	{
		for(j = i + 1; j < n; j++)
		{
			if(DNA[i]>DNA[j])
			{
				iUnsortedness++;
			}
		}
	}

	return iUnsortedness;
}

void InsertSort(int iArray[],int m)
{
	int itempArray[MMAX];
	int itemp = 0;
	int i = 0;
	int j = 0;
	for(i = 0; i < m; i++)
	{
		itempArray[i] = i;
	}
	for(i = 0; i < m-1; i++)
	{
		for(j = i+1; j < m; j++)
		{
			if(iArray[i] > iArray[j])
			{
				itemp = iArray[i];
				iArray[i] = iArray[j];
				iArray[j] = itemp;

				itemp = itempArray[i];
				itempArray[i] = itempArray[j];
				itempArray[j] = itemp;				
			}
		}
	}
	for(i = 0; i < m; i++)
	{
		iArray[i] = itempArray[i];
	}
}