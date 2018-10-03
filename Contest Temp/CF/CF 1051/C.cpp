#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

string c = "AB";
ll cnt[105];
char ans[105];

int main(int argc, char const *argv[])
{
	speedup;
	memset(ans, c[0], sizeof ans);
	ll n; cin >> n;
	ll s[n + 5]{};
	
	unordered_map<ll, vector<ll>>pos;
	for (ll i = 1; i <= n; ++i)
	{
		cin >> s[i];
		++cnt[s[i]];
		pos[s[i]].push_back(i);
	}
	ll cur = 0;
	for (auto pr : pos)
	{
		if (pr.second.size() == 1)
		{
			ans[pr.second.back()] = c[cur];
			cur ^= 1;
		}
	}
	if (!cur)
	{
		cout << "YES\n";
		for (ll i = 1; i <= n; ++i)
		{
			cout << ans[i];
		}
		return 0;
	}
	else
	{
		bool flag = false;
		for (auto pr : pos)
		{
			if (pr.second.size() > 2)
			{
				ans[pr.second.back()] = c[cur];
				flag = true;
				break;
			}
		}
		if (!flag)cout << "NO";
		else
		{
			cout << "YES\n";
			for (ll i = 1; i <= n; ++i)
			{
				cout << ans[i];
			}
			return 0;
		}
	}

	return 0;
}