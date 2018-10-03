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

constexpr ll mod = 1000000007;
ll T;
ll n, k;
char s[100000];
constexpr ll maxk = 105, maxn = 50005;
ll c[maxk][maxk];
ll v[maxn];

ll Power(ll n, ll k)
{
	if (k == 0)return 1;
	ll ret = Power(n, k >> 1);
	ret = ret * ret % mod;
	if (k & 1)ret = ret * n % mod;
	return ret;
}

ll V(ll n)
{
	return Power(n, mod - 2);
}

void InitV()
{
	for (ll i = 1; i < maxk; ++i)
		v[i] = V(i);
}

void InitC(ll n)
{
	c[n][0] = 1;
	for (ll i = 1; i <= n; ++i)
	{
		c[n][i] = c[n][i - 1] * (n - i + 1) % mod * v[i] % mod;
		fprintf(stderr, "%lli\n", c[n][i]);
	}
}

void InitP(ll n, ll a[])
{
	a[0] = 1;
	for (ll i = 1; i < maxk; ++i)
		a[i] = a[i - 1] * n % mod;
}

int main(int argc, char const *argv[])
{
	speedup;
	InitV();
	cin >> T;
	while (T--)
	{
		cin >> n >> k;
		InitC(k);
		cin >> &s[1];
		ll ans = 0;
		for (ll i = 1; i <= n; ++i)
		{
			ll p[maxn][maxk] = {};
			for (ll m = 1; m <= k; ++m)
			{
				ans = ans + c[k][m] * 
			}
		}
	}
	return 0;
}
