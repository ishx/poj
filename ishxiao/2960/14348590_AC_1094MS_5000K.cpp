//poj 2960
//sep9
#include <iostream>
#include <set>
using namespace std;
int s[128];
int grundy[10024];
int maxx;
int num;
int get_grundy(int x)
{
	if(grundy[x]!=-1)
		return grundy[x];
	int tmp[10024];
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<num;++i)
		if(x-s[i]>=0)
			tmp[get_grundy(x-s[i])]=1;		
	int t;
	for(t=0;;++t)
		if(tmp[t]==0)
			break;
	return grundy[x]=t;
}
int main()
{
	while(scanf("%d",&num)==1&&num){
		int maxx=-1;
		for(int i=0;i<num;++i){
			scanf("%d",&s[i]);
			maxx=max(maxx,s[i]);
		}
		int t;
		memset(grundy,-1,sizeof(grundy));
		scanf("%d",&t);
		while(t--){
			int x,ans=0;
			scanf("%d",&x);
			while(x--){
				int d;
				scanf("%d",&d);
				ans=ans^get_grundy(d);
			}
			if(ans)
				printf("W");
			else
				printf("L");
		}
		puts("");
	}
	return 0;	
} 