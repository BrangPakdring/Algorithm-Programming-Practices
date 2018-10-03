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

const set<ll>table= 
{
1,
199981,
199982,
199983,
199984,
199985,
199986,
199987,
199988,
199989,
199990,
200000,
200001,
1599981,
1599982,
1599983,
1599984,
1599985,
1599986,
1599987,
1599988,
1599989,
1599990,
2600000,
2600001,
13199998,
35000000,
35000001,
35199981,
35199982,
35199983,
35199984,
35199985,
35199986,
35199987,
35199988,
35199989,
35199990,
35200000,
35200001,
117463825,
500000000,
500000001,
500199981,
500199982,
500199983,
500199984,
500199985,
500199986,
500199987,
500199988,
500199989,
500199990,
500200000,
500200001,
501599981,
501599982,
501599983,
501599984,
501599985,
501599986,
501599987,
501599988,
501599989,
501599990,
502600000,
502600001,
513199998,
535000000,
535000001,
535199981,
535199982,
535199983,
535199984,
535199985,
535199986,
535199987,
535199988,
535199989,
535199990,
535200000,
535200001,
1111111110,
};

int main(int argc, char const *argv[])
{
	speedup;
	string n;

	while (cin >> n)
	{
		if (n.size() > 10)cout << "83 1111111110" << endl;
		else
		{
			ll N = stoll(n);
			auto it = --table.upper_bound(N);
			cout << distance(table.begin(), it) + 1 << ' ' << *it << endl;
		}
	}
	return 0;
}
