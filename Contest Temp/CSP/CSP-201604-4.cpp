#include <bits/stdc++.h>
using namespace std;
#define ll int
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const ll maxn = 105, maxt = 505;
ll n, m, t;
vector<pair<ll, ll> >timeBegin[maxt], timeEnd[maxt];
typedef vector<pair<ll, ll> >::iterator vit;
bool indanger[maxn][maxn];
bool vis[maxn][maxn][505];
struct Rec
{
	ll r, c;
	Rec(ll r, ll c): r(r), c(c) {}
};
queue<Rec>q[3];
const ll dx[] = { 1, -1, 0, 0 };
const ll dy[] = { 0, 0, -1, 1 };

int main()
{
	speedup;

	cin >> n >> m >> t;
	for (ll i = 0; i < t; ++i)
	{
		ll r, c, a, b; cin >> r >> c >> a >> b;
		timeBegin[a].push_back(pair<ll, ll>(r, c));
		timeEnd[b].push_back(pair<ll, ll>(r, c));
	}

	ll cur = 0;
	q[cur].push(Rec(1, 1));
	ll time = 1;
	while (true)
	{
		for (vit it = timeBegin[time].begin(), ed = timeBegin[time].end(); it != ed; ++it)
			indanger[it->first][it->second] = true;

		while (!q[cur].empty())
		{
			Rec p = q[cur].front(); q[cur].pop();
			ll r = p.r, c = p.c;
			if (vis[r][c][time])continue;
			vis[r][c][time] = true;

			if (r == n && c == m)
			{
				cout << time - 1 << endl;
				return 0;
			}

//			cerr << r << ' ' << c << ' ' << time - 1 << endl;

			for (ll d = 0; d < 4; ++d)
			{
				ll nx = r + dx[d], ny = c + dy[d];
				if (nx < 1 || ny < 1 || nx > n || ny > m)continue;
				if (indanger[nx][ny])continue;
				q[cur ^ 1].push(Rec(nx, ny));
			}
		}

		cur ^= 1;
		q[cur ^ 1] = q[2];

		for (vit it = timeEnd[time].begin(), ed = timeEnd[time].end(); it != ed; ++it)
			indanger[it->first][it->second] = false;

		++time;
	}
}
