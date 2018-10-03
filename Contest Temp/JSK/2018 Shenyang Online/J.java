import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;

class Main 
{
	static Scanner in = new Scanner(new BufferedInputStream(System.in));
	static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out), true);

	static BigInteger b0 = BigInteger.valueOf(0), b1 = BigInteger.valueOf(1), b2 = BigInteger.valueOf(2);

	static BigInteger sqrt(BigInteger n)
	{
		if (n.compareTo(b1) <= 0)return n;
		BigInteger l = b0;
		BigInteger r = n;
		BigInteger m = b0;
		while (l.compareTo(r) <= 0)
		{
			m = l.add( (r.subtract(l)).shiftRight(1) );
			if (m.equals(n.divide(m)))return m;
			if (m.compareTo(n.divide(m)) < 0)l = m.add(b1);
			else r = m.subtract(b1);
		}
		return r;
	}

	public static void main(String[] args) 
	{
		int T;
		T = in.nextInt();
		String[] str = new String[]{ "League of Legends", "Clash Royale", "Hearth Stone", "Arena of Valor" };
		while (T-- > 0)
		{
			String n = in.next();
			BigInteger N = new BigInteger(n);
			int ans = 0;

			{
				BigInteger n1 = N, n2 = N.subtract(b1);
				if (n1.and(b1).equals(b1))
				{
					n2 = n2.shiftRight(1);
				}
				else
				{
					n1 = n1.shiftRight(1);
				}
				BigInteger s1 = sqrt(n1);
				BigInteger s2 = sqrt(n2);
				if (s1.multiply(s1).equals(n1) && s2.multiply(s2).equals(n2))ans |= 1;
			}

			{
				BigInteger s = sqrt(N);
				if (s.multiply(s).equals(N))ans |= 2;
			}

			out.println(str[ans]);
		}
	}
}
