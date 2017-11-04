//3295 

#include<iostream>
using namespace std;

int pp,qq,rr,ss,tt;  //各个逻辑变量的值

typedef class STACK
{
	public:
		int value;
		class STACK* next;
		STACK()
		{
			next=0;
		}
}Stack;

typedef class Top
{
    public:
		Stack* top;
		Top()
		{
			top=0;
		}
}linkstack;

void Insert(linkstack* s,int e);  //入栈
int Pop(linkstack* s);  //栈顶值出栈
void Empty(linkstack* s);  //清空栈

bool isvariables(linkstack* s,char ch);  //判断ch是否为变量p q r s t，若是则把其当前值入栈
void operators(linkstack* s,char op);   //根据操作符op对栈执行操作
int K(int x,int y);  //and: x&&y
int A(int x,int y);  //or : x||y
int C(int x,int y);  //implies: (!x)||y
int E(int x,int y);  //equals: x==y
int N(int x);  //not: !x

int main(void)
{
	linkstack* s=new linkstack[sizeof(linkstack)];

	char WFF[110];
	while(cin>>WFF && WFF[0]!='0')
	{
		int len=strlen(WFF);  //逻辑表达式的长度

		bool flag=true;  //标记逻辑表达式是否为永真式
		for(pp=0;pp<=1;pp++)  //枚举逻辑变量的值
		{
			for(qq=0;qq<=1;qq++)
			{
				for(rr=0;rr<=1;rr++)
				{
					for(ss=0;ss<=1;ss++)
					{
						for(tt=0;tt<=1;tt++)
						{
							for(int pw=len-1;pw>=0;pw--)
							{
								if(!isvariables(s,WFF[pw]))
									operators(s,WFF[pw]);
							}

							int ans=s->top->value;   //最后栈剩一个值，即为逻辑表达式的值
							if(!ans)  //只要表达式有一个值为假，它就不是永真式
							{
								flag=false;
								break;
							}
							Empty(s);
						}
						if(!flag)
							break;
					}
					if(!flag)
						break;
				}
				if(!flag)
					break;
			}
			if(!flag)
				break;
		}
		if(flag)
			cout<<"tautology"<<endl;
		else
			cout<<"not"<<endl;
	}
	return 0;
}

void Insert(linkstack* s,int e)
{
	Stack* node=new Stack[sizeof(Stack)];
	node->value=e;
	node->next=s->top;
	s->top=node;

	return;
}

int Pop(linkstack* s)
{
	int e=s->top->value;
	Stack* temp=s->top;
	s->top=s->top->next;
	delete temp;

	return e;
}

void Empty(linkstack* s)
{
	while(s->top)
	{
		Stack* temp=s->top;
		s->top=s->top->next;
		delete temp;
	}
	return;
}

bool isvariables(linkstack* s,char ch)
{
	switch(ch)
	{
	    case 'p':Insert(s,pp);return true;
		case 'q':Insert(s,qq);return true;
		case 'r':Insert(s,rr);return true;
		case 's':Insert(s,ss);return true;
		case 't':Insert(s,tt);return true;
	}
	return false;
}

void operators(linkstack* s,char op)
{
	switch(op)
	{
	    case 'K':
			{
				int x=Pop(s);
				int y=Pop(s);
				Insert(s,K(x,y));
				break;
			}
		case 'A':
			{
				int x=Pop(s);
				int y=Pop(s);
				Insert(s,A(x,y));
				break;
			}
		case 'C':
			{
				int x=Pop(s);
				int y=Pop(s);
				Insert(s,C(x,y));
				break;
			}
		case 'E':
			{
				int x=Pop(s);
				int y=Pop(s);
				Insert(s,E(x,y));
				break;
			}
		case 'N':
			{
				int x=Pop(s);
				Insert(s,N(x));
				break;
			}
	}
	return;
}

int K(int x,int y)
{
	return x&&y;
}

int A(int x,int y)
{
	return x||y;
}

int C(int x,int y)
{
	return (!x)||y;
}

int E(int x,int y)
{
	return x==y;
}

int N(int x)
{
	return !x;
}
