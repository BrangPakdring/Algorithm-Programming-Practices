/* 
	revised from kuangbin's template.
	Prim() returns the total weight of MST.
	after calling Prim(), search for SBMST.
	mx[i][j] gives the maximum weight of an edge from i to j.

	Note:
	Qin Shi Huang's National Road System
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
