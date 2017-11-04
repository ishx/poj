/* TrieTree + MergeSet + EulerPath*/

//2513

#include<iostream>
using namespace std;  

const int large=500000;  //25W条棒子，有50W个端点

class TrieTree_Node   //字典树结点
{
	public:
		bool flag;   //标记到字典树从根到当前结点所构成的字符串是否为一个(颜色)单词
		int id;     //当前颜色(结点)的编号
		TrieTree_Node* next[27];

		TrieTree_Node()   //initial
		{
			flag=false;
			id=0;
			memset(next,0,sizeof(next));  //0 <-> NULL
		}
}root;   //字典树根节点

int color=0;  //颜色编号指针，最终为颜色总个数

int degree[large+1]={0};   //第id个结点的总度数
int ancestor[large+1];   //第id个结点祖先


/*寻找x结点的最终祖先*/

int find(int x)
{
	if(ancestor[x]!=x)
		ancestor[x]=find(ancestor[x]);   //路径压缩
	return ancestor[x];
}

/*合并a、b两个集合*/

void union_set(int a,int b)
{
	int pa=find(a);
	int pb=find(b);
	ancestor[pb]=pa;   //使a的祖先 作为 b的祖先
	return;
}

//利用字典树构造字符串s到编号int的映射

int hash(char *s)  
{
	TrieTree_Node* p=&root;  //从TrieTree的根节点出发搜索单词(单词不存在则创建)

    int len=0;
    while(s[len]!='\0')
    {
		int index=s[len++]-'a';  //把小写字母a~z映射到数字的1~26，作为字典树的每一层的索引

        if(!p->next[index])  //当索引不存在时，构建索引
			p->next[index]=new TrieTree_Node;

		p=p->next[index];
    }

	if(p->flag)  //颜色单词已存在
		return p->id;  //返回其编号
	else   //否则创建单词
	{
		p->flag=true;
		p->id=++color;
		return p->id;   //返回分配给新颜色的编号
	}
}

int main(void)  
{
	/*Initial the Merge-Set*/

    for(int k=1;k<=large;k++)   //初始化，每个结点作为一个独立集合
		ancestor[k]=k;  //对于只有一个结点x的集合，x的祖先就是它本身

	/*Input*/

	char a[11],b[11];
    while(cin>>a>>b)  
    {
		/*Creat the TrieTree*/

		int i=hash(a);
		int j=hash(b);  //得到a、b颜色的编号

		/*Get all nodes' degree*/

        degree[i]++;
        degree[j]++;   //记录a、b颜色出现的次数(总度数)

		/*Creat the Merge-Set*/

		union_set(i,j);
	}

	/*Judge the Euler-Path*/

	int s=find(1);  //若图为连通图，则s为所有结点的祖先
	                    //若图为非连通图，s为所有祖先中的其中一个祖先

	int num=0;  //度数为奇数的结点个数

	for(int i=1;i<=color;i++)
	{
		if(degree[i]%2==1)
			num++;
				
		if(num>2)   //度数为奇数的结点数大于3，欧拉路必不存在
		{
			cout<<"Impossible"<<endl;
			return 0;
		}

		if(find(i)!=s)   //存在多个祖先，图为森林，不连通
		{
			cout<<"Impossible"<<endl;
			return 0;
		}
	}

	if(num==1) //度数为奇数的结点数等于1，欧拉路必不存在
		cout<<"Impossible"<<endl;
	else       //度数为奇数的结点数恰好等于2或不存在，存在欧拉路
		cout<<"Possible"<<endl;

	return 0;
}