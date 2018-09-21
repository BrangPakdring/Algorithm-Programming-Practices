#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference: kuangbin's template
	edges' indeces are 0-based
	nodes' indeces are 1-based
	sccs' indeces are 1-based
	time complexity: O(V+E)

	problem link:
	Network of Schools 
*/

const ll maxn = 105;
const ll maxm = 10005;
struct Edge
{
	ll from, to, next;
}edge[maxm];
ll head[maxn], tot; // tot total edges added
ll low[maxn], dfn[maxn], stk[maxn];
ll belong[maxn]; // belong[i] the scc i belongs to
ll idx, top;
ll scc; // number of scc
bool inStack[maxn];
ll num[maxn]; // num[i] number of nodes i-th scc contains
 
void AddEdge(ll u, ll v)
{
	edge[tot].from = u;
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}
 
void Tarjan(ll u)
{
	ll v;
	low[u] = dfn[u] = ++idx;
	stk[top++] = u;
	inStack[u] = true;
	for (ll i = head[u]; i != -1; i = edge[i].next)
	{
		v = edge[i].to;
		if (!dfn[v])
		{
			Tarjan(v);
			if (low[u] > low[v])low[u] = low[v];
		}
		else if (inStack[v] && low[u] > low[v])
		{
			low[u] = dfn[v];
		}
	}
	if (low[u] == dfn[u])
	{
		++scc;
		do
		{
			v = stk[--top];
			inStack[v] = false;
			belong[v] = scc;
			++num[scc];
		} while (v != u);
	}
}
 
void CountSCC(ll n)
{
	memset(dfn, 0, sizeof dfn);
	memset(inStack, 0, sizeof inStack);
	memset(num, 0, sizeof num);
	idx = scc = top = 0;
	for (ll i = 1; i <= n; ++i)
		if (!dfn[i])
			Tarjan(i);
}
 
void Init()
{
	tot = 0;
	memset(head, -1, sizeof head);
}