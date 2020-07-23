#include <iostream>
#include <algorithm>

void InsertionSort(int array[], int size)
{
	// 0 - 作为手上的第一张牌
	for (int i = 1; i < size; ++i)
	{
		// 摸下一张
		int tmp = array[i];
		int j = i;
		for (; j > 0 && array[j - 1] > tmp; --j)
		{
			// 移出空位
			array[j] = array[j - 1];
		}
		// 新牌落位
		array[j] = tmp;
	}
}

void PrintArray(int array[], int size) 
{
	for (int i = 0; i < size; ++i) 
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int main() 
{
	int data[] = { 9, 5, 1, 4, 3 };

	int size = sizeof(data) / sizeof(data[0]);
	InsertionSort(data, size);
	std::cout << "Sorted array in ascending order:\n";
	PrintArray(data, size);

	return 0;
}