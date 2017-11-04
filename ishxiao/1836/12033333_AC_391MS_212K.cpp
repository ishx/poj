//1836

//O(n*logn)算法，注意LIS和LDS使用不同的二分法
#include<iostream>
using namespace std;
const int inf=3;

//ord[]为不降序列
//二分法搜索digit，若str中存在digit，返回其下标
//若不存在，返回str中比digit小的最大那个数的（下标+1）
int binary_search_1(double ord[],double digit,int head,int length)
{
	int left=head,right=length;
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

//ord[]为不升序列
//二分法搜索digit，若str中存在digit，返回其下标
//若不存在，返回str中比digit大的最小那个数的（下标+1）
int binary_search_2(double ord[],double digit,int head,int length)
{
	int left=head,right=length;
	int mid;
	while(right!=left)
	{
		mid=(left+right)/2;
		if(digit==ord[mid])
			return mid;
		else if(digit>ord[mid])
			right=mid;
		else
			left=mid+1;
	}
	return left;
}

int main(int i,int j)
{
	int n;  //士兵数
	while(cin>>n)
	{
		double* h=new double[n+1];

		for(i=1;i<=n;i++)
			cin>>h[i];

		int max=0;  
		for(int m=1;m<=n;m++)  //对身高队列每一个值作为分界点，进行枚举
		{
			double* ord=new double[n+1];

			/*Dp-(0~m)-LIS*/

			ord[0]=-1;  //下界无穷小
			int len_LIS=1;
			for(i=1;i<=m;i++)
			{
				ord[len_LIS]=inf; //上界无穷大
				j=binary_search_1(ord,h[i],0,len_LIS);
				if(j==len_LIS)  //sq[i]大于ord最大（最后）的元素
					len_LIS++;
				ord[j]=h[i];
			}
			len_LIS--; //减去ord[0]的长度1

			/*Dp-(m+1~n)-LDS*/

			ord[m]=inf;  //下界无穷大
			int len_LDS=1;
			for(i=m+1;i<=n;i++)
			{
				ord[m+len_LDS]=-1; //上界无穷小
				j=binary_search_2(ord,h[i],m,m+len_LDS);
				if(j==m+len_LDS)  //sq[i]大于ord最小（最后）的元素
					len_LDS++;
				ord[j]=h[i];
			}
			len_LDS--;  //减去ord[m]的长度1

			//max为对于当前m的 最长不升子序列LIS 和 最长不降子序列LDS 长度之和

			if(max<len_LIS+len_LDS)
				max=len_LIS+len_LDS;

			delete ord;
		}
		
		cout<<n-max<<endl;

		delete h;
	}
	return 0;
}