#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int CalcUnsortedness(char* DNA);

void InsertSort(int* iarray);

int main()
{
	char **strDNA;
	int *iDNA;
	int n = 0; //length of the strings
	int m = 0; //number of strings
	int i = 0; //number of loop

	scanf("%d %d",&n,&m);//input n and m

	iDNA = (int*)calloc(m, sizeof(int));
	strDNA = (char**)calloc(m,sizeof(char*));

	while(i < m)
	{
		strDNA[i] = (char*)calloc((n+1),sizeof(char));
		scanf("%s",strDNA[i]);
		iDNA[i] = CalcUnsortedness(strDNA[i]);
		i++;
	}
	InsertSort(iDNA);
	for(i = 0; i < m; i++)
	{
		printf("%s\n",strDNA[iDNA[i]]);
	}
	//
	free(iDNA);
	for(i = 0; i < m; i++)
	{
		free(strDNA[i]);
	}
	free(strDNA);

	return 0;
}

int CalcUnsortedness(char* DNA)
{
	int i,j,n;
	int iUnsortedness = 0;
	n = (int) _msize(DNA);
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

void InsertSort(int* iArray)
{
	int i,j,m,index;
	int *iBuffer;
	m = (int) _msize(iArray) / sizeof(int);
	iBuffer = (int*)calloc(m,sizeof(int));
	for(i = 0; i < m; i++)
	{
		index = 0;
		for(j = 0; j < m; j++)
		{
			if((iArray[i] > iArray[j])
			   ||( i > j && iArray[i] == iArray[j]))
			{
				index++;
			}
		}
		iBuffer[index] = i;
	}
	for(i = 0; i < m; i++)
	{
		iArray[i] = iBuffer[i];
	}

	free(iBuffer);
}