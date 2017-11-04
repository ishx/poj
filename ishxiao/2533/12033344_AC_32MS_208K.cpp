//2533mean2

//O(n*logn)算法
#include<iostream>
using namespace std;
const int inf=10001;

int binary_search(int ord[],int digit,int length)   //二分法搜索digit，若str中存在digit，返回其下标
{                                                   //若不存在，返回str中比digit小的最大那个数的（下标+1）
	int left=0,right=length;
	int mid;
	while(right!=left)
	{
		mid=(left+right)/2;
		if(digit==ord[mid])
			return mid;
		else if(digit<ord[mid])
			right=mid;
		else
			left=mid+1;
	}
	return left;
}

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		int* sq=new int[n+1];
		int* ord=new int[n+1];  //对于dp[]的每一个取值k，ord[k]记录满足dp[i]=k的所有sq[i]中的最小值，即ord[k]=min{sq[i]} (dp[i]=k)

		for(i=1;i<=n;i++)
			cin>>sq[i];

		int max_length=0;
		ord[0]=-1;  //下界无穷小
		int len=1;  //ord的长度
		for(i=1;i<=n;i++)
		{
			ord[len]=inf;  //上界无穷大,指针len总是指向ord最后一个元素的后一位
			j=binary_search(ord,sq[i],len);
			if(j==len)  //sq[i]大于ord最大（最后）的元素
				len++;
			ord[j]=sq[i];
		}
		cout<<len-1<<endl; //len要减去ord[0]的长度1

		delete sq,ord;
	}
	return 0;
}