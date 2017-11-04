//3411

/*---- C++面向对象 ----*/

#include<iostream>
using namespace std;

class Road
{
	public:
		int a,b,c,p,r;
};

class info
{
	public:
		info():MinCost(2000)   //C++的'='和'()'都能赋值
		{					   //但构造函数这里只能用'()'
			road=new Road[11];
			vist=new int[11];
			memset(vist,0,sizeof(int)*11);
			vist[1]=1;   //从城市1出发，因此预记录到达1次
		}
		~info()
		{
			delete[] road;
			delete[] vist;
		}

		void input(void);
		void output(void);
		void DFS(int a,int fee);

	protected:
		int n;  //城市数
		int m;  //道路数
		int MinCost;  //最小总花费
		int *vist;  //记录城市的访问次数,每个城市最多经过3次
		Road *road;  //每条道路的付费规则
};

void info::input(void)
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>road[i].a>>road[i].b>>road[i].c>>road[i].p>>road[i].r;

	return;
}

void info::output(void)
{
	if(MinCost==2000)
		cout<<"impossible"<<endl;
	else
		cout<<MinCost<<endl;

	return;
}

void info::DFS(int a,int fee)   //a:当前所在城市,fee:当前方案的费用
{
	if(a==n && MinCost>fee)
	{
		MinCost=fee;
		return;
	}

	for(int i=1;i<=m;i++)  //枚举道路
	{
		if(a==road[i].a && vist[ road[i].b ]<=3)
		{
			int b=road[i].b;
			vist[b]++;

			if(vist[ road[i].c ])
				DFS(b,fee+road[i].p);
			else
				DFS(b,fee+road[i].r);

			vist[b]--;       //回溯
		}
	}
	return;
}

int main(void)
{
	info poj3411;
	poj3411.input();
	poj3411.DFS(1,0);
	poj3411.output();
	return 0;
}