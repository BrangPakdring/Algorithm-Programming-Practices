#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll inf = 0x3f3f3f3f3f3f3f3f;
const ll maxn = 105;
const ll maxm = 10005;
ll n, m;
struct Edge
{
	ll u, v, w;
	bool vis;
}e[maxm];
vector<ll>G[maxn];
ll f[maxn];
ll maxd[maxn][maxn];

ll F(ll x)
{
	return x == f[x] ? x : f[x] = F(f[x]);
}

ll Kruskal()
{
	sort(e, e + m, [](Edge&a, Edge&b){ return a.w < b.w; });
	for (ll i = 0; i <= n; ++i)
	{
		G[i] = { i };
		f[i] = i;
	}
	ll sum = 0, k = 0;
	for (ll i = 0; i < m; ++i)
	{
		if (k == n - 1)break;
		ll x1 = F(e[i].u), x2 = F(e[i].v);
		if (x1 != x2)
		{
			++k;
			e[i].vis = true;
			sum += e[i].w;
			for (ll j = 0; j < G[x1].size(); ++j)
				for (ll k = 0; k < G[x2].size(); ++k)
					maxd[G[x1][j]][G[x2][k]] = maxd[G[x2][k]][G[x1][j]] = e[i].w;
			f[x1] = x2;
			auto temp = G[x1];
			G[x1].insert(G[x1].end(), G[x2].begin(), G[x2].end());
			G[x2].insert(G[x2].end(), temp.begin(), temp.end());
		}
	}
	ll secondSum = inf;
	for (ll i = 0; i < m; ++i)
		if (!e[i].vis)
			secondSum = min(secondSum, sum + e[i].w - maxd[e[i].u][e[i].v]);
	if (secondSum > sum)return sum;
	else return -1;
}

namespace POJ_1679
{
	int main()
	{
		ll T; cin >> T;
		while (T--)
		{
			cin >> n >> m;
			for (ll i = 0; i < m; ++i)
			{
				cin >> e[i].u >> e[i].v >> e[i].w;
				e[i].vis = false;
			}
			ll ans = Kruskal();
			if (ans == -1)cout << "Not Unique!" << endl;
			else cout << ans << endl;
		}
		return 0;
	}
}

namespace OpenJ_Bailian_1679 = POJ_1679;

int main()
{
	return 0;
}