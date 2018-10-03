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

ll d[100000 + 5][5][5];

struct P
{
	ll num;
	ll o2, o3;
	ll step;
	bool operator<(const P&rhs)const
	{
		return step > rhs.step;
	}
};

ll ten[10] = { 1, 10, 100, 1000, 10000, 100000 };

ll Swap(ll n, ll i) // i = 0(ge), 1, 2, 3
{
	ll nlow = n / ten[i] % 10;
	ll nhigh = n / ten[i + 1] % 10;
	ll ret = n - nlow * ten[i] - nhigh * ten[i + 1];
	ret = ret + nlow * ten[i + 1] + nhigh * ten[i];
	return ret;
}

const ll inf = 0x3f3f3f3f3f3f3f3f;
bool vis[100000 + 5][5][6];
priority_queue<P>q;

void BFS()
{
	memset(d, 0x3f, sizeof d);
	q.push({ 12345, 0, 0, 0 });
	d[12345][0][0] = 0;
	while (!q.empty())
	{
		auto p = q.top();
		q.pop();
		auto num = p.num, o2 = p.o2, o3 = p.o3, step = p.step;
		if (vis[num][o2][o3] )continue;
		vis[num][o2][o3] = true;

//		d[num][o2][o3] = step;

//		d[num][o2][o3] = min(d[num][o2][o3], step);
		for (ll i = 0; i < 4; ++i)
		{
			ll newn = Swap(num, i);
/*			fprintf(stderr, "%lli\n%lli\n", num, newn);
			pause;*/
			if (d[newn][o2][o3] > step + 1)
			{
				d[newn][o2][o3] = step + 1;
				q.push({newn, o2, o3, step + 1});
			}
		}

		if (o2 < 3)
			for (ll i = 0; i < 5; ++i) // o2
			{
				ll newn = num;
				ll dig = newn / ten[i] % 10;
				if (dig == 9)
				{
					newn = newn - dig * ten[i];
				}
				else 
				{
					newn = newn + ten[i];
				}
/*				fprintf(stderr, "%lli\n%lli\n", num, newn);
				pause;*/
				if (d[newn][o2 + 1][o3] > step + 1)
				{
					d[newn][o2 + 1][o3] = step + 1;
					q.push({newn, o2 + 1, o3, step + 1});
				}
			}

		if (o3 < 2)
			for (ll i = 0; i < 5; ++i) // o3
			{
				ll newn = num;
				ll dig = newn / ten[i] % 10;
				newn = newn - dig * ten[i];
				newn = newn + dig * 2 % 10 * ten[i];
/*				fprintf(stderr, "%lli\n%lli\n", num, newn);
				pause;*/
				if (d[newn][o2][o3 + 1] > step + 1)
				{
					d[newn][o2][o3 + 1] = step + 1;
					q.push({newn, o2, o3 + 1, step + 1});
				}
			}
	}
}

int main(int argc, char const *argv[])
{
//	for (ll i = 0; i < 4; ++i)
//		cout << Swap(12345, i) << endl;
	speedup;
	BFS();
//	cerr << "OK" << endl;
	ll ans[100000];
	memset(ans, 0x3f, sizeof ans);
	for (ll k = 0; k < 100000; ++k)
	{
		for (ll i = 0; i <= 3; ++i)
			for (ll j = 0; j <= 2; ++j)
				ans[k] = min(ans[k], d[k][i][j]);
//		fprintf(stderr, "ans[%05lli]=%lli\n", k, ans[k]==inf ? -1 : ans[k]);
//		pause;
	}
	ll n;
	while (cin >> n)cout << (ans[n] == inf ? -1 : ans[n]) << endl;
	return 0;
}
