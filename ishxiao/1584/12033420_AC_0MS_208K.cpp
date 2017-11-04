//1584

#include<iostream>
#include<cmath>
using namespace std;

const double eps=1e-6;
const double pi=3.141592654;

typedef class NODE
{
	public:
		double x,y;
}pos;

int n;
double PegR;  //钉子半径
pos Peg;  //钉子坐标

int precision(double x);  //精度讨论
double det(double x1,double y1,double x2,double y2);  //叉积
double dotdet(double x1,double y1,double x2,double y2);  //点积
double cross(pos A,pos B,pos C,pos D);
double distant(pos A,pos B);  //计算距离
double angle(pos A,pos B,pos P);  //计算向量PA与PB夹角

bool IsConvexBag(pos* Vectex);  //判断输入的点集是否为凸包(本题保证了输入的点集为按某一时针方向有序)
bool IsIn(pos* Vectex); //判断圆心是否在多边形内部
bool IsFit(pos* Vectex);  //判断圆的半径是否<=其圆心到多边形所有边的最小距离

int main(void)
{
	while(cin>>n && n>=3)
	{
		cin>>PegR>>Peg.x>>Peg.y;
		pos* Vectex=new pos[n+2];  //多边形顶点坐标

		for(int i=1;i<=n;i++)
			cin>>Vectex[i].x>>Vectex[i].y;

		Vectex[0].x=Vectex[n].x;  //封闭多边形
		Vectex[0].y=Vectex[n].y;
		Vectex[n+1].x=Vectex[1].x;
		Vectex[n+1].y=Vectex[1].y;

		if(!IsConvexBag(Vectex))
			cout<<"HOLE IS ILL-FORMED"<<endl;
		else
		{
			bool flag1=IsIn(Vectex);
			bool flag2=IsFit(Vectex);

			if(flag1 && flag2)
				cout<<"PEG WILL FIT"<<endl;
			else
				cout<<"PEG WILL NOT FIT"<<endl;
		}

		delete Vectex;
	}
	return 0;
}

/*精度讨论*/
int precision(double x)
{
	if(fabs(x)<=eps)
		return 0;
	return x>0?1:-1;
}

/*计算点积*/
double dotdet(double x1,double y1,double x2,double y2)
{
	return x1*x2+y1*y2;
}

/*计算叉积*/
double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}
double cross(pos A,pos B,pos C,pos D)
{
	return det(B.x-A.x , B.y-A.y , D.x-C.x , D.y-C.y);
}

/*计算距离*/
double distant(pos A,pos B)
{
	return sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
}

/*计算角度*/
double angle(pos A,pos B,pos P)
{
	return acos(dotdet(A.x-P.x,A.y-P.y,B.x-P.x,B.y-P.y)/(distant(A,P)*distant(B,P)));
}

/*凸包判断*/
bool IsConvexBag(pos* Vectex)
{
	int direction=0;
	//保存点集Vectex的旋转方向direction   1:右手正螺旋，逆时针   -1:左手正螺旋，顺时针
	for(int i=0;i<=n-1;i++)
	{
		int temp=precision(cross(Vectex[i],Vectex[i+1],Vectex[i+1],Vectex[i+2]));

		if(!direction)   //避免最初的点出现共线的情况
			direction=temp;

		if(direction*temp<0)  //只要Vectex是凸包，那么无论Vectex的旋转方向如何，direction*temp都会>=0
			return false;
	}
	return true;
}

/*判断点与多边形的关系*/
bool IsIn(pos* Vectex)
{
	double CircleAngle=0.0;  //环绕角
	for(int i=1;i<=n;i++)  //注意重复边不计算
		if(precision(cross(Peg,Vectex[i],Peg,Vectex[i+1]))>=0)
			CircleAngle+=angle(Vectex[i],Vectex[i+1],Peg);
		else
			CircleAngle-=angle(Vectex[i],Vectex[i+1],Peg);

	if(precision(CircleAngle)==0)  //CircleAngle=0, Peg在多边形外部
		return false;
	else if(precision(CircleAngle-pi)==0 || precision(CircleAngle+pi)==0)   //CircleAngle=180, Peg在多边形边上(不包括顶点)
	{
		if(precision(PegR)==0)
			return true;
	}
	else if(precision(CircleAngle-2*pi)==0 || precision(CircleAngle+2*pi)==0)   //CircleAngle=360, Peg在多边形边内部
		return true;
	else   //CircleAngle=(0,360)之间的任意角， Peg在多边形顶点上
	{
		if(precision(PegR)==0)
			return true;
	}
	return false;
}

/*判断圆与多边形的关系*/
bool IsFit(pos* Vectex)
{
	for(int i=0;i<=n;i++)
	{
		int k=precision(fabs(cross(Peg,Vectex[i],Peg,Vectex[i+1])/distant(Vectex[i],Vectex[i+1]))-PegR);
		if(k<0)
			return false;
	}
	
	return true;
}