// 参考：https://www.sanfoundry.com/cpp-program-implement-red-black-tree/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <ctime>

using namespace std;

// 递归打印孩子时候空格增量
#define INDENT_STEP 4

// 颜色
enum color 
{ 
	RED, 
	BLACK 
};

// 红黑树节点
typedef struct rbtree_node
{
	// 颜色
	enum color color;
	// key
	void* key;
	// value
	void* value;
	// 左孩子，右孩子，父亲
	rbtree_node*left, *right, *parent;
}* node;

// 红黑树
typedef struct rbtree_t
{
	// 根节点
	node root;
}* rbtree;

// 红黑树各种操作的实现
class RBTree
{
public:
	// 节点比较函数类型
	typedef int(*compare_func)(void* left, void* right);
	// 创建红黑树
	rbtree rbtree_create()
	{
		rbtree t = new rbtree_t;
		t->root = nullptr;
		// 检测红黑树性质
		verify_properties(t);

		return t;
	}
	// 获取指定节点的value
	void* rbtree_lookup(rbtree t, void* key, compare_func compare)
	{
		node n = lookup_node(t, key, compare);
		return n == nullptr ? nullptr : n->value;
	}
	// 红黑树插入
	void rbtree_insert(rbtree t, void* key, void* value, compare_func compare)
	{
		// 创建新节点
		// 新节点颜色设置为红色
		// 如果设为黑色，就会导致根到叶子的路径上有一条路上，
		// 多一个额外的黑节点，这个是很难调整的。
		// 但是设为红色节点后，可能会导致出现两个连续红色节点的冲突，
		// 那么可以通过颜色调换（color flips）和树旋转来调整。
		node inserted_node = new_node(key, value, RED, nullptr, nullptr);
		if (t->root == nullptr)
		{
			t->root = inserted_node;
		}
		else
		{
			node n = t->root;
			while (1)
			{
				int comp_result = compare(key, n->key);
				// 找到就返回吧
				if (comp_result == 0)
				{
					n->value = value;
					return;
				}
				// 小，向左边找
				else if (comp_result < 0)
				{
					if (n->left == nullptr)
					{
						// 插入
						n->left = inserted_node;
						break;
					}
					else
					{
						n = n->left;
					}
				}
				// 大，向右边找
				else
				{
					assert(comp_result > 0);
					if (n->right == nullptr)
					{
						// 插入
						n->right = inserted_node;
						break;
					}
					else
					{
						n = n->right;
					}
				}
			}
			inserted_node->parent = n;
		}
		// 以上都是二叉搜索树插入过程
		// 下面调平
		insert_case1(t, inserted_node);
		// 检测红黑树性质
		verify_properties(t);
	}
	// 删除节点
	void RBTree::rbtree_delete(rbtree t, void* key, compare_func compare)
	{
		node child;
		// 找到要删除的节点
		node n = lookup_node(t, key, compare);
		// 找不到还搞毛
		if (n == nullptr)
		{
			return;
		}
		// 相较于插入操作，红黑树的删除操作则要更为复杂一些。
		// 删除操作首先要确定待删除节点有几个孩子，如果有两个孩子，
		// 不能直接删除该节点。
		// 而是要先找到该节点的前驱（该节点左子树中最大的节点）或者
		// 后继（该节点右子树中最小的节点），然后将前驱或者后继的值复制到要删除的节点中，
		// 最后再将前驱或后继删除。
		// 由于前驱和后继至多只有一个孩子节点，
		// 这样我们就把原来要删除的节点有两个孩子的问题转化为只有一个孩子节点的问题，
		// 问题被简化了一些。
		// 我们并不关心最终被删除的节点是否是我们开始想要删除的那个节点，
		// 只要节点里的值最终被删除就行了，至于树结构如何变化，这个并不重要。
		if (n->left != nullptr && n->right != nullptr)
		{
			// 待删除节点中左孩子找最大那个
			node pred = maximum_node(n->left);
			// 找到后赋值一下
			n->key = pred->key;
			n->value = pred->value;
			// 后面要删掉pred
			n = pred;
		}
		// 转换成删除最多只有一个节点的问题了
		// 不可能右两个孩子！
		assert(n->left == nullptr || n->right == nullptr);
		// 取到这个孩子，当然也有可能是叶子节点
		child = n->right == nullptr ? n->left : n->right;
		// 红黑树删除操作的复杂度在于删除节点的颜色，当删除的节点是红色时，
		// 直接拿其孩子节点补空位即可。因为删除红色节点，
		// 性质5（从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点）仍能够被满足。
		// 当删除的节点是黑色时，那么所有经过该节点的路径上的黑节点数量少了一个，破坏了性质5。
		// 如果该节点的孩子为红色，直接拿孩子节点替换被删除的节点，并将孩子节点染成黑色，
		// 即可恢复性质5。但如果孩子节点为黑色，处理起来就要复杂的多。分为6种情况，下面会展开说明。
		if (node_color(n) == BLACK && node_color(child) == RED)
		{
			child->color = BLACK;
		}
		else if (node_color(n) == BLACK && node_color(child) == BLACK)
		{
			// 在展开说明之前，我们先做一些假设，方便说明。
			// 这里假设最终被删除的节点为X（至多只有一个孩子节点），
			// 其孩子节点为N，X的兄弟节点为S，S的左节点为 SL，右节点为 SR。
			// 接下来讨论是建立在节点 X 被删除，节点 N 替换X的基础上进行的。
			// 这里说明把被删除的节点X特地拎出来说一下的原因是防止大家误以为节点N会被删除，
			// 不然后面就会看不明白。
			// 
			// 需要进一步讨论的是在要删除的节点和它的儿子二者都是黑色的时候，
			// 这是一种复杂的情况
			//（这种情况下该结点的两个儿子都是叶子结点，否则若其中一个儿子是黑色非叶子结点，
			// 另一个儿子是叶子结点，那么从该结点通过非叶子结点儿子的路径上的黑色结点数最小为2，
			// 而从该结点到另一个叶子结点儿子的路径上的黑色结点数为1，违反了性质5）。
			// 我们首先把要删除的节点替换为它的儿子。
			// 出于方便，称呼这个儿子为N（在新的位置上），
			// 称呼它(待删除的节点)的兄弟（它父亲的另一个儿子）为S。
			// 我们还是使用P称呼N的父亲，SL称呼S的左儿子，SR称呼S的右儿子。
			delete_case1(t, n);
		}
		// 这里不会有颜色的调换
		replace_node(t, n, child);
		// 释放
		free(n);
		// 检测
		verify_properties(t);
	}
	// 祖父
	node grandparent(node n)
	{
		assert(n != nullptr);
		assert(n->parent != nullptr);
		assert(n->parent->parent != nullptr);
		return n->parent->parent;
	}
	// 兄弟
	node sibling(node n)
	{
		assert(n != nullptr);
		assert(n->parent != nullptr);
		if (n == n->parent->left)
		{
			return n->parent->right;
		}
		else
		{
			return n->parent->left;
		}
	}
	// 叔父节点
	node uncle(node n)
	{
		assert(n != nullptr);
		assert(n->parent != nullptr);
		assert(n->parent->parent != nullptr);
		return sibling(n->parent);
	}
	// 检测红黑树性质
	void verify_properties(rbtree t)
	{
		// 1.节点是红色或黑色
		verify_property_1(t->root);
		// 2.根是黑色
		verify_property_2(t->root);
		// 3.所有叶子必须是黑色，这个就不检测了，都是nullptr，默认都是黑色的
		// 4.每个红色节点必须有两个黑色的子节点
		// （从每个叶子到根的所有路径上不能有两个连续的红色节点）
		verify_property_4(t->root);
		// 5.从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点
		verify_property_5(t->root);
	}
	// 检测所有节点是红色或黑色
	void verify_property_1(node n)
	{
		assert(node_color(n) == RED || node_color(n) == BLACK);
		if (n == nullptr)
		{
			return;
		}
		verify_property_1(n->left);
		verify_property_1(n->right);
	}
	// 根是黑色
	void verify_property_2(node root)
	{
		assert(node_color(root) == BLACK);
	}
	// 返回节点颜色
	color node_color(node n)
	{
		return n == nullptr ? BLACK : n->color;
	}
	// 每个红色节点必须有两个黑色的子节点。
	// （从每个叶子到根的所有路径上不能有两个连续的红色节点。）
	void verify_property_4(node n)
	{
		if (node_color(n) == RED)
		{
			assert(node_color(n->left) == BLACK);
			assert(node_color(n->right) == BLACK);
			assert(node_color(n->parent) == BLACK);
		}
		// 没有孩子了，还递归啥
		if (n == nullptr)
		{
			return;
		}
		verify_property_4(n->left);
		verify_property_4(n->right);
	}
	// 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点
	void verify_property_5(node root)
	{
		// 获取给节点到其任意节点的黑色节点个数
		int black_count_path = -1;
		verify_property_5_helper(root, 0, &black_count_path);
	}
	// n - 要检测的节点
	// black_count - 用于递归记录黑色节点个数
	// path_black_count - 其中一条路径的黑色节点个数
	void verify_property_5_helper(node n, int black_count, int* path_black_count)
	{
		if (node_color(n) == BLACK)
		{
			black_count++;
		}
		if (n == nullptr)
		{
			// 都到叶子了，没有给 path_black_count 赋值，现在赋值
			if (*path_black_count == -1)
			{
				*path_black_count = black_count;
			}
			else
			{
				// 某条路径已经赋值，判断是满足性质
				assert(black_count == *path_black_count);
			}
			return;
		}
		verify_property_5_helper(n->left, black_count, path_black_count);
		verify_property_5_helper(n->right, black_count, path_black_count);
	}
	// 创建新节点
	node new_node(void* k, void* v, color n_color, node left, node right)
	{
		node result = new rbtree_node;
		result->key = k;
		result->value = v;
		result->color = n_color;
		result->left = left;
		result->right = right;
		if (left != nullptr)
		{
			left->parent = result;
		}
		if (right != nullptr)
		{
			right->parent = result;
		}
		result->parent = nullptr;

		return result;
	}
	// 二叉搜索树查找指定节点
	node lookup_node(rbtree t, void* key, compare_func compare)
	{
		node n = t->root;
		while (n != nullptr)
		{
			int comp_result = compare(key, n->key);
			// 和当前节点相同
			if (comp_result == 0)
			{
				return n;
			}
			// 比当前节点小，向左子树继续找
			else if (comp_result < 0)
			{
				n = n->left;
			}
			// 比当前节点大，向右孩子继续找
			else
			{
				assert(comp_result > 0);
				n = n->right;
			}
		}
		return n;
	}
	// 左旋
	void rotate_left(rbtree t, node n)
	{
		// 找到转轴
		node r = n->right;
		// 1.转轴的父亲节点还没有修改成n的父节点
		// 2.n的父亲的左右孩子指向也没有修改呢
		// 3.n没有父节点，需要将 t->root 赋值为转轴
		// 用r节点替换n节点
		replace_node(t, n, r);
		// n右边孩子以前连接的是转轴，左旋转后连接的是转轴的左孩子
		n->right = r->left;
		// 转轴的左孩子不为叶子结点，修改左孩子的父节点
		if (r->left != nullptr)
		{
			r->left->parent = n;
		}
		// 完成旋转
		r->left = n;
		n->parent = r;
	}
	// 右旋
	void rotate_right(rbtree t, node n)
	{
		// 找到转轴
		node l = n->left;
		// 用l节点替换n节点
		replace_node(t, n, l);
		// n左边孩子以前连接的是转轴，右旋转后连接的是转轴的右孩子
		n->left = l->right;
		// 转轴的右孩子不为叶子结点，修改右孩子的父节点
		if (l->right != nullptr)
		{
			l->right->parent = n;
		}
		// 完成旋转
		l->right = n;
		n->parent = l;
	}
	// 用newn节点替换oldn节点
	void replace_node(rbtree t, node oldn, node newn)
	{
		// 被替换节点没有父节点
		if (oldn->parent == nullptr)
		{
			// 根节点替换为新节点
			t->root = newn;
		}
		else
		{
			// 修改被替换节点左或者右孩子指向
			if (oldn == oldn->parent->left)
			{
				oldn->parent->left = newn;
			}
			else
			{
				oldn->parent->right = newn;
			}
		}
		// 新节点不是叶子结点，修改父节点指向
		if (newn != nullptr)
		{
			newn->parent = oldn->parent;
		}
	}
	// 情形1:新节点N位于树的根上，没有父节点。
	// 在这种情形下，我们把它重绘为黑色以满足性质2。
	// 因为它在每个路径上对黑节点数目增加一，性质5符合。
	void insert_case1(rbtree t, node n)
	{
		if (n->parent == nullptr)
		{
			n->color = BLACK;
		}
		else
		{
			insert_case2(t, n);
		}
	}
	// 情形2:新节点的父节点P是黑色，所以性质4没有失效（新节点是红色的）。
	// 在这种情形下，树仍是有效的。性质5也未受到威胁，尽管新节点N有两个黑色叶子子节点；
	// 但由于新节点N是红色，通过它的每个子节点的路径就都有同通过它所取代的黑色的叶子的
	// 路径同样数目的黑色节点，所以依然满足这个性质。
	void insert_case2(rbtree t, node n)
	{
		if (node_color(n->parent) == BLACK)
		{
			return;
		}
		else
		{
			insert_case3(t, n);
		}
	}
	// 如果父节点P和叔父节点U二者都是红色，
	//（此时新插入节点N做为P的左子节点或右子节点都属于情形3）
	// 则我们可以将它们两个重绘为黑色并重绘祖父节点G为红色（用来保持性质5）。
	// 现在我们的新节点N有了一个黑色的父节点P。
	// 因为通过父节点P或叔父节点U的任何路径都必定通过祖父节点G，
	// 在这些路径上的黑节点数目没有改变。但是，红色的祖父节点G可能是根节点，
	// 这就违反了性质2，也有可能祖父节点G的父节点是红色的，这就违反了性质4。
	// 为了解决这个问题，我们在祖父节点G上递归地进行情形1的整个过程。
	//（把G当成是新加入的节点进行各种情形的检查）
	void insert_case3(rbtree t, node n)
	{
		if (node_color(uncle(n)) == RED)
		{
			n->parent->color = BLACK;
			uncle(n)->color = BLACK;
			grandparent(n)->color = RED;
			insert_case1(t, grandparent(n));
		}
		else
		{
			insert_case4(t, n);
		}
	}
	// 父节点P是红色而叔父节点U是黑色或缺少，
	// 并且新节点N是其父节点P的右子节点而父节点P又是其父节点的左子节点。
	// 在这种情形下，我们进行一次左旋转调换新节点和其父节点的角色;
	// 接着，我们按情形5处理以前的父节点P以解决仍然失效的性质4。
	// 注意这个改变会导致某些路径通过它们以前不通过的新节点N（比如图中1号叶子节点）
	// 或不通过节点P（比如图中3号叶子节点），但由于这两个节点都是红色的，所以性质5仍有效。
	void insert_case4(rbtree t, node n)
	{
		// avl中的LR双旋，先RR单旋，即左旋，旋转完成后别忘了重新赋值n
		if (n == n->parent->right && n->parent == grandparent(n)->left)
		{
			rotate_left(t, n->parent);
			n = n->left;
		}
		// avl中的RL双旋，先LL单旋，即右旋，旋转完成后别忘了重新赋值n
		else if (n == n->parent->left && n->parent == grandparent(n)->right)
		{
			rotate_right(t, n->parent);
			n = n->right;
		}
		insert_case5(t, n);
	}
	// 父节点P是红色而叔父节点U是黑色或缺少，
	// 新节点N是其父节点的左子节点，而父节点P又是其父节点G的左子节点。
	// 在这种情形下，我们进行针对祖父节点G的一次右旋转；
	// 在旋转产生的树中，以前的父节点P现在是新节点N和以前的祖父节点G的父节点。
	// 我们知道以前的祖父节点G是黑色，否则父节点P就不可能是红色
	//（如果P和G都是红色就违反了性质4，所以G必须是黑色）。
	// 我们切换以前的父节点P和祖父节点G的颜色，结果的树满足性质4。
	// 性质5也仍然保持满足，因为通过这三个节点中任何一个的所有路径以前都通过祖父节点G，
	// 现在它们都通过以前的父节点P。在各自的情形下，这都是三个节点中唯一的黑色节点。
	void insert_case5(rbtree t, node n)
	{
		n->parent->color = BLACK;
		grandparent(n)->color = RED;
		// 刚才完成了RR单旋，现在完成LL单旋，即右旋
		if (n == n->parent->left && n->parent == grandparent(n)->left)
		{
			rotate_right(t, grandparent(n));
		}
		// 刚才完成了LL单旋，现在完成RR单旋，即左旋
		else
		{
			assert(n == n->parent->right && n->parent == grandparent(n)->right);
			rotate_left(t, grandparent(n));
		}
	}
	// 二叉搜索树要删除的结点有左，右两棵子树：
	// 用另一结点替代被删除结点：右子树的最小元素 或者 左子树的最大元素
	// 查找某个节点的最大节点
	node maximum_node(node n)
	{
		assert(n != nullptr);
		while (n->right != nullptr)
		{
			n = n->right;
		}
		return n;
	}
	// 情形1:N是新的根。在这种情形下，我们就做完了。
	// 我们从所有路径去除了一个黑色节点，而新根是黑色的，所以性质都保持着。
	// 上面是维基百科中关于红黑树删除的情况一说明，由于没有配图，看的有点晕。
	// 经过思考，我觉得可能会是下面这种情形：
	// 要删除的节点X是根节点，且左右孩子节点均为叶子节点，
	// 此时将节点X用叶子节点替换完成删除操作。
	void delete_case1(rbtree t, node n)
	{
		if (n->parent == nullptr)
		{
			return;
		}
		else
		{
			delete_case2(t, n);
		}
	}
	// S是红色。在这种情形下我们在N的父亲上做左旋转，
	// 把红色兄弟转换成N的祖父，我们接着对调N的父亲和祖父的颜色。
	// 完成这两个操作后，尽管所有路径上黑色节点的数目没有改变，
	// 但现在N有了一个黑色的兄弟和一个红色的父亲（它的新兄弟是黑色因为它是红色S的一个儿子），
	// 所以我们可以接下去按 情形4、情形5 或 情形6 来处理。
	//（注意：这里的图中没有显示出来，N是删除了黑色节点后替换上来的子节点，
	// 所以这个过程中由P->X->N变成了P->N，实际上是少了一个黑色节点，
	// 让他们做新兄弟肯定是不平衡的，还需后面继续处理。）
	void delete_case2(rbtree t, node n)
	{
		if (node_color(sibling(n)) == RED)
		{
			n->parent->color = RED;
			sibling(n)->color = BLACK;
			if (n == n->parent->left)
			{
				rotate_left(t, n->parent);
			}
			else
			{
				rotate_right(t, n->parent);
			}
		}
		delete_case3(t, n);
	}
	//  N的父亲、S和S的儿子都是黑色的。
	// 在这种情形下，我们简单的重绘S为红色。结果是通过S的所有路径，
	// 它们就是以前 不 通过N的那些路径，都少了一个黑色节点。
	// 因为删除N的初始的父亲使通过N的所有路径少了一个黑色节点，这使事情都平衡了起来。
	// 但是，通过P的所有路径现在比不通过P的路径少了一个黑色节点，所以仍然违反性质5。
	// 要修正这个问题，我们要从 情形1 开始，在P上做重新平衡处理。
	void delete_case3(rbtree t, node n)
	{
		if (node_color(n->parent) == BLACK && 
			node_color(sibling(n)) == BLACK &&
			node_color(sibling(n)->left) == BLACK && 
			node_color(sibling(n)->right) == BLACK)
		{
			sibling(n)->color = RED;
			delete_case1(t, n->parent);
		}
		else
		{
			delete_case4(t, n);
		}
	}
	// S和S的儿子都是黑色，但是N的父亲是红色。
	// 在这种情形下，我们简单的交换N的兄弟和父亲的颜色。
	// 这不影响不通过N的路径的黑色节点的数目，但是它在通过N的路径上对黑色节点数目增加了一，
	// 添补了在这些路径上删除的黑色节点。
	void delete_case4(rbtree t, node n)
	{
		if (node_color(n->parent) == RED && 
			node_color(sibling(n)) == BLACK &&
			node_color(sibling(n)->left) == BLACK && 
			node_color(sibling(n)->right) == BLACK)
		{
			sibling(n)->color = RED;
			n->parent->color = BLACK;
		}
		else
		{
			delete_case5(t, n);
		}
	}
	// S是黑色，S的左儿子是红色，S的右儿子是黑色，而N是它父亲的左儿子。
	// 在这种情形下我们在S上做右旋转，这样S的左儿子成为S的父亲和N的新兄弟。
	// 我们接着交换S和它的新父亲的颜色。所有路径仍有同样数目的黑色节点，
	// 但是现在N有了一个黑色兄弟，他的右儿子是红色的，
	// 所以我们进入了 情形6。N和它的父亲都不受这个变换的影响。
	void delete_case5(rbtree t, node n)
	{
		if (n == n->parent->left && 
			node_color(sibling(n)) == BLACK &&
			node_color(sibling(n)->left) == RED && 
			node_color(sibling(n)->right) == BLACK)
		{
			sibling(n)->color = RED;
			sibling(n)->left->color = BLACK;
			rotate_right(t, sibling(n));
		}
		else if (n == n->parent->right && 
			node_color(sibling(n)) == BLACK &&
			node_color(sibling(n)->right) == RED && 
			node_color(sibling(n)->left) == BLACK)
		{
			sibling(n)->color = RED;
			sibling(n)->right->color = BLACK;
			rotate_left(t, sibling(n));
		}
		delete_case6(t, n);
	}
	// S是黑色，S的右儿子是红色，而N是它父亲的左儿子，N的父节点颜色可红可黑。
	// 在这种情形下我们在N的父亲上做左旋转，这样S成为N的父亲（P）和S的右儿子的父亲。
	// 我们接着交换N的父亲和S的颜色，并使S的右儿子为黑色。
	// 子树在它的根上的仍是同样的颜色，所以性质3没有被违反。
	// 但是，N现在增加了一个黑色祖先：要么N的父亲变成黑色，
	// 要么它是黑色而S被增加为一个黑色祖父。所以，通过N的路径都增加了一个黑色节点。
	void delete_case6(rbtree t, node n)
	{
		sibling(n)->color = node_color(n->parent);
		n->parent->color = BLACK;
		if (n == n->parent->left)
		{
			assert(node_color(sibling(n)->right) == RED);
			sibling(n)->right->color = BLACK;
			rotate_left(t, n->parent);
		}
		else
		{
			assert(node_color(sibling(n)->left) == RED);
			sibling(n)->left->color = BLACK;
			rotate_right(t, n->parent);
		}
	}
};

