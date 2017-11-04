//2485
//思路、解法都和POJ1789基本一致，只是多了一个判定条件

#include<iostream>
using namespace std;

const int inf=65540;      //无限大
int dist[501][501];
int n;         //村落数量

int prim(void)
{
	int s=1;
	int m=1;
	bool u[501]={false};
	u[s]=true;

	int min_w;
	int point;
	int max_in_min=0;

	int low_dis[501];
	memset(low_dis,inf,sizeof(low_dis));

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
		if(max_in_min<min_w)           //寻找最小生成树中的最长路径
			max_in_min = min_w;
		s=point;
		u[s]=true;
		m++;
	}
	return max_in_min;
}

int main(void)
{
	int test;
	cin>>test;
	while(test--)
	{
		/*Input*/

		cin>>n;

		int w;        //两点间边权（临时变量）
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>dist[i][j];

		/*Prim Algorithm & Output*/

		cout<<prim()<<endl;

	}
	return 0;
}