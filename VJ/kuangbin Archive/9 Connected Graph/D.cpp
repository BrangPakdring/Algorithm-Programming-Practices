#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define abs(x) ((x)>0?(x):-(x))

const ll maxn = 100000 + 5;
const ll maxm = 200000 * 2 + 5;
const ll maxq = 1005;

namespace LCA
{
	const ll maxn = ::maxn;
	const ll maxq = ::maxq;

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
	ll dep[maxn];
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

	void Tarjan(ll u, ll depth = 0)
	{
		dep[u] = depth;
		ancestor[u] = u;
		vis[u] = true;
		for (ll i = head[u]; i != -1; i = edge[i].next)
		{
			ll v = edge[i].to;
			if (vis[v])continue;
			Tarjan(v, depth + 1);
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
}

namespace Cuts
{
	const ll maxn = ::maxn;
	const ll maxm = ::maxm;
	struct Edge
	{
		ll from, to, next;
		bool cut; // is cut edge
	}edge[maxm];
	ll head[maxn], tot; // tot total edges added
	ll low[maxn], dfn[maxn], stk[maxn];
	ll belong[maxn]; // belong[i] the scc node i belongs to
	ll idx, top;
	bool inStack[maxn];
	bool cut[maxn]; // is cut vertex
	ll addBlock[maxn]; // addBlock[i] number of connected components increased after deleting vertex i
	ll bridge;
	ll scc;
	 
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
			else if (/*inStack[v] && *//*low[u] > dfn[v]*/inStack[v] && low[u] > low[v])
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
			} while (v != u);
		}
		// cut vertex: u is the root with more than one branch
		if (u == pre && son > 1)cut[u] = true;
		if (u == pre)addBlock[u] = son - 1;
	//	inStack[u] = false;
	//	--top;
	}

	void FindCut(ll n)
	{
		for (ll i = 1; i <= n; ++i)
			if (!dfn[i])
				Tarjan(i, i);
	}
	 
	void Init()
	{
		memset(dfn, 0, sizeof dfn);
		memset(inStack, 0, sizeof inStack);
		memset(cut, 0, sizeof cut);
		memset(addBlock, 0, sizeof addBlock);
		memset(head, -1, sizeof head);
		idx = top = bridge = scc = tot = 0;
	}
}

namespace Graph
{
	const ll maxn = ::maxn;
	struct Edge
	{
		ll from, to, next;
	}edge[maxn << 1];
}

ll n, m;
ll cas, a, b, q;

int main(int argc, char const *argv[])
{
//	speedup;
	while (scanf("%lli%lli", &n, &m) != EOF)
	{
		LCA::Init();
		Cuts::Init();
		for (ll i = 0; i < m; ++i)
		{
			scanf("%lli%lli", &a, &b);
			Cuts::AddEdge(a, b);
			Cuts::AddEdge(b, a);
		}
		Cuts::FindCut(n);
//		fprintf(stderr, "scc=%lli\n", Cuts::scc);
//		for (ll i = 1; i <= n; ++i)
//		{
//			fprintf(stderr, "belong[%lli]=%lli\n", i, Cuts::belong[i]);
//		}
		for (ll u = 1; u <= n; ++u)
		{
			for (ll i = Cuts::head[u]; i != -1; i = Cuts::edge[i].next)
			{
				ll v = Cuts::edge[i].to;
				ll nu = Cuts::belong[u], nv = Cuts::belong[v];
				if (nu == nv)continue;
				LCA::AddEdge(nu, nv);
				LCA::AddEdge(nv, nu);
			}
		}
		scanf("%lli", &q);
		ll a[q], b[q];

		for (ll i = 0; i < q; ++i)
		{
			scanf("%lli%lli", a + i, b + i);
			a[i] = Cuts::belong[a[i]];
			b[i] = Cuts::belong[b[i]];
//			fprintf(stderr, "a[%lli]=%lli\tb[%lli]=%lli\n", i,a[i],i,b[i]);
			LCA::AddQuery(a[i], b[i], i);
		}
		LCA::Tarjan(1);
		ll bridge = Cuts::bridge;
		printf("Case %lli:\n", ++cas);
		for (ll i = 0; i < q; ++i)
		{
//			fprintf(stderr, "ans[%lli]=%lli\n", i,LCA::ans[i]);
//			fprintf(stderr, "dep[%lli]=%lli\tdep[%lli]=%lli\n\tdep[ans]=%lli\n", a[i], LCA::dep[a[i]], b[i], LCA::dep[b[i]], LCA::dep[LCA::ans[i]]);
			if (LCA::ans[i] == a[i] || LCA::ans[i] == b[i])
			{
				printf("%lli\n", bridge - abs(LCA::dep[a[i]] - LCA::dep[b[i]]));
			}
			else
			{
				printf("%lli\n", bridge - (LCA::dep[LCA::ans[i]] * 2 - LCA::dep[a[i]] - LCA::dep[b[i]]));
			}
		}
		puts("");
	}
	return 0;
}
