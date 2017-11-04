//Memory Time 
//232K   0MS 

#include<iostream>
#include<algorithm>
using namespace std;

int main(void)
{
	int room[401];   

	int test,move_time,i,j,temp;
	int from[200],to[200];

	cin>>test;
	for(j=0;j<test;j++)
	{
		memset(room,0,sizeof(room));  //注意每次测试都要初始化，而不是在输入测试次数前初始化

		cin>>move_time;
		for(i=0;i<move_time;i++)
		{
			cin>>from[i]>>to[i];
			if(from[i]>to[i])
			{
				temp=from[i];
				from[i]=to[i];
				to[i]=temp;
			}
			if(from[i]%2!=0)
				from[i]++;
			if(to[i]%2!=0)
				to[i]++;
			for(temp=from[i];temp<=to[i];temp+=2)
			{
				room[temp]++;
			}
		}
		sort(room,room+401);
		cout<<room[400]*10<<endl;
	}
	return 0;
}