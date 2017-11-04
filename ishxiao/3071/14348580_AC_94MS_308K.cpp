//poj 3071
//sep9
#include <iostream>
using namespace std;
const int maxN=128;
double p[maxN+10][maxN+10];
double dp[maxN+10][maxN+10];

int main()
{
	int n;
	while(scanf("%d",&n)==1&&n!=-1){
		for(int i=1;i<=(1<<n);++i)
			for(int j=1;j<=(1<<n);++j)
				scanf("%lf",&p[i][j]);
		for(int i=1;i<=(1<<n);++i)
			dp[0][i]=1.0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=(1<<n);++j){
				double sum=0;
				for(int k=1;k<=(1<<n);++k)
					if((j-1)>>i==(k-1)>>i&&(j-1)>>(i-1)!=(k-1)>>(i-1))
						sum+=dp[i-1][k]*p[j][k];
				dp[i][j]=dp[i-1][j]*sum;	
			}
		double maxx=-1.0;
		int idx;
/*		for(int i=1;i<=n;++i){
			for(int j=1;j<=(1<<n);++j)
				printf("%.3lf ",dp[i][j]);
			printf("\n");
		}
*/
		for(int i=1;i<=(1<<n);++i){
			if(maxx<dp[n][i]){
				maxx=dp[n][i];
				idx=i;
			}
		}
		printf("%d\n",idx);
	}
	return 0;	
} 