// 节点值比较
// 0 - 左右相等
// -1 - 左边小于右边
// 1 - 左边大于右边
int compare_int(void* leftp, void* rightp)
{
	int left = (int)leftp;
	int right = (int)rightp;
	if (left < right)
	{
		return -1;
	}
	else if (left > right)
	{
		return 1;
	}
	else
	{
		assert(left == right);
		return 0;
	}
}

// 打印树
/*
打印形如：(x)包裹的是黑色节点 - <x>包裹的是红色节点
		right		
root
		left
*/
void print_tree_helper(node n, int indent)
{
	int i;
	if (n == nullptr)
	{
		fputs("<empty tree>", stdout);
		return;
	}
	
	if (n->right != nullptr)
	{
		print_tree_helper(n->right, indent + INDENT_STEP);
	}
	
	for (i = 0; i < indent; i++)
	{
		fputs(" ", stdout);
	}
	
	if (n->color == BLACK)
	{
		cout << "(" << (int)n->key << ")" << endl;
	}
	else
	{
		cout << "<" << (int)n->key << ">" << endl;
	}

	if (n->left != nullptr)
	{
		print_tree_helper(n->left, indent + INDENT_STEP);
	}
}

// 打印
void print_tree(rbtree t)
{
	// 打印树
	print_tree_helper(t->root, 0);
	// 换行
	puts("");
}


int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	int i;
	RBTree rbt;
	rbtree t = rbt.rbtree_create();
	
	// 模拟插入节点
	for (i = 0; i < 12; ++i)
	{
		int x = rand() % 10;
		int y = rand() % 10;
		print_tree(t);
		cout << "Inserting " << x << " -> " << y << endl << endl;
		rbt.rbtree_insert(t, (void*)x, (void*)y, compare_int);
		// 查找这个节点确保value设置正确
		assert(rbt.rbtree_lookup(t, (void*)x, compare_int) == (void*)y);
	}
	
	// 模拟删除
	for (i = 0; i < 15; ++i)
	{
		int x = rand() % 10;
		print_tree(t);
		cout << "Deleting key " << x << endl << endl;
		rbt.rbtree_delete(t, (void*)x, compare_int);
	}

	return 0;
}