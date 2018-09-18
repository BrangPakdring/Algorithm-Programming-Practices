#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* 
	reference: https://blog.csdn.net/qq_33199236/article/details/52151553 .
	Kruskal() returns the total weight of SBMST, or if not exists, a NoAnswerType value.
	skip a used edge stored in rec[]

	problem link:
	Is There A Second Way Left?
*/

constexpr ll maxn = 105;
constexpr ll maxm = 10005;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

enum NoAnswerType : ll
{
	NO_WAY = -1,
	NO_SECOND_WAY = -2,
};
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

WeightType Kruskal(ll n, ll m)
{
	WeightType ansMST = 0;
	ll k = 0;
	iota(f, f + n, 0);
	sort(edge, edge + m);
	for (ll i = 0; i < m; ++i)
	{
		ll x = F(edge[i].u), y = F(edge[i].v);
		if (x != y)
		{
			f[x] = y;
			ansMST += edge[i].w;
			rec[k] = i;
			++k;
		}
		if (k == n - 1)break;
	}
	if (k != n - 1)return NoAnswerType::NO_WAY;
	WeightType ansSBMST = inf;
	for (ll i = 0; i < k; ++i)
	{
		iota(f, f + n, 0);
		ll k2 = 0, ansTmp = 0;
		for (ll j = 0; j < m; ++j)
		{
			if (j == rec[i])continue;
			ll x = F(edge[j].u), y = F(edge[j].v);
			if (x != y)
			{
				f[x] = y;
				ansTmp += edge[j].w;
				++k2;
			}
			if (k2 == n - 1)break;
		}
		if (k2 == n - 1)
			ansSBMST = min(ansTmp, ansSBMST);
	}
	if (ansSBMST == inf)return NoAnswerType::NO_SECOND_WAY;
	else return ansSBMST;
}
