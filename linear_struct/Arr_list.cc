#include <stdio.h>
#include <malloc.h>

// MAXSIZE 定义为 Data 数组大小
#define MAXSIZE 100

// 链表元素
typedef int ElementType;

struct List
{
	// 数组存储
	ElementType Data[MAXSIZE];
	// 最后一个元素下标
	int Last;
};

// 初始化(建立空的顺序表)
List* MakeEmpty()
{
	List* pList;
	pList = (List*)malloc(sizeof(struct List));
	pList->Last = -1;

	return pList;
}

// 释放
void FreeList(List* pList)
{
	if(pList)
	{
		free(pList);
		pList = nullptr;
	}
}

// 按值查找下标, O(n)
int Find(ElementType x, List* pList)
{
	int i = 0;
	while(i <= pList->Last && pList->Data[i] != x)
	{
		i++;
	}

	if(i > pList->Last)
	{
		return -1;
	}

	return i;
}

// 在第i位置插入, O(n)
void Insert(ElementType x, int i, List* pList)
{
	int j;
	// 表空间已满，不能插入
	if(pList->Last == MAXSIZE - 1)
	{
		printf("list full\n");
		return;
	}

	// 检查插入位置的合法性
	if(i < 1 || i > pList->Last + 2)
	{
		printf("position error\n");
		return;
	}

	for(j = pList->Last; j >= i-1; j--)
	{
		pList->Data[j+1] = pList->Data[j];
	}

	pList->Data[i-1] = x;
	pList->Last++;

	return;
}

// 删除指定i位置的元素, O(n)
void Delete(int i, List* pList)
{
	int j;
	if(i < 1 || i > pList->Last + 1)
	{
		printf("position error\n");
		return;
	}

	for(j=i; j<=pList->Last; j++)
	{
		pList->Data[j-1] = pList->Data[j];
	}

	pList->Last--;
	return;
}

// 按序查找
int FindKth(int k, List* pList, ElementType* elem)
{
	if(k < 0 || pList->Last < k)
	{
		printf("position error\n");
		return -1;
	}

	*elem = pList->Data[k];
	return 0;
}

// 链表长度
int Length(List* pList)
{
	return pList->Last + 1;
}

int main()
{
	int i = 0;
	List* L = MakeEmpty();
	
	Insert(11, 1, L);
	printf("insert 1 11\n");

	Insert(25, 1, L);
	printf("insert 1 25\n");
	
	Insert(33, 1, L);
	printf("insert 1 33\n");

	Insert(77, 1, L);
	printf("insert 1 77\n");

	printf("list: "); 
	for(i=0; i<Length(L); i++)
	{
		printf("%d ", L->Data[i]);
	}
	printf("\n");

	printf("find 11 val of index: %d\n", Find(11, L));
	ElementType val;
	int rst = FindKth(3, L, &val);
	printf("find 3 index：%d\n", val);

	Delete(2, L);
	printf("delete 2 index\n"); 

	Delete(2, L);
	printf("delete 2 index\n"); 

	printf("list: "); 
	for(i=0; i<Length(L); i++)
	{
		printf("%d ", L->Data[i]);
	}
	printf("\n");

	FreeList(L);
	L = nullptr;

	return 0;
}