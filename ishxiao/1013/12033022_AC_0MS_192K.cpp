//Memory Time 
//252K   0MS 

#include<iostream>
#include<cmath>
using namespace std;

int main(void)
{
	int cases;
	cin>>cases;
	for(int c=1;c<=cases;c++)
	{
		char left[3][6],right[3][6],status[3][6];

		int time['L'+1]={0};  //标记各个字母被怀疑的次数
		bool zero['L'+1]={false};  //标记绝对为真币的字母（令天枰平衡的所有字母）

		for(int k=0;k<3;k++)
			cin>>left[k]>>right[k]>>status[k];	

		for(int i=0;i<3;i++)
		{
			switch(status[i][0])  //检查天枰状态
			{
			    case 'u':     //up，天枰左重右轻
					{
						for(int j=0;left[i][j];j++)
						{
							time[ left[i][j] ]++;  //左重
							time[ right[i][j] ]--;  //右轻
						}
						break;
					}
				case 'd':     //down，天枰左轻右重
					{
						for(int j=0;left[i][j];j++)
						{
							time[ left[i][j] ]--;  //左轻
							time[ right[i][j] ]++;  //右重
						}
						break;
					}
				case 'e':     //down，天枰平衡
					{
						for(int j=0;left[i][j];j++)
						{
							zero[ left[i][j] ]=true;   //绝对真币
							zero[ right[i][j] ]=true;   //绝对真币
						}
						break;
					}
			}
		}

		int max=-1;  //查找被怀疑程度最高的硬币（假币）
		char alpha;
		for(int j='A';j<='L';j++)
		{
			if(zero[j])  //绝对真币
				continue;

			if(max<=abs(time[j]))
			{
				max=abs(time[j]);
				alpha=j;
			}
		}

		cout<<alpha<<" is the counterfeit coin and it is ";
		if(time[alpha]>0)
			cout<<"heavy."<<endl;
		else
			cout<<"light."<<endl;
	}
	return 0;
}