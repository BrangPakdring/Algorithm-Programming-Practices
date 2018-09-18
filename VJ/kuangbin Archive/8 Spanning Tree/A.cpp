#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <vector>
using namespace std;
#define ll long long

ll n, m;
const ll maxn = 100, maxm = 1000000;
ll x[maxm], y[maxm], w[maxm], r[maxm];
ll f[maxm];
vector<ll>span;

ll F(ll x)
{
    return x == f[x] ? x : f[x] = F(f[x]);
}

bool cmp(ll i, ll j)
{
	return w[i] < w[j];
}

void Kruskal()
{
	span.clear();
    ll res = 0, cnt = 0;
    for (ll i = 0; i < m; ++i)r[i] = i, f[i] = i;
    sort(r, r + m, cmp);
    for (ll i = 0; i < m; ++i)
    {
        ll e = r[i];
        ll u = F(x[e]), v = F(y[e]);
        if (u != v)
        {
            res += w[e];
            f[u] = v;
            span.push_back(e);
        }
    }

    ll tmp = 0; cnt = 0;
    bool flag = false;
    
    for (ll i = 0; i < n - 1 && !flag; ++i)
    {
    	for (ll i = 0; i < m; ++i)f[i] = i;
    	tmp = 0, cnt = 0;
    	for (ll j = 0; j < m; ++j)
    	{
    		ll e = r[j];
    		if (span[i] == e)continue;
    		ll u = F(x[e]), v = F(y[e]);
    		if (u != v)
    		{
    			f[u] = v;
    			tmp += w[e];
    			++cnt;
    		}
    		if (cnt == n - 1)
    		{
    			flag = tmp == res;
    			break;
    		}
    	}
    }

    if (flag)
    {
    	cout << "Not Unique!" << endl;
    }    
    else 
    {
    	cout << res << endl;
    }
}

int main()
{
    int t; cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (ll i = 0; i < m; ++i)
        {
        	cin >> x[i] >> y[i] >> w[i];
        }
        Kruskal();
    }
}
