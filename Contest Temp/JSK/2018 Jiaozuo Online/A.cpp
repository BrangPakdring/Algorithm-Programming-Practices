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

int main(int argc, char const *argv[])
{
	speedup;
	ll T; cin >> T;
	while (T--)
	{
		string str; cin >> str;
		for (auto&i : str)i = tolower(i);
		if (str == "jessie")cout << "Good guy!\n";
		else cout << "Dare you say that again?\n";
	}
	return 0;
}
