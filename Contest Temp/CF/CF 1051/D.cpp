#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

constexpr ll maxn = 1003, maxk = maxn << 1;
ll d[maxn][4][maxk];
constexpr ll mod = 998244353;

void Add(ll&a, ll b)
{
	a = (a + b) % mod;
}

int main(int argc, char const *argv[])
{
	speedup;
	d[1][0b00][1] = d[1][0b11][1] = d[1][0b10][2] = d[1][0b01][2] = 1;
	ll n, k;
	cin >> n >> k;
	for (ll i = 2; i <= n; ++i)
	{
		for (ll j = 1; j <= min(k, i * 2); ++j)
		{
			Add(d[i][0b11][j], d[i - 1][0b01][j]);
			Add(d[i][0b11][j], d[i - 1][0b10][j]);
			Add(d[i][0b11][j], d[i - 1][0b11][j]);
			if (j > 1)Add(d[i][0b11][j], d[i - 1][0b00][j - 1]);

			Add(d[i][0b00][j], d[i - 1][0b00][j]);
			Add(d[i][0b00][j], d[i - 1][0b01][j]);
			Add(d[i][0b00][j], d[i - 1][0b10][j]);
			if (j > 1)Add(d[i][0b00][j], d[i - 1][0b11][j - 1]);

			Add(d[i][0b10][j], d[i - 1][0b10][j]);
			if (j > 1)Add(d[i][0b10][j], d[i - 1][0b11][j - 1]);
			if (j > 1)Add(d[i][0b10][j], d[i - 1][0b00][j - 1]);
			if (j > 2)Add(d[i][0b10][j], d[i - 1][0b01][j - 2]);

			Add(d[i][0b01][j], d[i - 1][0b01][j]);
			if (j > 1)Add(d[i][0b01][j], d[i - 1][0b00][j - 1]);
			if (j > 1)Add(d[i][0b01][j], d[i - 1][0b11][j - 1]);
			if (j > 2)Add(d[i][0b01][j], d[i - 1][0b10][j - 2]);
		}
	}
	ll ans = 0;
	for (ll i = 0; i < 4; ++i)
		ans += d[n][i][k];
	cout << ans % mod << endl;

	return 0;
}

