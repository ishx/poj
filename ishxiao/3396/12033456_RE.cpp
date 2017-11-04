//3396

#include<iostream>
using namespace std;

int Month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};   //平年月
int Lmonth[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};  //闰年月
enum week{Sun,Mon,Tue,Wed,Thu,Fri,Sat};  //星期

bool leap(int year);  //判断year是否为闰年
int ComputeDay(int y,int m);  //计算从第1年1月1日到第y年m-1月的总天数+1 (即只包括第m个月的第一天)

int main(int i,int j,int* pm)
{
	int test;
	cin>>test;
	for(int t=0;t<test;t++)
	{
		int ys,ms,ye,me;
		cin>>ys>>ms>>ye>>me;

		int luck=0,good=0;
		int day=ComputeDay(ys,ms);

		if(((day+5)%7<=Mon) || ((day+5)%7==Sat))  //计算起始ys年ms月1号为星期几，判断是否为good month
			good++;                               //1年1月1号是星期六，而原本默认是星期日，因此+5调整

		/*计算从ys年ms+1开始 到ye-1年的月份是否为good month*/

		for(i=ys;i<ye;i++)
		{
			if(leap(i))
				pm=Lmonth;
			else
				pm=Month;

			if(i==ys)
				j=ms;
			else
				j=1;
			for(;j<=12;j++)
			{
				day+=*(pm+j);
				if(i==1752 && j==9)
					day-=11;
                                                          //由于day开始时+1缘故，当j时，计算的是第j+1月是否为good month
				if(((day+5)%7<=Mon) || ((day+5)%7==Sat))  //计算j+1月1号为星期几，判断是否为good month
				{
					good++;
					luck++;  //当j+1月为good month，j月必为luck month
				}
			}
		}

		/*计算第ye年的good month*/

		if(leap(i))
			pm=Lmonth;
		else
			pm=Month;

		if(i==ys)   //若ye==ys
			j=ms;
		else
			j=1;

		for(;j<=me;j++)
		{
			day+=*(pm+j);
			if(i==1752 && j==9)
				day-=11;
                                                      //由于day开始时+1缘故，当j时，计算的是第j+1月是否为good month
			if(((day+5)%7<=Mon) || ((day+5)%7==Sat))  //计算j+1月1号为星期几，判断是否为good month
			{
				if(j!=me)
					good++;

				luck++;  //当j+1月为good month，j月必为luck month
			}
		}
		
		cout<<luck<<' '<<good<<endl;
	}
	return 0;
}

bool leap(int year)  //判断year是否为闰年
{
	if(year<1582)
		return !(year%4);   //当year<1582时，只要能被4整除就是闰年
	else
	{
		if(year==1700) //当year=1700时，历史原因，无条件为闰年
			return true;

		if((!(year%4)&&(year%100)) || !(year%400))   //当year>=1582时，能被4整除且不被100整除为闰年
			return true;                             //或能被400整除时为闰年
	}
	return false;
}

int ComputeDay(int y,int m)  //计算从第1年1月1日到第y年m-1月的总天数+1 (即只包括第m个月的第一天)
{                            //"+1"是为了使从当月末变为下月初
	int i,j,day=1;
	for(i=1;i<y;i++)
		if(leap(i))
			day+=366;
		else
			day+=365;

	for(j=1;j<m;j++)
		if(leap(i))
			day+=Lmonth[j];
		else
			day+=Month[j];

	if(y>1752)
		day-=11;
	else if(y==1752 && m>9)
		day-=11;

	return day;
}