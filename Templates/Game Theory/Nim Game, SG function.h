#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
	reference: https://www.cnblogs.com/ECJTUACM-873284962/p/6921829.html

	problem link:
	Playing With Stones 
	Treblecross 
	Stone Game, Why are you always there? 
*/

const ll maxn = 1005;
ll s[maxn]; // s[sg[x]] equals i (visited in current loop) iff x is a subsequent state
ll sg[maxn];
ll f[maxn]; // difference changed

void Init(ll n)
{
	sg[0] = 0; // final state
	for (ll i = 1; i <= n; ++i)
	{
		for (ll j = 0; f[j] <= i && j <= n; ++j)
		{
			s[sg[i - f[j]]] = i;
		}
		for (ll j = 0;; ++j)
		{
			if (s[j] != i)
			{
				sg[i] = j;
				break;
			}
		}
	}
}