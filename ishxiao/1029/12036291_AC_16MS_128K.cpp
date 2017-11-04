//1029
#include<iostream>
using namespace std;
int test[520],judge[1005],real[1005];
int main()
{
	int n,k,pi,i,j,un,pos,num;
	char fml;
	scanf("%d%d",&n,&k);
	un=0;
	num=0;
	for(i=0;i<k;i++)
	{
		scanf("%d",&pi);
		for(j=1;j<=2*pi;j++)
			scanf("%d",&test[j]);
		getchar();
		scanf("%c",&fml);
		if(fml=='=')
		{
			for(j=1;j<=2*pi;j++)
				real[test[j]]=1;
		}
		if(fml=='<')
		{
			un++;
			for(j=1;j<=pi;j++)
				judge[test[j]]--;
			for(j=pi+1;j<=2*pi;j++)
				judge[test[j]]++;
		}
		if(fml=='>')
		{
			un++;
			for(j=1;j<=pi;j++)
				judge[test[j]]++;
			for(j=pi+1;j<=2*pi;j++)
				judge[test[j]]--;
		}
	}
	for(i=1;i<=n;i++)
	{
		if(real[i])
			continue;
		if(judge[i]==un||judge[i]==-un)
		{
			num++;
			pos=i;
		}
	}
	if(num==1)
		printf("%d\n",pos);
	else
		printf("0\n");
	return 0;
}