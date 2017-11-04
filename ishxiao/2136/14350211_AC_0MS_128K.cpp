//poj2136 
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std;

inline bool isUpperCase(char ch)
{
	return 'A' <= ch && ch <= 'Z';
}

int main()
{
	int cnt[26] = {0};
	char line[74];
	for (int l = 0; l < 4; ++l)
	{
		fgets(line, 74, stdin);
		for (int i = 0; line[i] != '\0'; ++i)
		{
			if (isUpperCase(line[i]))
			{
				cnt[line[i] - 'A']++;
			}
		}
	}

	int maxh = *max_element(cnt, cnt + 26);
	for (int h = maxh; h >= 1; --h)
	{
		for (int i = 0; i < 26; ++i)
		{
			if (cnt[i] >= h)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
			if (i != 25)
			{
				printf(" ");
			}
			else
			{
				printf("\n");
			}
		}
	}
	for (int i = 0; i < 26; ++i)
	{
		printf("%c", 'A' + i);
		if (i != 25)
		{
			printf(" ");
		}
		else
		{
			printf("\n");
		}
	}
	return 0;  
}