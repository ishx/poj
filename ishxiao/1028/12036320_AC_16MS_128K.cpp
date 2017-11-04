//1028
#include<stdio.h>
#include<string.h>
int main(void)
{
	int cp=0,maxp=0;
	char site[110][80];
	char commond[10];
	strcpy(site[0],"http://www.acm.org/");
	scanf("%s",commond);
	while(strcmp(commond,"QUIT")!=0)
	{
		if(strcmp(commond,"VISIT")==0)
		{
			cp++;
			maxp=cp;
			scanf("%s",site[cp]);
			printf("%s\n",site[cp]);
		}
		else if(strcmp(commond,"BACK")==0)
		{
			cp--;
			if(cp<0)
			{
				printf("Ignored\n");
				cp++;
			}
			else
			{
				printf("%s\n",site[cp]);
			}
		}
		else if(strcmp(commond,"FORWARD")==0)
		{
			cp++;
			if(cp>maxp)
			{
				printf("Ignored\n");
				cp--;
			}
			else
			{
				printf("%s\n",site[cp]);
			}
		}
		scanf("%s",commond);
	}
	return 0;
}