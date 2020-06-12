/*
题目
An AVL tree is a self-balancing binary search tree. 
In an AVL tree, the heights of the two child subtrees of any node differ by 
at most one; if at any time they differ by more than one, 
rebalancing is done to restore this property. 
Figures 1-4 illustrate the rotation rules.

Now given a sequence of insertions, 
you are supposed to tell the root of the resulting AVL tree.

Input Specification:
Each input file contains one test case. For each case, 
the first line contains a positive integer N (≤20) which is 
the total number of keys to be inserted. Then N distinct integer 
keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the root of the resulting AVL tree in one line.

Sample Input 1:

5
88 70 61 96 120

Sample Output 1:

70

Sample Input 2:

7
88 70 61 96 120 90 65

Sample Output 2:

88

*/

#include <iostream>
#include <malloc.h>

typedef struct AVLNode* AVLTree;
struct AVLNode 
{
	// 存值
	int data;
	// 左子树
	AVLTree left;
	// 右子树
	AVLTree right;
	// 高度，当前节点的高度
	int height;
};

// 返回最大值
int Max(int a, int b)
{
	return a > b ? a : b ;
}

// 返回树高，空树返回-1
int GetHeight(AVLTree A)
{
	return A == nullptr ? -1 : A->height;
}

// LL单旋
// 把B的右子树腾出来挂到A的左子树，再将A挂到B的右子树上
// 			A 				B
// 		B 			=>	C 		A
// C
AVLTree LLRotation(AVLTree A)
{
	// 得到B节点
	AVLTree B = A->left;
	// B的右子树挂到A的左子树上
	A->left = B->right;
	// A挂到B的右子树上
	B->right = A;
	// 重新计算高度
	A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
	B->height = Max(GetHeight(B->left), GetHeight(B->right)) + 1;
	// 此时B为根节点
	return B;
}

// RR单旋
// 把B的左子树腾出来挂到A的右子树，再将A挂到B的左子树上
// A 						B
// 		B 			=> 	A 		C
// 			C
AVLTree RRRotation(AVLTree A)
{
	// 得到B节点
	AVLTree B = A->right;
	// B的左子树挂到A的右子树上
	A->right = B->left;
	// A挂到B的左子树上
	B->left = A
	// 重新计算高度
	A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
	B->height = Max(GetHeight(B->left), GetHeight(B->right)) + 1;
	// 此时B为根节点
	return B;
}

// LR双旋
// 基本思想是先将B作为根结点进行RR单旋转化为LL插入，再将A作为根结点进行LL单旋(先RR再LL)
// 		A 				A 			C
// B 		=>  	C 		=> B 	 	A
// 		C       B
AVLTree LRRoation(AVLTree A)
{
	// 先RR单旋
	A->left = RRRotation(A->left);
	// 再LL单旋
	return LLRotation(A);
}

// RL双旋
// 基本思想是先将B作为根结点进行LL单旋转化为RR插入，再将A作为根结点进行RR单旋(先LL再RR)
// 	A 				A 					C
// 		B 		=>  	C 		=> A 	 	B
// 	C       				B
AVLTree RLRoation(AVLTree A)
{
	// 先LL单旋
	A->right = LLRotation(A->right);
	// 再LL单旋
	return RRRotation(A);	
}

AVLTree Insert(AVLTree A, int x)
{
	// 空树
	if (!A)
	{
		A = (AVLTree)malloc(sizeof(struct AVLNode));
		A->data = x;
		A->left = nullptr;
		A->right = nullptr;
		A->height = 0;
	}
	else 
	{
		if (x < A->data)
		{
			// 左子树
			A->left = Insert(A->left, x);
			if (GetHeight(A->left) - GetHeight(A->right) == 2)
			{
				// 如果左子树和右子树高度差为2
				if (x < A->left->data)
				{
					// 值为x的插入节点 是 被破坏节点A的左子树左边，LL单旋
					A = LLRotation(A);
				}
				else if (x > A->left->data)
				{
					// 值为x的插入节点 是 被破坏节点A的左子树右边，LR双旋
					A = LRRoation(A);
				}
			}
		}
		else if(A->data < x)
		{
			// 右子树
			A->right = Insert(A->right, x);
			if (GetHeight(A->right) - GetHeight(A->left) == 2)
			{
				// 如果右子树和左子树高度差为2
				if (x > A->right->data)
				{
					// 值为x的插入节点 是 被破坏节点A的右子树右边，RR单旋
					A = RRRoation(A);
				}
				else if(x < A->right->data)
				{
					// 值为x的插入节点 是 被破坏节点A的右子树左边，RL双旋
					A = RLRoation(A);
				}
			}
		}
	}
	// 更新树高
	A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;

	return T;
}

int main()
{
	AVLTree A = nullptr;

	int n;
	std::cin >> n;
	for(int i = 0; i < n; ++i)
	{
		int tmp;
		std::cin >> tmp;
		A = Insert(A, tmp);
	}
	std::cout << A->data;

	return 0;
}