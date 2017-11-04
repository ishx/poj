//2531 

#include<iostream>
using namespace std;

const int TimeLimit=2000;  //本题时间限制为2000ms

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		/*Input*/

		int w[30][30]={0};
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				cin>>w[i][j];
				w[j][i]=w[i][j];  //双向完全图
			}

		/*Random Algorithm*/

		bool subset[30]={false};    //A集:true  B集:false
		int time=TimeLimit*100;  //使随机次数尽可能大，随机结果尽可能接近最优解
		long max_w=0;   //最大割的权值之和
		long sum=0;  //当前边割集权和

		while(time--)
		{
			int x=rand()%n+1;  //生成随机数 x，对应于总集合的某个结点x
			                   //注意由于使用的结点序号为1~n，对应了数组下标，下标为0的数组元素没有使用
			                   //那么这里必须+1，因为若rand()=n，那么再对n取模结果就为0
			                   //这时就会导致使用了不存在的 [0]结点，本应使用的 [n]结点就被丢弃了

			subset[x]=!subset[x];  //改变x所在的集合位置

			for(int i=1;i<=n;i++)   //由于是完全图，所以每个顶点i都与x相关联，因此要全部枚举
			{
				if(subset[i]!=subset[x])   //结点i 和 x分别在两个集合内
					sum+=w[i][x];   //就是说因为x所在集合的改变，使得割边的个数增加
				                    //割集的原权值 要加上 当前新加入的割边(i,x)的权值

				if(i!=x && subset[i]==subset[x])  //结点i 和 x分别在相同的集合内，但他们不是同一元素
					sum-=w[i][x];   //就是说因为x所在集合的改变，使得割边的个数减少
				                    //割集的原权值 要减去 当前失去的割边(i,x)的权值
			}

			if(max_w < sum)
				max_w = sum;
		}

		cout<<max_w<<endl;
	}
	return 0;
}