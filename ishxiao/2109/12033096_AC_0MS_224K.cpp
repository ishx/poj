//2109 

#include<iostream>
#include<math.h>
using namespace std;


int main(void)
{
	double n,p;
	while(cin>>n>>p)
		cout<<pow(p,1.0/n)<<endl;  //指数的倒数就是开n次方
	return 0;
}