//3422

#include<stdio.h>
#include<string.h>
 const int maxn=5008;
 const int oo=200000000;
 int N;
 int head[maxn],tot,src,dest;
 struct Edge
 {
	 int from,to,cost,val,next;
 }edge[maxn*maxn];
 void add(int a,int b,int val,int cost)
 {
	 edge[tot].from=a,edge[tot].to=b,edge[tot].cost=cost,edge[tot].val=val;
	 edge[tot].next=head[a];head[a]=tot++;
	 edge[tot].from=b,edge[tot].to=a,edge[tot].cost=-cost,edge[tot].val=0;
	 edge[tot].next=head[b];head[b]=tot++;
 }
 //////////////////////////////SPFA用到的资源
 int que[maxn*maxn],dis[maxn],pre[maxn];
 bool vis[maxn];
 //////////////////////
 bool SPFA()
 {
	 int i,j,k,front=0,rear=0,tx,temp; 
	 for(i=src;i<=dest;i++)
	 {
		 vis[i]=false,dis[i]=oo,pre[i]=-1;
	 }
	 que[rear++]=src;
	 dis[src]=0,vis[src]=true;
	 while(front<rear)
	 {
		// printf("%d\n",rear);
		 tx=que[front++];
		 vis[tx]=false;
		 temp=head[tx];
		 while(temp!=-1)
		 {
			 k=edge[temp].to;
			 if(edge[temp].val>0&&dis[k]>dis[tx]+edge[temp].cost)
			 {
				 dis[k]=dis[tx]+edge[temp].cost;
				 pre[k]=temp;
				 if(!vis[k])
				 {
					 vis[k]=true;
					 que[rear++]=k;
				 }
			 }
			 temp=edge[temp].next;
 }
    }
    if(pre[dest]==-1)
    {
        return false;
    }
    return true;
}
void min_cost_max_flow()
{
    int i,j,k,l;
    int ans=0,min;
    while(1)
    { 
        if(!SPFA())
            break;
        ans+=dis[dest];
        min=oo,i=dest;
        while(pre[i]!=-1)
        {
            if(edge[pre[i]].val<min)
                min=edge[pre[i]].val;
            i=edge[pre[i]].from;
        }
        i=dest;
        while(pre[i]!=-1)
        {
            edge[pre[i]].val-=min;
            edge[pre[i]^1].val+=min;
            i=edge[pre[i]].from;
        }
    }
    printf("%d\n",-ans);
}
int mp[55][55],flow;
void init()
{
/////////////////////////
    memset(head,-1,sizeof(head));
    tot=0;
//////////////////////
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            scanf("%d",&mp[i][j]); 
            add(i*N+j+1,i*N+j+N*N+1,oo,0);
            add(i*N+j+1,i*N+j+N*N+1,1,-mp[i][j]);
        }
    }
    src=0,dest=2*N*N+1;
    add(src,1,flow,0);
    add(2*N*N,dest,flow,0);
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(j<N-1)
            {
                add(N*N+i*N+j+1,i*N+j+2,oo,0);
            }
            if(i<N-1)
            {
                 add(N*N+i*N+j+1,(i+1)*N+j+1,oo,0);
            }
        }
    }
    min_cost_max_flow();
}
int main()
{
    while(scanf("%d%d",&N,&flow)!=EOF)
    {
      init();
    }
    return 0;
}