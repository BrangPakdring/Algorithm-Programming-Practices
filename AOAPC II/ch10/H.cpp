#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

ll k;
char mat[2][6][5];
set<char>col[5];

int main()
{
	speedup;

	ll T; cin >> T;
	while (T--)
	{
		cin >> k;
		for (ll m = 0; m < 2; ++m)
			for (ll r = 0; r < 6; ++r)
				for (ll c = 0; c < 5; ++c)
					cin >> mat[m][r][c];
		for (auto&c : col)c.clear();
		for (ll c = 0; c < 5; ++c)
			for (ll r = 0; r < 6; ++r)
				for (ll rr = 0; rr < 6; ++rr)
				{
					if (mat[0][r][c] == mat[1][rr][c])
					{
						col[c].insert(mat[0][r][c]);
						break;
					}
				}
		ll idx[6] = {};
		bool no = false;
		for (auto&c : col)
		{
			if (c.empty())
			{
				no = true;
				break;
			}
		}
		for (ll i = 1; !no && i < k; ++i)
		{
			++idx[5];
			for (ll j = 5; j >= 1; --j)
			{
				if (idx[j] == col[j - 1].size())
				{
					idx[j] = 0;
					++idx[j - 1];
				}
			}
			if (idx[0])
			{
				no = true;
				break;
			}
		}
		if (no)
		{
			cout << "NO";
		}
		else
		{
			for (ll i = 0; i < 5; ++i)
			{
				auto it = col[i].begin();
				ll j = 0;
				for (; j < idx[i + 1]; ++j, ++it);
				cout << *it;
			}
		}
		cout << endl;
	}

	return 0;
}