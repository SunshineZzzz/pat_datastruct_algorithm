#include <inttypes.h>
#include <stdio.h>
#include <malloc.h>
#include <limits.h>

// 不可能取到的最大值
#define MaxData 2147483648ll


// 元素类型，实际元素类型是 int32_t
typedef int64_t ElementType;
// 最大堆
typedef struct HeapStruct* MaxHeap;
// 最大堆数据结构
struct HeapStruct
{
	// 存储堆元素的数组
	ElementType* Elements;
	// 堆当前元素个数
	int Size;
	// 堆的最大容量
	int Capacity;
};

// 创建最大堆
MaxHeap CreateMaxHeap(int MaxSize)
{
	MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
	// Elements[0] 作为哨兵，堆元素从 Elements[1] 开始存放 
	H->Elements = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	// "哨兵"大于堆中所有可能的值，哨兵的作用就是少一次判断
	H->Elements[0] = MaxData;

	return H;
}

void FreeHeap(MaxHeap& H)
{
	if (!H)
	{
		return;
	}

	free(H->Elements);
	H->Elements = nullptr;
	free(H);
	H = nullptr;
}

// 是否已满
bool IsFull(MaxHeap H)
{
	return (H->Size == H->Capacity);
}

// 是否为空
bool IsEmpty(MaxHeap H)
{
	return !H->Size;
}

// 插入，从完全二叉树的最后一个位置插入
bool Insert(MaxHeap H, ElementType item)
{
	if (IsFull(H)) 
	{
		printf("Max heap full!\n");
		return false;
	}

	// 指向堆的最后一个位置
	int i = ++H->Size;
	// 向上找比 item 小的节点
	// 不使用哨兵的话，需要加上 H->Elements[ i / 2 ] < item && i > 0
	// 存在哨兵，少一个判断
	for (;H->Elements[i / 2] < item; i /= 2)
	{
		// 既然比 item 小，赋值到当前下标位置吧
		H->Elements[i] = H->Elements[i / 2];
	}
	H->Elements[i] = item;

	return true;
}

// 删除
bool Delete(MaxHeap H, ElementType& x)
{
	// 从最大堆H中取出键值最大的元素，并且删除一个节点
	if (IsEmpty(H))
	{
		printf("Max heap empty!\n");
		return false;
	}

	// 打算被比较的父节点
	int parent = 0;
	// 记录左右孩子中那个较大的下标
	int child = 0;
	ElementType tmp;

	// 拿到要删除的值，即最大值
	x = H->Elements[1];
	// 用最大堆中最后一个元素从根节点开始向上过滤下层节点
	tmp = H->Elements[H->Size--];
	// parent * 2 <= H->Size - 判断parent是否有左孩子，没有左孩子，就更不可能有右孩子
	for (parent = 1; parent * 2 <= H->Size; parent = child)
	{
		// 左孩子节点下标
		child = 2 * parent;
		// child != H->Size 表示 child 不为当前最后一个结点，即 parent 有右孩子结点 
		// 左右孩子结点中找较大的值 
		if ((child != H->Size) && (H->Elements[child] < H->Elements[child + 1]))
		{
			child++;
		}
		// 给 tmp 找个合适的位置 
		// 如果当前左右孩子结点比 tmp 都小，说明 tmp 位置已经合适
		if (H->Elements[child] <= tmp)
		{
			break;
		}
		else
		{
			// 否则把较大的孩子结点提上来，自己继续下去找 
			H->Elements[parent] = H->Elements[child];
		}
	}
	// 在合适的位置把 tmp 放进去 
	H->Elements[parent] = tmp; 

	return true;
}

// 层序遍历
void LevelOrderTraversal(MaxHeap H) 
{
	int i;
	for (i = 1; i <= H->Size; i++) 
	{
		printf("%d ", H->Elements[i]);
	}
	printf("\n");
}

int main()
{
	MaxHeap H;
	int MaxSize = 100;
	H = CreateMaxHeap(MaxSize);
	Insert(H, 55);
	Insert(H, 66);
	Insert(H, 44);
	Insert(H, 33);
	Insert(H, 11);
	Insert(H, 22);
	Insert(H, 88);
	Insert(H, 99);
	/*
		  99
		 /  \
		88  66
		/ \  / \
	   55 11 22 44
	   /
	  33
	*/
	ElementType x;
	LevelOrderTraversal(H);
	Delete(H, x);
	LevelOrderTraversal(H);
	Delete(H, x);
	LevelOrderTraversal(H);
	Delete(H, x);
	LevelOrderTraversal(H);
	Delete(H, x);
	LevelOrderTraversal(H);

	FreeHeap(H);

	return 0;
}