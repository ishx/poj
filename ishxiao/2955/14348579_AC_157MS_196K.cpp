//poj 2955
//sep9
#include <iostream>
using namespace std;
char s[128];
int dp[128][128];
int n;

int rec(int l,int r)
{
	if(dp[l][r]!=-1)
		return dp[l][r];
	if(l==r)
		return dp[l][r]=0;
	if(l+1==r){
		if(s[l]=='('&&s[r]==')')
			return dp[l][r]=2;
		if(s[l]=='['&&s[r]==']')
			return dp[l][r]=2;
	}
	int maxx=0;
	if(s[l]=='('&&s[r]==')')
		maxx=max(maxx,2+rec(l+1,r-1));
	if(s[l]=='['&&s[r]==']')
		maxx=max(maxx,2+rec(l+1,r-1));	
	for(int k=l;k<=r-1;++k)
		maxx=max(maxx,rec(l,k)+rec(k+1,r));
	return dp[l][r]=maxx;
}

int main()
{
	while(scanf("%s",s)==1){
		if(s[0]=='e')
			break;
		memset(dp,-1,sizeof(dp));
		n=strlen(s);	
		printf("%d\n",rec(0,n-1));
	}
	return 0;	
} 