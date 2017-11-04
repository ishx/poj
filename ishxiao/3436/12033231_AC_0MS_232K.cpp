/*BFS+不拆点 -> 成功AC*/

//3436

#include<iostream>
using namespace std;

const int inf=10001;
int s; //超级源
int t;   //超级汇

int n;  //总结点数（包括超级源、超级汇）
int p;  //每台机器的部分数
int cap[52][52];// 边容量


int min(int a,int b)
{
	return a<b?a:b;
}

/*利用BFS找增广链求网络最大流*/

int maxflow(void)  
{
	int queue[52];
	int head,tail;
	int pre[52]; //结点i的前驱
    
	int minflow;
	int flow = 0;
    int x,y;

    while(true)
    {
        memset(pre, -1, sizeof(pre));

        for(queue[head=tail=0]=s;head<=tail;head++)
        {
            x=queue[head];
            for(int i=0;(i<n) && (pre[t]==-1);i++)//当汇点还没有被标记时
               if (cap[x][i]>0 && pre[i]==-1)  //当结点u指向i的边存在，且i还没有标记前驱时
               {
                    pre[i]=x;//记录结点i的前驱为u
                    queue[++tail]=i;
               }
        }

        if(pre[t]==-1)
			break;//BFS后汇点没有被标记，则跳出while，已经不存在增广链

        minflow=inf;//初始化
        for(x=pre[y=t];y!=s;)//回溯
		{
			if(cap[x][y] < minflow)
				minflow=cap[x][y];//寻找当前增广链中最小容量的边，记录其边权（容量）
			y=x;
			x=pre[y];
		}

        for(x=pre[y=t];y!=s;) //当前增广链 流量调整
		{
			cap[x][y] -= minflow;  //正向弧容量减少
			cap[y][x] += minflow;  //反向弧容量增加
			y=x;
			x=pre[y];
		}

        flow += minflow;  //最大流=每次寻得的增广链的调整量之和
    }
    return flow;//返回最大流
}

int main(int i,int j,int k)
{
	int in[52][21];
	int out[52][3];
	int backup[52][52];//备份图
    int N;  //除超级源、超级汇以外的总结点数
	int line;  //生产线数（容量发生变化的边数）
	int flow;  //最大流

    while (cin>>p>>N)
    {
		/*Initial*/

        memset(cap,0,sizeof(cap)); //所有正向弧和反向弧的容量都初始化为0

        s=0;//超级源
		t=N+1; //超级汇
        n=N+2; //总结点数+2
		line=0;  //记录变化的边的数量(生产线数量)

		/*Input*/

        for(i=1;i<=N;i++)
            for(j=0;j<2*p+1;j++)
                cin>>in[i][j];    //用一个数列存储第i个结点的信息 in[i][0] 为结点i的容量
        
		bool flag_s, flag_t;
        for(i=1;i<=N;i++)
        {
            flag_s=flag_t=true;
            for(k=0;k<p;k++)
            {
                if(in[i][1+k]==1)
					flag_s=false;  //检查第i个结点的输入序列信息，当输入列不含1时
                if(in[i][p+1+k]==0)
					flag_t=false;//检查第i个结点的输出序列信息，当输出列全为1时
            }
            if(flag_s)
				cap[s][i]=in[i][0];  //当输入列不含1时,S->i，边容量为i的容量
            if(flag_t)
				cap[i][t]=in[i][0]; //当输出列全为1时,i->t，边容量为i的容量

            bool flag=true;
            for(j=1;j<=N;j++)
				if(i!=j)
                {
                    flag=true;
                    for(k=0;(k<p) && flag;k++)
						if(in[i][p+1+k]+in[j][1+k]==1)  //当第i个结点的第k个输出位，对应第j个结点的第k个输入位之和全不为0时
                            flag=false;

                    if(flag)
						cap[i][j] = min(in[i][0], in[j][0]);  //i->j,边容量为i的容量和j的容量的最小值
                }
        }

		/*利用BFS找增广链求网络最大流*/

        memcpy(backup, cap, sizeof(cap));  //把寻找增广链前的图的容量信息复制
        flow=maxflow();  //返回最大流
        
		/*Output*/

        for(i=1;i<=N;i++)   //注意范围，排除了含超级源和超级汇的边
			for(j=1;j<=N;j++)
                if (cap[i][j] < backup[i][j])//比较调整前后的边权，若容量减少了，则输出这条边的信息
                {
                    out[line][0]=i;     //i,j为生产线的两端点
                    out[line][1]=j;
                    out[line][2]=backup[i][j] - cap[i][j];//变化的流量值（该生产线的最大生产量）
                    line++;
                }

        cout<<flow<<' '<<line<<endl;
        for(i=0;i<line;i++)
            cout<<out[i][0]<<' '<<out[i][1]<<' '<<out[i][2]<<endl;
    }
    return 0;
}
