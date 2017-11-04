//1936

#include<iostream>
#include<string>
using namespace std;

int main(long i,long j)
{
	char s1[100000],s2[100000];
	while(cin>>s1>>s2)
	{
		long len1=strlen(s1);
		long len2=strlen(s2);
		i=0;
		j=0;
		while(true)
		{
			if(i==len1)
			{
				cout<<"Yes"<<endl;
				break;
			}
			else if(i<len1 && j==len2)
			{
				cout<<"No"<<endl;
				break;
			}
			if(s1[i]==s2[j])
			{
				i++;
				j++;
			}
			else
				j++;
		}
		memset(s1,'\0',sizeof(s1));
		memset(s2,'\0',sizeof(s2));
	}
	return 0;
}