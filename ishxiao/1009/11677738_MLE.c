// -1009-
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define NUMMAX 1000000000
#define IMGMAX 1000

int MaxCenter(int* bSerial,int n)
{
	int i = 0;
	int bMax  = 0;
	int btemp = 0; 
	for(i = 1;i <= n;i++)
	{
		btemp = abs(bSerial[i]- bSerial[0]);
		if(bMax < btemp)
		{
			bMax = btemp;
		}
	}
	return bMax;
}

int** EdgeDetection(int** iInput,int n)
{
	int** iOutput;
	int i = 0;
	int j = 0;
	int m = 0;
	int bSerial[9];
	m = _msize(iInput)/sizeof(int*);
	iOutput = (int**) calloc(m,sizeof(int*));
	for(i = 0; i < m; i++)
	{
		iOutput[i] = (int*) calloc(n,sizeof(int));
	}
	//#01 0,0
	i = 0; j = 0;
	bSerial[0] = iInput[i][j];
	
	bSerial[1] = iInput[i][j+1];
	bSerial[2] = iInput[i+1][j];
	bSerial[3] = iInput[i+1][j+1];

	iOutput[i][j] = MaxCenter(bSerial,3);
	//#02 0,1 - (n-2)
	i = 0;
	for(j = 1 ; j < n-1; j++)
	{
		bSerial[0] = iInput[i][j];
		
		bSerial[1] = iInput[i][j-1];
		bSerial[2] = iInput[i][j+1];
		
		bSerial[3] = iInput[i+1][j-1];
		bSerial[4] = iInput[i+1][j];
		bSerial[5] = iInput[i+1][j+1];

		iOutput[0][j] = MaxCenter(bSerial,5);
	}
	//#03 0,(n -1)
	i = 0; j = n -1;
	bSerial[0] = iInput[i][j-1];
	
	bSerial[1] = iInput[i][j-1];
	
	bSerial[2] = iInput[i+1][j-1];
	bSerial[3] = iInput[i+1][j];

	iOutput[i][j] = MaxCenter(bSerial,3);
	//#04 1 - (m - 2),0
	j = 0;
	for(i = 1; i < m - 1; i++)
	{
			bSerial[0] = iInput[i][j];
			
			bSerial[1] = iInput[i-1][j];
			bSerial[2] = iInput[i-1][j+1];
			
			bSerial[3] = iInput[i][j+1];
			
			bSerial[4] = iInput[i+1][j];
			bSerial[5] = iInput[i+1][j+1];

			iOutput[i][j] = MaxCenter(bSerial,5);
	}
	//#05 1 - (m - 2),(n - 1) 
	j = n - 1;
	for(i = 1 ; i < m - 1; i++)
	{
		bSerial[0] = iInput[i][j];
		
		bSerial[1] = iInput[i-1][j-1];
		bSerial[2] = iInput[i-1][j];
		
		bSerial[3] = iInput[i][j-1];
		
		bSerial[4] = iInput[i+1][j-1];
		bSerial[5] = iInput[i+1][j];

		iOutput[i][j] = MaxCenter(bSerial,5);
	}
	//#06 (m - 1),0
	i = m - 1; j = 0;
	bSerial[0] = iInput[i][j];
	
	bSerial[1] = iInput[i-1][j];
	bSerial[2] = iInput[i-1][j+1];
	
	bSerial[3] = iInput[i][j+1];

	iOutput[i][j] = MaxCenter(bSerial,3);
	//#07 (m - 1),1 - (n - 2)
	i = m - 1;
	for(j = 1 ; j < n; j++)
	{
		bSerial[0] = iInput[i][j];
		
		bSerial[1] = iInput[i-1][j-1];
		bSerial[2] = iInput[i-1][j];
		bSerial[3] = iInput[i-1][j+1];
		
		bSerial[4] = iInput[i][j-1];
		bSerial[5] = iInput[i][j+1];

		iOutput[i][j] = MaxCenter(bSerial,5);
	}
	//#08 (m - 1),(n - 1)
	i = m -1; j = n -1;
	bSerial[0] = iInput[i][j];
	
	bSerial[1] = iInput[i-1][j-1];
	bSerial[2] = iInput[i-1][j];
	
	bSerial[3] = iInput[i][j-1];

	iOutput[i][j] = MaxCenter(bSerial,3);
	// #09 1 - (m - 1), 1 - (n - 1)
	for(i = 1; i < m -1; i++)
	{
		for(j = 1 ; j < n - 1; j++)
		{
			bSerial[0] = iInput[i][j];
			
			bSerial[1] = iInput[i-1][j-1];
			bSerial[2] = iInput[i-1][j];
			bSerial[3] = iInput[i-1][j+1];
			
			bSerial[4] = iInput[i][j-1];
			bSerial[5] = iInput[i][j+1];
			
			bSerial[6] = iInput[i+1][j-1];
			bSerial[7] = iInput[i+1][j];
			bSerial[8] = iInput[i+1][j+1];

			iOutput[i][j] = MaxCenter(bSerial,8);
		}
	}
	
	return iOutput;
}

