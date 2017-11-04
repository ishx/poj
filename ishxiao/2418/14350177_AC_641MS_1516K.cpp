//poj2418 
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

const int MAXM = 31;

// whitespace, a ~ z and A ~ Z
// screw it, use all ascii characters
const int NCHILD = 128;

class Trie
{
public:	
	Trie *next[NCHILD];
	int cnt;
	Trie() 
	{
		for (int i = 0; i < NCHILD; ++i)
		{
			next[i] = NULL;
		}
		cnt = 0;
	}
};

int char2index(int ch)
{
	return ch;
	// int c = -1;
	// if (ch == ' ')
	// {
	// 	c = 0;
	// }
	// else
	// {

	// 	if ('a' <= ch && ch <= 'z')
	// 	{
	// 		// 1 ~ 26
	// 		c = ch - 'a' + 1;	
	// 	}
	// 	else
	// 	{
	// 			// should be all uppercase now.
	// 		assert('A' <= ch && ch <= 'Z');
	// 			// 27  + 0 ~ 27 + 25
	// 		c = ch - 'A' + 27;
	// 	}
	// }
	// return c;
}

char index2char(int index)
{
	return index;
	// char ch;
	// if (index == 0)
	// {
	// 	ch = ' ';
	// }
	// else if (1 <= index && index <= 26)
	// {
	// 	ch = 'a' + index - 1;
	// }
	// else
	// {
	// 	assert (27 <= index && index < NCHILD);
	// 	ch = 'A' + index - 27;
	// }
	// return ch;
}

void insertTrie(Trie *trie, char name[])
{
	Trie *p = trie;
	int c;
	for (int i = 0; name[i] != '\0' && name[i] != '\n'; ++i)
	{
		c = char2index(name[i]);

		if (p->next[c] == NULL)
		{
			p->next[c] = new Trie();
		}

		p = p->next[c];
	}

	p->cnt++;
}

void printTrie(Trie *trie, const int N, char name[], int len)
{
	if (trie->cnt > 0)
	{
		name[len] = '\0';
		printf("%s %.4lf\n", name, trie->cnt * 100.0 / N);
	}

	for (int c = 0; c < NCHILD; ++c)
	{
		if (trie->next[c] != NULL)
		{
			name[len] = index2char(c);
			printTrie(trie->next[c], N, name, len + 1);
		}
	}
}

int main()
{
	char name[MAXM];
	Trie *trie = new Trie();
	int N = 0;
	while(fgets(name, MAXM, stdin) > 0)
	{
		// printf("name:[%s]\n", name);
		insertTrie(trie, name);
		N++;
	}

	// printf("N: %d\n", N);

	printTrie(trie, N, name, 0);

	return 0;
}
