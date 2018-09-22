#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference: kuangbin's template

	problem link:

*/

const ll maxn = 105;
const ll maxm = 100005;
struct Edge
{
	ll from, to, next;
	bool cut; // is cut edge
}edge[maxm];
ll head[maxn], tot; // tot total edges added
ll low[maxn], dfn[maxn], stk[maxn];
ll idx, top;
bool inStack[maxn];
bool cut[maxn]; // is cut vertex
ll addBlock[maxn]; // addBlock[i] number of connected components increased after deleting vertex i
ll bridge;
 
void AddEdge(ll u, ll v)
{
	edge[tot].from = u;
	edge[tot].to = v;
	edge[tot].next = head[u];
	edge[tot].cut = false;
	head[u] = tot++;
}
 
void Tarjan(ll u, ll pre)
{
	ll v;
	low[u] = dfn[u] = ++idx;
	stk[top++] = u;
	inStack[u] = true;
	ll son = 0;
	ll preCnt = 0; // deal with multiple edges
	for (ll i = head[u]; i != -1; i = edge[i].next)
	{
		v = edge[i].to;
		if (v == pre && preCnt == 0)
		{
			++preCnt;
			continue;
		}
		if (!dfn[v])
		{
			++son;
			Tarjan(v, u);
			if (low[u] > low[v])low[u] = low[v];
			// cut edge
			if (low[v] > dfn[u])
			{
				++bridge;
				edge[i].cut = true;
				edge[i ^ 1].cut = true;
			}
			// cut vertex: u is not a root and u -> v st dfn[u] <= low[v]
			if (u != pre && low[v] >= dfn[u])
			{
				cut[u] = true;
				++addBlock[u];
			}
		}
		else if (low[u] > dfn[v])
		{
			low[u] = dfn[v];
		}
	}
	// cut vertex: u is the root with more than one branch
	if (u == pre && son > 1)cut[u] = true;
	if (u == pre)addBlock[u] = son - 1;
	inStack[u] = false;
	--top;
}

void FindCut(ll n)
{
	memset(dfn, 0, sizeof dfn);
	memset(inStack, 0, sizeof inStack);
	memset(cut, 0, sizeof cut);
	memset(addBlock, 0, sizeof addBlock);
	idx = top = bridge = 0;
	for (ll i = 1; i <= n; ++i)
		if (!dfn[i])
			Tarjan(i, i);
}
 
void Init()
{
	tot = 0;
	memset(head, -1, sizeof head);
}