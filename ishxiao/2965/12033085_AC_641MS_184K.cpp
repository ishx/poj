/*代码一：DFS+Enum*/

//Memory Time 
//240K  641MS 

//本题由于要输出每次翻转的棋子，因此不适宜用BFS，应该使用DFS输出完整路径

#include<iostream>
using namespace std;

bool lock[10][10]={false};
bool flag;
int step;
int ri[16],cj[16];

bool isopen(void)
{
	for(int i=3;i<7;i++)
		for(int j=3;j<7;j++)
			if(lock[i][j]!=true)
				return false;
	return true;
}

void flip(int row,int col)               //其实参考POJ1753的翻棋方法也是可以做出来的，但是会超时不通过
{                                        //超时的原因就是翻棋时有太多多余的操作
	lock[row][col]=!lock[row][col];      //POJ1753使用6x6矩形，多余操作只有周围的“一圈”翻棋！
	for(int i=3;i<=6;i++)                //这里使用10x10矩形，多余操作有“三圈”翻棋！
		lock[i][col]=!lock[i][col];      //其实用位运算就可以只使用4x4矩形，大大降低时间复杂度，根本没有多余操作，但是程序会很复杂，不好看
	for(int j=3;j<=6;j++)
		lock[row][j]=!lock[row][j];
	return;
}

void dfs(int row,int col,int deep)
{
	if(deep==step)
	{
		flag=isopen();
	    return;
	}

	if(flag||row==7)return;

	flip(row,col);
	ri[deep]=row;
	cj[deep]=col;

	if(col<6)
		dfs(row,col+1,deep+1);
	else
		dfs(row+1,3,deep+1);

	flip(row,col);
	if(col<6)
		dfs(row,col+1,deep);
	else
	    dfs(row+1,3,deep);
	return;
}

int main(void)
{
	char temp;
	int i,j;
	for(i=3;i<7;i++)
		for(j=3;j<7;j++)
		{
			cin>>temp;
			if(temp=='-')
				lock[i][j]=true;
		}

	for(step=0;step<=16;step++)
	{
		dfs(3,3,0);
		if(flag)break;
	}

	cout<<step<<endl;
	for(i=0;i<step;i++)
		cout<<ri[i]-2<<' '<<cj[i]-2<<endl;
	return 0;
}

