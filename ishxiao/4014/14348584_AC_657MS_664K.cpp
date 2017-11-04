//poj 4014
//sep9
#include <iostream>
#include <algorithm>
using namespace std;
int n;
struct DICE
{
	int ids;
	int num;
	int a[128];
}d[1024];

int cmp1(DICE x,DICE y)
{
	return x.num<y.num;
}

int cmp2(DICE x,DICE y)
{
	return x.ids<y.ids;
}
int main()
{
	scanf("%d",&n);
	int sum=0;
	double ans=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&d[i].num);
		sum+=d[i].num;
		d[i].ids=i;
	}
	sort(d+1,d+1+n,cmp1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=d[i].num;++j){
			d[i].a[j]=sum--;
			ans+=d[i].a[j]*1.0/d[i].num;
		}
	sort(d+1,d+1+n,cmp2);
	printf("%.5lf\n",ans);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=d[i].num;++j)
			printf("%d ",d[i].a[j]);
		printf("\n");
	}
	return 0;	
}