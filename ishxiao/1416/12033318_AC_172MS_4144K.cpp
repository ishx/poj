//1416 

#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int getlen(int n)  //得到n的位长度
{
	if(n<10)
		return 1;
	else if(n<100)
		return 2;
	else if(n<1000)
		return 3;
	else if(n<10000)
		return 4;
	else if(n<100000)
		return 5;
	else
		return 6;
}

int getvalue(char* s,int i)  //得到数字字符串s前i位字符（数字）组成的int值
{
	int k=i;
	int sum=0;
	while(k)
	{
		k--;
		sum+=(s[k]-'0')*(int)pow(10.0,(double)(i-k-1));
	}
	return sum;
}

int gethead(int n,int i)  //得到由n的前i位数字构成的int
{
	int len=getlen(n);
	if(len<=i)
		return n;
	return n/(int)pow(10.0,(double)(len-i));
}

int gettail(int n,int i)  //得到由n的后i位数字构成的int
{
	return n%(int)pow(10.0,(double)i);
}

int aim;  //目标数

int result;  //最优划分的和
int path;  //最优划分的划分方式

int sum;   //某种划分的和
int p;  //某种划分方式

int vist[1000000];  //记录每个sum出现的次数
                     //999999是当n=999999时的最大和值

void DFS(char* s,int len)
{
	if(len==0)
	{
		vist[sum]++;
		if(sum>result && sum<=aim)
		{
			result=sum;
			path=p;
		}
		return;
	}

	for(int i=1;i<=len;i++)
	{
		int a=getvalue(s,i);  //n的前i位字符转变为数字留下，计入部分和
		sum+=a;  //部分和
		if(sum>aim)  //剪枝，部分和已经大于aim，无需继续往下搜索
		{
			sum-=a;
			continue;
		}
		p=p*10+i;  //记录划分方式

		char b[7];  //构造n的后i位字符序列，继续递归
		int j=0;
		for(int k=i;k<len;k++)
			b[j++]=s[k];
		b[j]='\0';

		DFS(b,len-i);

		sum-=a;  //回溯
		p/=10;
	}
	return;
}

int main(void)
{
	while(true)
	{
		/*Input*/

		char s[7];  //打印纸上的数字
		cin>>aim>>s;

		int len=strlen(s);
		int n=getvalue(s,len);  //构造s的数字序列n

		if(!aim && !n)
			break;

		if(aim==n)      //目标值与打印纸上的数字一致
		{
			cout<<aim<<' '<<n<<endl;
			continue;
		}

		int num=n; //temporary
		int k=0; //n的各位数字之和
		while(num)
		{
			k+=num%10;   //逐位划分是 和最小的划分方式
			num/=10;
		}
		if(k>aim) //最小和也大于aim，则所有划分都大于aim
		{
			cout<<"error"<<endl;
			continue;
		}

		/*Initial*/

		result=-1;
		sum=0;
		path=0;
		p=0;
		memset(vist,0,sizeof(vist));

		/*DFS*/

		DFS(s,len);

		/*Output*/

		if(vist[result]>1)  //最优解多于一个
			cout<<"rejected"<<endl;
		else if(vist[result]==1)  //有唯一最优解
		{
			cout<<result<<' ';

			int L=getlen(path);  //输出划分的方式
			for(int i=1;i<=L;i++)
			{
				int k=gethead(path,1);   //取path的第一位k，k的值等于n的第一段划分位数，即从n的第1位到第k位
				cout<<gethead(n,k)<<' ';
				n=gettail(n,len-=k);
				path=gettail(path,L-i);
			}
			cout<<endl;
		}
	}
	return 0;
}