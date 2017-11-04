//2299 

#include<iostream>
using namespace std;

const int inf=1000000000;  //10E

__int64 t; //s[]数列逆序数

void compute_t(int* s,int top,int mid,int end)
{
	int len_L=mid-top+1;
	int len_R=end-mid;

	int* left=new int[len_L+2];
	int* right=new int[len_R+2];

	int i,j;
	for(i=1;i<=len_L;i++)
		left[i]=s[top+i-1];
	left[len_L+1]=inf;   //设置无穷上界，避免比较大小时越界

	for(j=1;j<=len_R;j++)
		right[j]=s[mid+j];
	right[len_R+1]=inf;   //设置无穷上界，避免比较大小时越界

	i=j=1;
	for(int k=top;k<=end;)
		if(left[i]<=right[j])
			s[k++]=left[i++];
		else
		{
			s[k++]=right[j++];
			t+=len_L-i+1;    //计算逆序数
		}

	delete left;
	delete right;

	return;
}

void mergesort(int* s,int top,int end)
{
	if(top<end)
	{
		int mid=(top+end)/2;
		mergesort(s,top,mid);
		mergesort(s,mid+1,end);
		compute_t(s,top,mid,end);
	}
	return;
}

int main(void)
{
	int n;  //序列长度
	while(cin>>n)
	{
		if(!n)
			break;

		/*Input*/

		int* s=new int[n+1];
		for(int i=1;i<=n;i++)
			cin>>s[i];

		/*Merge-Sort*/

		t=0;  //initial
		mergesort(s,1,n);

		/*Output*/

		printf("%I64d\n",t);

		/*Relax*/

		delete s;

	}
	return 0;
}