// Poj: 1161
// @Hsiao
// Oct 18th, 2016

#include<iostream>
#include<cstring>
#define INF 100000000

using namespace std;

int main()
{
	int FreeLand[201][201],        //记录图
		City[251][251],            //记录城墙
		Club[31],                  //记录俱乐部成员
		AdjacentLand[251][201];    //记录俱乐部都和哪些空地相邻

	int m, n, l;
	int i, j, k, curr, first, temp, last, min, sum, place;

	cin >> m >> n >> l;

	for (i = 0; i<l; i++)
		cin >> Club[i];

	for (i = 0; i<m; i++)
	for (j = 0; j<m; j++)
	if (j == i)
		FreeLand[i][j] = 0;  //对图的预处理
	else
		FreeLand[i][j] = INF;

	memset(City, 0, sizeof(City));
	memset(AdjacentLand, 0, sizeof(AdjacentLand));

	for (i = 0; i<m; i++)             //两重循环构造图
	{
		cin >> temp;
		cin >> first;
		last = first;
		AdjacentLand[first][i] = 1; //包围空地的城市当然和空地相邻

		for (j = 1; j<temp; j++)
		{
			cin >> curr;
			AdjacentLand[curr][i] = 1;
			if (City[last][curr]>0) //如果该城墙已经记录过了，判断相邻
				FreeLand[City[last][curr] - 1][i] = FreeLand[i][City[last][curr] - 1] = 1;
			else                    //否则把空地的编号纪录在这个位置
				City[last][curr] = City[curr][last] = i + 1;
			last = curr;
		}
		if (City[last][first]>0)    //补充判断首尾连接的情况
			FreeLand[City[last][first] - 1][i] = FreeLand[i][City[first][last] - 1] = 1;
		else
			City[last][first] = City[first][last] = i + 1;
	}

	for (k = 0; k<m; k++)               //floyd算法
	for (i = 0; i<m; i++)
	for (j = 0; j<m; j++)
	if (FreeLand[i][k] + FreeLand[k][j]<FreeLand[i][j])
		FreeLand[i][j] = FreeLand[i][k] + FreeLand[k][j];

	min = INF;
	for (i = 0; i<m; i++)               //搜索最优的空地
	{
		sum = 0;
		for (j = 0; j<l; j++)           //考虑每个俱乐部
		{
			temp = INF;
			for (k = 0; k<m; k++)       //考虑每个俱乐部相邻的空地
			{
				if (AdjacentLand[Club[j]][k] == 0)
					continue;
				if (temp>FreeLand[k][i])
					temp = FreeLand[k][i];
			}
			sum += temp;
		}
		if (min>sum)
		{
			min = sum;
			place = i;
		}
	}

	cout << min << endl;

	return 0;
}