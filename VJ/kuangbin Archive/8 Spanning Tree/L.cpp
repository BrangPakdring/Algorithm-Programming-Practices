#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const double eps = 1e-6;
const ll maxn = 305;
const ll mod = 10007;
ll inv[mod];

ll Inverse(ll a, ll m)
{
	if (~inv[a])return inv[a];
	if (a == 1)return inv[a] = 1;
	return inv[a] = Inverse(m % a, m) * (m - m / a) % m;
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
				for (ll k = i; k < n; ++k)
				{
					mat[j][k] = (mat[j][k] - mat[i][k] * mut % mod + mod) % mod;
				}
			}
			res = res * mat[i][i] % mod;
		}
		return res;
	}
};

ll n, r;
struct Point
{
	ll x, y;
}point[maxn];

double Distance(Point&a, Point&b)
{
	return hypot(a.x - b.x, a.y - b.y);
}

ll CountSpanningTrees(bool G[maxn][maxn])
{
	Matrix C;
	for (ll i = 0; i < n; ++i)
		for (ll j = 0; j < n; ++j)
		{
			if (i == j)continue;
			if (G[i][j])
			{
				C.mat[i][j] = -1;
				++C.mat[i][i];
			}
		}
	return C.Determinant(n - 1);
}

ll gcd(ll a, ll b)
{
	if (!a || !b)return max(a, b);
	return __gcd(a, b);
}

bool equalTo(double a, double b)
{
	return fabs(a - b) < eps;
}

void BuildGraph(bool G[maxn][maxn])
{
	double distance[maxn][maxn] = {};
	for (ll i = 0; i < n; ++i)
		for (ll j = i + 1; j < n; ++j)
		{
			distance[i][j] = distance[j][i] = Distance(point[i], point[j]);
		}
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			auto dis = distance[i][j];
//			fprintf(stderr, "dis = %g, r = %lli\n", dis, r);
			if (dis - eps > r)continue;

			ll dxij = point[i].x - point[j].x;
			ll dyij = point[i].y - point[j].y;
//			ll gij = gcd(abs(dxij), abs(dyij));
//			dxij /= gij; 
//			dyij /= gij;
//			fprintf(stderr, "i=%i, j=%i, dxij=%lld, dyij=%lld\n", i, j, dxij, dyij);
			bool flag = false;
			for (int k = 0; k < n; ++k)
			{
				if (k == i || k == j)continue;
				ll dxik = point[i].x - point[k].x;
				ll dyik = point[i].y - point[k].y;
//				ll gik = gcd(abs(dxik), abs(dyik));
//				dxik /= gik;
//				dyik /= gik;
//				fprintf(stderr, "i=%i, k=%i, dxik=%lld, dyik=%lld\n", i, k, dxik, dyik);
				if (equalTo(atan2(dxik, dyik), atan2(dxij, dyij)) /*equalTo(static_cast<double>(dxik) / dxij, static_cast<double>(dyik) / dyij)*/)
//				if (dxik == dxij && dyik == dyij)
				{
					if (distance[i][k] < dis)
					{
						flag = true;
						break;
					}
				}
			}
			if (!flag)
			{
				G[i][j] = G[j][i] = true;
			}
		}
	}

/*	for (ll i = 0; i < n; ++i)
	{
		for (ll j = 0; j < n; ++j)
		{
			cout << G[i][j];
		}
		cout << endl;
	}*/
}

bool G[maxn][maxn];

int main(int argc, char const *argv[])
{
	memset(inv, -1, sizeof inv);
	ll T; scanf("%lli", &T);
	while (T--)
	{
		scanf("%lli%lli", &n, &r);
		memset(G, 0, sizeof G);
		for (ll i = 0; i < n; ++i)
		{
			auto&p = point[i];
			scanf("%lli%lli", &p.x, &p.y);
		}
		BuildGraph(G);
		printf("%lli\n", CountSpanningTrees(G));
	}
	return 0;
}