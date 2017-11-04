//1113

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

const int inf=10001;
const double pi=3.141592654;

typedef class
{
	public:
		int x,y;
}point;

/*AB距离平方*/

int distsquare(point A,point B)
{
	return (B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y);
}

/*AB距离*/

double distant(point A,point B)
{
	return sqrt((double)((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y)));
}

/*叉积计算*/

int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}

int cross(point A,point B,point C,point D)
{
	return det(B.x-A.x,B.y-A.y,D.x-C.x,D.y-C.y);
}

/*快排判断规则*/

point* s;
int cmp(const void* pa,const void* pb)
{
	point* a=(point*)pa;
	point* b=(point*)pb;

	int temp=cross(*s,*a,*s,*b);
	if(temp>0)
		return -1;
	else if(temp==0)
		return distsquare(*s,*b)-distsquare(*s,*a);
	else
		return 1;
}

int main(int i,int j)
{
	int N,L;
	while(cin>>N>>L)
	{
		/*Input*/

		point* node=new point[N+1];

		int min_x=inf;
		int fi;
		for(i=1;i<=N;i++)
		{
			cin>>node[i].x>>node[i].y;

			if(min_x > node[i].x)
			{
				min_x = node[i].x;
				fi=i;
			}
			else if(min_x == node[i].x)
				if(node[fi].y > node[i].y)
					fi=i;
		}

		/*Quicksort the Vertex*/

		node[0]=node[N];
		node[N]=node[fi];
		node[fi]=node[0];

		s=&node[N];
		qsort(node+1,N,sizeof(point),cmp);

		/*Structure Con-bag*/

		int* bag=new int[N+2];
		bag[1]=N;
		bag[2]=1;
		int pb=2;
		for(i=2;i<=N;)
			if(cross(node[ bag[pb-1] ],node[ bag[pb] ],node[ bag[pb] ],node[i]) >= 0)
				bag[++pb]=i++;
			else
				pb--;

		/*Compute Min-length*/

		double minlen=0;
		for(i=1;i<pb;i++)
			minlen+=distant(node[ bag[i] ],node[ bag[i+1] ]);

		minlen+=2*pi*L;

		cout<<fixed<<setprecision(0)<<minlen<<endl;

		delete node;
		delete bag;
	}
	return 0;
}

