//3414

#include<iostream>
#include<string>
#include<sstream>
#include<map>
using namespace std;

int v1,v2;  //两个瓶子的容量
int c;      //目标残余水量

int k1,k2;  //在某状态时两个瓶子的剩余水量,temporary

typedef class
{
	public:
		int x,y; //当前状态(两个瓶子中的水量)
		int pos;  //记录前一状态在队列queue中的下标
		int step;  //当前步数
}process;

//把整数a、b整合为 "a,b"  的字符串形式(不包括引号)，用于标记状态
string combAB(int a,int b)
{
	string s;
	ostringstream oss;

	oss<<a;
	oss<<',';
	oss<<b;

	s=oss.str();
	oss.str("");  //清空oss对象内所存储的流

	return s;
}

void fill(int i)
{
	switch(i)
	{
	    case 1: {k1=v1; return;}
		case 2: {k2=v2; return;}
	}
}

void drop(int i)
{
	switch(i)
	{
	    case 1: {k1=0; return;}
		case 2: {k2=0; return;}
	}
}

void pour(int i,int j)
{
	switch(i)
	{
	    case 1:   //  v1 to v2
			{
				if(k1+k2<=v2)
				{
					k2=k1+k2;
					k1=0;
				}
				else
				{
					k1=k1+k2-v2;
					k2=v2;
				}
				return;
			}
		case 2:   //  v2 to v1
			{
				if(k1+k2<=v1)
				{
					k1=k1+k2;
					k2=0;
				}
				else
				{
					k2=k1+k2-v1;
					k1=v1;
				}
				return;
			}
	}
}

void BFS(void)
{
	int operation[1000]={0}; //当前步的操作: 1z0:清空z瓶子  2z0:装满z瓶子  3xy:从x瓶倒向y瓶

	map<string,bool>vist;
	vist["0,0"]=true;

	process queue[1000];  //状态队列
	int head,tail;
	queue[head=0].x=0;
	queue[tail=0].y=0;
	queue[tail++].step=0;

	string ts;  //temporary
	while(head<tail)
	{
		process p=queue[head];

		if(p.x==c || p.y==c)   //得到要求的剩余水量c
		{
			cout<<p.step<<endl;

			/*下标回溯，输出操作过程*/

			int ps=p.step;
			int* steps=new int[ps+1];  //从1到p.step顺序记录各步操作的下标，不使用steps[0]

			steps[ps--]=tail-1;
			while(ps)
			{
				steps[ps]=queue[ steps[ps+1] ].pos;
				ps--;
			}

			for(int i=1;i<=p.step;i++)
			{
				int temp=operation[ steps[i]-1 ];  //注意各个数组间的下标关系

				switch(temp/100)
				{
				    case 1:
						{
							cout<<"DROP("<<(temp/10)%10<<')'<<endl;
							break;
						}
					case 2:
						{
							cout<<"FILL("<<(temp/10)%10<<')'<<endl;
							break;
						}
					case 3:
						{
							cout<<"POUR("<<(temp/10)%10<<','<<temp%10<<')'<<endl;
							break;
						}
				}
			}

			delete steps;

			return;
		}

		/*装满v1*/

		k1=p.x;
		k2=p.y;
		fill(1);
		ts=combAB(k1,k2);
		if(!vist[ts])
		{
			vist[ts]=true;
			queue[tail].x=k1;
			queue[tail].y=k2;
			queue[tail].step=p.step+1;  //当前的操作步数
			queue[tail].pos=head;      //前一步操作在queue[]中的下标
			operation[tail++]=210;     //当前的操作
		}

		/*装满v2*/

		k1=p.x;
		k2=p.y;
		fill(2);
		ts=combAB(k1,k2);
		if(!vist[ts])
		{
			vist[ts]=true;
			queue[tail].x=k1;
			queue[tail].y=k2;
			queue[tail].step=p.step+1;
			queue[tail].pos=head;
			operation[tail++]=220;
		}

		/*清空v1*/

		k1=p.x;
		k2=p.y;
		drop(1);
		ts=combAB(k1,k2);
		if(!vist[ts])
		{
			vist[ts]=true;
			queue[tail].x=k1;
			queue[tail].y=k2;
			queue[tail].step=p.step+1;
			queue[tail].pos=head;
			operation[tail++]=110;
		}

		/*清空v2*/

		k1=p.x;
		k2=p.y;
		drop(2);
		ts=combAB(k1,k2);
		if(!vist[ts])
		{
			vist[ts]=true;
			queue[tail].x=k1;
			queue[tail].y=k2;
			queue[tail].step=p.step+1;
			queue[tail].pos=head;
			operation[tail++]=120;
		}

		/*v1倒向v2*/

		k1=p.x;
		k2=p.y;
		pour(1,2);
		ts=combAB(k1,k2);
		if(!vist[ts])
		{
			vist[ts]=true;
			queue[tail].x=k1;
			queue[tail].y=k2;
			queue[tail].step=p.step+1;
			queue[tail].pos=head;
			operation[tail++]=312;
		}

		/*v2倒向v1*/

		k1=p.x;
		k2=p.y;
		pour(2,1);
		ts=combAB(k1,k2);
		if(!vist[ts])
		{
			vist[ts]=true;
			queue[tail].x=k1;
			queue[tail].y=k2;
			queue[tail].step=p.step+1;
			queue[tail].pos=head;
			operation[tail++]=321;
		}

		head++;
	}

	cout<<"impossible"<<endl;
	return;
}

int main(void)
{
	while(cin>>v1>>v2>>c)
		BFS();
	return 0;
}