//Memory Time
//216K   32MS 

#include<iostream>
#include<string>
using namespace std;

const int size=1000;   //大数位数

void add(char* aa,char* bb,char* cc,char* ans)
{
	int a[size+1]={0};
	int b[size+1]={0};
	int c[size+1]={0};
	int pa=0,pb=0,pc=0;

	int lena=strlen(aa);
	int lenb=strlen(bb);
	int lenc=strlen(cc);

	/*倒序*/

	for(int i=lena-1;i>=0;i--)
		a[pa++]=aa[i]-'0';
	for(int j=lenb-1;j>=0;j--)
		b[pb++]=bb[j]-'0';
	for(int k=lenc-1;k>=0;k--)
		c[pc++]=cc[k]-'0';

	int len=lena>lenb?lena:lenb;
	len=len>lenc?len:lenc;
	char* d=new char[len+2];  //倒序的ans

	int w=0;  //低位到高位的进位
	for(int x=0;x<=len;x++)  //'='为了处理最高位的进位
	{
		int temp=a[x]+b[x]+c[x]+w;
		d[x]=temp%10+'0';
		w=temp/10;
	}

	bool flag=false;
	bool sign=false;  //标记ans是否为全0
	for(w=0;len>=0;len--)  //w和len均作指针使用，已无意义
	{
		if(!flag && d[len]=='0')   //删除数字开头的0
			continue;
		else
			flag=true;

		sign=true;
		ans[w++]=d[len];
	}
	if(sign)
		ans[w]='\0';
	else
	{
		ans[0]='0';
		ans[1]='\0';
	}

	delete d;
	return;
}

char a[size+1];
char b[size+1];
char c[size+1];
char ans[size+1];
int main(void)
{
	while(cin>>a>>b>>c)
	{
		for(int i=1;i<=25;i++)
		{
			add(a,b,c,ans);
			add(b,c,ans,a);
			add(c,ans,a,b);
			add(ans,a,b,c);
		}
		cout<<ans<<endl;   //循环25次后，ans刚好是第99个数的值
	}
	return 0;
}