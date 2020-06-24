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
	// 右旋
	void rotate_right(Node* p)
	{
		// 转轴就是根了，还旋转啥
		if (p->parent == NULL)
		{
			root = p;
			return;
		}

		// pivot的祖父节点
		Node* gp = p->grandparent();
		// pivot的父节点
		Node* fa = p->parent;
		// pivot的右孩子
		Node* y = p->rightTree;

		// fa的左子树以前连接的是p，现在连接p的右孩子
		fa->leftTree = y;
		// 不是叶子赋值一下爸爸
		if (y != NIL) 
		{
			y->parent = fa;
		}
		// p现在作为p的左子树和fa的父亲
		p->rightTree = fa;
		fa->parent = p;

		// fa如果以前就是树的根节点，这里替换成p
		if (root == fa)
		{
			root = p;
		}
		// 设置祖父节点
		p->parent = gp;

		// 如果祖父节点存在，左孩子或者右孩子替换成p
		if (gp != NULL) 
		{
			if (gp->leftTree == fa)
			{
				gp->leftTree = p;
			}
			else
			{
				gp->rightTree = p;
			}
		}
	}
	// 左旋
	void rotate_left(Node* p)
	{
		// 转轴就是根了，还旋转啥
		if (p->parent == NULL)
		{
			root = p;
			return;
		}

		// 转轴的祖父节点
		Node* gp = p->grandparent();
		// 转轴的父节点
		Node* fa = p->parent;
		// 转轴的左孩子
		Node* y = p->leftTree;

		// fa的右孩子以前是p，旋转后fa成为了p的左孩子，fa的右孩子是p的左孩子
		fa->rightTree = y;
		// 不是叶子赋值一下爸爸
		if (y != NIL)
		{
			y->parent = fa;
		}
		// p作为fa和p的右子树的父节点
		p->leftTree = fa;
		fa->parent = p;

		// fa如果以前就是树的根节点，这里替换成p
		if (root == fa)
		{
			root = p;
		}
		// 设置祖父节点
		p->parent = gp;

		// 如果祖父节点存在，左孩子或者右孩子替换成p
		if (gp != NULL) 
		{
			if (gp->leftTree == fa)
			{
				gp->leftTree = p;
			}
			else 
			{
				gp->rightTree = p;
			}
		}
	}
	// 指定节点进行中序遍历
	void inorder(Node* p)
	{
		if (p == NIL)
		{
			return;
		}

		if (p->leftTree)
		{
			inorder(p->leftTree);
		}

		std::cout<<p->value<<" ";

		if (p->rightTree)
		{
			inorder(p->rightTree);
		}
	}
	// 输出节点颜色
	std::string outputColor(bool color)
	{
		return color ? "BLACK" : "RED"
	}
	// 获取指定节点上的最小值的孩子
	Node* getSmallestChild(Node* p)
	{
		if (p->leftTree == NIL)
		{
			return p;
		}
		// 一直向左孩子找吧
		return getSmallestChild(p->leftTree);
	}
	// 删除节点
	// 指定节点处插入节点
	void insert(Node* p, int data)
	{
		if (p == NULL)
		{
			Node* tmp = new Node;
			tmp->value = data;
			tmp->leftTree = tmp->rightTree = NIL;
			tmp->parent = NULL;
			// 插入各种case
			insert_case(tmp);
			return;
		}
		// 左孩子小于等于，右孩子大于
		// 新节点的值大于等于当前节点
		if (p->value >= data)
		{
			if (p->leftTree != NIL)
			{
				insert(p->leftTree, data);
			}
			else
			{
				Node* tmp = new Node;
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				// 新节点放在左子树上
				p->leftTree = tmp;
				// 插入各种case
				insert_case(tmp);
			}
		}
		else
		{
			if (p->rightTree != NIL)
			{
				insert(p->rightTree, data);
			}
			else 
			{
				Node* tmp = new Node;
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				// 新节点放在右子树上
				p->rightTree = tmp;
				// 插入各种case
				insert_case(tmp);
			}
		}
	}
	// 各种插入case判断
	void insert_case(Node* p)
	{
		// case 1
		// 新节点N位于树的根上，没有父节点。
		// 在这种情形下，我们把它重绘为黑色以满足性质2
		// 因为它在每个路径上对黑节点数目增加一，性质5符合。
		// 结束
		if (p->parent == NULL)
		{
			root = p;
			p->color = BLACK;
			return;
		}
		// case 2
		// 新节点的父节点P是黑色，所以性质4没有失效（新节点是红色的）。
		// 在这种情形下，树仍是有效的。性质5也未受到威胁，尽管新节点N有两个黑色叶子子节点；
		// 但由于新节点N是红色，通过它的每个子节点的路径就都有同通过它所取代的黑色的叶子的路径同样数目的黑色节点，
		// 所以依然满足这个性质。
		if (p->parent->color == BLACK)
		{
			return;
		}

		if (p->parent->color == RED)
		{
			// 必有叔父节点，当然叔父节点有可能是叶子节点
			// case 3
			// 如果父节点P和叔父节点U二者都是红色，
			//（此时新插入节点N做为P的左子节点或右子节点都属于情形3，这里右图仅显示N做为P左子的情形）
			// 则我们可以将它们两个重绘为黑色并重绘祖父节点G为红色（用来保持性质5）。
			// 现在我们的新节点N有了一个黑色的父节点P。
			// 因为通过父节点P或叔父节点U的任何路径都必定通过祖父节点G，
			// 在这些路径上的黑节点数目没有改变。但是，红色的祖父节点G可能是根节点，
			// 这就违反了性质2，也有可能祖父节点G的父节点是红色的，这就违反了性质4。
			// 为了解决这个问题，我们在祖父节点G上递归地进行 case 1 的整个过程。
			//（把G当成是新加入的节点进行各种情形的检查）
			if (p->uncle()->color == RED)
			{
				p->parent->color = p->uncle()->color = BLACK;
				p->grandparent()->color = RED;
				insert_case(p->grandparent());
			}
			else
			{
				// 在余下的情形下，我们假定父节点P是其祖父G的左子节点。
				// 如果它是右子节点 case 4 和 case 5 中的 左 和 右 应当对调。
				// case 4
				// 父节点P是红色而叔父节点U是黑色或缺少，
				// 并且新节点N是其父节点P的右子节点而父节点P又是其父节点的左子节点。
				// 在这种情形下，我们进行一次左旋转调换新节点和其父节点的角色；
				// 接着，我们按 case 5 处理以前的父节点P以解决仍然失效的性质4。
				// 
				// case 5
				// 父节点P是红色而叔父节点U是黑色或缺少，新节点N是其父节点的左子节点，
				// 而父节点P又是其父节点G的左子节点。
				// 在这种情形下，我们进行针对祖父节点G的一次右旋转；
				// 在旋转产生的树中，以前的父节点P现在是新节点N和以前的祖父节点G的父节点。
				// 我们知道以前的祖父节点G是黑色，
				// 否则父节点P就不可能是红色（如果P和G都是红色就违反了性质4，所以G必须是黑色）。
				// 我们切换以前的父节点P和祖父节点G的颜色，结果的树满足性质4。性质5也仍然保持满足，
				// 因为通过这三个节点中任何一个的所有路径以前都通过祖父节点G，现在它们都通过以前的父节点P。
				// 在各自的情形下，这都是三个节点中唯一的黑色节点。
				
				// p是父节点的右子树，p的父亲是p的祖父的左孩子
				// avl中的LR旋转，即p为轴左旋，
				if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent)
				{

				}
			}
		}
	}

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