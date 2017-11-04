//2706

#include<iostream>
using namespace std;

const int size=23;
const int num=251;
int n;  //chess size
int m;  //move steps
int lastx,lasty;
int map[size][size];  //对坐标为(x,y)的棋子编号
bool link[num][num];  //标记某两个编号的棋子是否有连线

int posx[]={0,-1,-2,-2,-1,1,2,2,1};   //对应于(x,y)的八个方位
int posy[]={0,2,1,-1,-2,-2,-1,1,2};

typedef class chess
{
	public:
	int color;   //黑棋:1 白棋:0
	int r,c;
	int connet[8];  //记录与当前棋子直接相连的棋子编号
	int pc;  //connet的指针

	chess()
	{
		color=-1;
		pc=0;
	}
}PEG;

void LinePeg(PEG* peg,int i);  //把棋子peg[i]与与其相邻的八个方位的同色棋子连线
bool CheckWin(PEG* peg,bool flag);  //BFS,检查先手(黑棋)是否把终域连接在一起(赢家)

int main(void)
{
	while(cin>>n>>m)
	{
		if(!n && !m)
			break;

		memset(map,0,sizeof(map));
		memset(link,false,sizeof(link));
		PEG* peg=new PEG[m+1];
		
		for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			map[x][y]=i;  //编号记录
			peg[i].r=x;
			peg[i].c=y;

			if(i%2)
				peg[i].color=1;  //黑棋
			else
				peg[i].color=0;  //白棋

			if(i==m)  //记录最后一步棋
			{
				lastx=x;
				lasty=y;
			}

			LinePeg(peg,i);  //把最新下的棋子与其附近的同色棋子相连
		}
		if(CheckWin(peg,true) && !CheckWin(peg,false))
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;
	}
	return 0;
}

