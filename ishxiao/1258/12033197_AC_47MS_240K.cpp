//1258

#include<iostream>
using namespace std;

const int inf=100001;      //无限大

int n;   //农场数量
int dist[101][101];

int prim(void)
{
	int s=1;
	int m=1;
	bool u[101]={false};
	u[s]=true;

	int min_w;
	int prim_w=0;
	int point;
	int low_dis[101];

	/*Initial*/

	for(int i=1;i<=n;i++)
		low_dis[i]=inf;

	/*Prim Algorithm*/

	while(true)
	{
		if(m==n)
			break;

		min_w=inf;
		for(int i=2;i<=n;i++)
		{
			if(!u[i] && low_dis[i]>dist[s][i])
				low_dis[i] = dist[s][i];
			if(!u[i] && min_w>low_dis[i])
			{
				min_w = low_dis[i];
				point=i;
			}
		}
		s=point;
		u[s]=true;
		prim_w+=min_w;
		m++;
	}
	return prim_w;
}

int main(void)
{
	while(cin>>n)
	{
		/*Input*/

		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>dist[i][j];

		/*Prim Algorithm & Output*/

		cout<<prim()<<endl;
	}
	return 0;
}