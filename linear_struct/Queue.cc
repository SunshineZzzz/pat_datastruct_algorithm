#include <stdio.h>
#include <malloc.h>

typedef int ElementType;
typedef struct QNode* Queue;
struct Node
{
	ElementType Data;
	struct Node *Next;
};

struct QNode
{
	// 指向队尾节点
	struct Node* rear;
	// 指向对头节点
	struct Node* front;
};

// 创建队列
Queue CreateQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = nullptr;
	Q->rear = nullptr;

	return Q;
}

// 释放
void FreeQueue(Queue Q)
{
	if(IsEmpty(Q))
	{
		free(Q);
		Q = nullptr;
		return;
	}

  	Node* p = Q->front;
  	Node* tmp = nullptr;
  	while(p)
  	{
  		tmp = p->Next;
  		free(p);
  		p = tmp;
  	}

  	free(Q);
  	Q = nullptr;
}

// 是否为空
bool IsEmpty(Queue Q)
{
	return (Q->front == nullptr);
}

// 入队
void AddQ(Queue Q, ElementType item)
{
	struct Node* node;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->Data = item;
	node->Next = nullptr;

	if(IsEmpty(Q))
	{
		Q->rear = node;
		Q->front = node;

		return;
	}

	// 将节点入队
	Q->rear->Next = node;
	// rear 仍然保持最后
	Q->rear = node;
}

// 出对
int DeleteQ(Queue Q, ElementType* x)
{
	struct Node* FrontCell;

	if(IsEmpty(Q))
	{
		printf("queue empty");
		return -1;
	}

	FrontCell = Q->front;
	if(Q->front == Q->rear)
	{
		Q->front = Q->rear = nullptr;
	}
	else
	{
		Q->front = FrontCell->Next;
	}

	*x = FrontCell->Data;
	free(FrontCell);

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