//2187 

#include<iostream>
using namespace std;

const int inf=10001;

typedef class location
{
	public:
		int x,y;
}node;

/*点A到点B的距离的平方*/

int distsquare(node A,node B)
{
	return (B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y);
}

/*计算叉积*/

int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}

int cross(node A,node B,node C,node D)
{
	return det(B.x-A.x , B.y-A.y , D.x-C.x , D.y-C.y);
}

/*qsort比较规则*/

node* p;  //极坐标原点
int cmp(const void* a,const void* b)
{
	node* s=(node*)a;
	node* t=(node*)b;

	int temp=cross(*p,*s,*p,*t);  //叉乘ps X pt 
	if(temp>0)    //说明pt向量的极角 小于 ps向量的极角
		return -1;  //从逆时针排序角度，t点位置在s点前面，即t<s ，根据qsort规则返回-1

	else if(temp==0) //说明pt向量的极角 等于 ps向量的极角
		return distsquare(*p,*t)-distsquare(*p,*s);  //距离原点近的点优先排序，用减法能够实现3出口：- 0 +
	                    //注意，网上有些程序在这里不是比较 距离之差，而是比较 横坐标绝对值 之差
	                    //这是欠缺考虑  多点与原点连线 垂直于x轴，不完善，之所以能AC是因为POJ的数据库不足够大而已
	else
		return 1; //pt向量的极角 大于 ps向量的极角
}

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		node* farm=new node[n+1];
		int* conbag=new int[n+2];  //conbag[]顺序记录输入的点中构造成凸包的顶点集的各点在farm[]中的下标

		/*Input & search the first vertex*/

		int min_x=inf;
		int fi=0;
		for(i=1;i<=n;i++)
		{
			cin>>farm[i].x>>farm[i].y;

			if(min_x > farm[i].x)
			{
				min_x = farm[i].x;   //先以横坐标为第一关键字搜索最左下角的点
				fi=i;
			}
			else if(min_x == farm[i].x)
			{
				if(farm[fi].y > farm[i].y)   //若第一关键字相同，则以纵坐标作为第二关键搜索
					fi=i;
			}
		}

		/*Quicksort Point Sets*/

		farm[0]=farm[n];   //这三步非常关键，是使用qsort前的准备工作
		farm[n]=farm[fi];  //目的是把前面找到的最左下角的点作为 极坐标原点
		farm[fi]=farm[0];  //即把第fi个点移到farm[]最后的位置,qsort则会把它作为排序的参考点

		p=&farm[n]; //极坐标原点传参

		qsort(farm+1,n,sizeof(node),cmp);  //farm[]散点集排序

		/*Graham Scan Algorithm*/

		int pc=1;  //conbag[]指针
		conbag[1]=n;  //(约定)极坐标原点 为凸包第1个顶点
		conbag[++pc]=1; //(在前面基础上,)有序点集farm[]的第一个点 (必)为凸包第2个顶点
		conbag[0]=2;   //凸包顶点计数器

		for(i=2;i<=n;)
			if(cross(farm[ conbag[pc-1] ],farm[ conbag[pc] ],farm[ conbag[pc] ],farm[i]) >= 0)
			{   //检查向量(前一点pc-1,当前点pc) 与 向量(当前点pc,待入栈点i) 的旋转关系
				conbag[++pc]=i++;  //入栈
				conbag[0]++;
			}
			else
			{
				pc--;         //当前点pc出栈
				conbag[0]--;
			}

		/*Search The Max distant*/

		int maxdist=0;
		for(i=1;i<=conbag[0]-2;i++)          //散点集的两点最大距离必定出现在该散点集的凸包的某两个顶点之间
			for(j=i+1;j<=conbag[0]-1;j++)
			{
				int temp=distsquare(farm[ conbag[i] ],farm[ conbag[j] ]);
				if(maxdist < temp)
					maxdist = temp;
			}

		/*Output*/

		cout<<maxdist<<endl;


		delete farm;
		delete conbag;
	}
	return 0;
}