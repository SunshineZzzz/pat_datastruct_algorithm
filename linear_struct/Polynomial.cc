#include <stdio.h>
#include <malloc.h>

// 输入样例:
// 4 3 4 -5 2 6 1 -2 0
// 3 5 20 -7 4 3 1
// 
// 输出样例:
// 15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
// 5 20 -4 4 -5 2 9 1 -2 0

typedef struct PolyNode* Polynomial;
struct PolyNode {
	// 系数
	int coef;
	// 指数
	int expon;
	// 下一个
	Polynomial link;
};

// 释放
void FreePolynomial(Polynomial p)
{
	if(p)
	{
		return;
	}

	Polynomial t = nullptr;
	while(p)
	{
		t = p->link;
		free(p);
		p = t;
	}
}

// 链接多项式节点
void Attach(int c, int e, Polynomial* Rear)
{
	Polynomial P;

	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;
	P->expon = e;
	P->link = nullptr;
	(*Rear)->link = P;
	*Rear = P;
}

// 读取多项式
Polynomial ReadPoly()
{
	Polynomial t = nullptr;
	Polynomial Rear = nullptr;
	// 冗余一个节点，函数结束后删除
	Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
	Rear = P;

	int c = 0, e = 0;
	int N = 0;
	
	// 多项式个数
	scanf("%d", &N);
	while(N--)
	{
		scanf("%d %d", &c, &e);
		Attach(c, e, &Rear);
	}

	Rear->link = nullptr;
	t = P;
	P = P->link;
	free(t);
	t = nullptr;

	return P;
}

// 指数比较
int Compare(int expon1, int expon2)
{
	if(expon1 == expon2)
	{
		return 0;
	}
	else if(expon1 > expon2)
	{
		return 1;
	}
	
	return -1;
}


// 多项式相加
Polynomial Add(Polynomial P1, Polynomial P2)
{
	if(!P1 || !P2)
	{
		return nullptr;
	}

	Polynomial front, rear, temp;
	int sum = 0;
	rear = (Polynomial)malloc(sizeof(struct PolyNode));
	// 由 front 记录结果多项式链表头节点
	front = rear;
	while(P1 && P2)
	{
		switch(Compare(P1->expon, P2->expon))
		{
			case 1:
			{
				Attach(P1->coef, P1->expon, &rear);
				P1 = P1->link;
			}
			break;
			case -1:
			{
				Attach(P2->coef, P2->expon, &rear);
				P2 = P2->link;
			}
			break;
			case 0:
			{
				sum = P1->coef + P2->coef;
				// 等于0就GG
				if(sum)
				{
					Attach(sum, P1->expon, &rear);
				}
				P1 = P1->link;
				P2 = P2->link;
			}
			break;
		}
	}

	// 将未处理完成的多项式的节点依次复制到结果多项式中
	// 下面两个只有一个有
	bool b1 = false, b2 = false;
	for(;P1;P1 = P1->link)
	{
		b1 = true;
		Attach(P1->coef, P1->expon, &rear);
	}
	for(;P2;P2 = P2->link)
	{
		b2 = true;
		Attach(P2->coef, P2->expon, &rear);
	}
	if (b1 && b2)
	{
		return nullptr;
	}

	rear->link = nullptr;
	temp = front;
	front = front->link;
	free(temp);
	temp = nullptr;

	return front;
}

// 多项式相乘
Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P = nullptr, Rear = nullptr;
	Polynomial t1 = nullptr, t2 = nullptr, t = nullptr;
	int c = 0, e = 0;

	if(!P1 || !P2)
	{
		return nullptr;
	}

	t1 = P1;
	t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = nullptr;
	Rear = P;

	// 先用P1的第1项乘以P2，得到P
	// 先构建一个基础多项式，以此为基础插入P1和P2乘积的节点
	while(t2)
	{
		Attach(t1->coef*t2->coef, t1->expon+t2->expon, &Rear);
		t2 = t2->link;
	}
	t1 = t1->link;

	while(t1)
	{
		t2 = P2;
		Rear = P;
		while(t2)
		{
			e = t1->expon+t2->expon;
			c = t1->coef*t2->coef;
			// 找到合适的位置
			while(Rear->link && Rear->link->expon > e)
			{
				Rear = Rear->link;
			}
			// 指数相等，系数相加
			if(Rear->link && Rear->link->expon == e)
			{
				if(Rear->link->coef + c)
				{
					Rear->link->coef += c;
				}
				else
				{
					// 系数等于0
					t = Rear->link;
					// 越过这个系数为零的宝贝
					Rear->link = t->link;
					// 释放这个宝贝
					free(t);
					t = nullptr;
				}
			}
			else
			{
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;
			}

			t2 = t2->link;
		}
		t1 = t1->link; 
	}

	t2 = P;
	P = P->link;
	free(t2);
	t2 = nullptr;

	return P;
}

// 输出多项式
void PrintPoly(Polynomial P)
{
	if(!P)
	{
		printf("0*X^0\n");
		return;
	}

	int flag = 0;

	while(P)
	{
		if(!flag)
		{
			flag = 1;
		}
		else
		{
			printf(" ");
		}
		printf("%d*X^%d", P->coef, P->expon);
		P = P->link;
	}
	printf("\n");
}

int main()
{
	Polynomial P1, P2, PP, PS;

	// 读入多项式，系数递减，有顺序啊
	P1 = ReadPoly();
	printf("Polynomial1: ");
	PrintPoly(P1);

	P2 = ReadPoly();
	printf("Polynomial2: ");
	PrintPoly(P2);

	// 多项式加法
	PS = Add(P1, P2);
	printf("Polynomial1 + Polynomial2 = ");
	PrintPoly(PS);

	// 多项式乘法
	PP = Mult(P1, P2);
	printf("Polynomial1 * Polynomial2 = ");
	PrintPoly(PP);

	FreePolynomial(P1);
	P1 = nullptr;

	FreePolynomial(P2);
	P2 = nullptr;

	FreePolynomial(PP);
	PP = nullptr;

	FreePolynomial(PS);
	PS = nullptr;
	
	return 0;
}