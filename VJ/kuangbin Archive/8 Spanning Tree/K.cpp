#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

ll n, m;
char mat[15][15];
const ll maxp = 12 * 12;
ll G[maxp][maxp];
const ll&maxn = maxp;
const ll mod = 1e9;
const ll dx[] = { 1, -1, 0, 0 };
const ll dy[] = { 0, 0, -1, 1 };
ll superDot = -1;

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

ll CoordToID(ll r, ll c)
{
	return r * m + c;
}

ll CoordToID(pair<ll, ll>coord)
{
	return CoordToID(coord.first, coord.second);
}

pair<ll, ll>IDToCoord(ll ID)
{
	return { ID / m, ID % m };
}

void Input()
{
	cin >> n >> m;
	for (ll i = 0; i < n; ++i)
	{
		for (ll j = 0; j < m; ++j)
		{
			cin >> mat[i][j];
			if (mat[i][j] == '.' && superDot == -1)
			{
				superDot = CoordToID(i, j);
			}
		}
	}	
}

void BuildGraph()
{
	for (ll i = 0; i < n; ++i)
	{
		for (ll j = 0; j < m; ++j)
		{
			if (mat[i][j] == '*')
			{
				if (superDot != -1)
					G[superDot][CoordToID(i, j)] = G[CoordToID(i, j)][superDot] = 1;
				continue;
			}
			for (ll d = 0; d < 4; ++d)
			{
				ll nx = i + dx[d], ny = j + dy[d];
				if (nx < 0 || ny < 0 || nx >= n || ny >= m)continue;
				if (mat[nx][ny] == '.')
				{
					ll p1 = CoordToID(nx, ny), p2 = CoordToID(i, j);
					G[p1][p2] = G[p2][p1] = 1;
				}
			}
		}
	}
//	for (ll i = 0; i < n; ++i, cerr << endl)
//		for (ll j = 0; j < m; ++j)
//			cerr << G[i][j];
}

void Solve()
{
	cout << CountingSpanningTrees(G, n * m) << endl;
}

int main(int argc, char const *argv[])
{
	speedup;
	Input();
	BuildGraph();
	Solve();
	return 0;
}