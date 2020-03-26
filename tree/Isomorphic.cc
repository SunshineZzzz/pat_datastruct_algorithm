#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <malloc.h>

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