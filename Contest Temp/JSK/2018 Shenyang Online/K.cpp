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

deque<ll>primes;
vector<ll>truePrimes;
const ll maxn = 760000;

bool Check(ll n)
{
	static set<ll>no = { 1, 2, 3, 5, 7 };
	ll vis[10] = {};
	while (n)
	{
		ll tmp = n % 10;
		if (no.find(tmp) == no.end() || tmp > 1 && vis[tmp] || tmp == 1 && vis[tmp] > 1)return false;
		++vis[tmp];
		n /= 10;
	}
	return true;
}

void NextCheck()
{
	primes.push_back(INT_MAX);
	for (auto k : primes)
	{
		if (k == INT_MAX)break;
		bool ok = true;
		for (ll m = 1; ok && m < 64; ++m)
		{
			string tmpn;
			ll kk = k;
			for (ll i = 1; ok && kk && i <= m; i <<= 1, kk /= 10)
			{
				if (i & m)
				{
					tmpn = to_string(kk % 10) + tmpn;
				}
			}
			if (tmpn.empty())continue;
//			shuchu(k);
//			shuchu(tmpn);
//			pause;
			if (*lower_bound(primes.begin(), primes.end(), stoll(tmpn)) != stoll(tmpn))ok = false;
		}
		if (ok)
		{
			truePrimes.push_back(k);
//			shuchu(k);
//			pause;
		}
	}
}

void InitPrimes()
{
	bool check[maxn] = {};
	ll tot = 0;
	for (ll i = 2; i < maxn; ++i)
	{
		if (!check[i] && Check(i))
		{
			primes.push_back(i);
			++tot;
		}
		for (ll j = 0; j < tot; ++j)
		{
			if (i * primes[j] >= maxn)break;
			check[i * primes[j]] = true;
			if (i % primes[j] == 0)
			{
				break;
			}
		}
	}

	primes.push_front(1);
	++tot;

//	for (auto i : primes)
//	{
//		shuchu(i);
//		pause;
//
//	}

	NextCheck();
}

int main(int argc, char const *argv[])
{
	speedup;
	InitPrimes();
	ll T; cin >> T;
	ll cas = 0;
	while (T--)
	{
		string n; cin >> n;
		ll ans;
		if (n.size() > 6)ans = truePrimes.back();
		else
		{
			ll N = stoll(n);
			if (N >= truePrimes.back())ans = truePrimes.back();
			else
			{
				ll id = upper_bound(truePrimes.begin(), truePrimes.end(), N) - truePrimes.begin();
				ans = truePrimes[id - 1];
			}
		}
		cout << "Case #" << ++cas << ": " << ans << endl;
	}
	return 0;
}

