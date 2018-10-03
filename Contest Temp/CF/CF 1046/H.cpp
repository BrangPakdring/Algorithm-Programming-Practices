#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char const *argv[])
{
	speedup;
	ll n;
	cin >> n;
	string str[n];
	multiset<ll>bits;
	for (auto&s : str)
	{
		cin >> s;
		ll bt = 0;
		for (auto&c : s)
		{
			bt ^= 1 << (c - 'a');
		}
		bits.insert(bt);
	}
	ll ans = 0;
	// same
	for (auto it = bits.begin(); it != bits.end(); it = bits.upper_bound(*it))
	{
		auto cnt = bits.count(*it);
//		fprintf(stderr, "cnt=%lli\n", cnt);
		ans += cnt * (cnt - 1) / 2;
	}
	// dif at most 1
	for (auto it = bits.begin(); it != bits.end(); it = bits.upper_bound(*it))
	{
		auto s = *it;
		for (ll j = 0; j < 26; ++j)
		{
			ll b = 1 << j;
			ll k = s ^ b;
			if (k < s)continue; // (i,j)==(j,i)
			if (bits.count(k))
			{
				ans += bits.count(s) * bits.count(k);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
