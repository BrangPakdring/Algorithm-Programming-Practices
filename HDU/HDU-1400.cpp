#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 15;
ll h, w;
ll d[2][1 << maxn | 1];
ll cur;

int main()
{
	speedup;
	while (cin >> h >> w, h)
	{
		memset(d, 0, sizeof d);
		cur = 0;
		d[cur][(1 << w) - 1] = 1;
		for (ll i = 0; i < h; ++i)
			for (ll j = 0; j < w; ++j)
			{
				memset(d[cur ^ 1], 0, sizeof d[cur]);
				for (ll k = 0; k < (1 << w); ++k)
				{
					if (k & (1 << (w - 1)))
						d[cur ^ 1][(k ^ (1 << (w - 1))) << 1] += d[cur][k];
					if (i && (k & (1 << (w - 1))) == 0)
						d[cur ^ 1][k << 1 | 0x1] += d[cur][k];
					if (j && (k & (1 << (w - 1))) && (k & 1) == 0)
						d[cur ^ 1][(k ^ (1 << (w - 1))) << 1 | 0x3] += d[cur][k];
				}
				cur ^= 1;
			}
		cout << d[cur ^ 1][(1 << w) - 1] << endl;
	}
	return 0;
}
