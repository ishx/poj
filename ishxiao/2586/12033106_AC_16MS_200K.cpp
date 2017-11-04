//2586


#include<iostream>
using namespace std;

int main(void)
{
	double s,d;
	while(cin>>s>>d)
	{
		bool flag=false;
		int surplus=0;
		if(s>=4*d)
			flag=true;

		else if((s>=1.5*d)&&(s<4*d))
		{
			surplus=3*s-9*d;
			if(surplus<0)
				flag=true;
		}

		else if((s>=0.666666*d)&&(s<1.5*d))
		{
			surplus=6*(s-d);
			if(surplus<0)
				flag=true;
		}

		else if((s>=0.25*d)&&(s<0.666666*d))
		{
			surplus=8*s-4*d;
			if(surplus<0)
				flag=true;
		}

		else if((s>=0)&&(s<0.25*d))
		{
			surplus=10*s-2*d;
			if(surplus<0)
				flag=true;
		}

		if(flag)
			cout<<"Deficit"<<endl;
		else
			cout<<surplus<<endl;
	}
	return 0;
}