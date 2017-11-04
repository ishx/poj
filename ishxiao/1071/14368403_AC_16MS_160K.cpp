// poj1071
#include<cstdio>
#include<cstring>
using namespace std;

int map[110][110];
struct node
{
    int l,r;
    char dir;
}step[10000];
int n,m,t;

bool move(int &x,int &y,char dir)
{
    if(dir == 'U')
    {
        if(x-1>=0 && map[x-1][y]==0)
        {
            x--;
            return true;
        }
        return false;
    }
    else if(dir == 'D')
    {
        if(x+1<m && map[x+1][y]==0)
        {
            x++;
            return true;
        }
        return false;
    }
    else if(dir == 'L')
    {
        if(y-1>=0 && map[x][y-1]==0)
        {
            y--;
            return true;
        }
        return false;
    }
    else
    {
        if(y+1<n && map[x][y+1]==0)
        {
            y++;
            return true;
        }
        return false;
    }
}

int walk(int x,int y,int k)
{
    if (x<0||x>=m||y<0||y>=n||map[x][y]==1)
		return 0;
	//起始位置不能是为1的障碍物处，
	//所以必须加这个判断，而不能以为move里已经有了相应判断。
    if(k==t) return 1;
    int i;
    int sx=x,sy=y;
    char dir = step[k].dir;
    for(i=1;i<step[k].l;i++)
    {
        if(!move(sx,sy,dir))
            return 0;
    }
    for(;i<=step[k].r;i++)
    {
        if(move(sx,sy,dir))
        {
            if(walk(sx,sy,k+1))
                return 1;
        }
        else break;
    }
    return 0;
}

int main()
{
    int T,a,b,cnt;
    char ch;
    scanf("%d",&T);
    while(T--)
    {
        t=0,cnt=0;
        scanf("%d%d",&m,&n);
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
                scanf("%d",&map[i][j]);
        }
        while(1)
        {
            scanf("%d%d",&a,&b);
            if(a==0 && b==0)
                break;
            scanf(" %c",&ch);
            step[t].l = a;
            step[t].r = b;
            step[t].dir = ch;
            t++;
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
                cnt+=walk(i,j,0);
        }
        printf("%d\n",cnt);
    }
    return 0;
}
