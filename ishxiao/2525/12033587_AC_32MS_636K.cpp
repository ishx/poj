//2525 

#include<iostream>
#include<cmath>
using namespace std;

struct Trie_Node   //TrieTree结点
{
	int id;					//标记从Root到当前Node的字符串是否为单词
							//id为该单词录入TrieTree的顺序编号, id=0表示该单词不存在
	int len;				//单词长度
	Trie_Node* next[128];	//分支，规模为未扩展ASCII的字符数
};

class solve
{
public:
	solve(int c,int a):C(c),A(a)
	{
		id=0;
		Trie_Node* Root=new Trie_Node;		//构造TrieTree的根结点
		initial(Root);						//初始化根结点

		Expand=new char*[C*3+A+1];			//申请扩展串的空间
		for(int i=1;i<=C*3+A;i++)
			Expand[i]=new char[StrSize()];

		EntryWord(Root);					//录入每个串的扩展串(字典登记)
		ReadText(Root);						//扩展文章
	}
	~solve()
	{
		for(int i=1;i<=C*3+A;i++)
			delete[] Expand[i];
	}

	int StrSize(void) const{return 81;}		//字符串的长度尺寸
	char UppAlp(char c);					//c若为小写字母，返回其大写；若为其他字符，返回其本身

	void initial(Trie_Node* p);				//初始化TireTree的结点
	void EntryWord(Trie_Node* Root);		//录入每个串的扩展串(字典登记)，并把其id映射到扩展串数组Expand
	void ReadText(Trie_Node* Root);			//逐行读入Text，逐行扩展输出
	
protected:

	int C;			//Contraction数量
	int A;			//Acronym数量
	int id;			//录入TrieTree的单词的顺序编号
	int KeyId;		//顺序编号<=KeyId的单词为Contraction ，顺序编号>KeyId的单词为Acronym
	char** Expand;	//记录Contraction和Acronym的扩展串,用id作为映射
};

void solve::initial(Trie_Node* p)
{
	p->id=0;
	p->len=0;
	memset(p->next,0,sizeof(p->next));
	return;
}

void solve::EntryWord(Trie_Node* Root)  
{
	int i,j,k;		//temporary
	char tc;

	/*录入Contraction到Trieree，同时录入其3种形式*/

	for(i=1;i<=C;i++)
	{
		Trie_Node* p1=Root;		//at list
		Trie_Node* p3=Root;		//uppercased
		Trie_Node* p2=Root;		//capitalized
		bool flag1=false,flag2=false,flag3=false;	//优先级标记，已录入扩展串的id不会被覆盖

		char Tmps[200];
		gets(Tmps);

		for(j=1;Tmps[j]!='\"';j++)
		{
			//at list
			if(!p1->next[Tmps[j]])
			{
				p1->next[Tmps[j]]=new Trie_Node;
				initial(p1->next[Tmps[j]]);
			}
			p1->next[Tmps[j]]->len = p1->len+1;
			p1 = p1->next[Tmps[j]];

			//uppercased
			tc=UppAlp(Tmps[j]);
			if(!p2->next[tc])
			{
				p2->next[tc]=new Trie_Node;
				initial(p2->next[tc]);
			}
			p2->next[tc]->len = p2->len+1;
			p2 = p2->next[tc];

			//capitalized
			tc=(j==1?UppAlp(Tmps[j]):Tmps[j]);
			if(!p3->next[tc])
			{
				p3->next[tc]=new Trie_Node;
				initial(p3->next[tc]);
			}
			p3->next[tc]->len = p3->len+1;
			p3=p3->next[tc];
		}

		//录入编号，建立缩写与扩展形式的映射
		//由于优先原则，若id此前已登记到TrieTree，则以后均不登记
		if(p1->id)
			flag1=true;
		else
			p1->id=++id;	
		
		if(p2->id)
			flag2=true;
		else
			p2->id=++id;

		if(p3->id)
			flag3=true;
		else
			p3->id=++id;

		/*录入Contraction的扩展形式到Expand*/

		while(Tmps[++j]!='\"');		//跳过 "->" 部分
		k=j+1;
		for(j=0;Tmps[k]!='\"';k++,j++)
		{
			//at list
			if(!flag1)
				Expand[p1->id][j]=Tmps[k];

			//uppercased
			if(!flag2)
				Expand[p2->id][j]=UppAlp(Tmps[k]);

			//capitalized
			if(!flag3)
			{
				if(j==0)
					Expand[p3->id][j]=UppAlp(Tmps[k]);
				else
					Expand[p3->id][j]=Tmps[k];
			}
		}
		if(!flag1)
			Expand[p1->id][j]='\0';
		
		if(!flag2)
			Expand[p2->id][j]='\0';

		if(!flag3)
			Expand[p3->id][j]='\0';
	}

	/*录入Acronym到Trieree*/

	KeyId=id;		//分界点编号登记

	for(i=1;i<=A;i++)
	{
		Trie_Node* p=Root;
		bool flag=false;

		char Tmps[200];
		gets(Tmps);

		for(j=1;Tmps[j]!='\"';j++)
		{
			if(!p->next[Tmps[j]])
			{
				p->next[Tmps[j]]=new Trie_Node;
				initial(p->next[Tmps[j]]);
			}
			p->next[Tmps[j]]->len = p->len+1;
			p = p->next[Tmps[j]];
		}
		if(p->id)
			flag=true;
		else
			p->id=++id;

		/*录入Acronym的扩展形式到Expand*/
		
		if(!flag)
		{
			while(Tmps[++j]!='\"');
			k=j+1;
			for(j=0;Tmps[k]!='\"';k++,j++)
				Expand[p->id][j]=Tmps[k];

			//Acronym的扩展串要求在最后加上" (Acronym)"
			Expand[id][j++]=' ';
			Expand[id][j++]='(';

			for(k=1;Tmps[k]!='\"';k++)
				Expand[id][j++]=Tmps[k];

			Expand[id][j++]=')';
			Expand[id][j]='\0';
		}
	}
    return;
}

