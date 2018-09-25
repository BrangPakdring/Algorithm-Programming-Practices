#include <bits/stdc++.h>
using namespace std;
typedef long ll;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 1e5 + 5;
const ll maxm = 2e5 + 5;
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
ll addBlock[maxn]; // addBlock[i] number of connected components increased by after deleting vertex i
ll bridge;
ll scc; // number of scc
ll num[maxn]; // num[i] number of nodes scc i contains
ll belong[maxn]; // belong[i] the scc node i belongs to

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
	// cut vertex: u is the root with more than one branch
	if (u == pre && son > 1)cut[u] = true;
	if (u == pre)addBlock[u] = son - 1;
	inStack[u] = false;
	--top;
}

void FindCutCountSCC(ll n)
{
	memset(dfn, 0, sizeof dfn);
	memset(inStack, 0, sizeof inStack);
	memset(cut, 0, sizeof cut);
	memset(addBlock, 0, sizeof addBlock);
	idx = top = bridge = top = 0;
	for (ll i = 1; i <= n; ++i)
		if (!dfn[i])
			Tarjan(i, i);
}
 
void Init()
{
	tot = 0;
	memset(head, -1, sizeof head);
}

ll n, m;

int main(int argc, char const *argv[])
{
	speedup;
	while (cin >> n >> m, n)
	{
		for (ll i = 1; i <= m; ++i)
		{
			ll a, b; cin >> a >> b;
			AddEdge(a, b);
			AddEdge(b, a);
		}
		FindCutCountSCC(n);
		ll q; cin >> q;
		for (ll i = 1; i <= q; ++i)
		{
			ll a, b; cin >> a >> b;
			ll e = head[a];
		}
	}
	return 0;
}