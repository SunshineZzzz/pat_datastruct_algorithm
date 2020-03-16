#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXN 1000

clock_t start, stop;
double duration;

// 方法一：确定子列的开头和结尾，再遍历累加，时间复杂度O(n^3)
int MaxSubseqSum1(int A[], int N)
{
	int ThisSum, MaxSum = 0;
	int i, j, k;
	// i是子列左端位置
	for(i=0; i<N; i++)
	{
		// j是子列右端位置
		for(j=i; j<N; j++)
		{
			// ThisSum是从A[i]和A[j]的子列和
			ThisSum = 0;
			for(k=i; k<=j; k++)
			{
				ThisSum += A[k];
			}
			if(ThisSum > MaxSum)
			{
				MaxSum = ThisSum;
			}
		}
	}

	return MaxSum;
}

// 方法二：确定子列的开头和结尾，直接累加，时间复杂度O(n^2)
int MaxSubseqSum2(int A[], int N)
{
	int ThisSum, MaxSum = 0;
	int i, j;
	// i是子列左端位置
	for(i=0; i<N; i++)
	{
		// ThisSum是从A[i]到A[j]的子列和
		ThisSum = 0;
		// j是子列的右端位置
		for(j=i; j<N; j++)
		{
			ThisSum += A[j];
			if(ThisSum > MaxSum)
			{
				MaxSum = ThisSum;
			}
		}
	}

	return MaxSum;
}

// 返回三者中最大值
int Max3(int A, int B, int C)
{
	return (A>B)?((A>C)?A:C):((B>C)?B:C);
}

// 方法三：分治法
// 分治法”，简单来说就是把一个大的问题分解成多个小问题求解，再从所有小的解里面寻求最优解。
// 对于此问题而言，可以把一个大的序列分为两个小的序列，再把小的序列分为更小的两个序列，…，
// 直到每个小序列只有一个数，这就是分的过程，在每个小序列中，会得到：
// 左边最大子列和（正数即本身，负数即0）
// 右边最大子列和
// 横跨划分边界的最大子列和
// 时间复杂度 T(n)=O(nlogn)
int DivideAndConquer(int a[], int left, int right)
{
	// 递归结束条件：子列只有一个数字
	// 当该数为正数时，最大子列和为其本身
	// 当该数为负数时，最大子列和为0
	if(left == right)
	{
		if(a[left] > 0)
		{
			a[left];
		}
		return 0;
	}

	// 分别递归找到左右最大子列和
	int center = (left + right)/2;
	int maxLeftSum = DivideAndConquer(a, left, center);
	int maxRightSum = DivideAndConquer(a, center+1, right);

	// 再分找到左右跨界最大子列和
	int maxLeftBorderSum = 0;
	int leftBorderSum = 0;
	// 从边界出发向左边找
	for(int i=center; i>=left; i--)
	{
		leftBorderSum += a[i];
		if(maxLeftBorderSum < leftBorderSum)
		{
			maxLeftBorderSum = leftBorderSum;
		}
	}

	int maxRightBorderSum = 0;
	int rightBorderSum = 0;
	// 从边界出发向右边找
	for(int i=center+1; i<=right; i++)
	{
		rightBorderSum += a[i];
		if(maxRightBorderSum < rightBorderSum)
		{
			maxRightBorderSum = rightBorderSum;
		}
	}

	// 最后返回分解的左边最大子列和，右边最大子列和，和跨界最大子列和三者中最大的数
	return Max3(maxLeftSum, maxRightSum, maxRightBorderSum + maxLeftBorderSum);
}

int MaxSubseqSum3(int A[], int N)
{
	return DivideAndConquer(A, 0, N-1);
}

// 方法四：在线处理
// "在线"的意思是指每输入一个数据就进行 即时处理，在任何一个地方终止输入，
// 算法都能正确给出当前的解。T(n)=O(n)
int MaxSubseqSum4(int A[], int N)
{
	int ThisSum, MaxSum;
	int i;
	ThisSum = MaxSum = 0;
	for(i=0; i<N; i++)
	{
		// 向右累加
		ThisSum += A[i];
		if(ThisSum > MaxSum)
		{
			// 发现更大和则更新当前结果
			MaxSum = ThisSum;
		}
		// 如果当前子列和为负
		else if(ThisSum < 0)
		{
			// 则不可能使后面的部分和增大，抛弃之
			ThisSum = 0;
		}
	}

	return MaxSum;
}

int main()
{
	srand((unsigned int)time(0));

	int A[MAXN];
	for(int i=0; i<MAXN; i++)
	{
		// [-5,5]随机数
		A[i] = rand() % 11 - 5;
	}

	start = clock();
	printf("MaxSubseqSum1 = %d\n", MaxSubseqSum1(A, MAXN));
	stop = clock();
	duration = ((double)(stop - start))/CLOCKS_PER_SEC;CLOCKS_PER_SEC;
	printf("ticks1 = %f\n", (double)(stop - start));
	printf("duration1 = %6.2f\n", duration);

	start = clock();
	printf("MaxSubseqSum2 = %d\n", MaxSubseqSum2(A, MAXN));
	stop = clock();
	duration = ((double)(stop - start))/CLOCKS_PER_SEC;CLOCKS_PER_SEC;
	printf("ticks2 = %f\n", (double)(stop - start));
	printf("duration2 = %6.2f\n", duration);
	
	start = clock();
	printf("MaxSubseqSum3 = %d\n", MaxSubseqSum1(A, MAXN));
	stop = clock();
	duration = ((double)(stop - start))/CLOCKS_PER_SEC;CLOCKS_PER_SEC;
	printf("ticks3 = %f\n", (double)(stop - start));
	printf("duration3 = %6.2f\n", duration);
	
	start = clock();
	printf("MaxSubseqSum4 = %d\n", MaxSubseqSum4(A, MAXN));
	stop = clock();
	duration = ((double)(stop - start))/CLOCKS_PER_SEC;CLOCKS_PER_SEC;
	printf("ticks4 = %f\n", (double)(stop - start));
	printf("duration4 = %6.2f\n", duration);

	return 0;
} 