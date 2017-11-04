//poj1033
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=10005;
int w[N],p[N],n,num;//w[i]：i位置上有一个应该移去w[i]的碎片;p[i]:应该放在i位置的碎片现在的位置
bool vis[N];
bool dfs(int k)//把现在在k位置的碎片复原，true代表有环
{
    vis[k]=true;
    int tp=w[k];
    if(w[tp]==0)
    {
        printf("%d %d\n",k,tp);
        w[k]=0;
        w[tp]=tp;
        p[tp]=tp;
        return false;
    }
    else if(vis[tp])
    {
        for(int i=n;i>=0;i--)
        {
            if(w[i]==0)
            {
                printf("%d %d\n",k,i);
                w[i]=w[k];
                w[k]=0;
                p[w[i]]=i;
                return true;
            }
        }
    }
    else
    {
        bool flag=dfs(tp);
        printf("%d %d\n",k,w[k]);
        w[k]=0;
        w[tp]=tp;
        p[tp]=tp;
        return flag;
    }
}
int main()
{
    while(scanf("%d%d",&n,&num)!=EOF)
    {
        int pos=1,nu,tp;
        memset(w,0,sizeof(w));
        bool flag=true;
        for(int i=1;i<=num;i++)
        {
            scanf("%d",&nu);
            for(int j=0;j<nu;j++)
            {
                scanf("%d",&tp);
                w[tp]=pos;
                p[pos]=tp;
                if(pos!=tp)
                    flag=false;
                pos++;
            }
        }
        if(flag)
        {
            printf("No optimization needed\n");
            continue;
        }
        for(int i=1;i<pos;i++)
        {
            if(p[i]!=i)
            {
                memset(vis,false,sizeof(vis));
                if(dfs(p[i]))
                    i--;
            }
        }
    }
    return 0;
}