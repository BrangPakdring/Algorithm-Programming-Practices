#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference: https://blog.csdn.net/morejarphone/article/details/51319373

	problem link:
	Find The Determinant III 
*/

const ll mod = 1e9 + 7;

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
