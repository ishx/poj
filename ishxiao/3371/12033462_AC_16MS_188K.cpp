//3371 

#include<iostream>
#include<iomanip>
using namespace std;

int word=0;     //单词数
int sentance=0; //句子数
int syllable=0; //音标数

bool isalpha(char ch)  //检查字符ch是否为字母
{
	if(ch>='A' && ch <='Z')
		return true;
	if(ch>='a' && ch <='z')
		return true;
	return false;
}

bool isvowel(char ch)  //检查字符ch是否为元音字母
{
	if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='y')
		return true;
	if(ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' || ch=='Y')
		return true;
	return false;
}

bool isword(char ch)  //检查字符ch是否为单词分隔符
{
	if(ch==',')
		return true;
	return false;
}

bool issentance(char ch)  //检查字符ch是否为句子分隔符
{
	if(ch=='.' || ch=='?'  || ch==':' || ch==';' || ch=='!')
		return true;
	return false;
}

int main(void)
{
	char msg[1000];

	while(cin>>msg)   //以空格为标记，截取文章片段
	{	
		int wordlen=0;
		bool flag_frevowel=false;   //当当前字符为元音时，检查前一字符是否为元音的标记
		int syl=0;  //假设当前单词长度>3时，记录音节数的变化量。若单词实际长度<=3，则syllable-syl
		int i;

		for(i=0;msg[i];i++)
		{
			if(isalpha(msg[i]))   //当前字符为 字母
			{
				wordlen++;  //当前所处理的单词的已知长度 (已知长度<=实际长度)

				if(wordlen<=3)  //当 已知长度<=3 时
				{
					if(!isalpha(msg[i+1]))   //检查单词实际长度是否<=3
					{
						syllable++;     //当实际长度<=3时，syllable无条件+1
						syllable-=syl;   //实际音节数调整，单词实际长度<=3，则syllable减去 "假设单词长度>3时" 音节数的变化量syl
						syl=0;
						continue;
					}
				}

				if(isvowel(msg[i]))    //当前字母为 元音字母
				{
					if(msg[i]=='e')
					{
						if(!isalpha(msg[i+1]) && msg[i-1]=='l')  //-le
						{
							syllable++;
							syl++;      //由于不知道单词的实际长度，因此总音节数syllable与音节数变化量syl同时递增
							continue;
						}
						else if(!isalpha(msg[i+1]))  // -e
							continue;
						else if((msg[i+1]=='d' || msg[i+1]=='s') && !isalpha(msg[i+2]))  // -ed  -es
							continue;
					}

					/*处理连续或单个元音*/

					if(!flag_frevowel)   //当前字母为元音，但前一字符不是元音
					{
						flag_frevowel=true;
						syllable++;
						syl++;
						continue;
					}
					else     //当前字母为元音，但前一字母也是元音，即出现连续元音，syllable不计数
						continue;
				}

				flag_frevowel=false;   //当前字母不是元音
			}
			else if(isword(msg[i]))   //当前字符为 单词分隔符
			{
				flag_frevowel=false;
				wordlen=0;  //当前单词操作已结束，长度清零，计算下一单词
				syl=0;
				word++;
			}
			else if(issentance(msg[i]))   //当前字符为 句子分隔符
			{
				flag_frevowel=false;
				wordlen=0;  //当前单词操作已结束，长度清零，计算下一单词
				word++;
				syl=0;
				sentance++;
			}

		}

		if(isalpha(msg[i-1]))     //当前文章片段最后一个字符为 字母
			word++;
	}

	cout<<fixed<<setprecision(2)<<206.835-1.015*(double)word/(double)sentance-84.6*(double)syllable/(double)word<<endl;
	return 0;
}