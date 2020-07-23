#include <iostream>
#include <algorithm>

void BubbleSort(int array[], int size)
{
	bool flag = false;
	for (int i = size - 1; i >= 0; --i)
	{
		flag = false;
		// 一趟冒泡
		for (int j = 0; j < i; ++j)
		{
			if (array[j] > array[j+1])
			{
				std::swap(array[j], array[j + 1]);
				flag = true;
			}
		}
		// 全程无交换，说明排序好了
		if (!flag)
		{
			break;
		}
	}
}

void PrintArray(int array[], int size) 
{
	for (int i = 0; i < size; ++i) 
	{
		std::cout << "  " << array[i];
	}
	std::cout << "\n";
}

int main() 
{
	int data[] = { -2, 45, 0, 11, -9 };
	int size = sizeof(data) / sizeof(data[0]);
	BubbleSort(data, size);
	std::cout << "Sorted Array in Ascending Order:\n";
	PrintArray(data, size);

	return 0;
}