void printData(int** iOutput,int n)
{
	int m = 0;
	int tempData = 0;
	int nData;
	int i = 0;
	int j = 0;
	m = _msize(iOutput)/sizeof(int*);
	printf("%d\n",n);
	tempData = iOutput[0][0];
	nData = 0;
	for(i = 0; i < m ; i++ )
	{
		for(j = 0; j < n; j++)
		{
			if(tempData == iOutput[i][j])
			{
				nData++;
			}
			else
			{
				printf("%d %d\n",tempData,nData);
				tempData = iOutput[i][j];
				nData = 1;
			}
		}
		//printf("\n");
	}
	printf("%d %d\n",tempData,nData);
	//End
	printf("0 0\n");
}

int main()
{
#if 0
	int iInput[5][7]=
	{
		15, 15, 15, 15, 100,100,100,
		100,100,100,100,100,100,100,
		100,100,100,100,100, 25, 25,
		175,175, 25, 25, 25, 25, 25,
		175,175, 25, 25, 25, 25, 25,
	};
#else
	int** iInput[IMGMAX];
#endif
		
	int** iOutput[IMGMAX];
	unsigned char iarrInput[NUMMAX];

// 	int iarrInput[] ={
// 		15, 15, 15, 15, 100,100,100,
// 		100,100,100,100,100,100,100,
// 		100,100,100,100,100, 25, 25,
// 		175,175, 25, 25, 25, 25, 25,
// 		175,175, 25, 25, 25, 25, 25,
// 	};
	int i = 0;
	int j = 0;
	int n[IMGMAX];
	int tempData = 0;
	int nData = 0;
	int indexStart = 0;
	int indexEnd = 0;
	int sumData = 0;
	int m = 0;
	int k = 0;
	//Initialize
	//Input number of column
	//Input Data
	do{
		indexStart = 0;
		indexEnd = 0;
		scanf("%d",&n[k]);
		if(n[k] == 0)
			break;
		do{
			
			scanf("%u %d",&tempData,&nData);
			indexEnd = indexEnd + nData;
			for(i = indexStart; i < indexEnd; i++)
			{
				iarrInput[i]= 0xFF&tempData;
			}
			indexStart = indexEnd;
		}while(!(tempData == 0&&nData == 0));
		//Restore
		m = indexEnd/n[k];
		iInput[k] = (int**) calloc(m,sizeof(int*));

		for(i = 0; i < m; i++)
		{
			iInput[0][i] = (int*) calloc(n[k],sizeof(int));
		}
		for(i = 0; i < m ; i++ )
		{
			for(j = 0; j < n[k]; j++)
			{
				iInput[k][i][j] = iarrInput[i*n[k]+j];
			}
		}
		k++;
	}while(!(n[k] == 0));
	for(i = 0; i < k; i++)
	{
		iOutput[i] = EdgeDetection(iInput[i],n[i]);
		printData(iOutput[i],n[i]);
	}
	printf("0\n");
	
	return 0;
}