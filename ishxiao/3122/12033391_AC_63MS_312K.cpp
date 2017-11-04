//3122

#include<iostream>
#include<iomanip>
using namespace std;

const double pi=3.14159265359; //百度搜pi就有了，我逐位提交，这是最短的pi长度，再短就WA了
                               //懒得测试精度的同学就把尽可能多位数的pi放进程序，肯定不会WA
const double esp=1e-6;     //根据题目要求的精度，为了实数二分法设定的最小精度限制值

int main(void)
{
	int test;
	cin>>test;
	while(test--)
	{
		int n,f;     //n:pie数  f:朋友数
		cin>>n>>f;
		double* v=new double[n+1];    //每个pie的size
		f++;   //加上自己的总人数

		double maxsize=0.0;
		for(int i=1;i<=n;i++)
		{
			cin>>v[i];
			v[i]*=v[i];      //半径平方，计算pie的体积时先不乘pi，为了提高精度和减少时间

			if(maxsize<v[i])
				maxsize=v[i];
		}

		double low=0.0;     //下界，每人都分不到pie
		double high=maxsize;//上界，每人都得到整个pie，而且那个pie为所有pie中最大的
		double mid;

		while(high-low>esp)  //还是那句，实数double的二分结束条件不同于整数int的二分结束条件
		{
			mid=(low+high)/2;  //对当前上下界折中，计算"如果按照mid的尺寸分pie，能分给多少人"

			int count_f=0;  //根据mid尺寸能分给的人数
			for(int i=1;i<=n;i++)  //枚举每个pie
				count_f+=(int)(v[i]/mid);  //第i个pie按照mid的尺寸去切，最多能分的人数（取整）
			                               //就是说如果mid尺寸为1.5，pie总尺寸为2，那么这个pie最多分给一个人
			                               //剩下的0.5要扔掉

			if(count_f < f)       //当用mid尺寸分，可以分的人数小于额定人数
				high=mid;         //说明mid偏大，上界优化
			else
				low=mid;          //否则mid偏小，下界优化（注意'='一定要放在下界优化，否则精度会出错）
		}

		cout<<fixed<<setprecision(4)<<mid*pi<<endl;  //之前的计算都只是利用半径平方去计算，最后的结果要记得乘pi

		delete v;
	}
	return 0;
}