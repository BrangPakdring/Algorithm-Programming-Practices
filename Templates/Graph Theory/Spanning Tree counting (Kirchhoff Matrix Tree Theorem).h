#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* 
	reference: 

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

	Matrix()
	{
		this->Init();
	}

	void Init()
	{
		memset(mat, 0, sizeof mat);
	}

	ll Determinant(ll n)
	{
		ll res = 1;
		for (ll i = 0; i < n; ++i)
		{
			if (mat[i][i] == 0)
			{
				bool flag = false;
				for (ll j = i + 1; j < n; ++j)
				{
					if (mat[j][i])
					{
						flag = true;
						for (ll k = i; k < n; ++k)
						{
							swap(mat[i][k], mat[j][k]);
						}
						res = -res;
						break;
					}
				}
				if (flag == false)
				{
					return 0;
				}
			}

			for (ll j = i + 1; j < n; ++j)
			{
				while (mat[j][i])
				{
					ll t = mat[i][i] / mat[j][i];
					for (ll k = i; k < n; ++k)
					{
						mat[i][k] = (mat[i][k] - t * mat[j][k]) % mod;
						swap(mat[i][k], mat[j][k]);
					}
					res = -res;
				}
			}
			res *= mat[i][i];
			res %= mod;
		}
		return (res + mod) % mod;
	}
};

ll CountingSpanningTrees(ll G[maxn][maxn], ll n)
{
	Matrix A;
	for (ll i = 0; i < n; ++i)
		for (ll j = 0; j < n; ++j)
		{
			if (i == j)continue;
			if (G[i][j])
			{
				++A.mat[i][i];
				A.mat[i][j] = -1;
			}
		}

	for (ll i = 0; i < n; ++i)
		for (ll j = 0; j < n; ++j)
			A.mat[i][j] = (A.mat[i][j] % mod + mod) % mod;

	return A.Determinant(n - 1);
}