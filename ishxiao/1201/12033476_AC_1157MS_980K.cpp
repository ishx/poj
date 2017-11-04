//1201

#include<iostream>
using namespace std;

const int inf=60000;

class
{
	public:
		int s,e;
}inter[50001];

int n; //区间数
int upli;
int doli; // UpLimit , Downlimit 上下限
int dist[50001];  //源点到各点的距离
int c[50001];  //边权

int main(int i,int j,int k)
{
	while(cin>>n)
	{
		upli=0;
		doli=inf;

		/*Input*/

		for(k=0;k<n;k++)
		{
			int a,b;
			cin>>a>>b>>c[k];
			inter[k].s=a;
			inter[k].e=b+1;

			if(doli>inter[k].s)  //寻找最小的顶点
				doli=inter[k].s;
			if(upli<inter[k].e)  //寻找最大的顶点，inter[k].e必大于inter[k].s，因此无需再与inter[k].s比较
				upli=inter[k].e;

			dist[k]=0; //初始化源点到各点的距离
		}

		/*Bellman-Ford:Relax*/

		bool flag=true;
		while(flag)
		{
			flag=false;
			for(i=0;i<n;i++)
				if(dist[ inter[i].s ]>dist[ inter[i].e ]-c[i])
				{
					dist[ inter[i].s ]=dist[ inter[i].e ]-c[i];
					flag=true;
				}

			for(j=doli;j<upli;j++)
				if(dist[j+1]>dist[j]+1)
				{
					dist[j+1]=dist[j]+1;
					flag=true;
				}

			for(j=upli-1;j>=doli;j--)
				if(dist[j]>dist[j+1])
				{
					dist[j]=dist[j+1];
					flag=true;
				}
		}
		cout<<dist[upli]-dist[doli]<<endl;
	}
	return 0;
}