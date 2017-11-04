//3083 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int r,c;
		int depth;
}SE;

SE s,e; //起止点
int Lstep;  //左边优先搜索 时从S到E的总步数
int Rstep;  //右边优先搜索 时从S到E的总步数
int shortstep;  //S到E的最少总步数

bool maze[41][41]; //记录迷宫的“可行域”与“墙”

void DFS_LF(int i,int j,int d)    //左边优先搜索，i,j为当前点坐标，d为当前位置方向
{
	Lstep++;
	if(i==e.r && j==e.c)
		return;

	switch(d)
	{
	    case 0:
			{
				if(maze[i][j-1])
					DFS_LF(i,j-1,1);
				else if(maze[i-1][j])
					DFS_LF(i-1,j,0);
				else if(maze[i][j+1])
					DFS_LF(i,j+1,3);
				else if(maze[i+1][j])
					DFS_LF(i+1,j,2);
				break;
			}
		case 1:
			{
				if(maze[i+1][j])
					DFS_LF(i+1,j,2);
				else if(maze[i][j-1])
					DFS_LF(i,j-1,1);
				else if(maze[i-1][j])
					DFS_LF(i-1,j,0);
				else if(maze[i][j+1])
					DFS_LF(i,j+1,3);
				break;
			}
		case 2:
			{
				if(maze[i][j+1])
					DFS_LF(i,j+1,3);
				else if(maze[i+1][j])
					DFS_LF(i+1,j,2);
				else if(maze[i][j-1])
					DFS_LF(i,j-1,1);
				else if(maze[i-1][j])
					DFS_LF(i-1,j,0);
				break;
			}
		case 3:
			{
				if(maze[i-1][j])
					DFS_LF(i-1,j,0);
				else if(maze[i][j+1])
					DFS_LF(i,j+1,3);
				else if(maze[i+1][j])
					DFS_LF(i+1,j,2);
				else if(maze[i][j-1])
					DFS_LF(i,j-1,1);
				break;
			}
	}

	return;
}

void DFS_RF(int i,int j,int d)    //右边优先搜索，i,j为当前点坐标，d为当前位置方向
{
	Rstep++;
	if(i==e.r && j==e.c)
		return;

	switch(d)
	{
	    case 0:
			{
				if(maze[i][j+1])
					DFS_RF(i,j+1,3);
				else if(maze[i-1][j])
					DFS_RF(i-1,j,0);
				else if(maze[i][j-1])
					DFS_RF(i,j-1,1);
				else if(maze[i+1][j])
					DFS_RF(i+1,j,2);
				break;
			}
		case 1:
			{
				if(maze[i-1][j])
					DFS_RF(i-1,j,0);
				else if(maze[i][j-1])
					DFS_RF(i,j-1,1);
				else if(maze[i+1][j])
					DFS_RF(i+1,j,2);
				else if(maze[i][j+1])
					DFS_RF(i,j+1,3);
				break;
			}
		case 2:
			{
				if(maze[i][j-1])
					DFS_RF(i,j-1,1);
				else if(maze[i+1][j])
					DFS_RF(i+1,j,2);
				else if(maze[i][j+1])
					DFS_RF(i,j+1,3);
				else if(maze[i-1][j])
					DFS_RF(i-1,j,0);
				break;
			}
		case 3:
			{
				if(maze[i+1][j])
					DFS_RF(i+1,j,2);
				else if(maze[i][j+1])
					DFS_RF(i,j+1,3);
				else if(maze[i-1][j])
					DFS_RF(i-1,j,0);
				else if(maze[i][j-1])
					DFS_RF(i,j-1,1);
				break;
			}
	}
	return;
}

void BFS_MSS(int i,int j)    //最短路搜索
{
	bool vist[41][41]={false};
	SE queue[1600];
	int head,tail;

	queue[head=0].r=i;
	queue[tail=0].c=j;
	queue[tail++].depth=1;  //当前树深标记，这是寻找最短路的关键点

	vist[i][j]=true;

	while(head<tail)
	{
		SE x=queue[head++];

		if(x.r==e.r && x.c==e.c)
		{
			cout<<x.depth<<endl;
			return;
		}

		if(maze[x.r][x.c-1] && !vist[x.r][x.c-1])
		{
			vist[x.r][x.c-1]=true;
			queue[tail].r=x.r;
			queue[tail].c=x.c-1;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.r-1][x.c] && !vist[x.r-1][x.c])
		{
			vist[x.r-1][x.c]=true;
			queue[tail].r=x.r-1;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.r][x.c+1] && !vist[x.r][x.c+1])
		{
			vist[x.r][x.c+1]=true;
			queue[tail].r=x.r;
			queue[tail].c=x.c+1;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.r+1][x.c] && !vist[x.r+1][x.c])
		{
			vist[x.r+1][x.c]=true;
			queue[tail].r=x.r+1;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
	}
	return;
}

int main(int i,int j)
{
	int test;
	cin>>test;
	while(test--)
	{
		int direction;  //起点S的初始方向
		int w,h;  //size of maze
		cin>>w>>h;

		/*Initial*/

		Lstep=1;
		Rstep=1;
		memset(maze,false,sizeof(maze));

		/*Structure the Maze*/

		for(i=1;i<=h;i++)
			for(j=1;j<=w;j++)
			{
				char temp;
				cin>>temp;
				if(temp=='.')
					maze[i][j]=true;
				if(temp=='S')
				{
					maze[i][j]=true;
					s.r=i;
					s.c=j;

					if(i==h)
						direction=0;
					else if(j==w)
						direction=1;
					else if(i==1)
						direction=2;
					else if(j==1)
						direction=3;
				}
				if(temp=='E')
				{
					maze[i][j]=true;
					e.r=i;
					e.c=j;
				}
			}

		/*Left First Search*/

		switch(direction)
		{
		    case 0: {DFS_LF(s.r-1,s.c,0); break;}
			case 1: {DFS_LF(s.r,s.c-1,1); break;}
			case 2: {DFS_LF(s.r+1,s.c,2); break;}
			case 3: {DFS_LF(s.r,s.c+1,3); break;}
		}
		cout<<Lstep<<' ';

		/*Right First Search*/

		switch(direction)
		{
		    case 0: {DFS_RF(s.r-1,s.c,0); break;}
			case 1: {DFS_RF(s.r,s.c-1,1); break;}
			case 2: {DFS_RF(s.r+1,s.c,2); break;}
			case 3: {DFS_RF(s.r,s.c+1,3); break;}
		}
		cout<<Rstep<<' ';

		/*Most Short Step Search*/

		BFS_MSS(s.r,s.c);
		
	}
	return 0;
}