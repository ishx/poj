#include<cstdlib>
#include<iostream>
using namespace std;

//1.从低位到高位1比特1比特地看过来，这就不多说了，随便搜搜一箩筐～
//2.负数转换成整数，并且n和p和互相转换，即n转换为p，p转换为n。
//3.对于long long边界的情况，我先用long long y读进来，然后赋值给unsigned long long x。用y来判断正负，发现小于零就x = -x。这里需要想一想unsigned数和signed数存储数据的时候其实都是用补码表示的，做相反数操作的时候都是按位取反，末尾加一。因此即使y<0，y也可以赋值给x，x在按位取反末尾加一后也就成为了y的相反数，而且x能表示的非负数范围比y广。
long long int x = -3;
unsigned long long int y = -x;    //y=3.
//4.提交时用C++编译。

int main()
{
	int N;
	int n;
	char pn[65] = {'\0'};
	char ans[65] = {'\0'};
	long long y;
	unsigned long long x;

	cin >> N;

	for(int i = 0 ; i < N; i ++){

		cin>>n>>pn>>y;
		x = y;
		if(y < 0){	//dealing with the x < 0 cases: convert to positive, and inverse the array pn[], 'n' -> 'p', 'p' -> 'n'.

			x = -x;	//convert to positive, note the relation between unsigned and signed.

			for(int j = 0; j < n; j ++)	//inverse the array pn[]
				if(pn[j] == 'n') pn[j] = 'p';
				else pn[j] = 'n';

		}

		for(int j = n - 1; j >= 0; j --){

			if(x&1 == 1){
				ans[j] = '1';
				if (pn[j] == 'p') x = x - 1;
				else x = x + 1;
				x = x >> 1;
			}
			else{
				ans[j] = '0';
				x = x >> 1;
			}

		}

		if(x != 0) cout<<"Impossible\n";
		else cout<<ans<<endl;
		memset(ans, '\0', sizeof(char)*65);
	}



	return 0;
}