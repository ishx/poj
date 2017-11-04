//poj 1694
//sep9
#include <iostream>
#include <algorithm>
using namespace std;
const int maxN=256;
int n;
int tree[maxN][maxN];
int ans[maxN];
int cmp(int a,int b)
{
	return a>b;
}
int dfs(int u)
{
	int tmp[maxN],t=0;
	if(tree[u][0]==0)
		return ans[u]=1;
	for(int i=1;i<=tree[u][0];++i){
		dfs(tree[u][i]);
		tmp[t++]=ans[tree[u][i]];
	}
	sort(tmp,tmp+t,cmp);
	int maxx=-1;
	for(int i=0;i<t;++i)
		maxx=max(maxx,tmp[i]+i);
	return ans[u]=maxx;	
}

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			tree[i][0]=0;
		for(int i=0;i<n;++i){
			int u,x;
			scanf("%d%d",&u,&x);
			while(x--){
				int v;
				scanf("%d",&v);
				tree[u][++tree[u][0]]=v;
			}
		}
		printf("%d\n",dfs(1));
	}	
}