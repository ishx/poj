//3007

#include<iostream>
using namespace std;

const int size=80;
const int mod=99991;
int count;  //计数器

typedef struct HASH
{
	char s[size];
	struct HASH* next;
	HASH()
	{
		next=0;  //0<=>NULL
	}
}Hashtable;

Hashtable* Hash[mod];   //hash[]是指针数组，存放地址

void hash(char* s);
void StrCopy(char* s1,char* s2);  //把s2复制到s1，要确保s1.len>s2.len
void StrCut(char* s,char* s1,char* s2,int k,int slen);  //把s前k个字符(0~k-1)复制到s1，第k到slen的字符复制到s2
void StrInvert(char* s1,char* s2,int len);  //把s1逆序存放到s2
char* StrCat(char* s1,char* s2,char* str);  //把s2连接到s1后，存放到s

int main(void)
{
	int n;
	cin>>n;
	while(n--)
	{
		char train[size];
		cin>>train;
		int len=strlen(train);
		if(len==1)
		{
			cout<<1<<endl;
			continue;
		}

		memset(Hash,0,sizeof(Hash));   //0 <-> NULL
		count=0;

		for(int i=1;i<=len-1;i++)   //i为火车分开的两部分中，前一部分的节数
		{
			char s1[size],s2[size];
			char s3[size],s4[size];  //s3为s1的逆序，s4为s2的逆序
			char str[size];

			StrCut(train,s1,s2,i,len);
			StrInvert(s1,s3,i);
			StrInvert(s2,s4,len-i);

			/*标记组合方式*/

			hash(train);  //s1与s2组合就是原来的train
			StrCat(s2,s1,str);
			hash(str);
			StrCat(s1,s4,str);
			hash(str);
			StrCat(s4,s1,str);
			hash(str);
			StrCat(s3,s2,str);
			hash(str);
			StrCat(s2,s3,str);
			hash(str);
			StrCat(s3,s4,str);
			hash(str);
			StrCat(s4,s3,str);
			hash(str);
		}

		cout<<count<<endl;
	}
	return 0;
}


void hash(char* s)
{
	char* ps=s;

	int key=0;
	for(int i=1;*ps;i++)
		key+=*(ps++)*i;
	key%=mod;

	if(!Hash[key])  //新key
	{
		Hashtable* pn=new Hashtable;  //由于要存放数据，必须申请空间
		                              //Hashtable* pn;只是单纯申请一个地址空间
		StrCopy(pn->s,s);
		Hash[key]=pn;

		count++;
	}
	else  //key值冲突
	{
		Hashtable* pn=Hash[key];  //pn指向冲突位置的链表开头

		if(!strcmp(pn->s,s))
			return;  //不计数返回
		else
		{
			while(pn->next)
			{
				if(!strcmp(pn->next->s,s))  //地址冲突且字符串相同
					return;

				pn=pn->next;
			}
			
			//地址冲突但字符串不同
			
			Hashtable* temp=new Hashtable;
			StrCopy(temp->s,s);
			pn->next=temp;  //记录新字符串

			count++;
		}
	}
	return;
}

void StrCopy(char* s1,char* s2)  //把s2复制到s1
{
	char* ps1=s1;
	char* ps2=s2;
	while(*ps2)
		*(ps1++)=*(ps2++);
	*ps1='\0';

	return;
}

void StrCut(char* s,char* s1,char* s2,int k,int slen)  //把s前k个字符(0~k-1)复制到s1，第k到slen的字符复制到s2
{
	int i,ps1=0,ps2=0;

	for(i=0;i<k;i++)
		s1[ps1++]=s[i];
	s1[ps1]='\0';

	for(;i<slen;i++)
		s2[ps2++]=s[i];
	s2[ps2]='\0';

	return;
}

void StrInvert(char* s1,char* s2,int len)  //把s1逆序存放到s2
{
	int ps=0;
	s2[len]='\0';
	for(int i=len-1;i>=0;i--)
		s2[i]=s1[ps++];
	
	return;
}

char* StrCat(char* s1,char* s2,char* str)  //把s2连接到s1后，存放到s
{
	int i,ps=0;
	for(i=0;s1[i]!='\0';i++)
		str[ps++]=s1[i];
	for(i=0;s2[i]!='\0';i++)
		str[ps++]=s2[i];
	str[ps]='\0';

	return str;
}