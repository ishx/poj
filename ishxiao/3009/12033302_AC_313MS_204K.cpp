/*DFS+回溯+剪枝*/

//3009

#include<iostream>
using namespace std;

const int inf=11;

typedef class
{
	public:
		int r,c;     //冰壶当前位置
		bool status; //status冰壶当前状态：运动true ,静止false
}SE;

SE s,e;   //记录冰壶起止点
int w,h;  //场地size
int MinStep;  //最短路
int board[30][30];  //场地

void DFS(int i,int j,bool status,int direction,int step,bool flag)  
{ //direction:冰壶当前运动方向  North:0  West:1  South:2  East:3 
  //flag:是否消除direction方向下一格位置的石头

	if(step>10)   //剪枝，超过10步的走法就不再考虑了
		return;

	if(board[i][j]==3)   //终点
	{
		if(MinStep>step)
			MinStep=step;
		return;
	}

	if(flag)  //消除石头
	{
		switch(direction)
		{
		    case 0: {board[i-1][j]=0; break;}
	    	case 1: {board[i][j-1]=0; break;}
			case 2: {board[i+1][j]=0; break;}
			case 3: {board[i][j+1]=0; break;}
		}
	}
	
	if(!status)  //静止
	{
		if(i-1>=1 && (board[i-1][j]==0 || board[i-1][j]==3))  //North
			DFS(i-1,j,true,0,step+1,false);

		if(j-1>=1 && (board[i][j-1]==0 || board[i][j-1]==3))  //West
			DFS(i,j-1,true,1,step+1,false);

		if(i+1<=h && (board[i+1][j]==0 || board[i+1][j]==3))  //South
			DFS(i+1,j,true,2,step+1,false);

		if(j+1<=w && (board[i][j+1]==0 || board[i][j+1]==3))  //East
			DFS(i,j-1,true,3,step+1,false);
	}
	else if(status)  //运动
	{
		switch(direction)
		{
	        case 0:
				{
					if(i-1<1)  //预判下一步是否越界
						return;
					else
					{
						if(board[i-1][j]==0)          //下一位置为0且不越界，继续运动
							DFS(i-1,j,true,0,step,false);
						else if(board[i-1][j]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,0,step,true);
						else if(board[i-1][j]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i-1,j,false,0,step,false);
					}

					break;
				}
			case 1:
				{
					if(j-1<1)  //预判下一步是否越界
						return;
					else
					{
						if(board[i][j-1]==0)          //下一位置为0且不越界，继续运动
							DFS(i,j-1,true,1,step,false);
						else if(board[i][j-1]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,1,step,true);
						else if(board[i][j-1]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i,j-1,false,1,step,false);
					}

					break;
				}
			case 2:
				{
					if(i+1>h)  //预判下一步是否越界
						return;
					else
					{
						if(board[i+1][j]==0)          //下一位置为0且不越界，继续运动
							DFS(i+1,j,true,2,step,false);
						else if(board[i+1][j]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,2,step,true);
						else if(board[i+1][j]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i+1,j,false,2,step,false);
					}

					break;
				}
			case 3:
				{
					if(j+1>w)  //预判下一步是否越界
						return;
					else
					{
						if(board[i][j+1]==0)          //下一位置为0且不越界，继续运动
							DFS(i,j+1,true,3,step,false);
						else if(board[i][j+1]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,3,step,true);
						else if(board[i][j+1]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i,j+1,false,3,step,false);
					}

					break;
				}
		}
	}

	if(flag)  //回溯前还原石头，即还原上一步的棋盘状态
	{
		switch(direction)
		{
		    case 0: {board[i-1][j]=1; break;}
	    	case 1: {board[i][j-1]=1; break;}
			case 2: {board[i+1][j]=1; break;}
			case 3: {board[i][j+1]=1; break;}
		}
	}

	return;
}

int main(void)
{
	while(cin>>w>>h)
	{
		if(!w && !h)
			break;

		/*Structure the Board*/

		MinStep=inf;
		
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)
			{
				cin>>board[i][j];

				if(board[i][j]==2)
				{
					s.r=i;
					s.c=j;
				    s.status=false;
					board[i][j]=0;  //记录起点位置后，把它作为0处理
				}
				if(board[i][j]==3)  //终点是特别位置，冰壶经过或到达该格都会停止
				{
					e.r=i;
					e.c=j;
				}
			}

		/*Search the min path*/

		DFS(s.r , s.c , s.status , 0 , 0 , false);

		if(MinStep<=10)
			cout<<MinStep<<endl;   //DFS里面虽然剪枝了，但是可能把全部走法都剪了，因此还是要判断
		else
			cout<<-1<<endl;

	}
	return 0;
}