// 8
// A 1 2
// B 3 4
// C 5 -1
// D -1 -1
// E 6 -1
// G 7 -1
// F -1 -1
// H -1 -1
// 8
// G -1 4
// B 7 6
// F -1 -1
// A 5 1
// H -1 -1
// C 0 -1
// D -1 -1
// E 2 -1
// 
//    A
//   /  \
//   B   C
//   /\  /
//   D E G
//    / /
//    F H
// 
//    A
//   /  \
//   C   B
//   /   / \
//   G   E D
//   \  /
//   H  F
//
// Yes
// 
// 8
// B 5 7
// F -1 -1
// A 0 3
// C 6 -1
// H -1 -1
// D -1 -1
// G 4 -1
// E 1 -1
// 8
// D 6 -1
// B 5 -1
// E -1 -1
// H -1 -1
// C 0 2
// G -1 3
// F -1 -1
// A 1 4
// 
//    A
//   /  \
//   B   C
//   /\  /
//   D E G
//    / /
//    F H
// 
//    A
//   / \
//  B   C
//  /  / \
// G   D  E
// \  /
// H  F
//
// NO

#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <malloc.h>
#include <vector>

// 静态链表数组容量
#define MaxTree 10
// 节点元素
#define ElementType char
// 节点对应的下标
#define Tree int
// 无节点
#define Null -1

// 结构体节点
struct TreeNode
{
	// 节点元素
	ElementType Element;
	// 左子树下标
	Tree Left;
	// 右子树下标
	Tree Right;
}T1[MaxTree], T2[MaxTree];

// 返回根节点下标
Tree BuildTree(struct TreeNode T[])
{
	Tree Root = Null;
	Tree cl, cr;
	std::vector<unsigned char> check;
	int N;
	scanf("%d", &N);
	if(N && N <= MaxTree) 
	{
		check.resize(N, 0);
		for(int i = 0; i < N; ++i)
		{
			// %c前面加个空格或者\n等空白符，目的是跳过缓冲区中空白符读取
			scanf(" %c %d %d", &T[i].Element, &cl, &cr);
			if(cl != -1)
			{
				T[i].Left = cl;
				check[cl] = 1;
			}
			else
			{
				T[i].Left = Null;
			}

			if(cr != -1)
			{
				T[i].Right = cr;
				check[cr] = 1;
			}
			else
			{
				T[i].Right = Null;
			}
		}

		for(int index = 0; index < check.size(); ++index)
		{
			if(!check[index])
			{
				Root = index;
				break;
			}
		}
	}

	return Root;
}

int Isomorphic(Tree R1, Tree R2)
{
	// 两个树都是叶子节点，返回同构
	if((R1 == Null) && (R2 == Null))
	{
		return 1;
	}

	// 一个树为空，另一个树非空，返回非同构
	if((R1 == Null) && (R2 != Null) || (R1 != Null) && (R2 == Null))
	{
		return 0;
	}

	// 两个树本身的根节点元素不同，返回非同构
	if(T1[R1].Element != T2[R2].Element)
	{
		return 0;
	}

	// 两个树的左子树都为空，返回两个树的右子树是否同构
	if((T1[R1].Left == Null) && (T2[R2].Left == Null))
	{
		return Isomorphic(T1[R1].Right,T1[R1].Right);
	}
	
	// 两个树的左子树都不为空，并且两个树的左子树的根节点承载的元素都相同。
	// 说明：这两个子树的左右子树无需交换，返回这两个树的左子树是否同构 并且 右子树是否同构
	if( ((T1[R1].Left != Null) && (T2[R2].Left != Null)) &&
	    ((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element)) )
	{
		return ( Isomorphic( T1[R1].Left, T2[R2].Left ) && 
			Isomorphic( T1[R1].Right, T2[R2].Right ) );
	}
	// 两个树的左右子树需要交换，返回这两个树的左子树和右子树是否同构 并且 右子树和左子树是否同构
	else
	{
		return ( Isomorphic( T1[R1].Left, T2[R2].Right) && 
			Isomorphic( T1[R1].Right, T2[R2].Left ) );
	}
}

int main()
{
	// 根节点下标
	Tree R1, R2;

	// 创建二叉树
	R1 = BuildTree(T1);
	R2 = BuildTree(T2);

	// 判断是否同构
	if(Isomorphic(R1, R2))
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}

	return 0;
}