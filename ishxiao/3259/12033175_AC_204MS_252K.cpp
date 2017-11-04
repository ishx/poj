//3259 

#include<iostream>
using namespace std;

int dis[1001];      //源点到各点权值
const int max_w=10001;      //无穷远

class weight
{
public:
    int s;
	int e;
	int t;
}edge[5200];

int N,M,W_h; //N (1≤N≤500)fields 顶点数
             //M (1≤M≤2500)paths 正权双向边
             //W_h (1≤W≤200) wormholes 虫洞（回溯），负权单向边
int all_e;   //边集（边总数）

bool bellman(void)
{
    bool flag;

	/*relax*/

    for(int i=0;i<N-1;i++)
    {
        flag=false;
        for(int j=0;j<all_e;j++)
            if(dis[edge[j].e] > dis[edge[j].s] + edge[j].t)
			{
                dis[edge[j].e] = dis[edge[j].s] + edge[j].t;
                flag=true;         //relax对路径有更新
			}
        if(!flag)   
            break;  //只要某一次relax没有更新，说明最短路径已经查找完毕，或者部分点不可达，可以跳出relax
    }

	/*Search Negative Circle*/

    for(int k=0;k<all_e;k++)
        if( dis[edge[k].e] > dis[edge[k].s] + edge[k].t)
            return true;

    return false;
}
int main(void)
{
    int u,v,w;

	int F;
    cin>>F;
    while(F--)
    {
		memset(dis,max_w,sizeof(dis));    //源点到各点的初始值为无穷，即默认不连通

        cin>>N>>M>>W_h;

        all_e=0;      //初始化指针

		/*read in Positive Paths*/

        for(int i=1;i<=M;i++)
        {
            cin>>u>>v>>w;
            edge[all_e].s=edge[all_e+1].e=u;
            edge[all_e].e=edge[all_e+1].s=v;
            edge[all_e++].t=w;
            edge[all_e++].t=w;               //由于paths的双向性，两个方向权值相等，注意指针的移动
        }

		/*read in Negative Wormholds*/

        for(int j=1;j<=W_h;j++)
        {
            cin>>u>>v>>w;
            edge[all_e].s=u;
            edge[all_e].e=v;
            edge[all_e++].t=-w;     //注意权值为负
        }

		/*Bellman-Ford Algorithm*/

        if(bellman())
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
	}
	return 0;
}