void solve::ReadText(Trie_Node* Root)
{
	int i,j,f;

	bool* FirstApp;		//标记Acronym是否已经扩展过一次
	FirstApp=new bool[id+1];
	for(f=KeyId+1;f<=id;f++)
		FirstApp[f]=false;

	char* line=new char[StrSize()];
	while(gets(line))	//逐行输入文章
	{
		for(i=0;line[i];i++)
		{
			/*文章结束符*/
			if(line[i]=='#' && line[i+1]!='#')
			{
				printf("#");
				for(f=KeyId+1;f<=id;f++)	//清空acronym首次出现的标记
					FirstApp[f]=false;

				break;
			}

			Trie_Node* p=Root;

			//以当前字符line[i]为首的单词没有登记到TrieTree，直接输出
			if(!p->next[ line[i] ])	
			{
				printf("%c",line[i]);
				continue;
			}

			//以当前字符line[i]为首的单词可能有登记到TrieTree，检查后续字符是否构成单词
			for(j=i;!p->id;j++)
			{
				if(p->next[line[j]])
					p=p->next[line[j]];
				else
					break;
			}
			if(p->id!=0)	
			{
				if(p->id <= KeyId)		//以字符line[i]为首的单词为Contraction
				{
					printf("%s",Expand[p->id]);
					i+=p->len-1;
				}
				else if(p->id>KeyId && !FirstApp[p->id])//以字符line[i]为首的单词为Acronym
				{										//且在当前Text从未被扩展过
					FirstApp[p->id]=true;
					printf("%s",Expand[p->id]);
					i+=p->len-1;
				}
				else if(p->id>KeyId && FirstApp[p->id])//以字符line[i]为首的单词为Acronym
				{										//且在当前Text已被扩展过，直接输出line[i]
					printf("%c",line[i]);
				}
			}
			else	//以字符line[i]为首的单词均未登记到TrieTree，直接输出line[i]
			{
				printf("%c",line[i]);
			}
		}
		printf("\n");	//文章Text每行换行
	}

	delete[] FirstApp;
	return;
}

char solve::UppAlp(char c)
{
	if(c<'a' || c>'z')
		return c;

	return c-32;
}

int main(void)  
{
	int c,a;
	scanf("%d %d",&c,&a);
	getchar();		//下次输入函数为gets()，则此处要吃掉回车符

	solve poj2525(c,a);

	return 0;
}