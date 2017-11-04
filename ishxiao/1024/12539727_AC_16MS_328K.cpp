//1024
# include <iostream>
using namespace std;
# include <cstring>
class bar
{
public:
	int x1,x2,y1,y2;
	void add(int,int,int,int);
	bool check(int,int,int,int);
};
class graph
{
private:
	int map1[100][100];
	int map2[100][100];
	int endx,endy,w,h;
	char *path;
	void peek(int &,int &,int,int,int,int,bool visit[100][100],int map[100][100]);
	bool check(int,int,int,int,bool visit[100][100]);
	bool checkbar(int,int,int,int);
	inline bool barchk(int);
	inline bool bchk(int,int);
	inline bool chkd(int,int,int);
	inline void change(int,int,int&,int&,int&,int&);
	void culpath();
	void buildmap(int,int,int map[100][100]);
public:
	graph(int,int,char*);
	bool istrue();
};


bar *barrier;
int barnum;
//-----------------bar start------------------------------------
void bar::add(int x1,int y1,int x2,int y2)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
}
bool bar::check(int x1, int y1, int x2, int y2)
{
	if(x1==this->x1&&x2==this->x2&&y1==this->y1&&y2==this->y2) return 0;
	else if(x1==this->x2&&x2==this->x1&&y1==this->y2&&y2==this->y1) return 0;
	else return 1;
}
//-----------------bar end--------------------------------------

//-----------------graph start----------------------------------
graph::graph(int width,int height,char *temp)
{
  path=temp;
  w=width;
  h=height;
  culpath();
  //---------------代价矩阵初始化---------------------
  for(int i=0;i<width;i++)
	  for(int j=0;j<height;j++)
		  map1[i][j]=map2[i][j]=9999999;
  //---------------------------------------------------
}


bool graph::checkbar(int x1,int y1,int x2,int y2)
{
	   for(int i=1;i<=barnum;i++) 
	   if(!barrier[i].check(x1,y1,x2,y2)) return 0;
   return 1;
}
bool graph::check(int x1, int y1, int x2, int y2,bool visit[100][100])
{
   if(x2<0||x2>=w||y2<0||y2>=h) return 0;
   if(visit[x2][y2]) return 0;
   for(int i=1;i<=barnum;i++) 
	   if(!barrier[i].check(x1,y1,x2,y2)) return 0;
   return 1;
}
void graph::culpath()
{
	endx=0;
	endy=0;
	for(int i=0;i<strlen(path);i++)
	  switch(path[i])
	  {
		 case 'U': endy++;break;
		 case 'D': endy--;break;
		 case 'L': endx--;break;
		 case 'R': endx++;break;
	  };
}



void graph::buildmap(int x,int y,int map[100][100])
{
	bool visit[100][100];
	memset(visit,0,sizeof(visit));
	map[x][y]=0;
	int xd=x,yd=y,xu=x,yu=y;
	int count=w*h;
	while(count>0)
	{
		peek(x,y,xd,yd,xu,yu,visit,map);
		visit[x][y]=1;
		count--;
		int len=map[x][y];
		if(check(x,y,x+1,y,visit))
		{
          change(x+1,y,xd,yd,xu,yu);
		  if(len+1<map[x+1][y]) map[x+1][y]=len+1;
		}
		if(check(x,y,x-1,y,visit))
		{
		  change(x-1,y,xd,yd,xu,yu);
		  if(len+1<map[x-1][y]) map[x-1][y]=len+1;
		}
		if(check(x,y,x,y-1,visit))
		{
		  change(x,y-1,xd,yd,xu,yu);
		  if(len+1<map[x][y-1]) map[x][y-1]=len+1;
		}
		if(check(x,y,x,y+1,visit))
		{
		  change(x,y+1,xd,yd,xu,yu);
		  if(len+1<map[x][y+1]) map[x][y+1]=len+1;
		}
	}
}
inline void graph::change(int x,int y,int& xd,int &yd,int &xu,int &yu)
{
	if(x<xd) xd=x;
	if(x>xu) xu=x;
	if(y<yd) yd=y;
	if(y>yu) yu=y;
}
void graph::peek(int &x, int &y, int xd, int yd, int xu, int yu, bool visit[100][100],int map[100][100])	
{
	int min=999999;
	for(int i=xd;i<=xu;i++)
		for(int j=yd;j<=yu;j++)
			if(!visit[i][j]&&map[i][j]<min)
			{
				min=map[i][j];
				x=i;
				y=j;
			}
}

inline bool graph::bchk(int x,int y)
{
 if(x<0||y<0||x>=w||y>=h) return false;
 else return true;
}
inline bool graph::chkd(int x,int y,int n)
{
	int total=0;
	if(bchk(x-1,y))
		if(map1[x-1][y]==n-1&&checkbar(x,y,x-1,y))
			total++;
    if(bchk(x+1,y))
		if(map1[x+1][y]==n-1&&checkbar(x,y,x+1,y))
			total++;
	if(bchk(x,y-1))
		if(map1[x][y-1]==n-1&&checkbar(x,y,x,y-1))
			total++;
	if(bchk(x,y+1))
		if(map1[x][y+1]==n-1&&checkbar(x,y,x,y+1))
			total++;
	if(total==1) return 1;
	else return 0;
}
inline bool graph::barchk(int s)
{
	if(map1[barrier[s].x1][barrier[s].y1]+map2[barrier[s].x2][barrier[s].y2]+1>map1[endx][endy]&&
       map1[barrier[s].x2][barrier[s].y2]+map2[barrier[s].x1][barrier[s].y1]+1>map1[endx][endy])
	   return 0;
	return 1;
}
bool graph::istrue()
{
	buildmap(0,0,map1);
	buildmap(endx,endy,map2);
         /* 测试最短路径矩阵
        cout<<endl<<endl;
	for(int j=h-1;j>=0;j--)
	{
		for(int i=0;i<w;i++) printf("%5d ",map1[i][j]);
		cout<<endl;
	}
	cout<<endl<<endl;
	for(int j=h-1;j>=0;j--)
	{
		for(int i=0;i<w;i++) printf("%5d ",map2[i][j]);
		cout<<endl;
	}
        */
	if(map1[endx][endy]!=strlen(path)) return 0;//最短路径判断
	//-------------------------唯一性判断------------------
	int tx=0,ty=0;
	for(int i=0;i<strlen(path);i++)
	{
	   switch(path[i])
	  {
		 case 'U': ty++;break;
		 case 'D': ty--;break;
		 case 'L': tx--;break;
		 case 'R': tx++;break;
	  };
	   if(!chkd(tx,ty,i+1)) return 0;
	}
	//-----------------------------------------------------

	//-----------------------墙多余判断--------------------
	for(int i=1;i<=barnum;i++)
	  if(!barchk(i)) return 0;
	//-----------------------------------------------------

	return 1;//PASS
}   
//-----------------graph end------------------------------------
int main()
{
	int test;
	cin>>test;
	for(int i=1;i<=test;i++)
	{
	   int w,h;
	   char *temp=new char[10001];
	   cin>>w>>h;
	   cin>>temp;
	   cin>>barnum;
	   graph data(w,h,temp);
	   barrier=new bar[barnum+1];
	   for(int j=1;j<=barnum;j++)
	   {
		   int t1,t2,t3,t4;
		   cin>>t1>>t2>>t3>>t4;
		   barrier[j].add(t1,t2,t3,t4);
	   }
	   if(data.istrue()) cout<<"CORRECT"<<endl;
	   else cout<<"INCORRECT"<<endl;
	   delete[] barrier;
	   delete[] temp;
	}
	return 0;
}