/*差分约束+优化Bellman*/

//2983

#include <iostream>
using namespace std;

const int inf=1000000000;

class
{
public:
	int s,e;
}edge[200001];

int N; //太空站数目
int M; //tips数

int dist[1001];  //源点到各点的距离
int w[200001];  //边权

int main(int i,int j)
{
    while(cin>>N>>M)
    {
		memset(dist,0,sizeof(dist));  //初始化源点到各点的距离
		int pe=0;

		for(i=0;i<M;i++)
		{
			char pv;
			int a,b,x;

			getchar();   //吃掉回车
			scanf("%c",&pv);   //由于要频繁输入，用scanf比cin要快1500ms

			if(pv=='P')  //清晰边权，即A、B间距离确定，建立双向边
			{
				scanf("%d%d%d",&a,&b,&x);
				edge[pe].s=a;
				edge[pe].e=b;
				w[pe++]=x;
				edge[pe].s=b;
				edge[pe].e=a;
				w[pe++]=-x;
			}
			else if(pv=='V')  //模糊边权，即A、B间距离不确定，建立单向边
			{
				scanf("%d%d",&a,&b);
				edge[pe].s=a;
				edge[pe].e=b;
				w[pe++]=1;
			}
		}

		/*Bellman-Ford*/

		bool sign;  //用于Bellman-Ford算法优化
		for(j=0;j<N;j++)
		{
			sign=false;
			for(i=0;i<pe;i++)
				if(dist[ edge[i].e ] > dist[ edge[i].s ] - w[i])
				{
					dist[ edge[i].e ] = dist[ edge[i].s ] - w[i];
					sign=true;
				}  
			if(!sign)//若dist没有任何改变，则以后也不会改变，可以直接退出循环
				break;
		}//循环n次后若flag == false 说明有负权回路，或者权值矛盾

		if(sign)
			cout<<"Unreliable"<<endl; //存在负权环
		else
			cout<<"Reliable"<<endl;   //不存在负权环
  
    }
    return 0;
}