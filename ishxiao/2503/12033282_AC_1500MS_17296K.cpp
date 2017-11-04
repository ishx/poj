//2503 

#include<iostream>
#include<string>
#include<map>
using namespace std;

int main(void)
{
	char english[11],foreign[11];

	map<string,bool>appear;  //记录foreign与engliash的配对映射是否出现
	map<string,string>translate; //记录foreign到engliash的映射

	/*Input the dictionary*/

	while(true)
	{
		char t;  //temporary

		if((t=getchar())=='\n')  //判定是否输入了空行
			break;
		else     //输入english
		{
			english[0]=t;
			int i=1;
			while(true)
			{
				t=getchar();
				if(t==' ')
				{
					english[i]='\0';
					break;
				}
				else
					english[i++]=t;
			}
		}
		
		cin>>foreign;
		getchar();  //吃掉 输入foreign后的 回车符

		appear[foreign]=true;
		translate[foreign]=english;
	}

	/*Translate*/

	char word[11];
	while(cin>>word)
	{
		if(appear[word])
			cout<<translate[word]<<endl;
		else
			cout<<"eh"<<endl;
	}
	
	return 0;
}