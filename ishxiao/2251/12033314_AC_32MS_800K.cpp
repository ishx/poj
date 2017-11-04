//2251 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int l,r,c;
		int depth;  //树深（分钟）
}SE;

SE s,e;
bool maze[40][40][40];
int shortminute;

bool BFS(int k,int i,int j)
{
	bool vist[40][40][40]={false};

	SE queue[30000];
	int head,tail;
	queue[head=0].l=k;
	queue[tail=0].r=i;
	queue[0].c=j;
	queue[tail++].depth=1;

	vist[k][i][j]=true;

	while(head<tail)
	{
		SE x=queue[head++];

		if(x.l==e.l && x.r==e.r && x.c==e.c)
		{
			shortminute=x.depth;
			return true;
		}

		if(maze[x.l][x.r][x.c-1] && !vist[x.l][x.r][x.c-1])  //West
		{
			vist[x.l][x.r][x.c-1]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r;
			queue[tail].c=x.c-1;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l][x.r-1][x.c] && !vist[x.l][x.r-1][x.c])  //North
		{
			vist[x.l][x.r-1][x.c]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r-1;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l][x.r][x.c+1] && !vist[x.l][x.r][x.c+1])  //East
		{
			vist[x.l][x.r][x.c+1]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r;
			queue[tail].c=x.c+1;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l][x.r+1][x.c] && !vist[x.l][x.r+1][x.c])  //South
		{
			vist[x.l][x.r+1][x.c]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r+1;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l-1][x.r][x.c] && !vist[x.l-1][x.r][x.c])  //Up
		{
			vist[x.l-1][x.r][x.c]=true;
			queue[tail].l=x.l-1;
			queue[tail].r=x.r;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l+1][x.r][x.c] && !vist[x.l+1][x.r][x.c])  //Down
		{
			vist[x.l+1][x.r][x.c]=true;
			queue[tail].l=x.l+1;
			queue[tail].r=x.r;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
	}
	return false;
}

int main(int i,int j,int k)
{
	int L,R,C;
	while(cin>>L>>R>>C)
	{
		if(!L && !R && !C)
			break;

		/*Initial*/

		memset(maze,false,sizeof(maze));
		
		/*Structure the Maze*/

		for(k=1;k<=L;k++)
			for(i=1;i<=R;i++)
				for(j=1;j<=C;j++)
				{
					char temp;
					cin>>temp;
					if(temp=='.')
						maze[k][i][j]=true;
					if(temp=='S')
					{
						maze[k][i][j]=true;
						s.l=k;
						s.r=i;
						s.c=j;
					}
					if(temp=='E')
					{
						maze[k][i][j]=true;
						e.l=k;
						e.r=i;
						e.c=j;
					}
				}

		/*Search the min Minute*/

		if(BFS(s.l,s.r,s.c))
			cout<<"Escaped in "<<shortminute-1<<" minute(s)."<<endl;
		else
			cout<<"Trapped!"<<endl;

	}
	return 0;
}