#include <stdio.h>
#include <malloc.h>

// 堆栈元素最大个数
#define MAXSIZE 100

typedef int ElementType;
typedef struct SNode* Stack;
struct SNode {
	// 存储堆栈元素
	ElementType Data[MAXSIZE];
	// 记录栈顶元素下标
	int Top;
};

// 初始化堆栈
Stack CreateStack()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Top = -1;
	return S;
}

// 释放
void FreeStack(Stack S)
{
	if(S)
	{
		free(S);
		S = nullptr;
	}
}

// 是否已满
bool IsFull(Stack S)
{
	return (S->Top == MAXSIZE - 1); 
}

// 是否为空
bool IsEmpty(Stack S)
{
	return (S->Top == -1);
}

// 入栈
void Push(Stack S, ElementType x)
{
	if(IsFull(S))
	{
		printf("stack full");
		return;
	}

	S->Data[++S->Top] = x;
}

// 出栈
int Pop(Stack S, ElementType* x)
{
	if(IsEmpty(S))
	{
		printf("Stack empty");
		return -1;
	}

	*x = S->Data[S->Top--];
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