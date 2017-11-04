// Poj: 2252
// @Hsiao
// Oct 19th, 2016

#include <stdio.h>
#include <memory.h>

#define MAXX  32000	//最大范围

int f[(MAXX + 1) * 3];		//f值
int level[15001];		//记录各个level的星星个数

int main()
{
	int i, k, l, r, s, n, x, y, mid;
	memset(f, 0, sizeof(f));
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		s = 0; k = 1; l = 0; r = MAXX;
		while (l < r)
		{
			mid = (l + r) >> 1;
			if (x > mid) // 如果在右侧
			{
				l = mid + 1; s += f[k]; k <<= 1; k++;
			}
			else         // 否则在左侧
			{
				r = mid;
				f[k]++;
				k = k << 1;
			}
		}
		s += f[k];      // 叶结点
		f[k]++;
		level[s]++;
	}

	for (i = 0; i < n; i++)		//输出
		printf("%d\n", level[i]);

	return 0;
}