#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

using WeightType = ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const ll maxn = 1005;
const ll maxm = 40005;
struct Edge
{
	ll u, v;
	WeightType w;
}edge[maxm];
ll pre[maxn], id[maxn], vis[maxn];
WeightType in[maxn];

WeightType ChuLiu(ll root, ll n, ll m, Edge edge[])
{
	WeightType res = 0;
	ll u, v;
	while (true)
	{
		for (ll i = 0; i < n; ++i)in[i] = inf;
		for (ll i = 0; i < m; ++i)
		{
			if (edge[i].u != edge[i].v && edge[i].w < in[edge[i].v])
			{
				pre[edge[i].v] = edge[i].u;
				in[edge[i].v] = edge[i].w;
			}
		}
		for (ll i = 0; i < n; ++i)
			if (i != root && in[i] == inf)
				return -1;
		ll tn = 0;
		memset(id, -1, sizeof id);
		memset(vis, -1, sizeof vis);
		in[root] = 0;
		for (ll i = 0; i < n; ++i)
		{
			res += in[i];
			v = i;
			while (vis[v] != i && id[v] == -1 && v != root)
			{
				vis[v] = i;
				v = pre[v];
			}
			if (v != root && id[v] == -1)
			{
				for (ll u  = pre[v]; u != v; u = pre[u])
					id[u] = tn;
				id[v] = tn++;
			}
		}
		if (tn == 0)break;
		for (ll i = 0; i < n; ++i)
			if (id[i] == -1)
				id[i] = tn++;
		for (ll i = 0; i < m;)
		{
			v = edge[i].v;
			edge[i].u = id[edge[i].u];
			edge[i].v = id[edge[i].v];
			if (edge[i].u != edge[i].v)
				edge[i++].w -= in[v];
			else
				swap(edge[i], edge[--m]);
		}
		n = tn;
		root = id[root];
	}
	return res;
}

ll n, m;

int main(int argc, char const *argv[])
{
	speedup;
	ll N; cin >> N;
	for (ll cas = 1; cas <= N; ++cas)
	{
		cin >> n >> m;
		for (ll i = 0; i < m; ++i)
		{
			ll u, v, w; cin >> u >> v >> w;
			edge[i] = { u, v, w };
		}
		ll ans = ChuLiu(0, n, m, edge);
		cout << "Case #" << cas << ": ";
		if (ans == -1)cout << "Possums!" << endl;
		else cout << ans << endl;

	}
	return 0;
}