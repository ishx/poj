/*优先队列*/

//3253 

#include<iostream>
using namespace std;

int cmp(const void* a,const void* b)
{
	return *(int*)a-*(int*)b;
}

int main(void)
{
	int n;
	while(cin>>n)
	{
		__int64 * w=new __int64[n+1];  //每块木板的价值

		for(int p=1;p<=n;p++)
			scanf("%I64d",&w[p]);

		qsort(w,n+1,sizeof(__int64),cmp);

		__int64 mincost=0;
		for(int i=1;i<=n-1;i++)  //每次枚举余下数列的前2个（最小）的元素，则i到n-1即可
		{
			__int64 sum=w[i]+w[i+1];   //此时w[i]和w[i+1]已经没有用了
			mincost+=sum;

			for(int j=i+2;j<=n;j++)  //寻找w[i]+w[i+1]即sum在余下数列的合适位置，并插入
			{
				if(sum>w[j])   //sum大于当前元素
				{
					w[j-1]=w[j];  //当前元素前移一格
					if(j==n)   //sum大于最后的元素(即大于所有元素)
					{
						w[j]=sum; //插入到最后
						break;
					}
				}
				else
				{
					w[j-1]=sum;  //插入到比sum大的第一个元素前面(此前的元素均被前移)
					break;
				}
			}
		}

		printf("%I64d\n",mincost);
	}
	return 0;
}