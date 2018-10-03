#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

ll n, m, d;
const ll maxn = 2e5 + 5;
ll a[maxn];
map<ll, ll>minInDay;
ll ans[maxn];
ll tot;

int main(int argc, char const *argv[])
{
	speedup;
	cin >> n >> m >> d;
	for (ll i = 1; i <= n; ++i)
	{
		cin >> a[i];
		minInDay[a[i]] = i;
	}
	decltype(minInDay.begin()) it;
	while (!minInDay.empty())
	{
		it = minInDay.begin();
		++tot;
		while (it != minInDay.end())
		{
			ans[it->second] = tot;
			auto it0 = it;
			it = minInDay.upper_bound(it->first + d);
			minInDay.erase(it0);
		}
	}
	cout << tot << endl;
	for (ll i = 1; i <= n; ++i)
	{
		cout << ans[i] << ' ';
	}

	return 0;
}