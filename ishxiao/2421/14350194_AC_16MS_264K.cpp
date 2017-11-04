// poj2421 
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

void makeset(const int N, std::vector<int> &parent, std::vector<int> &rank)
{
	for (int u = 0; u < N; ++u)
	{
		parent[u] = u;
		rank[u] = 0;
	}
}

int find(int u, std::vector<int> &parent)
{
	if (parent[u] != u)
	{
		parent[u] = find(parent[u], parent);
	}
	return parent[u];
}

void union_set(int u, int v, std::vector<int> &parent, std::vector<int> &rank)
{
	int ru = find(u, parent);
	int rv = find(v, parent);
	if (ru == rv)
	{
		return;
	}

	if (rank[ru] < rank[rv])
	{
		parent[ru] = rv;
	}
	else if (rank[rv] < rank[ru])
	{
		parent[rv] = ru;
	}
	else
	{
		parent[ru] = rv;
		rank[rv]++;
	}
}

class Edge
{
public:
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}

	bool operator< (const Edge &rhs) const
	{
		if (this->w != rhs.w)
		{
			return this->w < rhs.w;
		}
		return this->u < rhs.u || (this->u == rhs.u && this->v < rhs.v);
	}
};

int kruskal(const int N, std::vector<Edge> &edges)
{
	std::vector<int> parent(N);
	std::vector<int> rank(N);

	makeset(N, parent, rank);

	sort(edges.begin(), edges.end());

	int mst = 0;
	for (int i = 0; i < edges.size(); ++i)
	{
		Edge edge = edges[i];
		if (find(edge.u, parent) != find(edge.v, parent))
		{
			mst += edge.w;
			union_set(edge.u, edge.v, parent, rank);
		}
	}
	return mst;
}


int main()
{
	int N;	
	scanf("%d", &N);

	vector<vector<int> > dis(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			scanf("%d", &dis[i][j]);
		}
	}
	
	int Q;
	scanf("%d", &Q);
	for (int i = 0; i < Q; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;

		dis[u][v] = 0;
		dis[v][u] = 0;
	}

	std::vector<Edge> edges(N * (N - 1) / 2);
	int edgeno = 0;
	for (int u = 0; u < N; ++u)
	{
		for (int v = u + 1; v < N; ++v)
		{
			edges[edgeno] = Edge(u, v, dis[u][v]);
			edgeno++;
		}
	}

	assert (edgeno == N * (N - 1) / 2); 

	sort(edges.begin(), edges.end());

	printf("%d\n", kruskal(N, edges));

	return 0;
}