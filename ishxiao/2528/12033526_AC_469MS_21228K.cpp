//2528

#include<iostream>
#include<algorithm>
using namespace std;

class LineTree_Node
{
public:
	int s,e;		//区间端点
	int col;		//区间颜色
	LineTree_Node():s(0),e(0),col(0){}
};

class solve
{
public:
	solve(int n):N(n)
	{
		Initial();
		Input();
		CreatLineTree(1,Maxp,1);
		Solution();
	}
	~solve()
	{
		for(int i=1;i<=N;i++)
			delete[] reg[i];

		delete[] ep;
		delete[] dis;
		delete[] tagcol;
		delete[] LT;
	}

	void Initial(void);							//初始化并申请存储空间
	void Input(void);							//输入
	void CreatLineTree(int sp,int tp,int p);	//构造[sp,tp]线段树
	void Solution(void);						//插入区间，统计颜色
	void Insert(int a,int b,int p,int color);	//[a,b]:把区间[a,b]插入线段树
												//p:当前所在线段树的位置
												//color:当前区间的染色
	void DFS(int p);							//遍历线段树,计算线段树中不同颜色的个数

protected:

	int N;					//海报数(区间数)
	int Maxp;				//记录(压缩后的)最大端点,用于建造区间[1,Maxp]的线段树
	LineTree_Node* LT;		//线段树

	int **reg;				//顺序存储输入的区间（每张海报的宽度）
	int *ep;				//顺序存储输入的每个区间的2个端点
	unsigned short *dis;	//映射端点，压缩区间（离散化）

	bool* tagcol;			//标记能看见的颜色
	int cnt;				//计数器，记录线段树中能看见的不同的颜色数
};

void solve::Initial(void)
{
	cnt=0;

	reg=new int*[N+1];
	for(int i=1;i<=N;i++)
		reg[i]=new int[2];

	ep=new int[2*N+1];
	dis=new unsigned short[1e7+1];
	memset(dis,0,sizeof(unsigned short)*(1e7+1));

	tagcol=new bool[N+1];
	memset(tagcol,false,sizeof(bool)*(N+1));

	return;
}

void solve::Input(void)
{
	int p=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d %d",&reg [ i ][0],&reg [ i ][1]);

		/*避免相通的端点重复映射到不同的值*/
		/*也为了减少参与排序的元素个数，这里必须做标记*/
		/*同时为了节约空间，本用于离散化的dis[]数组暂时用来标记端点*/

		if(dis[reg[i][0]]==0)
		{
			ep[p++]=reg[i][0];
			dis[reg[i][0]]=1;
		}

		if(dis[reg[i][1]]==0)
		{
			ep[p++]=reg[i][1];
			dis[reg[i][1]]=1;
		}
	}

	/*离散化*/

	sort(ep,ep+p);			//区间端点排序

	unsigned short hash=0;
	for(int j=0;j<p;j++)
		dis[ep[j]]=++hash;	//把排好序的端点依次映射到1,2,...,Maxp

	Maxp=hash;
	LT=new LineTree_Node[4*Maxp+1];

	return;
}

void solve::CreatLineTree(int sp,int tp,int p)	
{
	LT[p].s=sp;
	LT[p].e=tp;

	if(sp==tp)
		return;

	/*注意线段树不一定都是完全二叉树*/
	/*但是为了处理方便，加快搜索效率*/
	/*我们完全可以把线段树以完全二叉树的形式进行构造、存储*/

	int mid=(sp+tp)>>1;
	CreatLineTree(sp,mid,p*2);
	CreatLineTree(mid+1,tp,p*2+1);
	
	return;
}

void solve::Solution(void)
{
	for(int i=1;i<=N;i++)
		Insert(dis[reg[i][0]],dis[reg[i][1]],1,i);	//逐个区间(海报)对线段树染色

	DFS(1);
	printf("%d\n",cnt);
	return;
}

void solve::Insert(int a,int b,int p,int color)
{
	if(b<LT[p].s || a>LT[p].e)	//[a,b]与[s,e]完全无交集
		return;					//说明[a,b]不被[s,e]所在的子树包含，无需向下搜索

	if(a<=LT[p].s && b>=LT[p].e)//[a,b]完全覆盖[s,e]
	{
		LT[p].col=color;//[s,e]染单色，暂时无需对[s,e]的子树操作(这是由线段树的搜索机制决定的)
		return;			//因此直接返回
	}

	/*若能执行到这里，说明[a,b]部分覆盖[s,e]*/

	if(LT[p].col>=0)	//[s,e]本为无色或者单色
	{											//由于不知道[a,b]覆盖了[s,e]多少
		LT[p*2].col=LT[p*2+1].col=LT[p].col;	//因此先由[s,e]的孩子继承[s,e]的单色
		LT[p].col=-1;							//[s,e]由于被部分覆盖，染色为多色
	}

	/*若能执行到这里，说明[s,e]为多色*/
	/*细化处理[s,e]的孩子，确定[s,e]中哪部分的区间是什么颜色*/

	Insert(a,b,p*2,color);
	Insert(a,b,p*2+1,color);

	return;
}

void solve::DFS(int p)
{
	if(LT[p].col==0)	//[s,e]为无色，其孩子也必为无色，无需继续搜索
		return;

	if(LT[p].col>0)		//[s,e]为单色，则无需向下搜索
	{					//因为其子区间必被[s,e]覆盖,能看见的只有[s,e]的颜色
		if(!tagcol[LT[p].col])
		{
			tagcol[LT[p].col]=true;
			cnt++;
		}
		return;
	}

	if(LT[p].col==-1)	//[s,e]为多色，说明能在[s,e]看到集中颜色
	{					//搜索其子区间具体有什么颜色
		DFS(p*2);
		DFS(p*2+1);
	}
	return;
}


int main(void)
{
	int test;
	scanf("%d",&test);
	for(int t=1;t<=test;t++)
	{
		int n;
		scanf("%d",&n);
		solve poj2528(n);
	}
	return 0;
}