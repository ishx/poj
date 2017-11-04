//poj 2945
//sep9
#include <iostream>
using namespace std;
int ans[20048];
int v[200],index;
char s[32];
struct TRIE
{
	int s[6];
	int cnt;	
}a[400010];

void insert(char ss[])
{
	int i=0,h=0;
	while(ss[i]!='\0'){
		if(!a[h].s[v[ss[i]]])
			a[h].s[v[ss[i]]]=++index;
		h=a[h].s[v[ss[i]]];
		++i;
	}
	++a[h].cnt;
}

int main()
{
	int n,m;
	v['A']=0;v['G']=1;v['T']=2;v['C']=3;
	while(scanf("%d%d",&n,&m)==2){
		if(n==0&&m==0)
			break;
		memset(a,0,sizeof(a));		
		index=0;
		for(int i=0;i<n;++i){
			scanf("%s",s);
			insert(s);	
		}
		memset(ans,0,sizeof(ans));
		for(int i=0;i<=index;++i)
			if(a[i].cnt)
				++ans[a[i].cnt];
		for(int i=1;i<=n;++i)
			printf("%d\n",ans[i]);
	}
	return 0;	
} 