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

enum { MX, MN, };
const ll maxn = 1005;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll n, k, m;
ll a[maxn];
ll d[maxn][10][2];
char f[10];

int main(int argc, char const *argv[])
{
	speedup;
	ll T; cin >> T;
	while (T--)
	{
		cin >> n >> m >> k;
		for (ll i = 1; i <= n; ++i)
		{
			cin >> a[i];
		}
		for (ll i = 1; i <= m; ++i)
		{
			cin >> f[i];
		}
//		memset(d, 0, sizeof d);
		for (ll i = 0; i <= n; ++i)
			for (ll j = 0; j <= m; ++j)
				d[i][j][MX] = -inf, d[i][j][MN] = inf;
		for (ll i = 0; i <= n; ++i)d[i][0][MX] = d[i][0][MN] = k;
		for (ll i = 1; i <= n; ++i)
		{
			for (ll j = 1; j <= i && j <= m; ++j)
			{
				d[i][j][MX] = d[i - 1][j][MX];
				d[i][j][MN] = d[i - 1][j][MN];
				ll tmp[2];
				tmp[MX] = d[i - 1][j - 1][MX];
				tmp[MN] = d[i - 1][j - 1][MN];
				switch (f[j])
				{
					case '+': tmp[MX] += a[i], tmp[MN] += a[i];
					break;
					case '-': tmp[MX] -= a[i], tmp[MN] -= a[i];
					break;
					case '*': tmp[MX] *= a[i], tmp[MN] *= a[i];
					break;
					case '/': tmp[MX] /= a[i], tmp[MN] /= a[i];
					break;
					default:
					break;
				}
				d[i][j][MX] = max({d[i][j][MX], tmp[MX], tmp[MN]});
				d[i][j][MN] = min({d[i][j][MN], tmp[MX], tmp[MN]});
			}
		}
		cout << d[n][m][MX] << endl;
	}
	return 0;
}
