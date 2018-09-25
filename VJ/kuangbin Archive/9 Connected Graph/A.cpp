#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
 
const ll maxn = 105;
const ll maxm = 10005;
struct Edge
{
	ll from, to, next;
}edge[maxm];
ll head[maxn], tot;
ll low[maxn], dfn[maxn], stk[maxn], belong[maxn];
ll idx, top;
ll scc;
bool inStack[maxn];
ll num[maxn];
ll indeg[maxn], outdeg[maxn];
 
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
 
ll n;

int main()
{
	Init();
	cin >> n;
	for (ll i = 1; i <= n; ++i)
	{
		ll v;
		while (cin >> v, v)
		{
			AddEdge(i, v);
		}
	}
	CountSCC(n);
	if (scc == 1)
	{
		cout << "1\n0";
		return 0;
	}
/*	for (ll i = 1; i <= n; ++i)
	{
		fprintf(stderr, "belong[%lli]=%lli\n", i,belong[i]);
	}*/
	ll a = 0, b = 0;
	for (ll i = 0; i < tot; ++i)
	{
		ll u = edge[i].from, v = edge[i].to;
		if (belong[u] != belong[v])
			++indeg[belong[v]], ++outdeg[belong[u]];
	}
	for (ll i = 1; i <= scc; ++i)
	{
		fprintf(stderr, "indeg[%lli]=%lli, outdeg[%lli]=%lli\n", i,indeg[i],i,outdeg[i]);
		if (!indeg[i])++a;
		if (!outdeg[i])++b;
	}
	
	cout << a << '\n' << max(a, b);
}