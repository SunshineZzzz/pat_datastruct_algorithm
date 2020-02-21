#include <stdio.h>
#include <malloc.h>

typedef int ElementType;
typedef struct SNode* Stack;
struct SNode
{
	ElementType Data;
	Stack Next;
};

// 初始化
// 实际返回堆栈的head指针
Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->Data = -1;
	S->Next = nullptr;
	return S;
}

// 释放
void FreeStack(Stack S)
{
	if(S && !S->Next)
	{
		free(S);
		S = nullptr;
		return;
	}

	Stack p = S->Next;
	Stack tmp = nullptr;
	while(p)
	{
		tmp = p->Next;
		free(p);
		p = tmp;
	}

	free(S)
	S = nullptr;
}

// 判断是否为空
bool IsEmpty(Stack S)
{
	return (S->Next == nullptr); 
}

// 入栈
void Push(Stack S, ElementType item)
{
	Stack tmp;
	tmp = (Stack)malloc(sizeof(struct SNode));
	tmp->Data = item;
	// 链栈栈顶元素是链表头结点，新入栈的链表在栈顶元素后面 
	tmp->Next = S->Next;
	S->Next = tmp;
}

// 出栈
int Pop(Stack S, ElementType* x)
{
	Stack First;
	if(IsEmpty(S))
	{
		printf("Stack empty");
		return -1;
	}

	First = S->Next;
	S->Next = First->Next;
	First->Next = nullptr;
	*x = First->Data;
	free(First);

	return 0;
}

int main()
{
	Stack S = CreateStack();

	printf("5 push\n");
	Push(S, 5);
	
	ElementType x;
	int rst = Pop(S, &x);
	printf("%d pop\n", x);

	printf("7 push\n");
	Push(S, 7);

	printf("66 push\n");
	Push(S, 66);

	rst = Pop(S, &x);
	printf("%d pop\n", x);

	rst = Pop(S, &x);
	printf("%d pop\n", x);

	printf("is empty %s\n", IsEmpty(S)?"true":"false");

	FreeStack(S);
	S = nullptr;

	return 0;
}