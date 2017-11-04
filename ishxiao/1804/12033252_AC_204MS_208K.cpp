/*借助Mergesort求逆序数O(nlogn)*/

//1804 

#include<iostream>
using namespace std;

const int inf=1000001;
int t;  //数字序列s[]的逆序数

void compute_t(int* s,int top,int mid,int end)
{
	int len1=mid-top+1;
	int len2=end-mid;

	int* left=new int[len1+2];
	int* right=new int[len2+2];

	int i,j;
	for(i=1;i<=len1;i++)
		left[i]=s[top+i-1];
	left[len1+1]=inf;

	for(j=1;j<=len2;j++)
		right[j]=s[mid+j];
	right[len2+1]=inf;

	i=j=1;
	for(int k=top;k<=end;k++)
		if(left[i]<=right[j])
			s[k]=left[i++];
		else
		{
			s[k]=right[j++];
			t+=len1-i+1;
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
	int test;
	cin>>test;
	for(int p=1;p<=test;p++)
	{
		int n;  //数字序列s[]长度
		cin>>n;

		int* s=new int[n+1];

		for(int i=1;i<=n;i++)
			cin>>s[i];

		t=0;
		mergesort(s,1,n);

		cout<<"Scenario #"<<p<<':'<<endl<<t<<endl<<endl;

		delete s;
	}
	return 0;
}