//Memory Time 
//248K   16MS 

#include<iostream>
#include<string.h>
using namespace std;

const int len=60;

int main(int i,int j)
{
	int test;
	cin>>test;
	for(int t=1;t<=test;t++)
	{
		int n;  //DNA个数
		cin>>n;
		char** DNA=new char*[n];
		for(int p=0;p<n;p++)
		{
			DNA[p]=new char[len+1];
			cin>>DNA[p];
		}

		char obj[len+1];  //所有DNA的公共串
		int StrLen=0;    //最长公共串长度
		int length=1;    //当前枚举的公共串长度

		for(i=0;;i++)  //枚举公共串dna[]
		{
			/*截取DNA[0][]中以pi为起点，长度为length的子串dna[]*/
			char dna[len+1];
			int pi=i;
			if(pi+length>len)
			{
				length++;
				i=-1;
				if(length>len)
					break;
				continue;
			}
			for(j=0;j<length;j++)
				dna[j]=DNA[0][pi++];
			dna[j]='\0';

			/*检查其他DNA[][]是否都存在字符串dna[]*/
			bool flag=true;
			for(int k=1;k<n;k++)
				if(!strstr(DNA[k],dna))  //存在一个DNA不含有dna[]
				{
					flag=false;
					break;
				}

			/*确认最大公共串*/
			if(flag)
			{
				if(StrLen<length)
				{
					StrLen=length;
					strcpy(obj,dna);	
				}
				else if(StrLen==length)
				{
					if(strcmp(obj,dna)>0)  //存在相同长度的公共串时，取最小字典序的串
						strcpy(obj,dna);
				}
			}
		}

		if(StrLen<3)
			cout<<"no significant commonalities"<<endl;
		else
			cout<<obj<<endl;

		delete DNA;
	}
	return 0;
}