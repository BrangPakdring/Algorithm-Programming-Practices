#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 1e4 + 5;
ll n;

namespace SegmentTree
{
	const ll inf = 0x3f3f3f3f3f3f3f3f;
	ll n;

	struct Node
	{
		ll l, r;
		ll mx;
	}node[maxn << 2];

	#define ls (p << 1)
	#define rs (ls | 1)
	#define lm ((l + r) >> 1)
	#define rm (lm + 1)

	void Build(ll p = 1, ll l = 1, ll r = n)
	{
		node[p] = { l, r, -inf };
		if (l == r)return;
		Build(ls, l, lm);
		Build(rs, rm, r);
	}

	void Change(ll p, ll l, ll r, ll q, ll val)
	{
		if (l == q && r == q)
		{
			node[p].mx = max(node[p].mx, val);
			return;
		}
		Change(ls, l, lm, q, val);
		Change(rs, rm, r, q, val);
		node[p].mx = max(node[ls].mx, node[rs].mx);
	}

	ll Query(ll p, ll l, ll r, ll ql, ll qr)
	{
		if (l == ql && r == qr)
		{
			return node[p].mx;
		}
		if (lm >= qr)return Query(ls, l, lm, ql, qr);
		else if (rm <= ql)return Query(rs, rm, r, ql, qr);
		else return max(Query(ls, l, lm, ql, qr), Query(rs, rm, r, ql, qr));
	}

	void Init(ll n)
	{
		SegmentTree::n = n;
		Build();
	}
}

int main(int argc, char const *argv[])
{
	speedup;
	ll t; cin >> t;
	while (t--)
	{
		cin >> n;
		for (ll i = 0; i < n - 1; ++i)
		{
			ll a, b, c; cin >> a >> b >> c;
		}
	}
	return 0;
}
