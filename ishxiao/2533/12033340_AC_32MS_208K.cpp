//2533mean1 

//O(n^2)算法
#include<iostream>
using namespace std;

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		int* sq=new int[n];
		int* dp=new int[n];  //dp[i]表示以第i个位置为终点的最长不下降序列的长度

		for(i=0;i<n;i++)
			cin>>sq[i];

		int max_length=0;
		for(i=0;i<n;i++)
		{
			dp[i]=1;  //初始化dp[0]=1,其他最小值为1
			for(j=0;j<i;j++)
				if(sq[j]<sq[i] && dp[i]<dp[j]+1)
					dp[i]=dp[j]+1;

			if(max_length<dp[i])
				max_length=dp[i];
		}
		cout<<max_length<<endl;

		delete sq,dp;
	}
	return 0;
}