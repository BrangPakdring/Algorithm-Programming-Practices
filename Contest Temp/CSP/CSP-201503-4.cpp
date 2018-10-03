#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 10005;
ll n, m;
ll ans;
vector<ll>G[maxn << 1];
ll d[maxn << 1];

inline ll PC(ll i) { return i + maxn; }

ll D(ll i)
{
	if (~d[i])return d[i];
	multiset<ll, greater<ll> >tmp;
	for (ll j = 0; j < G[i].size(); ++j)
	{
		tmp.insert(D(G[i][j]) + 1);
	}
/*	cerr << i << endl;
	for (auto&n : tmp)
	{
		cerr << n << '\t';
	}
	cerr << "\n--------------\n";*/
	if (tmp.empty())return d[i] = 0;
	if (tmp.size() == 1)
	{
		ans = max(ans, *tmp.begin());
		return d[i] = *tmp.begin();
	}
	if (tmp.size() > 1)
	{
		ans = max(ans, *tmp.begin() + *++tmp.begin());
		return d[i] = *tmp.begin();
	}
//	return d[i] = *tmp.begin() + *++tmp.begin();
}

int main()
{
	speedup;
	memset(d, -1, sizeof d);
	cin >> n >> m;
	for (ll i = 2; i <= n; ++i)
	{
		ll tmp; cin >> tmp;
		G[tmp].push_back(i);
	}
	for (ll i = 1; i <= m; ++i)
	{
		ll tmp; cin >> tmp;
		G[tmp].push_back(PC(i));
	}
	D(1);
//	for (ll i = 0; i < (maxn << 1); ++i)
//		ans = max(ans, d[i]);
	cout << ans << endl;

	return 0;
}
