#define LOCAL

#include <bits/stdc++.h>

#define speedup cin.tie(0),cout.tie(0),ios::sync_with_stdio(0)
#ifdef LOCAL
	#define shuchu(a) cerr<<#a<<"\t= "<<a<<endl
	#define pause system("pause")
	#define frein freopen(R"(in.txt)","r",stdin)
	#define freout freopen(R"(out.txt)","w+",stdout)
	#define fre frein;freout
#else
	#define shuchu(a) 0
	#define pause 0
	#define fre 0
	#define frein 0
	#define freout 0
#endif

ll N, M;
const ll maxn = 50005;
#define ls (p<<1)
#define rs (ls|1)
#define lm ((l+r)>>1)
#define rm (lm+1)

struct Node
{
	ll lazy;
	ll tot;
}node[maxn << 2];

void PushDown(ll p, ll l, ll r)
{
	if (node[p].lazy == -1)return;
	node[ls].lazy = node[p].lazy;
	node[ls].tot = node[ls].lazy * (lm - l + 1);
	node[rs].lazy = node[p].lazy;
	node[rs].tot = node[rs].lazy * (r - rm + 1);
	node[p].lazy = -1;
}

void Update(ll p)
{
	node[p].tot = node[ls].tot + node[rs].tot;
}

void Build(ll p = 1, ll l = 0, ll r = N - 1)
{
	node[p].tot = 0;
	node[p].lazy = -1;
	if (l == r)return;
	Build(ls, l, lm);
	Build(rs, rm, r);
}

void Change(ll p, ll l, ll r, ll ql, ll qr, ll val)
{
	if (ql > r || qr < l)return;
	if (ql <= l && qr >= r)
	{
		node[p].lazy = val;
		node[p].tot = val * (r - l + 1);
		return;
	}
	PushDown(p);
	Change(ls, l, lm, ql, qr, val);
	Change(rs, rm, r, ql, qr, val);
	Update(p, l, r);
}

ll Query(ll p, ll l, ll r, ll ql, ll qr)
{
	if (ql > r || qr < l)return 0;
	if (ql <= l && qr >= r)return node[p].tot;
	PushDown(p);
	ll ret = Query(ls, l, lm, ql, qr) + Query(rs, rm, r, ql, qr);
	Update(p, l, r);
	return ret;
}

int main()
{
	speedup;
	ll T; cin >> T;
	while (T--)
	{
		cin >> N >> M;
		for (ll i = 0; i < M; ++i)
		{
			ll K; cin >> K;
			if (K == 1)
			{
				ll A, F; cin >> A >> F;
				ll tmp = Query(1, 0, N - 1, A, N - 1);
				ll emptyLeft = (N - 1 - A + 1) - tmp;

				ll putL = A, putR = N - 1;

				if (emptyLeft == 0)
				{
					cout << "Can not put any one." << endl;
					continue;
				}
				else if (emptyLeft <= F) // directly
				{
				}
				else // binary search
				{
					ll l = A, r = N - 1;
					ll tmp;
					while (tmp = N - 1 - A + 1 - Query(1, 0, N - 1, A, (l + r) / 2), tmp != F)
					{
						if (tmp > F)
						{
							r = (l + r) / 2;
						}
						else
						{
							l = (l + r) / 2 + 1;
						}
					}
					putR = (l + r) / 2;
				}

				{
					ll l = putL, r = putR;
					ll tmp;
					while (tmp = putR - putL + 1 - Query(1, 0, N - 1, ))
				}
			}
			else
			{
				ll A, B; cin >> A >> B;
				cout << B - A + 1 - Query(1, 0, N - 1, A, B) << endl;
				Change(1, 0, N - 1, A, B, 0);
			}
		}

		cout << endl;
	}
}