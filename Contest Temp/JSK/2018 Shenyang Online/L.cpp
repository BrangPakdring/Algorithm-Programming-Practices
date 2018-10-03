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
using ui = ll;

const ll mod = 1e9 + 7;

struct Mat
{
	ui mat[9][9] = {};
	Mat(){}
	Mat(int)
	{
		for (ll i = 0; i < 9; ++i)mat[i][i] = 1;
	}
	Mat operator*(const Mat&b)
	{
		Mat ret;
		for (ll i = 0; i < 9; ++i)
			for (ll j = 0; j < 9; ++j)
				for (ll k = 0; k < 9; ++k)
					ret.mat[i][j] += mat[i][k] * b.mat[k][j] % mod, ret.mat[i][j] %= mod;
		return ret;
	}
};

const Mat I = Mat(1);

Mat Power(Mat a, ll b)
{
	auto ret = I;
	while (b)
	{
		if (b & 1)ret = ret * a;
		a = a * a;
		b >>= 1;
	}
	return ret;
}

const ll a[] = { 0, 3, 9, 20, 46 };

int main(int argc, char const *argv[])
{
	speedup;
	ll T; cin >> T;

	Mat D;
	D.mat[0][1] = 1;D.mat[0][2] = 1;
	D.mat[1][3] = 1;D.mat[1][4] = 1;D.mat[1][5] = 1;
	D.mat[2][6] = 1;D.mat[2][8] = 1;
	D.mat[3][0] = 1;D.mat[3][1] = 1;D.mat[3][2] = 1;
	D.mat[4][3] = 1;D.mat[4][5] = 1;
	D.mat[5][7] = 1;D.mat[5][8] = 1;
	D.mat[6][0] = 1;D.mat[6][1] = 1;
	D.mat[7][3] = 1;D.mat[7][4] = 1;
	D.mat[8][6] = 1;D.mat[8][7] = 1;

	while (T--)
	{
		ll N; cin >> N;
		if (N <= 4)cout << a[N] << endl;
		else
		{
			Mat A = D;
			A = Power(A, N - 2);
			ll ans = 0;
			for (ll i = 0; i < 9; ++i)
				for (ll j = 0; j < 9; ++j)
					ans += A.mat[i][j];
			cout << ans % mod << endl;
		}
	}
	return 0;
}
