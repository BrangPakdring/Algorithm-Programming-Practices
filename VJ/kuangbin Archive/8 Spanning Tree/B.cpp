#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

using WeightType = double;
constexpr ll maxn = 1005, maxm = 1000005;
constexpr double eps = 1e-6;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
ll n;
ll m;
struct Point
{
	ll x, y, p;
}p[maxn];
bool vis[maxn];
WeightType lowc[maxn];
ll pre[maxn];
WeightType mx[maxn][maxn];
bool used[maxn][maxn];
WeightType cost[maxn][maxn];

double Dis(Point&i, Point&j)
{
	return hypot(i.x - j.x, i.y - j.y);
}

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

	cout << fixed << setprecision(2);
	ll t; cin >> t;
	while (t--)
	{
		cin >> n;
		for (ll i = 0; i < n; ++i)
		{
			cin >> p[i].x >> p[i].y >> p[i].p;
		}
		for (ll i = 0; i < n; ++i)
			for (ll j = i + 1; j < n; ++j)
				cost[i][j] = cost[j][i] = Dis(p[i], p[j]);
		double dis = Prim(cost, n);
		double ans = 0;
		for (ll i = 0; i < n; ++i)
		{
			for (ll j = i + 1; j < n; ++j)
			{
				if (used[i][j])
				{
					ans = max(ans, (p[i].p + p[j].p) / (dis - cost[i][j]));
				}
				else
				{
					ans = max(ans, (p[i].p + p[j].p) / (dis - mx[i][j]));
				}
			}
		}
		cout << ans << endl;
	}

	return 0;
}
