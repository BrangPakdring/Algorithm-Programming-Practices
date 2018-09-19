#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const double eps = 1e-8;
const ll maxn = 110;

struct Matrix
{
	double a[maxn][maxn], b[maxn][maxn];
	ll n;
	
	Matrix(ll n): n(n)
	{
		this->Init();
	}
	
	void Init()
	{
		for (ll i = 0; i < n; ++i)
			for (ll j = 0; j < n; ++j)
				a[i][j] = 0;
	}
	
	static ll Sgn(double x)
	{
		return x > eps ? 1
			: x < -eps ? -1
			: 0;
	}
	
	double Determinant(ll n)
	{
		ll i, j, k, sign = 0;
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

int main() 
{
	speedup;
	ll t; cin >> t;
	while (t--)
	{
		ll n, m; cin >> n >> m;
		Matrix A(n);
		ll G[n][n] = {};
		for (ll i = 0; i < m; ++i)
		{
			ll u, v; cin >> u >> v;
			--u, --v;
			G[u][v] = G[v][u] = 1;
		}
		for (ll i = 0; i < n; ++i)
			for (ll j = 0; j < n; ++j)
			{
				if (i == j)continue;
				if (G[i][j])
				{
					++A.a[i][i];
					A.a[i][j] = -1;
				}
			}
		cout << static_cast<ll>(round(A.Determinant(n - 1))) << endl;
	}
	return 0;
}