//poj1149 
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

const int MAXN = 100 + 2;
const int MAXM = 1000;
const int INF = numeric_limits<int>::max();

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

	return GL[sink] > 0;
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

		maxflow += DFS(source, INF, GL, adjs, edges, sink);
	}

	return maxflow;
}

void addEdge(Edge edges[], int &edgeno, int adjs[], int u, int v, int w)
{
	// u -> v, capacity: w
	edges[edgeno].v = v;
	edges[edgeno].w = w;
	edges[edgeno].next = adjs[u];
	adjs[u] = edgeno;
	edgeno++;

	// v -> u, capacity: 0
	edges[edgeno].v = u;
	edges[edgeno].w = 0;
	edges[edgeno].next = adjs[v];
	adjs[v] = edgeno;
	edgeno++;
}


// see http://ycool.com/post/zhhrrm6 for how to construct network
int main()
{
	Edge edges[100000];	
	int edgeno = 0;

	int adjs[MAXN];

	int GL[MAXN];
	int Queue[MAXN];

	int M, N;
	scanf("%d%d", &M, &N);
	
	memset(adjs, -1, (N + 2) * sizeof(int));

	int pighouses[MAXM], customer[MAXM];

	for (int i = 0; i < M; ++i)
	{
		scanf("%d", &pighouses[i]);
		customer[i] = -1;
	}

	const int source = 0, sink = N + 1;
	for (int i = 1; i <= N; ++i)
	{
		int A, K, B;
		scanf("%d", &A);
		for (int j = 0; j < A; ++j)
		{
			scanf("%d", &K);
			K--;

			// if customer i is the first customer that has key to pig house K
			// then draw a line from source to i with capacity of pig house K
			if (customer[K] < 0)
			{
				addEdge(edges, edgeno, adjs, source, i, pighouses[K]);
			}
			// else draw a line from customer[K] to customer i with unlimited capacity
			else
			{
				int u = customer[K];
				addEdge(edges, edgeno, adjs, u, i, INF);
			}
			customer[K] = i;
		}
		scanf("%d", &B);
		// add edges from i to sink
		addEdge(edges, edgeno, adjs, i, sink, B);
	}

	// assert(edgeno <= MAXN + MAXN - 1 + MAXN);

	// printf("[debug]edges(%d):\n", edgeno);
	// for (int i = 0; i < edgeno; ++i)
	// {
	// 	printf("i: %d, v: %d, w: %d, next: %d, reverse: %d\n", i, edges[i].v, edges[i].w, edges[i].next, i ^ 1);
	// }

	N += 2;
	printf("%d\n", dinic(GL, Queue, adjs, edges, N, source, sink));

	return 0;
}
