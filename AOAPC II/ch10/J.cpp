#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

int main()
{
	speedup;

	ll a, b, c;
	cout << fixed << setprecision(5);
	while (cin >> a >> b >> c)
	{
		cout << 1. * b / (a + b) * (b - 1) / (a - c + b - 1) + 1. * a / (a + b) * b / (a - c + b - 1) << endl;
	}

	return 0;
}
