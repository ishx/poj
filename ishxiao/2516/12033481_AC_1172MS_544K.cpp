//2516

#include<iostream>
#include<queue>
using namespace std;

class solve
{
public:
	solve(int n,int m,int k):N(n),M(m),K(k)
	{
		MinTotalCost=0;
		Nump=N+M+2;
		s=0;
		t=N+M+1;
		Err=false;

		AppRoom();
		Input();
		Compute();
	}
	~solve()
	{
		if(Err)
			cout<<-1<<endl;
		else
			cout<<MinTotalCost<<endl;

		Relax();
	}

	int inf() const{return 0x7FFFFFFF;}
	int min(int a,int b) {return a<b?a:b;}
	bool check(int kind) const{return ksupp[kind]>=kneed[kind];}

	void AppRoom(void);			//申请存储空间
	void Input(void);			//输入
	void Compute(void);			//计算MinTotalCost
	void Initial(int kind);		//初始化数据，重新构造第kind种物品的流量图
	bool spfa(void);			//对当前图求最小费用流(增广链)
	void AddFlow(int kind);		//对最小费用流增流，调整增广链上的流量和费用，并累计第kind种物品的费用MinCost[kind]
	void Relax(void);			//释放空间

protected:
	int N;				//店主数
	int M;				//供货商数
	int K;				//商品种数
	int s,t;			//超级源s 与 超级汇t 的编号
	int Nump;			//N+M+超级源s+超级汇t (即总结点数量)
	int** supply;		//supply[j][k]:供货商j对第k种物品的供货量
	int** need;			//need[i][k]: 店主i对第k种物品的需求量
	int*** InputCost;	//InputCost[kind][N][M] 对应输入的K的花费矩阵
	int* MinCost;		//所有供货商运送第k种货物给所有店主的最小花费
	int MinTotalCost;	//所有供货商运送所有物品给所有店主的最小总花费

	/*构图时各点编号-- 超级源s:0 , 供应商M:1~M , 店主N:M+1~M+N , 超级汇t:N+M+1*/
	int** cost;			//任意两点之间的花费
	int** cap;			//任意两点之间的容量
	int* dist;			//超级源到各点的距离
	int* vist;			//判断某点是否在队列中

	int* pre;			//记录前驱. u->v，pre[v]=u
	bool Err;			//标记供不应求
	int* ksupp;			//第k种物品的总供应量
	int* kneed;			//第k种物品的总需求量
};

void solve::AppRoom(void)
{
	int i,k;

	/*申请构图与解题必要空间*/

	MinCost=new int[K+1];
	ksupp=new int[K+1];
	kneed=new int[K+1];
	dist=new int[Nump];
	vist=new int[Nump];
	pre=new int[Nump];

	cost=new int*[Nump];
	cap=new int*[Nump];
	for(i=0;i<Nump;i++)
	{
		cost[i]=new int[Nump];
		cap[i]=new int[Nump];
	}

	/*申请输入空间*/

	supply=new int*[M+1];
	for(i=1;i<=M;i++)
		supply[i]=new int[K+1];

	need=new int*[N+1];
	for(i=1;i<=N;i++)
		need[i]=new int[K+1];

	InputCost=new int**[K+1];	//K个矩阵
	for(k=1;k<=K;k++)
	{
		InputCost[k]=new int*[N+1];
		for(i=1;i<=N;i++)
			InputCost[k][i]=new int[M+1];
	}


	return;
}

void solve::Input(void)
{
	int i,j,k;

	for(i=1;i<=N;i++)
		for(k=1;k<=K;k++)
			cin>>need[i][k];

	for(j=1;j<=M;j++)
		for(k=1;k<=K;k++)
			cin>>supply[j][k];
	
	for(k=1;k<=K;k++)
		for(i=1;i<=N;i++)
			for(j=1;j<=M;j++)
				cin>>InputCost[k][i][j];

	/*计算第k种物品的供应总量和需求总量*/

	for(k=1;k<=K;k++)
	{
		ksupp[k]=0;
		for(j=1;j<=M;j++)
			ksupp[k]+=supply[j][k];

		kneed[k]=0;
		for(i=1;i<=N;i++)
			kneed[k]+=need[i][k];
	}

	return;
}

