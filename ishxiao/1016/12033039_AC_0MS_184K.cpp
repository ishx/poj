//Memory Time 
//232K   32MS 

#include<iostream>
#include<string>
using namespace std;

/*压缩数字串n，存放到t*/
void R(char* n,char* t)
{
	int i,j;
	int time[10]={0};  //记录n中各个数字出现的次数
	for(i=0;n[i];i++)
		time[ n[i]-'0' ]++;

	for(i=0,j=0;i<10;i++)
	{
		if(time[i])
		{
			if(time[i]<10)  //数字i出现次数<10，即占1位
			{
				t[j++]=time[i]+'0';
				t[j++]=i+'0';
			}
			else    //数字i出现次数>=10，即占2位
			{
				t[j++]=time[i]/10+'0';
				t[j++]=time[i]%10+'0';
				t[j++]=i+'0';
			}
		}
	}
	t[j]='\0';

	return;
}

int main(int i,int j)
{
	char n[16][85];    //n[0]为原串，n[1~15]分别为n连续压缩15次的数字串

	while(cin>>n[0] && n[0][0]!='-')
	{
		bool flag1=false;    //属性1，n is self-inventorying
		int flag2=0;         //属性2，n is self-inventorying after j steps，顺便记录j
		int flag3=0;         //属性3，n is enters an inventory loop of length k，顺便记录k

		for(i=1;i<=15;i++)
			R(n[i-1],n[i]);

		if(!strcmp(n[0],n[1]))  //属性1，n压缩1次就是其本身
			flag1=true;

		if(!flag1)
		{
			for(j=1;j<15;j++)
				if(!strcmp(n[j],n[j+1]))  //属性2, n压缩j次后的数字串n[j]具有属性1
				{
					flag2=j;
					break;
				}

			if(!flag2)
			{
				for(j=1;j<=15;j++)  //属性3，两两枚举各次压缩的数字串，注意循环间隔>=2
				{
					for(i=0;i<=j-2;i++)
					{
						if(!strcmp(n[j],n[i]))
						{
							flag3=j-i;
							break;
						}
					}
					if(flag3)
						break;
				}
			}
		}

		if(flag1)
			cout<<n[0]<<" is self-inventorying"<<endl;
		else if(flag2)
			cout<<n[0]<<" is self-inventorying after "<<flag2<<" steps"<<endl;
		else if(flag3)
			cout<<n[0]<<" enters an inventory loop of length "<<flag3<<endl;
		else
			cout<<n[0]<<" can not be classified after 15 iterations"<<endl;
	}
	return 0;
}