/*把棋子(x,y)与与其相邻的八个方位的同色棋子连线*/
void LinePeg(PEG* peg,int i)
{
	int color=peg[i].color;
	for(int k=1;k<=8;k++)
	{
		int r=peg[i].r+posx[k];
		int c=peg[i].c+posy[k];
		
		if(r>=0 && r<=n && c>=0 && c<=n)  //检查边界
		{
			if(map[r][c] && peg[ map[r][c] ].color==color)  //检查颜色
			{
				switch(k)  //"日"字对角连线
				{
				    case 1:  //30度方位
					{
						if(link[ map[r][c-2] ][ map[r+1][c] ])
							break;
						if(c-3>=0 && link[ map[r][c-3] ][ map[r+1][c-1] ])
							break;
						if(c+1<=n && link[ map[r][c-1] ][ map[r+1][c+1] ])
							break;
						if(r-1>=0)
						{
							if(link[ map[r-1][c-2] ][ map[r+1][c-1] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r+1][c] ])
								break;
							if(link[ map[r-1][c] ][ map[r+1][c-1] ])
								break;
						}
						if(r+2<=n)
						{
							if(link[ map[r+2][c-2] ][ map[r][c-1] ])
								break;
							if(link[ map[r+2][c-1] ][ map[r][c-2] ])
								break;
							if(link[ map[r+2][c] ][ map[r][c-1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 2:  //60度方位
					{
						if(link[ map[r][c-1] ][ map[r+2][c] ])
							break;
						if(r-1>=0 && link[ map[r-1][c-1] ][ map[r+1][c] ])
							break;
						if(r+3<=n && link[ map[r+1][c-1] ][ map[r+3][c] ])
							break;
						if(c-2>=0)
						{
							if(link[ map[r][c-2] ][ map[r+1][c] ])
								break;
							if(link[ map[r+1][c-2] ][ map[r+2][c] ])
								break;
							if(link[ map[r+2][c-2] ][ map[r+1][c] ])
								break;
						}
						if(c+1<=n)
						{
							if(link[ map[r][c-1] ][ map[r+1][c+1] ])
								break;
							if(link[ map[r+1][c-1] ][ map[r][c+1] ])
								break;
							if(link[ map[r+1][c-1] ][ map[r+2][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 3:  //120度方位
					{
						if(link[ map[r][c+1] ][ map[r+2][c] ])
							break;
						if(r-1>=0 && link[ map[r-1][c+1] ][ map[r+1][c] ])
							break;
						if(r+3<=n && link[ map[r+1][c+1] ][ map[r+3][c] ])
							break;
						if(c-1>=0)
						{
							if(link[ map[r][c-1] ][ map[r+1][c+1] ])
								break;
							if(link[ map[r+1][c-1] ][ map[r][c+1] ])
								break;
							if(link[ map[r+2][c-1] ][ map[r+1][c+1] ])
								break;
						}
						if(c+2<=n)
						{
							if(link[ map[r+1][c] ][ map[r][c+2] ])
								break;
							if(link[ map[r+2][c] ][ map[r+1][c+2] ])
								break;
							if(link[ map[r+1][c] ][ map[r+2][c+2] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 4:  //150度方位
					{
						if(link[ map[r][c+2] ][ map[r+1][c] ])
							break;
						if(c-1>=0 && link[ map[r+1][c-1] ][ map[r][c+1] ])
							break;
						if(c+3<=n && link[ map[r+1][c+1] ][ map[r][c+3] ])
							break;
						if(r-1>=0)
						{
							if(link[ map[r-1][c] ][ map[r+1][c+1] ])
								break;
							if(link[ map[r-1][c+1] ][ map[r+1][c] ])
								break;
							if(link[ map[r-1][c+2] ][ map[r+1][c+1] ])
								break;
						}
						if(r+2<=n)
						{
							if(link[ map[r][c+1] ][ map[r+2][c] ])
								break;
							if(link[ map[r][c+1] ][ map[r+2][c+2] ])
								break;
							if(link[ map[r][c+2] ][ map[r+2][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 5:  //210度方位
					{
						if(link[ map[r-1][c] ][ map[r][c+2] ])
							break;
						if(c-1>=0 && link[ map[r-1][c-1] ][ map[r][c+1] ])
							break;
						if(c+3<=n && link[ map[r-1][c+1] ][ map[r][c+3] ])
							break;
						if(r-2>=0)
						{
							if(link[ map[r-2][c] ][ map[r][c+1] ])
								break;
							if(link[ map[r-2][c+1] ][ map[r][c+2] ])
								break;
							if(link[ map[r-2][c+2] ][ map[r][c+1] ])
								break;
						}
						if(r+1<=n)
						{
							if(link[ map[r][c] ][ map[r-1][c+1] ])
								break;
							if(link[ map[r+1][c+1] ][ map[r-1][c] ])
								break;
							if(link[ map[r+1][c+2] ][ map[r-1][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 6:  //240度方位
					{
						if(link[ map[r-2][c] ][ map[r][c+1] ])
							break;
						if(r-3>=0 && link[ map[r-3][c] ][ map[r-1][c+1] ])
							break;
						if(r+1<=n && link[ map[r-1][c] ][ map[r+1][c+1] ])
							break;
						if(c-1>=0)
						{
							if(link[ map[r-2][c-1] ][ map[r-1][c+1] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r][c+1] ])
								break;
							if(link[ map[r][c-1] ][ map[r-1][c+1] ])
								break;
						}
						if(c+2<=n)
						{
							if(link[ map[r-1][c] ][ map[r-2][c+2] ])
								break;
							if(link[ map[r-2][c] ][ map[r-1][c+2] ])
								break;
							if(link[ map[r-1][c] ][ map[r][c+2] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 7:  //300度方位
					{
						if(link[ map[r-2][c] ][ map[r][c-1] ])
							break;
						if(r-3>=0 && link[ map[r-3][c] ][ map[r-1][c-1] ])
							break;
						if(r+1<=n && link[ map[r-1][c] ][ map[r+1][c-1] ])
							break;
						
						if(c-2>=0)
						{
							if(link[ map[r-2][c-2] ][ map[r-1][c] ])
								break;
							if(link[ map[r-1][c-2] ][ map[r-2][c] ])
								break;
							if(link[ map[r][c-2] ][ map[r-1][c] ])
								break;
						}
						if(c+1<=n)
						{
							if(link[ map[r-1][c-1] ][ map[r-2][c+1] ])
								break;
							if(link[ map[r][c-1] ][ map[r-1][c+1] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 8:  //330度方位
					{
						if(link[ map[r][c-2] ][ map[r-1][c] ])
							break;
						if(c-3>=0 && link[ map[r][c-3] ][ map[r-1][c-1] ])
							break;
						if(c+1<=n && link[ map[r][c-1] ][ map[r-1][c+1] ])
							break;
						if(r-2>=0)
						{
							if(link[ map[r-2][c-2] ][ map[r][c-1] ])
								break;
							if(link[ map[r-2][c-1] ][ map[r][c-2] ])
								break;
							if(link[ map[r-2][c] ][ map[r][c-1] ])
								break;
						}
						if(r+1<=n)
						{
							if(link[ map[r-1][c-1] ][ map[r+1][c-2] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r+1][c] ])
								break;
							if(link[ map[r-1][c] ][ map[r+1][c-1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
				}
			}
		}
	}
	return;
}

/*BFS,检查先手(黑棋)是否把终域连接在一起(赢家)*/
bool CheckWin(PEG* peg,bool flag)
{
	int NUM;
	if(!flag)  //通过舍弃最后一步棋，检查最后一步棋是否为决定赢棋的一步
		NUM=map[lastx][lasty];

	for(int k=0;k<=n;k++)
	{
		int p=map[0][k];
		if(p && p!=NUM && peg[p].color==1)
		{
			int queue[num];
			bool vist[num]={false};
			int head=0;
			int tail=0;
			queue[tail++]=p;
			vist[p]=true;

			while(head<tail)
			{
				int s=queue[head++];
				if(peg[s].r==n)
					return true;

				for(int i=0;i<peg[s].pc;i++)
				{
					int x=peg[s].connet[i];
					if(!vist[x])
					{
						vist[x]=true;
						if(!flag && x==NUM)
							continue;
						queue[tail++]=x;
					}
				}
			}
		}
	}
	return false;
}