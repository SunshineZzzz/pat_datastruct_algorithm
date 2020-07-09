#include <iostream>
#include <malloc.h>
#include <vector>

// 最小堆的容量
#define MaxSize 1000
// 不可能被设置的权值，即最小权值
#define MinData -1000

// 预先定义好一组权值  
// int weight[] = { 10, 1, 100, 200, 11, 2, 5, 8, 90, 911 };
int weight[] = { 8, 5, 3, 1 };
// 权值数组的长度
// int weight_length = 10;
int weight_length = 4;

// 最小堆
typedef struct HeapStruct* MinHeap;
// 哈夫曼树
typedef struct TreeNode* HuffmanTree;
// 最小堆结构体
struct HeapStruct
{
	// 存储哈夫曼树节点元素的数组
	HuffmanTree* data;
	// 大小
	int size;
	// 容量
	int capacity;
};
// 哈夫曼树节点
struct TreeNode
{
	// 权值
	int weight;
	// 左子树
	HuffmanTree left;
	// 右子树
	HuffmanTree right;
};

// 创建哈夫曼树节点
HuffmanTree CreateHuffman()
{
	HuffmanTree Huff;
	Huff = (HuffmanTree)malloc(sizeof(struct TreeNode));
	Huff->weight = 0;
	Huff->left = nullptr;
	Huff->right = nullptr;

	return Huff;
}

// 释放哈夫曼树
void FreeHuffman(HuffmanTree H)
{
	if (H)
	{
		FreeHuffman(H->left);
		FreeHuffman(H->right);
		free(H);
	}
}

// 创建最小堆
MinHeap CreateMinHeap()
{
	MinHeap H;
	HuffmanTree Huff;
	H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->data = (HuffmanTree*)malloc(sizeof(struct TreeNode) * (MaxSize + 1));
	H->capacity = MaxSize;
	H->size = 0;
	// 设置哨兵
	Huff = CreateHuffman();
	Huff->weight = MinData;
	H->data[0] = Huff;

	return H;
}

// 释放最小堆
void FreeMinHeap(MinHeap& H)
{
	if (!H)
	{
		return;
	}

	free(H->data);
	H->data = nullptr;
	free(H);
	H = nullptr;
}

// 层序遍历最小堆
void LevelOrderTraversalMinHeap(MinHeap H)
{
	int i;
	for (i = 1; i <= H->size; i++)
	{
		std::cout<<H->data[i]->weight<<" ";
	}
	std::cout << std::endl;
}

// 重排以i为根的子树，从而满足最小堆属性
void Sort(MinHeap H, int i)
{
	// 用于交换节点
	HuffmanTree old = nullptr;
	// 打算被比较的父节点
	int parent = 0;
	// 记录左右孩子中较小的下标
	int child = 0;
	// 取得根节点
	HuffmanTree tmp = H->data[i];
	// parent * 2 <= H->Size - 判断parent是否有左孩子，没有左孩子，就更不可能有右孩子
	for (parent = i; parent * 2 <= H->size; parent = child)
	{
		// 左孩子节点下标
		child = 2 * parent;
		// child != H->Size 表示 child 不为当前最后一个结点，即 parent 有右孩子结点 
		// 左右孩子结点中找较小的值 
		if ( (child != H->size) && (H->data[child + 1]->weight < H->data[child]->weight) )
		{
			++child;
		}
		// 给 tmp 找个合适的位置 
		// 如果当前左右孩子结点比 tmp->weight 都大，说明 tmp 位置已经合适
		if (H->data[child]->weight >= tmp->weight)
		{
			break;
		}
		else
		{
			// 否则把较小的孩子结点提上来，自己继续下去找 
			old = H->data[parent];
			H->data[parent] = H->data[child];
			H->data[child] = old;
		}
	}
	H->data[parent] = tmp;
}

// 调整堆中元素，从而满足最小堆属性
void Adjust(MinHeap H) 
{
	// 循环子树根节点重排
	for (int i = H->size / 2; i > 0; --i)
	{
		Sort(H, i);
		// 调试
		// LevelOrderTraversalMinHeap(H);
	}
}

// 构建最小堆
void BuildMinHeap(MinHeap H) 
{
	// 堆元素
	HuffmanTree Huff;
	// 循环插入
	for (int i = 0; i < weight_length; ++i)
	{
		Huff = CreateHuffman();
		Huff->weight = weight[i];
		H->data[++H->size] = Huff;
	}
	/*
					   <10>
				/				\
			   <1>			    <100>
			/		\			/    \
		<200>		<11>	 <2>	   <5>
		/	\		/
	   <8>  <90>  <911>
	*/
	// 调整
	Adjust(H);
	/*
					<1>
			/				\
		  <8>			    <2>
		/		\			/    \
	  <10>		<11>	 <100>	  <5>
	  /	 \		/
	<200> <90> <911>
	*/
}

