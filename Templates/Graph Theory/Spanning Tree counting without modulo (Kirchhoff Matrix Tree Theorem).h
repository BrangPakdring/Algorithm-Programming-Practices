#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* 
	reference: kuangbin's template

	problem link:
*/

const ll maxn = 105;
const double eps = 1e-8;

ll Sgn(double x)
{
	return x > eps ? 1
		: x < -eps ? -1
		: 0;
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

	double Determinant(ll n)
	{
		ll i, j, k, sign = 0;
		auto&a = mat;
		decltype(mat)b = {};
		double ret = 1;
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				b[i][j] = a[i][j];
		for (i = 0; i < n; ++i)
		{
			if (Sgn(b[i][i]) == 0)
			{
				for (j = i + 1; j < n; ++j)
					if (Sgn(b[j][i]) != 0)
						break;
				if (j == n)return 0;
				for (k = i; k < n; ++k)
					swap(b[i][k], b[j][k]);
				++sign;
			}
			ret *= b[i][i];
			for (k = i + 1; k < n; ++k)
				b[i][k] /= b[i][i];
			for (j = i + 1; j < n; ++j)
				for (k = i + 1; k < n; ++k)
					b[j][k] -= b[j][i] * b[i][k];
		}
		if (sign & 1)ret = -ret;
		return ret;
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

	return A.Determinant(n - 1);
}