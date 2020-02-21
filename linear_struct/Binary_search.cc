// 本题要求实现二分查找算法。
// 函数接口定义：
// Position BinarySearch( List L, ElementType X );
// 其中List结构定义如下：
// typedef int Position;
// typedef struct LNode *List;
// struct LNode {
//     ElementType Data[MAXSIZE];
//     Position Last; /* 保存线性表中最后一个元素的位置 */
// };
// L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，
// 并且题目保证传入的数据是递增有序的。
// 函数BinarySearch要查找X在Data中的位置，即数组下标（注意：元素从下标1开始存储）。
// 找到则返回下标，否则返回一个特殊的失败标记NotFound。
// 输入样例1:
// 12 31 55 89 101
// 31
// 输出样例1:
// 2
// 输入样例2:
// 26 78 233
// 31
// 输出样例2:
// 0
// 分析
// 这题就是写一个二分查找算法的函数接口
// 1.已经排序好的数组
// 2.确定最左边的start,最右边的end
// 3.无限循环当中找mid角标对应的值,start和end会根据情况改变
// 4.当发现start和end交叉,那么证明找不到,即如果放入该元素,那么就应该放在此时的start位置.

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0

typedef int ElementType;
typedef int Position;
typedef struct LNode* List;
struct LNode 
{
	ElementType Data[MAXSIZE];
	// 保存线性表中最后一个元素的位置
	Position Last;
};

List ReadInput(); 
Position BinarySearch( List L, ElementType X );
Position BinarySearch_Recursion( List L, ElementType X, int start, int end );

int main()
{
	List L;
	ElementType X;
	Position P;

	printf("ReadInput:\n");
	L = ReadInput();
	printf("Find val:\n");
	scanf("%d", &X);

	printf("normal BinarySearch: \n");
	P = BinarySearch( L, X );
	printf("%d\n", P);

	printf("recursion BinarySearch: \n");
	P = BinarySearch_Recursion( L, X, 0, L->Last);
	printf("%d\n", P);

	return 0;
}

// 你的代码将被嵌在这里
List ReadInput()
{
	ElementType X = ElementType();
	List pList = (List)malloc(sizeof(struct LNode));
	pList->Last = -1;

	int i = 0;
	while(scanf("%d", &X) != EOF)
	{
		pList->Data[i] = X;
		pList->Last = i;
		i++;
	}

	return pList;
}

// 非递归二分查找
Position BinarySearch( List L, ElementType X )
{
	if(!L || L->Last == -1)
	{
		return NotFound;
	}

	int start = 0;
	int end = L->Last;
	int middle = 0;

	while(true)
	{
		middle = (start + end)/2;
		ElementType middleVal = L->Data[middle];
		if(middleVal == X)
		{
			return middle + 1;
		}
		else if(middleVal > X)
		{
			end = middle - 1;
		}
		else
		{
			start = middle + 1;
		}

		if(start > end)
		{
			return NotFound;
		}
	}
}

// 递归查找
Position BinarySearch_Recursion( List L, ElementType X, int start, int end )
{
	if(!L || L->Last == -1)
	{
		return NotFound;
	}

	if(start > end)
	{
		return NotFound;
	}

	int middle = (start + end)/2;
	ElementType middleVal = L->Data[middle];
	if(middleVal == X)
	{
		return middle + 1;
	}
	else if(middleVal > X)
	{
		end = middle - 1;
		return BinarySearch_Recursion(L, X, start, end);
	}
	else
	{
		start = middle + 1;
		return BinarySearch_Recursion(L, X, start, end);
	}

	return NotFound;
}