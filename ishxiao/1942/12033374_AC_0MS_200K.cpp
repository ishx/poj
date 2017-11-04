/*自定义精度输出*/

//1942_2

#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

/*Compute (n+m)C min{n,m}*/

double comp(unsigned n,unsigned m)
{
	unsigned a=m+n;
	unsigned b=(m<n?m:n);
	double cnm=1.0;
	while(b>0)
		cnm*=(double)(a--)/(double)(b--);

	return cnm;
}

int main(void)
{
	unsigned m,n;
	while(true)
	{
		cin>>m>>n;
		if(!m && !n)
			break;

		cout<<fixed<<setprecision(0)<<comp(n,m)<<endl;  
		//fixed是为了固定小数位数
		//setprecision()函数是会自动四舍五入的，所以不用像强制类型转换那样预先+0.5
	}
	return 0;
}