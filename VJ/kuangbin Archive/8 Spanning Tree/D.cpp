#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

constexpr ll maxn = 105;
constexpr ll maxm = 205;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

using WeightType = ll;
struct Edge
{
	ll u, v;
	WeightType w;
	bool operator<(const Edge&rhs)const
	{
		return w < rhs.w;
	}
}edge[maxn];
ll v, e;
ll f[maxn];
ll rec[maxn];

ll F(ll x)
{
	return x == f[x] ? x : f[x] = F(f[x]);
}

ll Kruskal(ll n, ll m)
{
	ll ans = 0;
	ll k = 0;
	iota(f, f + n, 0);
	sort(edge, edge + m);
	for (ll i = 0; i < m; ++i)
	{
		ll x = F(edge[i].u), y = F(edge[i].v);
		if (x != y)
		{
			f[x] = y;
			ans += edge[i].w;
			rec[k] = i;
			++k;
		}
		if (k == n - 1)break;
	}
	if (k != n - 1)return -1;
	ans = inf;
	for (ll i = 0; i < k; ++i)
	{
		iota(f, f + n, 0);
		ll k2 = 0, ans2 = 0;
		for (ll j = 0; j < m; ++j)
		{
			if (j == rec[i])continue;
			ll x = F(edge[j].u), y = F(edge[j].v);
			if (x != y)
			{
				f[x] = y;
				ans2 += edge[j].w;
				++k2;
			}
			if (k2 == n - 1)break;
		}
		if (k2 == n - 1)
			ans = min(ans2, ans);
	}
	if (ans == inf)return -2;
	else return ans;
}

ll cas;

int main(int argc, char const *argv[])
{
	speedup;

	ll t; cin >> t;
	while (t--)
	{
		cout << "Case #" << ++cas << " : ";
		cin >> v >> e;
		for (ll i = 0; i < e; ++i)
		{
			auto&e = edge[i];
			cin >> e.u >> e.v >> e.w;
			--e.u, --e.v;
		}
		ll ans = Kruskal(v, e);
		if (ans == -1)cout << "No way";
		else if (ans == -2)cout << "No second way";
		else cout << ans;
		cout << endl;
	}

	return 0;
}