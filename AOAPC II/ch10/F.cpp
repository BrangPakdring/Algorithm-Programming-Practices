#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

constexpr ll maxn = 1e5 + 5, maxm = 1e9 + 5;
constexpr ll lim = sqrt(maxm);
ll n, m;
vector<ll>primes;
array<ll, maxn>mFacts, mFactsCnt, cFacts;
bitset<maxn>ans;
ll k;
ll sz;
bool imp;

void Init()
{
	fill(mFacts.begin(), mFacts.end(), 0);
	fill(cFacts.begin(), cFacts.end(), 0);
	ans.reset();
	sz = 0;
	imp = false;
}

void InitPrimes()
{
	bitset<lim>vis = 0;
	for (ll i = 2; i < lim; ++i)
	{
		if (vis[i] == 0)
		{	
			primes.push_back(i);
			for (ll j = i * i; j < lim; j += i)
				vis[j] = 1;
		}	
	}
}

void InitMFacts()
{
	ll tmp = m;
	for (auto&i : primes)
	{
		if (tmp < i)break;
		while (tmp % i == 0)
		{
			++mFacts[i];
			tmp /= i;
		}
	}
	if (tmp != 1)imp = true;
}

void ChangeCFacts()
{
	ll fz = n - 1 - k + 1, fm = k;
	for (auto&i : primes)
	{
		if (fz < i)break;
		while (fz % i == 0)
		{
			++cFacts[i];
			fz /= i;
		}
	}
	for (auto&i : primes)
	{
		if (fm < i)break;
		while (fm % i == 0)
		{
			--cFacts[i];
			fm /= i;
		}
	}
	if (fz != 1)++cFacts[fz];
	if (fm != 1)--cFacts[fm];
}

void ChangeAns()
{
	if (imp)return;
	for (auto i = 2; i < maxn; ++i)
	{
		if (cFacts[i] < mFacts[i])return;
	}
	ans[k + 1] = 1;
	ans[n/* - 1*/ - k/* + 1*/] = 1;
	++sz;
	sz += k + 1 != n - k;
}

void PrintAns()
{
	cout << sz << endl;
	bool fir = true;
	for (auto i = 0; i < maxn; ++i)
	{
		if (ans[i])
		{
			if (!fir)cout << ' ';
			fir = false;
			cout << i + 1;
		}
	}
	cout << endl;
}

int main()
{
	speedup;
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w+", stdout);
	InitPrimes();
	while (cin >> n >> m)
	{
		Init();
		InitMFacts();
		for (k = 1; k <= n / 2; ++k)
		{
			ChangeCFacts();
			ChangeAns();
		}
		PrintAns();
	}
	return 0;
}