void solve::Compute(void)
{
	for(int kind=1;kind<=K;kind++)
	{
		Initial(kind);
		if(!check(kind))	//检查第k种物品的供求情况
		{
			Err=true;
			return;
		}

		while(spfa())
			AddFlow(kind);

		MinTotalCost+=MinCost[kind];
	}

	return;
}

void solve::Initial(int kind)
{
	int i,j;

	MinCost[kind]=0;
	memset(pre,0,sizeof(int)*Nump);

	for(i=0;i<Nump;i++)		//目的是处理不属于当前所构造的图的边
	{
		memset(cap[i],0,sizeof(int)*Nump);
		memset(cost[i],0,sizeof(int)*Nump);
	}

	/*初始化超级源s到各个供货商的容量*/

	for(j=1;j<=M;j++)
		cap[s][j]=supply[j][kind];	//s到供货商j的容量为供货商j的供应量
		

	/*初始化各个店主到超级汇t的容量*/

	for(i=M+1;i<t;i++)
		cap[i][t]=need[i-M][kind];	//店主i到t的容量为店主i的需求量

	/*初始化各个供应商到各个店主的容量和费用*/

	for(i=M+1;i<t;i++)
		for(j=1;j<=M;j++)
		{
			cost[j][i]=InputCost[kind][i-M][j];	//注意这里的费用存储方式与输入的存储方式相反
			cost[i][j]=-cost[j][i];				//反向弧费用
			cap[j][i]=supply[j][kind];			//供应商j到店主i的容量为供货商j的供应量
		}

	return;
}

bool solve::spfa(void)
{
	for(int i=s;i<=t;i++)
	{
		dist[i]=inf();
		vist[i]=false;
	}
	dist[s]=0;

	queue<int>q;
	q.push(s);
	vist[s]=true;

	while(!q.empty())
	{
		int u=q.front();
		for(int v=s;v<=t;v++)
		{
			if(cap[u][v] && dist[v]>dist[u]+cost[u][v])
			{
				dist[v]=dist[u]+cost[u][v];
				pre[v]=u;

				if(!vist[v])
				{
					q.push(v);
					vist[v]=true;
				}
			}
		}

		q.pop();
		vist[u]=false;
	}

	if(dist[t]<inf())
		return true;		//dist[t]被修正，说明找到增广链

	return false;	//已无增广链，spfa结束
}

void solve::AddFlow(int kind)
{
	int MaxFlow=inf();		//可分配最大流
	int i;
	for(i=t;i!=s;i=pre[i])
		MaxFlow=min(MaxFlow,cap[pre[i]][i]);	//可分配最大流=增广链上的最小容量

	for(i=t;i!=s;i=pre[i])
	{
		cap[pre[i]][i]-=MaxFlow;	//正向弧容量调整
		cap[i][pre[i]]+=MaxFlow;	//反向弧容量调整
		MinCost[kind]+=cost[pre[i]][i]*MaxFlow;		//最小费用=单位费用*可分配最大流
	}

	return;
}

void solve::Relax(void)
{
	int i,k;

	delete[] MinCost;
	delete[] dist;
	delete[] vist;
	delete[] pre;
	delete[] ksupp;
	delete[] kneed;

	for(i=0;i<Nump;i++)
	{
		delete[] cost[i];
		delete[] cap[i];
	}

	for(i=1;i<=M;i++)
		delete[] supply[i];

	for(i=1;i<=N;i++)
		delete[] need[i];

	for(k=1;k<=K;k++)
	{
		for(i=1;i<=N;i++)
			delete[] InputCost[k][i];

		delete[] InputCost[k];
	}

	return;
}

int main(void)
{
	int n,m,k;
	while(cin>>n>>m>>k && (n+m+k))
		solve poj2516(n,m,k);

	return 0;
}