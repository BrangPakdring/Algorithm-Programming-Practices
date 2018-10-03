import java.io.*;
import java.util.*;
import java.math.*;

class Main
{
    public static Scanner in = new Scanner(new BufferedInputStream(System.in));
    public static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static BigInteger b0 = BigInteger.valueOf(0), b1 = BigInteger.valueOf(1), b2 = BigInteger.valueOf(2), mod = BigInteger.valueOf(1000000007);

    static BigInteger power(BigInteger a, BigInteger n)
    {
    	BigInteger ret = new BigInteger("1");
    	while (!n.equals(b0))
    	{
    		if (n.and(b1).equals(b1))
    		{
    			ret = ret.multiply(a).mod(mod);
    		}
    		a = a.multiply(a).mod(mod);
    		n = n.shiftRight(1);
    	}
    	return ret;
    }

    public static void main(String[]args)
    {
        int T;
        T = in.nextInt();
        while (T-- > 0)
        {
            BigInteger N = new BigInteger(in.next());
            N = N.subtract(b1);
            out.println(power(b2, N));
            out.flush();
        }
        out.flush();
    }
}
