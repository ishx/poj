//Memory   Time 
//188K      16MS 

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(void)
{
	int i;
	int cipher[26],clear[26];
	memset(cipher,0,sizeof(cipher));       //对长度为sizeof(cipher)=int*26=104的连续内存空间cipher全部元素初始化为0
	memset(clear,0,sizeof(clear));
	string input;
	cin>>input;
	for(i=0;i<input.length();i++)
	{
		cipher[input[i]-'A']++;
	}
	cin>>input;
	for(i=0;i<input.length();i++)
	{
		clear[input[i]-'A']++;
	}
	sort(cipher,cipher+26);        // 标准库自带排序函数sort(ip_start,ip_end) 对某连续的地址段的对象内容进行升序快排（从小到大），<algorithm>
    sort(clear,clear+26);          //亦即sort(ip_start+m,ip_start+n)，其中为从ip_start+m开始（包括ip_start+m）对第n到第m个对象进行排序
	for(i=0;i<26;i++)
		if(cipher[i]!=clear[i])
		{
			cout<<"NO"<<endl;
			return 0;
		}
	cout<<"YES"<<endl;
	return 0;
}