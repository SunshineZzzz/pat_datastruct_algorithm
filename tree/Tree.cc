#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <malloc.h>
#include <vector>
#include <algorithm>

typedef int ElementType;
typedef struct TreeNode* BinTree;
struct TreeNode
{
	// 元素
	ElementType Data;
	// 左儿子节点
	BinTree Left;
	// 右儿子节点
	BinTree Right;
};

// 创建二叉树节点
BinTree CreateNode(ElementType Data)
{
	BinTree BT;
	BT = (BinTree)malloc(sizeof(struct TreeNode));
	BT->Data = Data;
	BT->Left = nullptr;
	BT->Right = nullptr;
	return BT;
}

// 创建二叉树，返回根节点
//			1
//		/		\
//	  2 		  3
//	/	\		/	\
//	4 	6		7	9
//     /	    \
//    5	         8
BinTree CreateBinTree()
{
	// 创建根节点
	BinTree root = CreateNode(1);

	root->Left = CreateNode(2);
	root->Right = CreateNode(3);

	root->Left->Left = CreateNode(4);
	root->Left->Right = CreateNode(6);
	root->Left->Right->Left = CreateNode(5);

	root->Right->Left = CreateNode(7);
	root->Right->Right = CreateNode(9);
	root->Right->Left->Right = CreateNode(8);

	return root;
}

// 释放内存
void FreeBinTree(BinTree root)
{
	if (root)
	{
		FreeBinTree(root->Left);
		FreeBinTree(root->Right);
		free(root);
	}
}

// 先序遍历
void PreOrderTraversal(BinTree root)
{
	if (root)
	{
		printf("%d ", root->Data);
		PreOrderTraversal(root->Left);
		PreOrderTraversal(root->Right);
	}
}

// 先序遍历非递归
void PreOrderTraversalNoRecursion(BinTree root)
{
	std::vector<BinTree> S;
	BinTree T = root;

	while (T || !S.empty())
	{
		while (T)
		{
			printf("%d ", T->Data);
			S.push_back(T);
			T = T->Left;
		}
		if (!S.empty())
		{
			T = S[S.size() - 1];
			S.pop_back();
			T = T->Right;
		}
	}
}

// 中序遍历
void InOrderTraversal(BinTree root)
{
	if (root)
	{
		InOrderTraversal(root->Left);
		printf("%d ", root->Data);
		InOrderTraversal(root->Right);
	}
}

// 中序遍历非递归
void InOrderTraversalNoRecursion(BinTree root)
{
	std::vector<BinTree> S;
	BinTree T = root;
	// 当树不为空或者堆栈不为空
	while (T || !S.empty())
	{
		while (T)
		{
			S.push_back(T);
			T = T->Left;
		}
		// 当堆栈不为空
		if (!S.empty())
		{
			T = S[S.size() - 1];
			S.pop_back();
			printf("%d ", T->Data);
			// 访问右节点
			T = T->Right;
		}
	}
}

// 后序遍历
void PostOrderTraversal(BinTree root)
{
	if (root)
	{
		PostOrderTraversal(root->Left);
		PostOrderTraversal(root->Right);
		printf("%d ", root->Data);
	}
}

// 后序遍历非递归
// 左右根 = 反序(根右左)
void PostOrderTraversalNoRecursion(BinTree root)
{
	std::vector<BinTree> S1;
	std::vector<BinTree> S2;
	BinTree T = root;
	S1.push_back(T);
	while (!S1.empty())
	{
		T = S1[S1.size() - 1];
		S1.pop_back();
		S2.push_back(T);
		if (T->Left)
		{
			S1.push_back(T->Left);
		}
		if (T->Right)
		{
			S1.push_back(T->Right);
		}
	}
	std::reverse(S2.begin(), S2.end());
	for (const auto& elem : S2)
	{
		printf("%d ", elem->Data);
	}
}

// 层次遍历
void LevelOrderTraversal(BinTree root)
{
	if (!root)
	{
		return;
	}

	std::vector<BinTree> Q;
	Q.push_back(root);
	while (!Q.empty())
	{
		BinTree T = Q[0];
		Q.erase(Q.begin());
		printf("%d ", T->Data);
		if (T->Left)
		{
			Q.push_back(T->Left);
		}
		if (T->Right)
		{
			Q.push_back(T->Right);
		}
	}
}

// 输出叶子节点
void PreOrderPrintLeaves(BinTree root)
{
	if(root)
	{
		if(!root->Left && !root->Right)
		{
			printf("%d ", root->Data);
		}
		else
		{
			PreOrderPrintLeaves(root->Left);
			PreOrderPrintLeaves(root->Right);
		}
	}
}

// 二叉树的高度
int PostOrderGetHeight(BinTree root)
{
	int HL, HR, MaxH;
	if(root)
	{
		// 求左子树的深度
		HL = PostOrderGetHeight(root->Left);
		// 求右子树的深度
		HR = PostOrderGetHeight(root->Right);
		// 取左右子树较大的深度
		MaxH = (HL > HR) ? HL : HR;
		// 返回树的深度
		return (MaxH + 1);
	}
	else
	{
		// 空树深度为0
		return 0;
	}
}

int main()
{
	BinTree root;
	root = CreateBinTree();

	printf("先序遍历：");
	PreOrderTraversal(root);
	printf("\n");

	printf("非递归先序遍历：");
	PreOrderTraversalNoRecursion(root);
	printf("\n");

	printf("中序遍历：");
	InOrderTraversal(root);
	printf("\n");

	printf("非递归中序遍历：");
	InOrderTraversalNoRecursion(root);
	printf("\n");

	printf("后序遍历：");
	PostOrderTraversal(root);
	printf("\n");

	printf("非递归后序遍历：");
	PostOrderTraversalNoRecursion(root);
	printf("\n");

	printf("层次遍历：");
	LevelOrderTraversal(root);
	printf("\n");

	printf("树的叶子节点：");
	PreOrderPrintLeaves(root);
	printf("\n");

	printf("树的深度：");
	printf("%d", PostOrderGetHeight(root));
	printf("\n");

	FreeBinTree(root);
	root = nullptr;

	return 0;
}