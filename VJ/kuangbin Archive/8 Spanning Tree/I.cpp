#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define double long double

struct Matrix;

const ll maxn = 55, maxm = 55, maxk = 1505;
const ll mod = INT64_MAX;
ll n, m, k;
const double eps = 1e-8;

ll Sgn(double x)
{
	return x > eps ? 1
		: x < -eps ? -1
		: 0;
}

struct Matrix
{
	double mat[maxn][maxn];

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

double CountingSpanningTrees(double G[maxn][maxn], ll n)
{
	Matrix A;
	for (ll i = 0; i < n; ++i)
		for (ll j = 0; j < n; ++j)
		{
			if (i == j)continue;
			if (Sgn(G[i][j]))
			{
				++A.mat[i][i];
				A.mat[i][j] = -1;
			}
		}

	return A.Determinant(n - 1);
}

int main(int argc, char const *argv[])
{
	speedup;
	while (cin >> n >> m >> k)
	{
		Matrix A;
		for (ll i = 0; i < n; ++i)
			for (ll j = 0; j < n; ++j)
				if (i != j)A.mat[i][j] = 1;
		for (ll k = 0; k < m; ++k)
		{
			ll i, j; cin >> i >> j;
			--i, --j;
			A.mat[i][j] = A.mat[j][i] = 0;
		}
/*		for (ll i = 0; i < n; ++i)
		{
			for (ll j = 0; j < n; ++j)
			{
				cerr << A.mat[i][j];
			}
			cerr << endl;
		}*/
		cout << static_cast<ll>(CountingSpanningTrees(A.mat, n) + .5) << endl;
	}
	return 0;
}