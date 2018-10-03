#include <iostream>
#include <queue>
using namespace std;
#define ll long long
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

ll n, m, k, d;
const ll maxn = 1005;
bool forbidden[maxn][maxn];
ll mat[maxn][maxn];
ll cntt[maxn][maxn];
bool vis[maxn][maxn];
const ll dx[] = { 1, -1, 0, 0 };
const ll dy[] = { 0, 0, -1, 1 };
struct Rec
{
	ll x, y;
	ll cnt;
};
queue<Rec>q;
ll ans;

void BFS()
{
	while (!q.empty())
	{
		Rec p = q.front(); q.pop();
		ll x = p.x, y = p.y, cnt = p.cnt;
		if (vis[x][y])continue;
		vis[x][y] = true;
		if (cntt[x][y])
		{
			ans += cntt[x][y] * cnt;
		}
		for (ll d = 0; d < 4; ++d)
		{
			ll nx = x + dx[d], ny = y + dy[d];
			if (nx < 1 || ny < 1 || nx > n || ny > n || forbidden[nx][ny])continue;
			Rec rec;
			rec.x = nx, rec.y = ny, rec.cnt = cnt + 1;
			q.push(rec);
		}
	}
}

int main()
{
	speedup;

	cin >> n >> m >> k >> d;
	for (ll i = 0; i < m; ++i)
	{
		ll xi, yi; cin >> xi >> yi;
		Rec rec;
		rec.x = xi, rec.y = yi, rec.cnt = 0;
		q.push(rec);
	}
	for (ll i = 0; i < k; ++i)
	{
		ll xi, yi, ci; cin >> xi >> yi >> ci;
		cntt[xi][yi] += ci;
	}
	for (ll i = 0; i < d; ++i)
	{
		ll xi, yi; cin >> xi >> yi;
		forbidden[xi][yi] = true;
	}
	BFS();
	cout << ans << endl;

	return 0;
}