#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference: kuangbin's template
	edges' indices are 0-based
	nodes' indices are 1-based
	sccs' indices are 1-based
	time complexity: O(V+Q)

	problem link:
*/

const ll maxn = 1005;
const ll maxq = 500005;

ll f[maxn];

ll Find(ll x)
{
	if (f[x] == -1)return x;
	return f[x] = Find(f[x]);
}

void Merge(ll u, ll v)
{
	ll x = Find(u);
	ll y = Find(v);
	if (x != y)
		f[x] = y;
}

bool vis[maxn];
ll ancestor[maxn];
struct Edge
{
	ll from, to, next;
}edge[maxn << 1];
ll head[maxn], tot;

void AddEdge(ll u, ll v)
{
	edge[tot].from = u;
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
	++tot;
}

struct Query
{
	ll q, next;
	ll index;
}query[maxq << 1];
ll ans[maxq]; // 0-based
ll headQuery[maxq];
ll totQuery;
ll Q;

void AddQuery(ll u, ll v, ll index)
{
	query[totQuery].q = v;
	query[totQuery].next = headQuery[u];
	query[totQuery].index = index;
	headQuery[u] = totQuery++;
	query[totQuery].q = u;
	query[totQuery].next = headQuery[v];
	query[totQuery].index = index;
	headQuery[v] = totQuery++;
}

void Init()
{
	tot = 0;
	memset(head, -1, sizeof head);
	totQuery = 0;
	memset(headQuery, -1, sizeof headQuery);
	memset(vis, 0, sizeof vis);
	memset(f, -1, sizeof f);
	memset(ancestor, 0, sizeof ancestor);
}

void Tarjan(ll u)
{
	ancestor[u] = u;
	vis[u] = true;
	for (ll i = head[u]; i != -1; i = edge[i].next)
	{
		ll v = edge[i].to;
		if (vis[v])continue;
		Tarjan(v);
		Merge(u, v);
		ancestor[Find(u)] = u;
	}
	for (ll i = headQuery[u]; i != -1; i = query[i].next)
	{
		ll v = query[i].q;
		if (vis[v])
			ans[query[i].index] = ancestor[Find(v)];
	}
}

bool flag[maxn];
ll cntNum[maxn];

