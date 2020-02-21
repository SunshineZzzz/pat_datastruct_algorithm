#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 64

typedef int ElementType;
typedef struct LNode* List;
struct LNode
{
	ElementType Element[MAXSIZE];
	int Length;
};

// 有哨兵
int SequentialSearch_yes(List Tb1, ElementType K)
{
	// 在Element[1]~Element[n]中查找关键字为K的数据元素
	int i;

	// 建立哨兵
	Tb1->Element[0] = K;

	for(i = Tb1->Length; Tb1->Element[i] != K; i--);

	return i;
}

// 无哨兵
int SequentialSearch_no(List Tb1, ElementType K)
{
	// 在Element[1]~Element[n]中查找关键字为K的数据元素
	int i;

	for(i = Tb1->Length; i > 0 && Tb1->Element[i] != K; i--);

	return i;
}

int main()
{
	srand((unsigned int)time(0));

	List L = (List)malloc(sizeof(struct LNode));

	int k = 0;
	for(int i = 1; i < MAXSIZE; i++)
	{
		L->Element[i] = rand() % 100 - 50;
		L->Length++;
	}

	printf("List length = %d\n", L->Length);
	printf("SequentialSearch_yes(10): %d\n", SequentialSearch_yes(L, 10));
	printf("SequentialSearch_no(10): %d\n", SequentialSearch_no(L, 10));

	free(L);
	L = nullptr;

	return 0;
}