#include <stdio.h>
#include <malloc.h>

typedef int ElementType;

struct ListNode
{
	// 数据域
	ElementType Data;
	// 下一个链表的地址
	ListNode* Next;
};

// 初始化链表
ListNode* MakeEmpty()
{
	return nullptr;
}

// 释放
void FreeList(ListNode* pListNode)
{
	ListNode* p = nullptr;
	while(pListNode)
	{
		p = pListNode->Next;
		free(pListNode);
		pListNode = p;
	}
}

// 求表长
int Length(ListNode* pListNode)
{
	ListNode* p = pListNode;
	int len = 0;
	while(p && p->Next)
	{
		p = p->Next;
		len++;
	}

	return len;
}

// 按序查找
ListNode* FindKth(int k, ListNode* pListNode)
{
	ListNode* p = pListNode;
	int i = 1;
	while(p && i < k)
	{
		p = p->Next;
		i++;
	}

	if(i == k)
	{
		return p;
	}
	
	return nullptr;
}

// 按值查找
ListNode* Find(ElementType x, ListNode* pListNode)
{
	ListNode* p = pListNode;
	while(p && p->Data != x)
	{
		p = p->Next;
	}

	return p;
}

ListNode* Insert(ElementType x, int i, ListNode* pListNode)
{
	ListNode* p = nullptr, *s = nullptr;
	// 新结点插入在表头
	if(i == 1)
	{
		s = (ListNode*)malloc(sizeof(struct ListNode));
		s->Data = x;
		s->Next = pListNode;
		// 插入结点为头结点
		return s;
	}

	p = FindKth(i-1, pListNode);
	if(!p)
	{
		printf("%d index error\n", i-1);
		return nullptr;
	}
	else
	{
		s = (ListNode*)malloc(sizeof(struct ListNode));
		s->Data = x;
		s->Next = p->Next;
		p->Next = s;
		return pListNode;
	}
}

ListNode* Delete(int i, ListNode* pListNode)
{
	ListNode* p = nullptr, *s = nullptr;
	if(i==1)
	{
		s = pListNode;
		if(pListNode)
		{
			pListNode = pListNode->Next;
		}
		else
		{
			return nullptr;
		}

		free(s);
		s = nullptr;
		return pListNode;
	}

	p = FindKth(i - 1, pListNode);
	if(!p || !(p->Next))
	{
		printf("%d index error\n", i-1);
		return nullptr;
	}
	else
	{
		s = p->Next;
		p->Next = s->Next;
		free(s);
		return pListNode;
	}
}

// 输出链表元素
void Print(ListNode* pListNode)
{
	ListNode* t;
	int flag = 1;
	printf("list: ");
	for(t=pListNode; t; t=t->Next)
	{
		printf("%d ", t->Data);
		flag = 0;
	}

	if(flag)
	{
		printf("nullptr");
	}
	printf("\n");
}

int main()
{
	int i = 0;
	ListNode* L = MakeEmpty();

	L = Insert(11, 1, L);
	printf("insert 1 11\n");

	L = Insert(25, 1, L);
	printf("insert 1 25\n");
	
	L = Insert(33, 1, L);
	printf("insert 1 33\n");

	L = Insert(77, 1, L);
	printf("insert 1 77\n");

	L = Insert(88, 2, L);
	printf("insert 2 88\n");

	Print(L);

	printf("list length: %d\n", Length(L));
	printf("list 2 index of val: %d\n", FindKth(2, L)->Data);
	
	printf("find 22 of list: ");
	if(Find(22, L))
	{
		printf("yes!\n");
	}
	else
	{
		printf("no!\n");
	}

	printf("find 33 of list: ");
	if(Find(33, L))
	{
		printf("yes!\n");
	}
	else
	{
		printf("no!\n");
	}

	L = Delete(1, L);
	printf("delete 1 index\n"); 
	L = Delete(3, L);
	printf("delete 3 index\n");
	
	Print(L);

	FreeList(L);
	L = nullptr;
	
	return 0;
}