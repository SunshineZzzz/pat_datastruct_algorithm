#include <iostream>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void SelectSort(int A[], int size)
{
	for (int step = 0; step < size - 1; ++step)
	{
		int min_idx = step;
		for (int i = step + 1; i < size; ++i)
		{
			if (A[i] < A[min_idx])
			{
				min_idx = i;
			}
		}
		swap(&A[step], &A[min_idx]);
	}
}

void PrintArray(int array[], int size) 
{
	for (int i = 0; i < size; i++) 
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int main() 
{
	int data[] = { 20, 12, 10, 15, 2 };
	int size = sizeof(data) / sizeof(data[0]);
	SelectSort(data, size);
	std::cout << "Sorted array in Acsending Order:\n";
	PrintArray(data, size);

	return 0;
}