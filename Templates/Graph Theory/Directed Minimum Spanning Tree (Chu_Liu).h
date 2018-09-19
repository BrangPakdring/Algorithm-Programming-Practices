#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* 
	reference: kuangbin's template.
	ChuLiu() returns the total weight of Directed MST.
	O(mn)

	problem link:
	Command Network
*/

using WeightType = ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const ll maxn = 105;
const ll maxm = 1e4 + 5;
struct Edge
{
	ll u, v;
	WeightType w;
}edge[maxm];
ll pre[maxn]; // pre[i] parent of i
ll id[maxn]; // id[i] index of a cycle node i is in
ll vis[maxn]; 
WeightType in[maxn]; // in[i] minimum weight of edges end at i
ll pos; // find root if not assigned

WeightType ChuLiu(ll root, ll n, ll m, Edge edge[])
{
	WeightType res = 0;
	ll u, v;
	while (true)
	{
		// step 1: find minimum incoming edge of each edge
		for (ll i = 0; i < n; ++i)in[i] = inf;
		for (ll i = 0; i < m; ++i)
		{
			auto&e = edge[i];
			if (e.u != e.v && e.w < in[e.v])
			{
				pre[e.v] = e.u; // u -> v
				in[e.v] = e.w;
				if (e.u == root)
					pos = i;
			}
		}
		for (ll i = 0; i < n; ++i)
			if (i != root && in[i] == inf)
				return -1; // another node without incoming edge

		// step 2: find circuits
		ll tn = 0; // sum of circuits in current search
		memset(id, -1, sizeof id);
		memset(vis, -1, sizeof vis);
		in[root] = 0;
		for (ll i = 0; i < n; ++i)
		{
			res += in[i];
			v = i;
			// while loop finds circuits:
			// vis[v] == i: found same flag in current search
			// id[v] != -1: node belongs to another cycle
			// v == root: found root
			while (vis[v] != i && id[v] == -1 && v != root)
			{
				vis[v] = i;
				v = pre[v];
			}
			// circuit found, constraction
			if (v != root && id[v] == -1)
			{
				for (ll u = pre[v]; u != v; u = pre[u])
					id[u] = tn; // u belongs to tn-th circuit
				id[v] = tn++;
			}
		}
		if (tn == 0)break; // no more circuit found
		for (ll i = 0; i < n; ++i) // nodes not in circuits
			if (id[i] == -1)
				id[i] = tn++;

		// step 3: build new graph, constraction, remarks
		for (ll i = 0; i < m; ++i)
		{
			v = edge[i].v;
			edge[i].u = id[edge[i].u];
			edge[i].v = id[edge[i].v];
			// u and v are not in a same cycle
			if (edge[i].u != edge[i].v)
				edge[i].w -= in[v];
		}
		n = tn;
		root = id[root];
	}
	return res;
}
