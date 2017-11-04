/*STL<map>标记*/

//3096

#include<iostream>
#include<string>
#include<map>
using namespace std;

int main(void)
{
	char s[80];
	while(cin>>s && s[0]!='*')
	{
		int len=strlen(s);
		if(len<=2)  //长度小于等于2的串必定是surprising String
		{
			cout<<s<<" is surprising."<<endl;
			continue;
		}

		bool mark=true;  //标记s是否为Surprising String
		for(int d=0;d<=len-2;d++)  //d为当前所选取的两个字母之间的距离，d(max)=len-2
		{
			map<string,bool>flag;

			bool sign=true;  //标记D-pairs字母对是不是D-unique
			for(int i=0;i<=len-d-2;i++)  //i为所选取的两个字母中第一个字母的下标
			{
				char pair[3]={s[i],s[i+d+1],'\0'};  //构成D-pairs字母对
				
				if(!flag[ pair ])
					flag[ pair ]=true;
				else
				{
					sign=false;  //存在相同的D-pairs,该字母对不是D-unique
					break;
				}
			}
			if(!sign)
			{
				mark=false;  //存在非D-unique，s不是Surprising String
				break;
			}
		}
		if(mark)
			cout<<s<<" is surprising."<<endl;
		else
			cout<<s<<" is NOT surprising."<<endl;
	}
	return 0;
}