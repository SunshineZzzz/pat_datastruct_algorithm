#include <stdio.h>
#include <malloc.h>

#define MAXSIZE 100

typedef int ElementType;

// 支持环形，最多容纳 MAXSIZE - 1
typedef struct QNode* Queue;
struct QNode
{
	ElementType Data[MAXSIZE];
	// 记录对头
	int front;
	// 记录队尾
	int rear;
};

// 初始化，最多容纳 MAXSIZE - 1
Queue CreateQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	// 指向对首元素的前空位置
	Q->front = -1;
	// 指向队尾元素
	Q->rear = -1;

	return Q;
}

// 释放
void FreeQueue(Queue Q)
{
	if(Q)
	{
		free(Q);
		Q = nullptr;
	}
}

// 判断队列是否已满，最多容纳 MAXSIZE - 1
bool IsFull(Queue Q)
{
	return ((Q->rear + 1) % MAXSIZE == Q->front);
}

// 判断队列是否为空，最多容纳 MAXSIZE - 1
bool IsEmpty(Queue Q)
{
	return (Q->front == Q->rear);
}

// 入队
int AddQ(Queue Q, ElementType item)
{
	if(IsFull(Q))
	{
		printf("queue full");
		return -1;
	}

	Q->rear = (Q->rear + 1) % MAXSIZE;
	Q->Data[Q->rear] = item;

	return 0;
}

// 出对
int DeleteQ(Queue Q, ElementType* item)
{
	if(IsEmpty(Q))
	{
		printf("queue empty");
		return -1;
	}

	Q->front = (Q->front + 1) % MAXSIZE;
	*item = Q->Data[Q->front];

	return 0;
}

int main()
{
	Queue Q;
	Q = CreateQueue();

	printf("push 5\n"); 
	AddQ(Q, 5);

	printf("push 4\n"); 
	AddQ(Q, 4);

	printf("push 3\n"); 
	AddQ(Q, 3);

	ElementType x;
	int rst = DeleteQ(Q, &x);
	printf("pop %d\n", x);

	rst = DeleteQ(Q, &x);
	printf("pop %d\n", x);

	rst = DeleteQ(Q, &x);
	printf("pop %d\n", x);

	rst = DeleteQ(Q, &x);
	printf("pop %d\n", x);

	printf("is empty %s\n", IsEmpty(Q)?"true":"false");
	
	FreeQueue(Q);
	Q = nullptr;
	
	return 0;
}