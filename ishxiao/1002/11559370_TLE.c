#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NONMAX 100000

int tel2no(char *str)
{
	char tStr[8],tel;
	int i=0;
	while(*str != '\0'||i <7)
	{
		tel = *str++;
		if(tel>='A'&&tel<='C')
			tStr[i++] = '2';
		else if(tel>='D'&&tel<='F')
			tStr[i++] = '3';
		else if(tel>='G'&&tel<='I')
			tStr[i++] = '4';
		else if(tel>='J'&&tel<='L')
			tStr[i++] = '5';
		else if(tel>='M'&&tel<='O')
			tStr[i++] = '6';
		else if(tel>='P'&&tel<='S')
			tStr[i++] = '7';
		else if(tel>='T'&&tel<='V')
			tStr[i++] = '8';
		else if(tel>='W'&&tel<='Y')
			tStr[i++] = '9';
		else if(tel >= '0'&&tel <= '9')
			tStr[i++] = tel;
	}
	return atoi(tStr);
}

int main()
{
	char telTemp[20];
	int n = 0,i = 0,telNO[NONMAX][2]={0},j = 0,tempNo=0,temSame=0,temFlag;
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%s",telTemp);
		telNO[i][0] = tel2no(telTemp);
		telNO[i][1] = 1;
		temFlag = i;
		for(j = i;j > 0;j--)
		{
			if(telNO[j][0] < telNO[j-1][0]||telNO[j-1][1]==0)
			{
				tempNo = telNO[j-1][0];
				telNO[j-1][0] = telNO[j][0];
				telNO[j][0] = tempNo;
				//
				temSame = telNO[j-1][1];
				telNO[j-1][1] = telNO[j][1];
				telNO[j][1] = temSame;
				//
				temFlag = j-1;
			}
			else if(telNO[temFlag][0] == telNO[temFlag-1][0]
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