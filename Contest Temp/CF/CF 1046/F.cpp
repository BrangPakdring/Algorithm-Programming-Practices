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

int main(int argc, char const *argv[])
{
	speedup;
	ll n; cin >> n;
	ll a[n + 1];
	for (ll i = 1; i <= n; ++i)
	{
		cin >> a[i];
	}
	ll x, f; cin >> x >> f;
	ll ans = 0;
	for (ll i = 1; i <= n; ++i)
	{
		if (a[i] <= x)continue;
		ll tmp = a[i] / (f + x);
		ll tmp2 = a[i] - tmp * (f + x);
		ans += tmp + (tmp2 > x);
//		ans += (a[i] - x) / (f + x);
	}
	cout << ans * f << endl;
	return 0;
}
