#include <iostream>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 最大堆构建
void Heapify(int arr[], int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
	{
		largest = left;
	}

	if (right < n && arr[right] > arr[largest])
	{
		largest = right;
	}

	if (largest != i)
	{
		swap(&arr[i], &arr[largest]);
		Heapify(arr, n, largest);
	}
}

void PrintArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

// 堆排序
void HeapSort(int arr[], int n) 
{
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; --i)
	{
		// 非叶子节点
		Heapify(arr, n, i);
	}
	// PrintArray(arr, n);
	// Heap sort
	for (int i = n - 1; i >= 0; i--) 
	{
		// 交换首尾元素，将最大值交换到数组的最后位置保存
		swap(&arr[0], &arr[i]);
		// 去除最后位置的元素重新建堆，此处i表示数组的长度
		Heapify(arr, i, 0);
	}
}

int main() 
{
	int arr[] = { 1, 12, 9, 5, 6, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, n);

	std::cout << "Sorted array is \n";
	PrintArray(arr, n);

	return 0;
}