#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 1005;
ll f[maxn * maxn + 10];
ll t, a, b, n, mod;

void Init()
{
	f[0] = 0 % n, f[1] = 1 % n;
	for (ll i = 0;; ++i)
	{
		f[i + 2] = f[i + 1] + f[i];
		f[i + 2] %= n;
		if (i && f[i + 1] == f[1] && f[i + 2] == f[2])
		{
			mod = i;
			break;
		}
	}
}

ll Power(ll n, ll k)
{
	if (!k)return 1;
	ll ret = Power(n, k >> 1);
	(ret *= ret) %= mod;
	if (k & 1)(ret *= n) %= mod;
	return ret;
}

int main()
{
	speedup;

	cin >> t;
	while (t--)
	{
		cin >> a >> b >> n;
		Init();
		a %= mod;
		cout << f[Power(a, b)] << endl;
	}

	return 0;
}
