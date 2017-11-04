// poj1093
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

const int maxn = 1000;

int n, wordsnum;
string words[maxn];
int sum[maxn];
int f[maxn][maxn];
int from[maxn][maxn];

void turntowords(string st)
{
	int i = 0;

	while (1)
	{
		i = 0;
		while (st[i] != ' ' && i < signed(st.length()))
			i++;
		words[wordsnum++] = st.substr(0, i);
		sum[wordsnum] = i + sum[wordsnum - 1];
		if (i == signed(st.length()))
			break;
		st.erase(0, i);
		while (st[0] == ' ')
			st.erase(0, 1);
	}
}

void init()
{
	string st;

	wordsnum = 0;
	memset(sum, 0, sizeof(sum));
	getchar();
	while (1)
	{
		getline(cin, st);
		if (st == "")
			break;
		turntowords(st);
	}
}

int cost(int start, int end)
{
	int left, right, tot, len;

	if (end - start == 1)
		return 500;
	tot = n - (sum[end] - sum[start]);
	len = tot / (end - start - 1);
	left = end - start - 1 - tot % (end - start - 1);
	right = tot % (end - start - 1);
	return left * (len - 1) * (len - 1) + right * len * len;
}

void work()
{
	int i, j, k;

	memset(f, -1, sizeof(f));
	f[0][0] = 0;
	for (i = 1; i <= wordsnum; i++)
	for (j = 1; j <= wordsnum; j++)
	for (k = 1; k <= j && j - k >= i - 1 && n - (sum[j] - sum[j - k]) >= k - 1; k++)
	if (f[i - 1][j - k] != -1 && (f[i][j] > f[i - 1][j - k] + cost(j - k, j) || f[i][j] == -1))
	{
		f[i][j] = f[i - 1][j - k] + cost(j - k, j);
		from[i][j] = k;
	}
}

void printline(int start, int end)
{
	int left, tot, len, i, j;

	if (end - start == 1)
	{
		cout << words[start] << endl;
		return;
	}
	tot = n - (sum[end] - sum[start]);
	len = tot / (end - start - 1);
	left = end - start - 1 - tot % (end - start - 1);
	for (i = start; i < end - 1; i++)
	{
		cout << words[i];
		for (j = 0; j < len; j++)
			printf(" ");
		if (i - start + 1 > left)
			printf(" ");
	}
	cout << words[end - 1] << endl;
}

void output()
{
	int i, best = 1000000000, besti;

	for (i = 0; i <= wordsnum; i++)
	if (f[i][wordsnum] < best && f[i][wordsnum] >= 0)
	{
		best = f[i][wordsnum];
		besti = i;
	}
	int line[maxn];
	int j = wordsnum;
	for (i = besti; i > 0; i--)
	{
		line[i] = from[i][j];
		j -= from[i][j];
	}
	j = 0;
	for (i = 1; i <= besti; i++)
	{
		printline(j, j + line[i]);
		j += line[i];
	}
	cout << endl;
}

int main()
{
	//freopen("D:\\t.txt", "r", stdin);
	while (cin >> n && n != 0)
	{
		init();
		work();
		output();
	}
	return 0;
}