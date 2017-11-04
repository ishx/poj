/*强制类型转换输出*/

//1942_1

#include<iostream>
#include<math.h>
using namespace std;

/*Compute (n+m)C min{n,m}*/

unsigned comp(unsigned n,unsigned m)
{
	unsigned a=m+n;
	unsigned b=(m<n?m:n);
	double cnm=1.0;
	while(b>0)
		cnm*=(double)(a--)/(double)(b--);

    cnm+=0.5;      //double转unsigned会强制截断小数，必须先四舍五入
	return (unsigned)cnm;
}

int main(void)
{
	unsigned m,n;
	while(true)
	{
		cin>>m>>n;
		if(!m && !n)//承认这题的猥琐吧！竟然有其中一边为0的矩阵，一定要&&，用||会WA
			break;

		cout<<comp(n,m)<<endl;
	}
	return 0;
}