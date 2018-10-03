#ifndef ONLINE_JUDGE
	#define frein freopen("in.txt", "r", stdin)
	#define freout freopen("out.txt", "w+", stdout)
	#define fre frein; freout
	#define shuchu(a) cerr << #a << "\t= " << a << endl
	#define pause getchar()
#else
	#define frein 0
	#define freout 0
	#define fre 0
	#define shuchu(a) 0
	#define pause 0
#endif
#define MST(a, b) memset(a, b, sizeof a)
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace Table
{
	const ll maxn = 1000;
	ll gay[maxn] = {};
	int main()
	{
		memset(gay, -1, sizeof (gay));

		for (ll k = 1; k < maxn; ++k)
		{
			for (ll x = 2; x < maxn; ++x)
			{
				ll i = k * x * x;
				if (i >= maxn)continue;
				gay[i] = 0;
			}
		}
		for (ll i = 1; i < maxn; ++i)
			if (gay[i] == -1)gay[i] = i * i;
		for (ll i = 1; i < maxn; ++i)
		{
			printf("gay[%lld] = %lld\n", i, gay[i]);
		}

		for (ll n = 1; n <= 100; ++n)
		{
			ll res = 0;
			for (ll num = 1; num <= n; ++num)
			{
				for (ll i = 1; i <= num; ++i)
				{
					res += gay[i];
				}
			}
			printf("ans[%lld] = %lld\n", n, res);
		}

		return 0;
	}
}

int main(int argc, char const *argv[])
{
	Table::main();
	speedup;
	pause;
	return 0;
}
