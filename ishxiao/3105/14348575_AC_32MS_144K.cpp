//poj 3105
//sep9
#include <iostream>
using namespace std;

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--){
		int n;
		double ans=0;
		scanf("%d",&n);
		for(int i=0;i<31;++i){
			int s=1<<i;		
			double p=(((n-1)>>(i+1)<<i)+((n-1)&(s-1))+1)/(double)n;
			ans+=2*p*(1-p)*s;
		}	
		printf("%.2lf\n",ans);
	}
}
 