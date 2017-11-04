//1061 Dating of frog
#include<stdio.h>
long long k, t, d;
long long extended_gcd(long long a, long long b)
{
	long long tp_gcd;
	long long temp;
	if (b == 0)
	{
		k = 1;
		t = 0;
		d = a;
		return a;

	}
	else
	{
		//long long tp_gcd;
		tp_gcd = extended_gcd(b, a%b);
		//long long temp;
		temp = k;
		k = t;
		t = temp - (a / b)*t;
		return tp_gcd;
	}
}

int main()
{
	long long x, y, m, n, a, b, l;
	//while (scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &l) != EOF)
	scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &l);
	//{
		a = m - n; b = y - x;
		if (a < 0){
			a = -a; b = -b;
		}
		extended_gcd(a, l);
		if (b%d != 0) printf("Impossible\n");
		else
		{
			k = k*b / d;
			t = t*b / d;
			l = l / d;
			if (k >= 0)
				k = k%l;
			else k = k%l + l;
			printf("%lld\n", k);
		}

	//}
	return 0;
}