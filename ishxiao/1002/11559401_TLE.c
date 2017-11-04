#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NONMAX 100000

int tel2no(char *str)
{
	char tStr[8]="iPhone5";
	int i=0;
	while(*str != '\0'&&i<7)
	{
		if(*str>='A'&&*str<='O')
			tStr[i++] = (*str - 'A')/3 +'2';
		else if(*str>='P'&&*str<='S')
			tStr[i++] = '7'; 
		else if(*str>='T'&&*str<='V')
			tStr[i++] = '8';
		else if(*str>='W'&&*str<='Y')
			tStr[i++] = '9';
		else if(*str >= '0'&&*str <= '9')
			tStr[i++] = *str;
		str++;
	}
	return atoi(tStr);
}

int main()
{
	char telTemp[16];
	int n = 0,i = 0,telNO[NONMAX][2]={0},j = 0,temp=0,temFlag=0;
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%s",telTemp);
		telNO[i][0] = tel2no(telTemp);
		telNO[i][1] = 1;
		temFlag = i;
		for(j = i;j > 0;j--)
		{
			if(telNO[j][0]<telNO[j-1][0]||telNO[j-1][1]==0)
			{
				temp = telNO[j-1][0];
				telNO[j-1][0] = telNO[j][0];
				telNO[j][0] = temp;
				//
				temp = telNO[j-1][1];
				telNO[j-1][1] = telNO[j][1];
				telNO[j][1] = temp;
				//
				temFlag = j-1;
			}
			if(telNO[temFlag][0] == telNO[temFlag-1][0]
			&&temFlag>0&&telNO[temFlag-1][1]>0)
			{
				telNO[temFlag][1] = 0;
				telNO[temFlag-1][1]++;
				break;
			}
		}		
	}
	temFlag = 0;
	for(i = 0;i < n;i++)
	{
		if(telNO[i][1]>1)
		{
			printf("%03d-%04d %d\n",(int)telNO[i][0]/10000,
				telNO[i][0]%10000,telNO[i][1]);
			temFlag = 1;
		}
	}
	if(0 == temFlag)
	{
		printf("No duplicates.");
	}
	return 1;
}