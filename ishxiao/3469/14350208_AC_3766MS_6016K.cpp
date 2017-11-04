// poj3469 
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

const int MAXN = 20000 + 2;
const int MAXM = 200000;

class Edge{
public:
	// edge (`u` -> `v`) with capacity `w`
	int v, w;
	// use (pre-allocated) array as linked list here
	// thus we need `next` point to next edge in adjacent list of node `u`
	int next;
	// the reverse edge (from `v` -> `u`) should be (edgeno ^ 1)
	// as we are adding edges sequentially
	// for convenience in updating residual graph 

	Edge()
	{
		this->v = -1;
		this->w = -1;
		this->next = -1;
	}
};


// construct level graph(GL) using BFS
// return true if sink is reachable from source (thus there is GL)
// return false otherwise
bool BFS(int GL[], int Queue[], int adjs[], Edge edges[], const int N, const int source, const int sink)
{	
	// initialize all levels as negative(-1)
	memset(GL, -1, N * sizeof(int));
	GL[source] = 0;
	
	int front = 0, rear = 0;
	Queue[0] = source;

	while (front <= rear)
	{
		int u = Queue[front];
		front++;
		int e = adjs[u];
		while (e >= 0)
		{
			int v = edges[e].v;
			// not set before (GL in this case can be thought as visited[])
			if (GL[v] < 0 && edges[e].w > 0)
			{
				GL[v] = GL[u] + 1;
				rear++;
				assert (rear < N);
				Queue[rear] = v;
			}

			// set as next node in adjacent list
			e = edges[e].next;
		}
	}

	if (GL[sink] > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int DFS(int u, int low, int GL[], int adjs[], Edge edges[], const int sink)
{
	// if reached sink, then return the narrowest capacity in the path (low)
	if (u == sink || !low)
	{
		return low;
	}

	// otherwise recursively check each adjacent edge (thus reach next node)
	int total = 0;
	int e = adjs[u];
	while (e >= 0 && low)
	{
		int v = edges[e].v;
		// v is at next level in level graph
		if (GL[v] == GL[u] + 1 && edges[e].w > 0)
		{
			int flow = DFS(v, min(low, edges[e].w), GL, adjs, edges, sink);
			// if can reach sink (because otherwise `flow` will be 0)
			if (flow > 0)
			{
				// update residual graph
				edges[e].w -= flow;
				edges[e ^ 1].w += flow;
				low -= flow;
				total += flow;
			}
		}

		e = edges[e].next;	
	}

	// optimization, no need to try this node any more if it has no outgoing flows
	if (total == 0)
	{
		GL[u] = -1;
	}

	return total;
}

// for more about dinic: http://comzyh.com/blog/archives/568/
int dinic(int GL[], int Queue[], int adjs[], Edge edges[], const int N, const int source, const int sink)
{
	int maxflow = 0;
	// construct level graph G_L using BFS
	// until sink cannot be reached from source
	while (BFS(GL, Queue, adjs, edges, N, source, sink))
	{
		// search a blocking flow (augment path) using DFS
		
		// int flow = DFS(source, numeric_limits<int>::max(), GL, adjs, edges, sink);
		// while (flow > 0)
		// {
		// 	maxflow += flow;
		// 	flow = DFS(source, numeric_limits<int>::max(), GL, adjs, edges, sink);
		// }

		maxflow += DFS(source, numeric_limits<int>::max(), GL, adjs, edges, sink);
	}

	return maxflow;
}

int main()
{
	Edge edges[2 * MAXN + 2 * MAXM + 2 * MAXN];
	int edgeno = 0;

	int adjs[MAXN];
	// int current[MAXN];

	int GL[MAXN];
	int Queue[MAXN];

	int N, M;
	scanf("%d%d", &N, &M);
	
	memset(adjs, -1, (N + 2) * sizeof(int));

	for (int i = 0; i < N; ++i)
	{
		int Ai, Bi;
		scanf("%d%d", &Ai, &Bi);

		// 0 -> i + 1, capacity: Ai
		edges[edgeno].v = i + 1;
		edges[edgeno].w = Ai;
		edges[edgeno].next = adjs[0];
		adjs[0] = edgeno;
		edgeno++;

		// i + 1 -> 0, capacity: 0
		edges[edgeno].v = 0;
		edges[edgeno].w = 0;
		edges[edgeno].next = adjs[i + 1];
		adjs[i + 1] = edgeno;
		edgeno++;

		// i + 1 -> N + 1, capacity: Bi
		edges[edgeno].v = N + 1;
		edges[edgeno].w = Bi;
		edges[edgeno].next = adjs[i + 1];
		adjs[i + 1] = edgeno;
		edgeno++;

		// N + 1 -> i + 1, capacity: 0
		edges[edgeno].v = i + 1;
		edges[edgeno].w = 0;
		edges[edgeno].next = adjs[N + 1];
		adjs[N + 1] = edgeno;
		edgeno++;
	}

	for (int i = 0; i < M; ++i)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);

			// a -> b, capacity: w
		edges[edgeno].v = b;
		edges[edgeno].w = w;
		edges[edgeno].next = adjs[a];
		adjs[a] = edgeno;
		edgeno++;

			// b -> a, capacity: w
		edges[edgeno].v = a;
		edges[edgeno].w = w;
		edges[edgeno].next = adjs[b];
		adjs[b] = edgeno;
		edgeno++;
	}

	assert(edgeno <= 2 * MAXN + 2 * MAXM + 2 * MAXN);

	// printf("[debug]edges(%d):\n", edgeno);
	// for (int i = 0; i < edgeno; ++i)
	// {
	// 	printf("i: %d, v: %d, w: %d, next: %d, reverse: %d\n", i, edges[i].v, edges[i].w, edges[i].next, edges[i].reverse);
	// }

	N += 2;
	const int source = 0, sink = N - 1;
	printf("%d\n", dinic(GL, Queue, adjs, edges, N, source, sink));

	return 0;
}
