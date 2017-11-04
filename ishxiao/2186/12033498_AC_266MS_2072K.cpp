//2186 

#include<iostream>
#include<stack>
using namespace std;

/*图G的结点的存储结构*/
class Node
{
public:
	int id;
	class Node* next;
	Node():id(0),next(0){}
};

/*缩点(极大强连通分量)的存储结构*/
class Shrink_point
{
public:
	int in;		//缩点入度
	int out;	//缩点出度
	int num;	//缩点内含有图G的结点的个数
	Shrink_point():in(0),out(0),num(0){}
};

/*******************************************************/

class solve
{
public:
	solve(int n,int m):N(n),M(m)
	{
		Initial();
		Input_Creat();

		/*注意:有向图G不一定从任何位置开始搜索都能遍历所有点*/
		for(int i=1;i<=N;i++)
			if(DFN[i]==0)
			{
				stack_Node.push(i);		//搜索起点入栈
				Status[i]=1;
				Tarjan(i);
			}

		printf("%d\n",solution());

	}
	~solve()
	{
		delete[] DFN;
		delete[] Low;
		delete[] Status;
		delete[] SCC;
		delete[] sp;

		EmptyList();

		while(!stack_Node.empty())
			stack_Node.pop();
	}

	int min(int a,int b) const{return a<b?a:b;}

	void Initial(void);		//申请存储空间并初始化
	void Input_Creat(void);	//输入并构造有向图G
	void Tarjan(int s);		//寻找图G的所有极大强连通分量
	int solution(void);		//若缩点图只有1个出度为0的缩点，返回缩点内包含的结点数。否则无解,返回0

	void DelLink(Node* p);	//释放以p为表头的整条链
	void EmptyList(void);	//释放邻接链表

protected:
	int N;					//the number of cows
	int M;					//the number of popular pairs
	Node** LinkHead;		//邻接链表表头

	int TimeStamp;			//(外部)时间戳
	int* DFN;				//DFN[u]: 结点u的搜索次序(时间戳)
	int* Low;				//Low[u]: 结点u或u的子树能够追溯到的最早的栈中结点的次序号

	stack<int>stack_Node;	//辅助栈，用于寻找极大强连通分量
	int* Status;			//Status[i]-> 0:i未入栈  1:i在栈中  2:i已出栈
	int* SCC;				
	int SCC_id;				//SCC[i]=SCC_id  图G中结点i所属的极大强连通分量(缩点)的编号为SCC_id
	Shrink_point* sp;		//存储每个缩点(极大强连通分量)的信息
};

void solve::Initial(void)
{
	LinkHead=new Node*[N+1];
	for(int i=1;i<=N;i++)
		LinkHead[i]=0;

	TimeStamp=0;
	DFN=new int[N+1];
	Low=new int[N+1];
	memset(DFN,0,sizeof(int)*(N+1));
	memset(Low,0,sizeof(int)*(N+1));

	SCC_id=0;
	SCC=new int[N+1];
	Status=new int[N+1];
	memset(Status,0,sizeof(int)*(N+1));

	sp=new Shrink_point[N+1];

	return;
}

void solve::Input_Creat(void)
{
	int a,b;
	for(int j=1;j<=M;j++)
	{
		scanf("%d %d",&a,&b);

		if(!LinkHead[a])
			LinkHead[a]=new Node;

		Node* tmp=LinkHead[a]->next;
		LinkHead[a]->next=new Node;
		LinkHead[a]->next->id=b;
		LinkHead[a]->next->next=tmp;
	}
	return;
}

void solve::Tarjan(int s)
{
	DFN[s]=Low[s]=++TimeStamp;
	if(LinkHead[s])
	{
		for(Node* p=LinkHead[s]->next;p;p=p->next)
		{
			int t=p->id;
			if(DFN[t]<DFN[s])
			{
				if(DFN[t]==0)			//s->t为树枝边
				{
					stack_Node.push(t);
					Status[t]=1;

					Tarjan(t);
					Low[s]=min(Low[s],Low[t]);
				}
				else if(DFN[t]!=0 && Status[t]==1)	//s->t为后向边
				{
					Low[s]=min(Low[s],DFN[t]);
				}
			}
		}
	}
	if(DFN[s]==Low[s])	//找到极大强连通分量
	{
		SCC_id++;
		for(int node=stack_Node.top();;node=stack_Node.top())
		{
			stack_Node.pop();
			Status[node]=2;
			SCC[node]=SCC_id;
			sp[ SCC_id ].num++;

			if(node==s || stack_Node.empty())
				break;
		}
	}
	return;
}

int solve::solution(void)
{
	/*计算所有缩点的入度和出度*/

	for(int i=1;i<=N;i++)
		if(LinkHead[i])
		{
			for(Node* p=LinkHead[i]->next;p;p=p->next)
			{
				int j=p->id;
				if(SCC[i]!=SCC[j])
				{
					sp[ SCC[i] ].out++;
					sp[ SCC[j] ].in++;
				}
			}
		}

	/*寻找出度为0的缩点*/

	int cnt=0;		//记录出度为0的缩点个数
	int pk;			//记录出度为0的缩点编号

	for(int k=1;k<=SCC_id;k++)
		if(sp[k].out==0)
		{
			cnt++;
			pk=k;
		}
	if(cnt!=1)			//出度为0的缩点的个数不为1，本题无解
		return 0;
	
	return sp[pk].num;	//返回出度为0的缩点所包含图G中的结点个数
}

void solve::DelLink(Node* p)
{
	if(p->next)
		p=p->next;
	delete[] p;
	return;
}

void solve::EmptyList(void)
{
	for(int i=1;i<=N;i++)
		if(LinkHead[i])
			DelLink(LinkHead[i]);
	return;
}

int main(void)
{
	int n,m;
	while(scanf("%d %d",&n,&m)!=EOF)
		solve poj2186(n,m);

	return 0;
}