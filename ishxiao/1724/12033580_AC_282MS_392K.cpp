//1724

/*--- C++ Class ---*/

#include<iostream>
using namespace std;

class Road
{
	public:
		int S,D,L,T;  //Source,Destination,Length,Toll
		int next;     //指向相同Source的下一条边
};

class info
{
	public:
		info(int N,int R)
		{
			road=new Road[R+1];
			vist=new bool[N+1];
			ListTable_Head=new int[N+1];

			memset(vist,false,sizeof(bool)*(N+1));
			memset(ListTable_Head,-1,sizeof(int)*(N+1));
			MinLen=1e7;
			pr=0;
		}
		~info()
		{
			delete[] road;
			delete[] vist;
			delete[] ListTable_Head;
		}

		void input(int R);
		void output(void);
		void DFS(int NowCity,int NowLen,int RestMoney,int N);

	protected:
		Road* road;
		bool* vist;
		int* ListTable_Head;  //邻接链表头指针数组
		int MinLen;
		int pr;   //road[]指针
};

void info::input(int R)
{
	for(int i=1;i<=R;i++)
	{
		int s,d,l,t;
		cin>>s>>d>>l>>t;

		road[pr].S=s;
		road[pr].D=d;
		road[pr].L=l;
		road[pr].T=t;
		road[pr].next=ListTable_Head[s];
		ListTable_Head[s]=pr++;
	}
	return;
}

void info::output()
{
	cout<<(MinLen<1e7?MinLen:-1)<<endl;
	return;
}

void info::DFS(int NowCity,int NowLen,int RestMoney,int N)
{
	if(NowLen>MinLen)
		return;

	if(NowCity==N && RestMoney>=0 && NowLen<MinLen)
	{
		MinLen=NowLen;
		return;
	}

	for(int i=ListTable_Head[NowCity];i!=-1;i=road[i].next)
	{
		int tD=road[i].D;
		int tL=road[i].L;
		int tT=road[i].T;

		if(!vist[tD] && RestMoney>=tT)
		{
			vist[tD]=true;
			DFS(tD,NowLen+tL,RestMoney-tT,N);
			vist[tD]=false;
		}
	}
	return;
}

int main(void)
{
	int K,N,R;  //Money,CityNum,RoadNum
	while(cin>>K>>N>>R)
	{
		info poj1724(N,R);
		poj1724.input(R);
		poj1724.DFS(1,0,K,N);
		poj1724.output();
	}
	return 0;
}