#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const double eps = 1e-6;
const ll maxn = 205;
ll n, p;
ll&mod = p;

ll Inverse(ll a, ll m)
{
	if (a == 1)return 1;
	return Inverse(m % a, m) * (m - m / a) % m;
}

struct Matrix
{
	ll mat[maxn][maxn];

	Matrix()
	{
		this->Init();
	}

	void Init()
	{
		memset(mat, 0, sizeof mat);
	}

	ll Determinant(ll n)
	{
		long long res = 1;
		for(int i = 0; i < n; ++i)
		{
			if (!mat[i][i])
			{
		    bool flag = false;
		    for (int j = i + 1; j < n; ++j)
		    {
		        if (mat[j][i])
		        {
		            flag = true;
		            for (int k = i; k < n; ++k)
		            {
		                swap (mat[i][k], mat[j][k]);
		            }
		            res = -res;
		            break;
		        }
		    }

		    if (!flag)
		    {
		        return 0;
		    }
		}

		for (int j = i + 1; j < n; ++j)
		{
		    while (mat[j][i])
		    {
		        long long t = mat[i][i] / mat[j][i];
		        for (int k = i; k < n; ++k)
		        {
		            mat[i][k] = (mat[i][k] - t * mat[j][k]) % mod;
		            swap (mat[i][k], mat[j][k]);
		        }
		        res = -res;
		    }
		}
		res *= mat[i][i];
		res %= mod;
	}
		return (res+mod)%mod;
  	
  }
};

int main(int argc, char const *argv[])
{
	speedup;
	while (cin >> n >> p)
	{
		Matrix A;
		for (ll i = 0; i < n; ++i/*, fprintf(stderr, "\n")*/)
			for (ll j = 0; j < n; ++j)
			{
				cin >> A.mat[i][j];
//				fprintf(stderr, "%lli\t", A.mat[i][j]);
			}

		cout << A.Determinant(n) << endl;
	}
	return 0;
}