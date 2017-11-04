//2195 

#include<iostream>
#include<memory.h>
#include<cmath>
#include<queue>
using namespace std;

struct coordinate
{
	int x,y;
};

class solve
{
public:
	solve(int row,int col):R(row),C(col)
	{
		MinCost=0;
		n=0;

		Input();
		StructureBinaryMap();

		pre=new int[2*n+2];
		memset(pre,0,sizeof(int)*(2*n+2));
		dist=new int[2*n+2];
		vist=new bool[2*n+2];

		while(spfa())
			AddMaxFlow();
	}
	~solve()
	{
		cout<<MinCost<<endl;

		delete[] m;
		delete[] H;
		delete[] dist;
		delete[] vist;

		for(int i=0;i<R;i++)
			delete[] InMap[i];

		for(int j=0;j<2*n+2;j++)
		{
			delete[] cost[j];
			delete[] cap[j];
		}
	}

	int inf() const{return 0x7FFFFFFF;}
	int min(int a,int b) {return a<b?a:b;}

	void Input(void);
	void StructureBinaryMap(void);   //构造二分图
	bool spfa(void);				 //搜索从超级源到超级汇的最短路(即最小费用)的增广链
	void AddMaxFlow(void);			 //增广链调整(曾流)，计算最小费用

protected:
	int R,C;		//地图尺寸R*C ，
	int n;          //the number of man or Houses
	int s,t;		//s:超级源编号，t:超级汇编号
	int MinCost;    //最小花费

	char** InMap;   //输入的地图
	coordinate* m;	//记录所有man的坐标
	coordinate* H;	//记录所有House的坐标
	int* pre;		//最小费用流路径上，结点i的前驱结点为pre[i]
		
	int** cost;		//两点间费用,其中超级源为0，1~n为man，n+1~2n为house,2n+1为超级汇
	int** cap;		//两点间容量,其中超级源为0，1~n为man，n+1~2n为house,2n+1为超级汇
	int* dist;		//超级源到各点的最短距离
	bool* vist;		//标记各点是否在队列
};

void solve::Input(void)
{
	int i,j;
	
	InMap=new char*[R];
	for(i=0;i<R;i++)
	{
		InMap[i]=new char[C];
		for(j=0;j<C;j++)
		{
			cin>>InMap[i][j];

			if(InMap[i][j]=='m')	//检查'm'
				n++;				//得到man or house的数量
		}
	}
	return;
}

void solve::StructureBinaryMap(void)
{
	int i,j;
	int pm=0,pH=0;

	m=new coordinate[n+1];
	H=new coordinate[n+1];	

	/*记录各个man与house的坐标*/

	for(i=0;i<R;i++)
		for(j=0;j<C;j++)
			if(InMap[i][j]=='m')
			{
				m[++pm].x=i;
				m[pm].y=j;
			}
			else if(InMap[i][j]=='H')
			{
				H[++pH].x=i;
				H[pH].y=j;
			}

	/*建立存储空间*/

	cost=new int*[2*n+2];
	cap=new int*[2*n+2];
	for(i=0;i<2*n+2;i++)
	{
		cost[i]=new int[2*n+2];
		cap[i]=new int[2*n+2];

		memset(cost[i],0,sizeof(int)*(2*n+2));  //所有路径费用默认为0
		memset(cap[i],0,sizeof(int)*(2*n+2));   //所有路径容量默认为0(饱和，不连通)
	}

	/*初始化超级源s到各个man的容量*/

	s=0;
	for(i=1;i<=n;i++)
		cap[s][i]=1;	//容量默认为1

	/*初始化各个man到house的距离(费用)及容量*/

	for(i=1;i<=n;i++)
		for(j=n+1;j<=2*n;j++)
		{
			cost[i][j]=abs(m[i].x-H[j-n].x)+abs(m[i].y-H[j-n].y);   //man到house的费用为abs(△x)+abs(△y)
			cost[j][i]=-cost[i][j];		//注意顺便构造负权边
			cap[i][j]=1;
		}

	/*初始化各个house到超级汇t的容量*/

	t=2*n+1;
	for(j=n+1;j<t;j++)
		cap[j][t]=1;	//容量默认为1

	return;
}

bool solve::spfa(void)
{
	dist[s]=0;
	for(int i=1;i<2*n+2;i++)   //注意这里不能用memset(),memset是对字节为单位进行赋值
		dist[i]=inf();	//若非置0，memset对char、bool以外的类型都会赋一个与期望完全不同的数值
	
	memset(vist,false,sizeof(bool)*(2*n+2));
	vist[s]=true;

	queue<int>q;
	q.push(s);

	while(!q.empty())
	{
		int u=q.front();	//获取队头元素
		for(int v=0;v<=t;v++)
		{
			if(cap[u][v] && dist[v]>dist[u]+cost[u][v])  //u->v容量未饱和，且能够松弛
			{
				dist[v]=dist[u]+cost[u][v];
				pre[v]=u;		//记录u的前驱结点

				if(!vist[v])
				{
					q.push(v);
					vist[v]=true;
				}
			}
		}
		q.pop();	 //队头元素出队
		vist[u]=false;
	}

	if(dist[t]==inf())  //dist[t]没有被调整，说明已不存在增广链
		return false;

	return true;	//找到一条当前费用和最小的增广链
}

void solve::AddMaxFlow(void)
{
	int MaxFlow=inf();  //可分配最大流
	int i;

	for(i=t;i!=s;i=pre[i])  //可分配最大流 为增广链上的最小容量边的容量
		MaxFlow=min(MaxFlow,cap[pre[i]][i]);

	for(i=t;i!=s;i=pre[i])	//增广链上流量调整(增流)
	{
		cap[pre[i]][i]-=MaxFlow;	//正向弧容量减去可分配最大流
		cap[i][pre[i]]+=MaxFlow;	//反向弧容量加上可分配最大流
		MinCost+=cost[pre[i]][i]*MaxFlow;  //最小费用=单位费用*流量
	}

	return;
}

int main(void)
{
	int row,col;
	while(cin>>row>>col && (row+col))
		solve poj2195(row,col);

	return 0;
}