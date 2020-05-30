#include <iostream>
#include <malloc.h>

typedef int ElementType;
typedef struct TreeNode* BinTree;
struct TreeNode 
{
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

// 查找递归实现
BinTree Find(ElementType X, BinTree BST) 
{
	// 查找根节点为空，返回nullptr
	if(!BST) 
	{
		return nullptr;
	}
	// 比根节点小，去左子树查找
	if(X < BST->Data) 
	{
		return Find(X, BST->Left);
	}
	// 比根节点大，去右子树查找
	else if(X > BST->Data) 
	{
		return Find(X, BST->Right);
	}

	return BST;
}

// 查找非递归实现
BinTree IterFind(ElementType X, BinTree BST) 
{
	while(BST) 
	{
		if(X < BST->Data)
		{
			BST = BST->Left;
		}
		else if(X > BST->Data)
		{
			BST = BST->Right;
		}
		else 
		{
			return BST;
		}
	}

	return nullptr;
}

// 查找最小值的递归实现
BinTree FindMin(BinTree BST)
{
	if(!BST)
	{
		return nullptr;
	}
	else if(BST->Left)
	{
		return FindMin(BST->Left);
	}

	return BST;
}

// 查找最大值的非递归实现
BinTree FindMax(BinTree BST)
{
	if(BST)
	{
		while(BST->Right)
		{
			BST = BST->Right;
		}
	}

	return BST;
}

// 插入
BinTree Insert(ElementType X, BinTree BST) 
{
	// 如果为空，初始化该节点
	if(!BST)
	{
		BST = (BinTree)malloc(sizeof(struct TreeNode));
		BST->Data = X;
		BST->Left = nullptr;
		BST->Right = nullptr;
	}
	else
	{
		// 如果小，挂在左边
		if(X < BST->Data)
		{
			BST->Left = Insert(X, BST->Left);
		}
		// 如果大，挂在右边
		else if(BST->Data < X)
		{
			BST->Right = Insert(X, BST->Right);
		}
		// 相等，说名都已经有这个节点了，什么都不做了
	}

	return BST;
}

// 删除
BinTree Delete(ElementType X, BinTree BST)
{
	BinTree tmp;
	if(!BST)
	{
		std::cout << "The element to be delete wsa not found";
	}
	// X 比当前节点值小，在左子树继续查找
	else if(X < BST->Data)
	{
		BST->Left = Delete(X, BST->Left);
	}
	// X 比当前结点值大，在右子树继续查找删除 
	else if(X > BST->Data)
	{
		BST->Right = Delete(X, BST->Right);
	}
	// 找到了要删除的节点
	else 
	{
		// 被删除节点有左右两个子节点
		if(BST->Left && BST->Right)
		{
			// 右子树的最小元素或者左子树最大元素
			tmp = FindMin(BST->Right);
			// 在右子树中找最小的元素填充删除节点
			BST->Data = tmp->Data;
			// 在删除节点的右子树中删除最小元素
			BST->Right = Delete(BST->Data, BST->Right);
		}
		// 被删除节点有一个 或者 无孩子节点
		else
		{
			tmp = BST;
			// 有右孩子 或者 无孩子节点
			if(!BST->Left)
			{
				BST = BST->Right;
			}
			// 有左孩子 或者 无孩子节点
			else if(!BST->Right)
			{
				BST = BST->Left;
			}
			free(tmp);
		}
	}

	return BST;
}

// 中序遍历
void InOrderTraversal(BinTree BT) 
{
	if(BT)
	{
		InOrderTraversal(BT->Left);
		std::cout<<BT->Data<<" ";
		InOrderTraversal(BT->Right);
	}
}

void FreeBinTree(BinTree BT)
{
	if(BT)
	{
		FreeBinTree(BT->Left);
		FreeBinTree(BT->Right);
		free(BT);
	}
}

int main(){
	BinTree BST = nullptr;
	BST = Insert(5, BST);
	BST = Insert(7, BST);
	BST = Insert(3, BST);
	BST = Insert(1, BST);
	BST = Insert(2, BST);
	BST = Insert(4, BST);
	BST = Insert(6, BST);
	BST = Insert(8, BST);
	BST = Insert(9, BST);
	/*
				5
			   /\
			  3  7
			 /\	 /\
			1 4 6  8
			\      \
			 2      9
	*/
	std::cout << "中序遍历的结果是："; 
	InOrderTraversal(BST);
	std::cout << std::endl;
	std::cout << "查找最小值是：" << FindMin(BST)->Data << std::endl;
	std::cout << "查找最大值是：" << FindMax(BST)->Data << std::endl; 
	std::cout << "查找值为3的结点左子树结点值为："<< Find(3, BST)->Left->Data << std::endl;
	std::cout << "查找值为7的结点右子树结点值为：" << IterFind(7, BST)->Right->Data << std::endl;
	std::cout << "删除值为5的结点" << std::endl;
	Delete(5, BST);
	/*
				6
			   /\
			  3  7
			 /\	  \
			1 4    8
			\      \
			 2      9
	*/
	std::cout << "中序遍历的结果是："; 
	InOrderTraversal(BST);
	std::cout << std::endl;

	FreeBinTree();
	return 0;
}