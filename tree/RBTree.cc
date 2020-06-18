#include <iostream>

#define BLACK 1
#define RED 0

class bst 
{
private:
	struct Node 
	{
		// 值
		int value;
		// 颜色
		bool color;
		// 左子树
		Node* leftTree;
		// 右子树
		Node* rightTree;
		// 父节点
		Node* parent;

		// 新节点颜色设置为红色
		// 如果设为黑色，就会导致根到叶子的路径上有一条路上，
		// 多一个额外的黑节点，这个是很难调整的。
		// 但是设为红色节点后，可能会导致出现两个连续红色节点的冲突，
		// 那么可以通过颜色调换（color flips）和树旋转来调整。
		Node():
			value(0),
			color(RED),
			leftTree(nullptr),
			rightTree(nullptr),
			parent(nullptr)
		{
		}

		// 获取祖父节点
		Node* grandparent()
		{
			if (parent == nullptr)
			{
				return nullptr;
			}
			return parent->parent;
		}
		// 获取叔父节点
		Node* uncle()
		{
			if (grandparent() == nullptr) 
			{
				return nullptr;
			}
			if (parent == grandparent()->rightTree)
			{
				return grandparent()->leftTree;
			}
			else
			{
				return grandparent()->rightTree;
			}
		}
		// 获取兄弟节点
		Node* sibling() 
		{
			if (parent == nullptr)
			{
				return nullptr;
			}
			if (parent->leftTree == this)
			{
				return parent->rightTree;
			}
			else
			{
				return parent->leftTree;
			}
		}
	};

public:
	bst()
	{
		// 构建叶子节点
		NIL = new Node();
		NIL->color = BLACK;
		root = nullptr;
	}

private:
	// 根节点
	Node* root;
	// 叶子节点
	Node* NIL;
}