#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 1005;
ll n;
ll c[maxn];
ll arr[maxn];
deque<ll>num0, ans;

int main(int argc, char const *argv[])
{
	speedup;
	cin >> n;
	for (ll i = 1; i < n; ++i)
	{
		ll a, b; cin >> a >> b;
		if (a != n && b != n)
		{
			cout << "NO";
			return 0;
		}
		++c[min(a, b)];
	}
//	iota(arr + 1, arr + n + 1, 1);
	for (ll i = 1, tot = 0; i < n; ++i)
	{
		tot += c[i];
		if (tot > i)
		{
			cout << "NO";
			return 0;
		}
/*		if (c[i] > 1)
		{
			ll cnt0 = 0, lim = c[i] - 1;
			for (ll j = i; j > 1 && cnt0 < lim; --j)
			{
				if (c[j - 1] == 0)++cnt0;
				swap(arr[j], arr[j - 1]);
				swap(c[j], c[j - 1]);
			}
			if (cnt0 != lim)
			{
				cout << "NO";
				return 0;
			}
		}*/
	}
	cout << "YES" << endl;
	
	for (ll i = 1; i < n; ++i)
	{
		if (c[i] == 0)
		{
			num0.push_back(i);
		}
	}

	ans.push_front(n);
	for (ll i = n - 1; i >= 1; --i)
	{
		ll dif = c[i] - 1;
//		cerr << dif << endl;
		while (dif-- > 0)
		{
			ans.push_front(num0.back());
			num0.pop_back();
		}
		if (c[i] > 0)ans.push_front(i);
	}

//	for (auto&i : ans)cerr << i << ' '; cerr << endl;

	for (ll i = 1; i < n; ++i)
	{
		cout << ans[i - 1] << ' ' << ans[i] << endl;
	}
	return 0;
}