#include<bits/stdc++.h>
using namespace std;

long long acc;
long long n;

long ac(long long x)
{
	long tmp,ret;
	ret=0;
	while(x)
	{
		tmp=x%10;
		if(tmp==1) ret++;
		x/=10;
	}
	return ret;
}

int main()
{
	scanf("%lld",&n);
	freopen("out.txt", "w", stdout);
	acc=0;
	for(long long i=1;i<=n;i++)
	{
		acc+=ac(i);
//		if (i % 100000000 == 0)
//		cout << "acc=" << acc << "  i=" << i << "  " << acc -i << endl;
//		if(acc==i)	printf("%lld\n",i);
		if (acc==i)cout << acc << ',' << endl;
	}
	
	return 0;
}
