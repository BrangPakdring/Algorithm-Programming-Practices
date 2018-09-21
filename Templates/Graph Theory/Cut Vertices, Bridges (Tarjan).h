#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll maxn = 105;
const ll maxm = 100005;
struct Edge
{
	ll from, to, next;
	bool cut;
}edge[maxm];
ll head[maxn], tot; // tot total edges added
ll low[maxn], dfn[maxn], stk[maxn];
ll idx, top;
bool inStack[maxn];
bool cut[maxn];
ll addBlock[maxn];
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
	ll preCnt = 0;
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
			if (low[v] > dfn[u])
			{
				++bridge;
				edge[i].cut = true;
				edge[i ^ 1].cut = true;
			}
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