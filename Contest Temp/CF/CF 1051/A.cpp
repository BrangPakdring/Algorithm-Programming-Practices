#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const char up = 'A', low = 'a', dig = '0';

int main(int argc, char const *argv[])
{
	speedup;
	ll T; cin >> T;
	while (T--)
	{
	    string str; cin >> str;
	    set<ll>lower, upper, digit;
	    for (ll i = 0; i < str.size(); ++i)
	    {
	    	auto c = str[i];
	    	if (isupper(c))upper.insert(i);
	    	else if (islower(c))lower.insert(i);
	    	else if (isdigit(c))digit.insert(i);
	    }
	    if (!lower.empty() && !upper.empty() && !digit.empty())
	    {
	    	cout << str << endl;
	    	continue;
	    }
	    else if (lower.empty() + upper.empty() + digit.empty() == 2)
	    {
	    	ll dis = INT64_MAX;

	    	if (lower.empty() && upper.empty())
	    	{
	    		ll p1, p2;
	    		for (auto it = digit.begin(), it0 = it++; it != digit.end(); ++it, ++it0)
	    		{
	    			if (*it - *it0 < dis)
	    			{
	    				p1 = *it0;
	    				p2 = *it;
	    				dis = *it - *it0;
	    			}
	    		}
	    		str[p1] = low;
	    		str[p2] = up;
	    	}
	    	else if (upper.empty() && digit.empty())
	    	{
	    		ll p1, p2;
	    		for (auto it = lower.begin(), it0 = it++; it != lower.end(); ++it, ++it0)
	    		{
	    			if (*it - *it0 < dis)
	    			{
	    				p1 = *it0;
	    				p2 = *it;
	    				dis = *it - *it0;
	    			}
	    		}
	    		str[p1] = dig;
	    		str[p2] = up;
	    	}
	    	else if (digit.empty() && lower.empty())
	    	{
	    		ll p1, p2;
	    		for (auto it = upper.begin(), it0 = it++; it != upper.end(); ++it, ++it0)
	    		{
	    			if (*it - *it0 < dis)
	    			{
	    				p1 = *it0;
	    				p2 = *it;
	    				dis = *it - *it0;
	    			}
	    		}
	    		str[p1] = low;
	    		str[p2] = dig;
	    	}	   
	    	cout << str << endl;
	    	continue; 	
	    }
	    else
	    {
	    	ll dis = INT64_MAX;
	    	if (lower.empty())
	    	{
	    		if (digit.size() > 1)
	    		{
	    			str[*digit.begin()] = low;
	    		}
	    		else
	    		{
	    			str[*upper.begin()] = low;
	    		}
	    	}
	    	else if (upper.empty())
	    	{
	    		if (digit.size() > 1)
	    		{
	    			str[*digit.begin()] = up;
	    		}
	    		else
	    		{
	    			str[*lower.begin()] = up;
	    		}
	    	}
	    	else if (digit.empty())
	    	{
	    		if (lower.size() > 1)
	    		{
	    			str[*lower.begin()] = dig;
	    		}
	    		else
	    		{
	    			str[*upper.begin()] = dig;
	    		}
	    	}
	    	cout << str << endl;
	    }
	}
	return 0;
}

