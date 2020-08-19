#ifdef _WIN32
#	define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

// 最小堆
typedef struct
{
	// 数组
	ElemType heapArray[MAXSIZE];
	// 数组个数
	int length;
} MinHeap;

//对数组进行元素的输入
Status Init_heapArray(MinHeap* M, int Number)
{
	ElemType data;
	for (int i = 0; i<Number; i++)
	{
		scanf("%d", &data);
		M->heapArray[i] = data;
		M->length++;
	}
	return OK;
}

// 最小堆的初始化
Status Init_MinHeap(MinHeap* M)
{
	int Number;
	M->length = 0;
	printf("请输入数组的元素个数：\n");
	scanf("%d", &Number);
	printf("请输入%d个数据：\n", Number);
	Init_heapArray(M, Number);

	return OK;
}

// 返回左孩子的下标
int MinHeap_Leftchild(int pos)
{
	return 2 * pos + 1;
}

// 返回右孩子的下标
int MinHeap_Rightchild(int pos)
{
	return 2 * pos + 2;
}

// 返回指定下标的父亲节点
int MinHeap_Parent(int pos)
{
	// 根节点的父节点的下标还是0，-1 / 2 = 0
	return (pos - 1) / 2;
}

// 指定下标向下调整最小堆
void MinHeap_SiftDown(MinHeap* M, int index)
{
	// 标识父结点
	int parent_index = index;
	// 用于记录值较小的子结点的小标
	int child_index = MinHeap_Leftchild(parent_index);
	// 保存父结点的值
	ElemType tempValue = M->heapArray[parent_index];
	// 循环向下给index下标的节点找个适合的位置
	while (child_index < M->length)
	{
		// 若有右子结点，且小于左子结点
		if ( (child_index < M->length - 1) && (M->heapArray[child_index] > M->heapArray[child_index + 1]) )
		{
			// 指向右子结点
			++child_index;
		}
		// 如果父结点 大于 左右子结点中最小的值则交换位置
		if (tempValue > M->heapArray[child_index])
		{
			M->heapArray[parent_index] = M->heapArray[child_index];
			parent_index = child_index;
			child_index = MinHeap_Leftchild(child_index);
		}
		else
		{
			// 堆的性质满足时则跳出
			break;
		}
	}
	// 在合适的位置把 tempValue 放进去 
	M->heapArray[parent_index] = tempValue;
}

// 建立最小堆
void Create_MinHeap(MinHeap* M)
{
	// 从二叉树最后的父节点，依次向上遍历父节点
	for (int i = M->length / 2 - 1; i >= 0; --i)
	{
		// 指定下标向下构建最小堆
		MinHeap_SiftDown(M, i);
	}
}

// 从指定节点向上调整最小堆
void MinHeap_SiftUp(MinHeap* M, int index)
{
	int temppos = index;
	ElemType temp = M->heapArray[temppos];
	// 循环向上给temppos下标的节点找个适合的位置
	while ( (temppos > 0) && (M->heapArray[MinHeap_Parent(temppos)] > temp) )
	{
		M->heapArray[temppos] = M->heapArray[MinHeap_Parent(temppos)];
		temppos = MinHeap_Parent(temppos);
	}
	M->heapArray[temppos] = temp;
}

// 删除指定下标的最小堆元素
Status MinHeap_Delete(MinHeap* M, int pos, ElemType* Del)
{
	if ((pos < 0) || (pos >= M->length))
	{
		return ERROR;
	}

	// 记录删除的元素
	(*Del) = M->heapArray[pos];
	// 用最后的元素值替代被删除的结点
	M->heapArray[pos] = M->heapArray[--M->length];
	// 最后元素小于父结点，需要向上调整
	if (M->heapArray[MinHeap_Parent(pos)] > M->heapArray[pos])
	{
		MinHeap_SiftUp(M, pos);
	}
	// 当前元素大于父结点，向下调整
	else
	{
		MinHeap_SiftDown(M, pos);
	}

	return OK;
}

//输出元素
void Print(MinHeap* M)
{
	for (int i = 0; i<M->length; i++)
	{
		printf("%d ", M->heapArray[i]);
	}
	printf("\n");
}

//请输入数组的元素个数：
//8
//请输入8个数据：
//55 66 44 33 11 22 88 99
//输出先前元素：
//55 66 44 33 11 22 88 99
//输出最小堆的元素：
//11 33 22 55 66 44 88 99
//请输入删除元素的下标:
//0
//删除的元素为：11
//输出删除后的元素：
//22 33 44 55 66 99 88
//请输入删除元素的下标 :
//1
//删除的元素为：33
//输出删除后的元素：
//22 55 44 88 66 99
// 
//	55
//	/  \
//   66   44
//   / \  / \
//  33 11 22 88
//  /
// 99
//
//	 11
//	/  \
//   33   22
//   / \  / \
//  55 66 44 88
//  /
// 99
//
//	 22
//	/  \
//  33   44
//  / \  / \
// 55 66 99 88
//
//    22
//   /  \
//  55   44
// / \  / \
// 88 66 99
int main()
{
	MinHeap M;

	// 初始化最小堆
	Init_MinHeap(&M);
	printf("输出先前元素：\n");
	Print(&M);
	// 构建最小堆
	Create_MinHeap(&M);
	printf("输出最小堆的元素：\n");
	Print(&M);


	ElemType Del;
	int Del_pos;
	printf("请输入删除元素的下标:\n");
	scanf("%d", &Del_pos);
	MinHeap_Delete(&M, Del_pos, &Del);
	printf("删除的元素为：%d\n", Del);
	printf("输出删除后的元素：\n");
	Print(&M);

	printf("请输入删除元素的下标:\n");
	scanf("%d", &Del_pos);
	MinHeap_Delete(&M, Del_pos, &Del);
	printf("删除的元素为：%d\n", Del);
	printf("输出删除后的元素：\n");
	Print(&M);

	return 0;
}