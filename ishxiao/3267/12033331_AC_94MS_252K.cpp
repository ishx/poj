//3267

#include<iostream>
#include<string>
using namespace std;

int min(int a,int b)
{
	return a<b?a:b;
}

int main(int i,int j)
{
	int w,L;
	while(cin>>w>>L)
	{
		/*Read In*/

		int* dp=new int[L+1];
		char* mesg=new char[L];
		string* dict=new string[w];

		cin>>mesg;
		for(i=0;i<w;i++)
			cin>>dict[i];

	    /*Initial*/

		dp[L]=0;       //dp[i]表示从i到L所删除的字符数

		/*Dp-Enum*/

		for(i=L-1;i>=0;i--)  //从message尾部开始向前检索
		{
			dp[i]=dp[i+1]+1;  //字典单词和message无法匹配时，删除的字符数（最坏的情况）
			for(j=0;j<w;j++) //对字典单词枚举
			{
				int len=dict[j].length();
				if(len<=L-i && dict[j][0]==mesg[i])  //单词长度小于等于当前待匹配message长度
				{                                    //且单词头字母与信息第i个字母相同
					int pm=i;  //message的指针
					int pd=0;  //单词的指针
					while(pm<L) //单词逐字匹配
					{
						if(dict[j][pd]==mesg[pm++])
							pd++;
						if(pd==len)
						{     //字典单词和message可以匹配时，状态优化（更新）
							dp[i]=min(dp[i],dp[pm]+(pm-i)-len);//dp[pm]表示从pm到L删除的字符数
							break;                            //(pm-i)-pd表示从i到pm删除的字符数
						}                                     //则dp[pm]+(pm-i)-pd表示从i到L删除的字符数
					}
				}
			}
		}
		cout<<dp[0]<<endl;

		delete dp,mesg,dict;
	}
	return 0;
}