// 删除最小堆中的根节点元素，并且返回这个节点，即哈夫曼树
HuffmanTree Delete(MinHeap H)
{
	// 用于交换节点
	HuffmanTree old = nullptr;
	// 打算被比较的父节点
	int parent = 0;
	// 记录左右孩子中较小的下标
	int child = 0;
	// 取出根节点的哈夫曼树，即要删除的节点
	HuffmanTree T = H->data[1];
	// 要删除的位置
	int delPos = H->size--;
	// 取出最后一个哈夫曼树节点
	HuffmanTree tmp = H->data[delPos];
	// parent * 2 <= H->Size - 判断parent是否有左孩子，没有左孩子，就更不可能有右孩子 
	for (parent = 1; parent * 2 <= H->size; parent = child) 
	{
		// parent的左孩子
		child = 2 * parent;
		// child != H->Size 表示 child 不为当前最后一个结点，即 parent 有右孩子结点 
		// 左右孩子结点中找较小的值 
		if ( (child != H->size) && (H->data[child + 1]->weight < H->data[child]->weight) )
		{
			++child;
		}
		// 给 tmp 找个合适的位置 
		// 如果当前左右孩子结点比 tmp 都大，说明 tmp 位置已经合适
		if (H->data[child]->weight >= tmp->weight)
		{
			break;
		}
		else
		{
			// 否则把较小的孩子结点提上来，自己继续下去找 
			old = H->data[parent];
			H->data[parent] = H->data[child];
			H->data[child] = old;
		}
	}

	H->data[parent] = tmp;
	H->data[delPos] = nullptr;

	return T;
}

// 将哈夫曼节点插入最小堆中
void Insert(MinHeap H, HuffmanTree Huff)
{
	int weight = Huff->weight;
	// 指向堆的最后一个位置
	int i = ++H->size;
	// 向上找比 新插入哈夫曼节点权值 大的节点
	// 不使用哨兵的话，需要加上 H->data[i / 2]->weight > weight && i > 0
	// 存在哨兵，少一个判断
	for (; H->data[i / 2]->weight > weight; i /= 2)
	{
		H->data[i] = H->data[i / 2];
	}
	H->data[i] = Huff;
}

// 构建哈夫曼树
HuffmanTree Huffman(MinHeap H)
{
	HuffmanTree T;
	// 首先构建最小堆
	BuildMinHeap(H);
	// 层次遍历一下，看看最小堆是否正确
	LevelOrderTraversalMinHeap(H);
	int times = H->size;
	// 合并次数为 size - 1 次
	for (int i = 1; i < times; ++i)
	{
		// 两两合并一个新节点
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		// 从堆中删除一个结点，作为新 T 的左子结点 
		T->left = Delete(H);
		// 调试
		LevelOrderTraversalMinHeap(H);
		// 从堆中删除一个结点，作为新 T 的右子结点 
		T->right = Delete(H);
		// 调试
		LevelOrderTraversalMinHeap(H);
		// 重新计算新节点的权值 
		T->weight = T->left->weight + T->right->weight;
		// 再加进堆中 
		Insert(H, T);
		// 调试
		LevelOrderTraversalMinHeap(H);
	}
	T = Delete(H);
	return T;
}

// 先序遍历
void PreOrderTraversalHuffman(HuffmanTree Huff)
{
	if (Huff) 
	{
		std::cout << Huff->weight << " ";
		PreOrderTraversalHuffman(Huff->left);
		PreOrderTraversalHuffman(Huff->right);
	}
}

// 中序遍历
void InOrderTraversalHuffman(HuffmanTree Huff)
{
	if (Huff) 
	{
		InOrderTraversalHuffman(Huff->left);
		std::cout << Huff->weight << " ";
		InOrderTraversalHuffman(Huff->right);
	}
}

// 层次遍历
void LevelOrderTraversalHuffman(HuffmanTree Huff)
{
	if (Huff)
	{
		// 队列
		std::vector<HuffmanTree> Q;
		Q.push_back(Huff);
		while (!Q.empty())
		{
			HuffmanTree T = Q[0];
			Q.erase(Q.begin());
			std::cout << T->weight << " ";
			if (T->left)
			{
				Q.push_back(T->left);
			}
			if (T->right)
			{
				Q.push_back(T->right);
			}
		}
	}
}

int main()
{
	MinHeap H;
	HuffmanTree Huff;
	// 创建最小堆
	H = CreateMinHeap();
	// 构建哈夫曼树
	Huff = Huffman(H);
	// 先序遍历
	PreOrderTraversalHuffman(Huff);
	std::cout << std::endl;
	// 中序遍历
	InOrderTraversalHuffman(Huff);
	std::cout << std::endl;
	// 层次遍历
	LevelOrderTraversalHuffman(Huff);
	std::cout << std::endl;
	// 虽然不是工业级代码，该释放内存还是释放内存吧
	FreeMinHeap(H);
	FreeHuffman(Huff);
	Huff = nullptr;

	return 0;
}