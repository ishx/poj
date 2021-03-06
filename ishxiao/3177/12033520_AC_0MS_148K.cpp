//3177 

#include<iostream>
using namespace std;

class Node
{
public:
	int id;
	class Node* next;
	Node():id(0),next(0){}
};

class solve
{
public:
	solve(int f,int r):F(f),R(r)
	{
		Initial();			
		Input_Creat();
		Tarjan(1,-1);		//本题给定的图G为连通的，因此从任意节点开始搜索均可
		printf("%d\n",BCC_SP_D_E());
	}
	~solve()
	{
		delete[] DFN;
		delete[] Low;
		delete[] degree;

		EmptyList();
	}

	int min(int a,int b) const{return a<b?a:b;}

	void Initial(void);				//申请存储空间并初始化
	void Input_Creat(void);			//输入并创建图G
	void AddEdge(int a,int b);		//向链表插入边a<->b (尾插入法，避免重边)

	void Tarjan(int s,int father);	//计算Low[]数组，用于寻找所有边双连通分量
	int BCC_SP_D_E(void);			//把每个边双连通分量(BCC)构造为缩点(SP)，并计算每个缩点的度数(D)
									//返回值为使得图G为双连通所需添加的最少的边(E)的数量

	void DelLink(Node* p);			//释放以p为表头的整条链
	void EmptyList(void);			//释放邻接链表

protected:

	int F;					//the number of islands
	int R;					//the number of roads
	Node** LinkHead;		//邻接链表表头

	int TimeStamp;			//(外部)时间戳
	int* DFN;				//DFN[u]: 结点u的搜索次序(时间戳)
	int* Low;				//Low[u]: 结点u或u的子树能够追溯到的最早的栈中结点的次序号

	int* degree;			//记录每个缩点的总度数
};

void solve::Initial(void)
{
	LinkHead=new Node*[F+1];
	for(int i=1;i<=F;i++)
		LinkHead[i]=0;

	TimeStamp=0;
	DFN=new int[F+1];
	Low=new int[F+1];
	memset(DFN,0,sizeof(int)*(F+1));
	memset(Low,0,sizeof(int)*(F+1));

	degree=new int[F+1];
	memset(degree,0,sizeof(int)*(F+1));

	return;
}

void solve::Input_Creat(void)
{
	int a,b;
	Node* tmp;
	for(int j=1;j<=R;j++)
	{
		scanf("%d %d",&a,&b);

		if(!LinkHead[a])
			LinkHead[a]=new Node;
		if(!LinkHead[b])
			LinkHead[b]=new Node;

		AddEdge(a,b);
	}
	return;
}

void solve::AddEdge(int a,int b)
{
	Node* pa=LinkHead[a];
	Node* p1=new Node;
	p1->id=b;

	while(pa->next)
	{
		pa=pa->next;
		if(pa->id==p1->id)	//出现重边，重边不插入链表
			return;
	}
	pa->next=p1;

	Node* pb=LinkHead[b];
	Node* p2=new Node;
	p2->id=a;

	while(pb->next)			//能执行到这里说明a<->b不是重边
		pb=pb->next;		//直接搜索到链表尾部插入
	pb->next=p2;

	return;
}

void solve::Tarjan(int s,int father)
{
	DFN[s]=Low[s]=++TimeStamp;
	for(Node* p=LinkHead[s]->next;p;p=p->next)
	{
		int t=p->id;
		if(t!=father && DFN[t]<DFN[s])
		{
			if(DFN[t]==0)			//s->t为树枝边
			{
				Tarjan(t,s);
				Low[s]=min(Low[s],Low[t]);
			}
			else					//s->t为后向边
			{
				Low[s]=min(Low[s],DFN[t]);
			}
		}
	}
	return;
}

int solve::BCC_SP_D_E(void)
{
	for(int i=1;i<=F;i++)
		if(LinkHead[i])
		{
			for(Node* p=LinkHead[i]->next;p;p=p->next)	//枚举图G中每两个连通的点i<->j
			{											//由于图G为无向图，则连通是双向的
				int j=p->id;
				if(Low[i]!=Low[j])		//图G中Low值相同的两个点必定在同一个边双连通分量(即同一个缩点)中
				{						//检查i、j是否不在同一个缩点中

					degree[Low[i]]++;	//结点i所在的缩点的度+1
					degree[Low[j]]++;	//结点j所在的缩点的度+1
				}
			}
		}
	
	int leave=0;			//记录总度数=1（叶子）的缩点
	for(int k=1;k<=F;k++)	//枚举各个缩点的度数D
		if(degree[k]/2==1)	//由于是无向图，因此每个缩点的度都重复计算了2次，除2后才是真实的度数
			leave++;

	return (leave+1)/2;		//将一棵树连成一个边双连通分量至少需要添加的边数=(叶子节点数+1)/2
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
	for(int i=1;i<=F;i++)
		if(LinkHead[i])
			DelLink(LinkHead[i]);
	return;
}

int main(void)
{
	int f,r;
	while(scanf("%d %d",&f,&r)!=EOF)
		solve poj3177(f,r);

	return 0;
}