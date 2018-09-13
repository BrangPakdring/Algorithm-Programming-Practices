#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr ll maxn = 105;
constexpr ll maxm = 10005 * 10;
struct Edge
{
	ll a, b, c;
}edge[maxm];
ll N, M;

using WeightType = ll;
bool vis[maxn];
ll pre[maxn];
bool used[maxn][maxn];
WeightType lowc[maxn];
WeightType mx[maxn][maxn];
WeightType cost[maxn][maxn];

WeightType Prim(WeightType cost[][maxn], ll n)
{
	WeightType ans = 0;
	memset(vis, false, sizeof vis);
	memset(mx, 0, sizeof mx);
	memset(used, false, sizeof used);
	vis[0] = true;
	pre[0] = -1;
	for (ll i = 1; i < n; ++i)
	{
		lowc[i] = cost[0][i];
		pre[i] = 0;
	}
	lowc[0] = 0;
	for (ll i = 1; i < n; ++i)
	{
		WeightType minc = inf;
		ll p = -1;
		for (ll j = 0; j < n; ++j)
		{
			if (!vis[j] && minc > lowc[j])
			{
				minc = lowc[j];
				p = j;
			}
		}
		if (minc == inf)return -1;
		ans += minc;
		vis[p] = true;
		used[p][pre[p]] = used[pre[p]][p] = true;
		for (ll j = 0; j < n; ++j)
		{
			if (vis[j] && j != p)
				mx[j][p] = mx[p][j] = max(mx[j][pre[p]], lowc[p]);
			if (!vis[j] && lowc[j] > cost[p][j])
			{
				lowc[j] = cost[p][j];
				pre[j] = p;
			}
		}
	}
	return ans;
}

int main(int argc, char const *argv[])
{
	speedup;

	ll T; cin >> T;
	while (T--)
	{
		cin >> N >> M;
		memset(cost, 0x3f, sizeof cost);
		for (ll i = 0; i < M; ++i)
		{
			auto&c = edge[i];
			cin >> c.a >> c.b >> c.c;
			--c.a, --c.b;
			cost[c.a][c.b] = cost[c.b][c.a] = min(cost[c.a][c.b], c.c);
		}
		auto dis = Prim(cost, N);
		decltype(dis)dis2 = inf;
		for (ll i = 0; i < N; ++i)
			for (ll j = i + 1; j < N; ++j)
				if (!used[i][j])
					dis2 = min(dis2, dis + cost[i][j] - mx[i][j]);

		cout << dis << ' ' << dis2 << endl;
	}

	return 0;
}
