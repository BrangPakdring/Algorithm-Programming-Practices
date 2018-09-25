#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
 
const ll maxn = 5005;
const ll maxm = 20005;
struct Edge
{
	ll from, to, next;
	bool cut; // is cut edge
}edge[maxm];
ll head[maxn], tot; // tot total edges added
ll low[maxn], dfn[maxn], stk[maxn];
ll belong[maxn];
ll idx, top;
ll block;
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
		else if (inStack[v] && low[u] > dfn[v])
		{
			low[u] = dfn[v];
		}
	}
	// cut vertex: u is the root with more than one branch
	if (low[u] == dfn[u])
	{
		++block;
		do
		{
			v = stk[--top];
			inStack[v] = false;
			belong[v] = block;
		} while (v != u);
	}
	if (u == pre && son > 1)cut[u] = true;
	if (u == pre)addBlock[u] = son - 1;
//	inStack[u] = false;
//	--top;
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

ll f, r;
ll ans;
ll deg[maxn];

int main(int argc, char const *argv[])
{
	speedup;
	cin >> f >> r;
	Init();
	for (ll i = 0; i < r; ++i)
	{
		ll u, v; cin >> u >> v;
//		--u, --v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	FindCut(f);
//	printf("bridge=%lli\n", bridge);
	for (ll u = 1; u <= f; ++u)
	{
		for (ll i = head[u]; i != -1; i = edge[i].next)
		{
			if (edge[i].cut)
				++deg[belong[u]];
		}
	}
	for (ll i = 1; i <= block; ++i)
	{
		if (deg[i] == 1)++ans;
	}
	cout << ++ans / 2 << endl;
	return 0;
}