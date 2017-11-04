//poj 3154
//sep9
#include <iostream>
#include <cmath>
using namespace std;
double a[2048];
double b[2048];

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)==2){
		for(int i=0;i<n;++i)
			a[i]=i*(10000.0/n);
		for(int i=0;i<(n+m);++i)
			b[i]=i*(10000.0/(n+m));
		double ans=0;
		for(int i=0;i<n;++i){
			double minx=9999999.9;
			for(int j=0;j<m+n;++j)
				minx=min(minx,fabs(a[i]-b[j]));
			ans+=minx;	
		}
		printf("%.4lf\n",ans);
	}
	return 0;	
} 