#include <stdio.h>
#include <math.h>

// Z_p
int p = 2;
// in Z_2
#define N 8
int Fa[N], table[N][N];

/*	Since deg f = 3, the power of zero 'a' in F(a) is below 3;
 *	that is, the "length" of elements in F(a) is 1, 2 or 3.
 *	Then we can observe that the 2 product of these element has it's coefficients all below 4.
 *	(exactly, deg f + 1)
 *	Hence we should take a >= 4 and multiply things in F(a).*/
int a = 4;

int printPoly(int);

int main(void)
{
	// calculate Fa
	printf("F(a) = [");
	for (int i = 0; i < N; i++)
	{
		//	calculate the i-th element of F(a)
		int power = 0;
		for (int j = i; j > 0; j /= p)
		{
			//	let each bit (in base p) of j reprecent the coefficients of the i-th element
			Fa[i] += (j % p) * pow(a, power);
			power++;
		}
		printf("%d, ", Fa[i]);
	}
	printf("]\n\n");

	// calculate table
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int num = Fa[i] * Fa[j];

			//	reduce the coefficients
			int power = 1;
			while (power <= num)
			{
				int coef = num % (power * a) / power;
				num -= (coef - coef % p) * power;
				if (power >= a * a * a && coef % p)
				{
					//	a ^ 3 = a + 1
					num -= power;
					power /= a * a;
					num += power;
					power /= a;
					num += power;
					//	check angain in next loop
					continue;
				}
				power *= a;
			}
			table[i][j] = num;
			// printf("%d\t", table[i][j]);
			printPoly(table[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int printPoly(int num)
{
	// for f(x) = x^3 + x + 1
	if (num == 0)
	{
		printf("0\t");
		return 0;
	}
	int power = 2;
	int base = pow(a, power);
	int isprint = 0;
	while (base != 0)
	{
		if (num / base > 1)
		{
			printf("%d", num / base);
			isprint = 1;
		}
		else if (power == 0)
		{
			if (num / base)
			{
				printf("1");
				isprint = 1;
			}
		}
		if (num / base != 0 && power != 0)
		{
			printf("a");
			if (power > 1)
			{
				printf("^%d", power);
			}
			isprint = 1;
		}

		num %= base;
		power -= 1;
		base /= a;
		if (isprint && base != 0 && num / base != 0)
		{
			printf("+");
		}
	}
	printf("\t");
	return 0;
}