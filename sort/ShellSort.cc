#include <iostream>

void ShellSort(int A[], int N)
{
	// 间隔每次减半，直到减到1
	for (int D=N/2; D > 0; D = D / 2)
	{
		// 开始插入排序
		for (int P = D; P < N; ++P)
		{
			int Tmp = A[P];
			int i = 0;
			for ( i = P; i >= D && A[i - D] > Tmp; i -= D)
			{
				A[i] = A[i - D];
			}
			A[i] = Tmp;
		}
	}
}

void PrintArray(int array[], int size) 
{
	int i;
	for (i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int main() 
{
	int data[] = { 9, 8, 3, 7, 5, 6, 4, 1 };
	int size = sizeof(data) / sizeof(data[0]);
	ShellSort(data, size);
	std::cout << "Sorted array: \n";
	PrintArray(data, size);

	return 0;
}