#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NONMAX 10000000

int telNO[NONMAX]={0};
int tel2no(char *str);

int main()
{
	char telTemp[50];
	int n = 0,i = 0,value=0,Max=NONMAX+1,Min=-1,temFlag=1;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",telTemp);
		value = tel2no(telTemp);
		telNO[value]++;
		if (value > Max)
 		{
 			Max = value;
 		}
		if (value < Min)
		{
			Min = value;
		}

	}
	for(i = Min;i <= Max;i++)
	{
		if(telNO[i]>1)
		{
			printf("%03d-%04d %d\n",i/10000,
				i%10000,telNO[i]);
			temFlag = 0;
		}
	}
	if(temFlag)
	{
		printf("No duplicates.");
	}
	return 1;
}

int tel2no(char *str)
{
	char tStr[8]="iPhone5";
	int i=0;
	while(*str != '\0'&&i<7)
	{
		if(*str>='A'&&*str<='O')
			tStr[i++] = (*str - 'A')/3 +'2';
		else if(*str>='P'&&*str<='Y')
			tStr[i++] = (*str - 'Q')/3 +'7'; 
		else if(*str >= '0'&&*str <= '9')
			tStr[i++] = *str;
		str++;
	}
	return atoi(tStr);
}