#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* 
	reference: kuangbin's template.

	problem link:
*/

const ll maxn = 105;
const ll mod = 10007;
ll inv[mod];

ll Inverse(ll a, ll m)
{
	if (a == 1)return 1;
	return Inverse(m % a, m) * (m - m / a) % m;
}

struct Matrix
{
	ll mat[maxn][maxn];

	void Init()
	{
		memset(mat, 0, sizeof mat);
	}

	ll Determinant(ll n)
	{
		for (ll i = 0; i < n; ++i)
			for (ll j = 0; j < n; ++j)
				mat[i][j] = (mat[i][j] % mod + mod) % mod;
		ll res = 1;
		for (ll i = 0; i < n; ++i)
		{
			for (ll j = i; j < n; ++j)
			{
				if (mat[j][i] != 0)
				{
					for (ll k = i; k < n; ++k)
						swap(mat[i][k], mat[j][k]);
					if (i != j)
						res = (-res + mod) % mod;
					break;
				}					
			}
			if (mat[i][i] == 0)
			{
				res = -1;
				break;
			}
			for (ll j = i + 1; j < n; ++j)
			{
				ll mut = mat[j][i] * Inverse(mat[i][i], mod) % mod;
				for (ll k = 1; k < n; ++k)
				{
					mat[j][k] = (mat[j][k] - mat[i][k] * mut % mod + mod) % mod;
				}
			}
			res = res * mat[i][i] % mod;
		}
		return res;
	}
};