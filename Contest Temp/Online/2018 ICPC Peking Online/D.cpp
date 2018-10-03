#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

int main(int argc, char const *argv[])
{
	speedup;
	ll T; cin >> T;
	while (T--)
	{
		ll n, c; 
		cin >> n >> c;
		ll a[n], b[n];
		for (auto&i : a)cin >> i;
		for (auto&i : b)cin >> i;
		ll head = 0;
		ll money = c;
		ll cnt = 0;
		for (ll i = head; cnt <= n + n; ++cnt)
		{
			money += a[i] - b[i];
			if (money >= 0)
			{
				++i %= n;
				if (i == head)break;
			}
			else
			{
				while (head != (i + 1) % n && money < 0)
				{
					money -= a[head] - b[head];
					++head %= n;
				}
				++i %= n;
			}
		}
		fprintf(stderr, "head=%lli\n", head);
		fprintf(stderr, "cnt=%lli\n", cnt);
		fprintf(stderr, "money=%lld\n", money);
		if (cnt > n + n || money < 0)
		{
			cout << -1 << endl;
		}
		else
		{
			cout << head + 1 << endl;
		}
	}
	return 0;
}
