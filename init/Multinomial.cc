#include <stdio.h>
#include <math.h>
#include <time.h>

clock_t start, stop;
double duration;
// 多项式最大项
#define MAXN 10
// 被测函数最大重复调用次数
#define MAXK 1e6

// f(x) = a0 + a1x + ... + an-1xn-1 + anxn 
double f1(int n, double a[], double x)
{
	int i;
	double p = a[0];
	for(i=1; i<=n; i++)
	{
		p += (a[i] * pow(x, i));
	}
	return p;
}

// f(x) = a0 + x(a1 + x(...(an-1 + x(an))...))
double f2(int n, double a[], double x)
{
	int i;
	double p = a[n];
	for(i=n; i>0; i--)
	{
		p = a[i-1] + x*p;
	}
	return p;
}

int main()
{
	int i;
	// 存储多项式的系数
	double a[MAXN];
	for(i=0; i<MAXN; i++)
	{
		a[i] = (double)i;
	}

	start = clock();
	for(i=0; i<MAXK; i++)
	{
		f1(MAXN-1, a, 1.1);
	}
	stop = clock();
	duration = ((double)(stop - start))/CLOCKS_PER_SEC;
	printf("ticks1 = %f\n", (double)(stop - start));
	printf("duration1 = %6.2e\n", duration);

	start = clock();
	for(i=0; i<MAXK; i++)
	{
		f2(MAXN-1, a, 1.1);
	}
	stop = clock();
	duration = ((double)(stop - start))/CLOCKS_PER_SEC;CLOCKS_PER_SEC;
	printf("ticks2 = %f\n", (double)(stop - start));
	printf("duration2 = %6.2e\n", duration);

	return 0;
}