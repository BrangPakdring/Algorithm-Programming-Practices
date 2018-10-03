#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
using pll = pair<ll, ll>;

ll n, m;
char mat[105][105];
pll s, t;
struct P
{
	ll x, y;
	ll b;
	ll p;
	ll step;
	bool operator<(const P&rhs)const
	{
		return step > rhs.step;
	}
};
ll dx[] = { 1, -1, 0, 0 };
ll dy[] = { 0, 0, 1, -1 };
ll vis[105][105][9];
ll cas;

inline bool outOfRange(ll x, ll y)
{
	return x < 0 || y < 0 || x == n || y == m;
}

void bfs()
{
	priority_queue<P>q;
	q.push({ s.first, s.second, 0, 0, 0 });
	while (!q.empty())
	{
		auto pp = q.top(); q.pop();
		auto x = pp.x, y = pp.y, b = pp.b, p = pp.p, step = pp.step;
		if (vis[x][y][b] == cas)continue;
		vis[x][y][b] = cas;
		if (t == pll{ x, y })
		{
//			fprintf(stderr, "x=%lli y=%lli b=%lli p=%lli, step=%lli\n", x,y,b,p,step);
			cout << step << endl;
			return;
		}
		for (ll d = 0; d < 4; ++d)
		{
			ll nx = dx[d] + x, ny = dy[d] + y;
			if (outOfRange(nx, ny))continue;
			if (b == 0 && mat[nx][ny] == '#')continue;
			ll nstep = step, nb = b, np = p;
			++nstep;
			if (mat[nx][ny] == '#')
			{
				--nb;
				++nstep;
			}
			if (mat[nx][ny] == 'B')
			{
				if (nb == 5)continue;
				++nb;
			}
			if (mat[nx][ny] == 'P')
			{
				++np;
				--nstep;
			}
//			fprintf(stderr, "nx=%lli ny=%lli nb=%lli np=%lli, nstep=%lli\n", nx,ny,nb,np,nstep);

//			getchar();
			q.push({ nx, ny, nb, np, nstep });
		}
	}
	cout << -1 << endl;
	return;
}

int main(int argc, char const *argv[])
{
	speedup;
	while (cin >> n >> m, n)
	{
		++cas;
		for (ll i = 0; i < n; ++i)
		{
			for (ll j = 0; j < m; ++j)
			{
				cin >> mat[i][j];
				if (mat[i][j] == 'S')
				{
					s = { i, j };
				}
				if (mat[i][j] == 'T')
				{
					t = { i, j };
				}
			}
		}
		bfs();
	}
	return 0;
}
