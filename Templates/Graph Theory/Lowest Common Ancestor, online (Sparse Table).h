#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference: kuangbin's template

	problem link:
*/

const ll maxn = 10005;
ll rmq[maxn << 1];

namespace ST
{
	ll mm[maxn << 1];
	ll d[maxn << 1][20]; // 

	void Init(ll n)
	{
		mm[0] = -1;
		for (ll i = 1; i <= n; ++i)
		{
			mm[i] = (i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1];
			d[i][0] = i;
		}
		for (ll j = 1; j <= mm[n]; ++j)
		{
			for (ll i = 1; i + (1 << j) - 1  <= n; ++i)
				d[i][j] = rmq[d[i][j - 1]] < rmq[d[i + (1 << (j - 1))]][j - 1] ? d[i][j - 1] : d[i + (1 << (j - 1))][j - 1];
		}
	}

	ll Query(ll a, ll b) // [a, b]
	{
		if
	}
}