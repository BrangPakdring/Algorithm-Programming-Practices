#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference:

	problem link:
	Classy Numbers
*/

const ll maxp = 30;
const ll totalCond = 5;

ll d[maxp][totalCond];
ll digit[maxp];

#define START_COND 0
#define RUNNING_COND 0
#define NEXT_COND 0

ll D(ll pos, ll cond, bool lim)
{
	if (pos == -1)return TERMINATE_COND;
	if (lim == false && d[pos][cond] != -1)return d[pos][cond];
	if (TERMINATE_COND == false)return d[pos][cond] = 0;
	ll uplim = lim ? digit[pos] : 9;
	ll ret = 0;
	for (ll i = 0; i <= uplim; ++i)
	{
		if (RUNNING_COND == false)continue;
		ret += D(pos - 1, NEXT_COND, lim && i == uplim);
	}
	return lim ? ret : d[pos][cond] = ret;
}

ll Sum(ll n)
{
	memset(digit, 0, sizeof digit);
	ll i = 0;
	while (n)
	{
		digit[i++] = n % 10;
		n /= 10;
	}
	return D(i - 1, START_COND, true);
}

void Init()
{
	memset(d, -1, sizeof d);
}