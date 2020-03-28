// 完全二叉树由于其结构上的特点，通常采用顺序存储方式存储。
// 一棵有n个结点的完全二叉树的所有结点从1到n编号，就得到结点的一个线性系列。
// 完全二叉树除最下面一层外，各层都被结点充满了，
// 每一层结点的个数恰好是上一层结点个数的2倍，
// 因此通过一个结点的编号就可以推知它的双亲结点及左，右孩子结点的编号：
// ① 当 2i ≤ n 时，结点 i 的左孩子是 2i，否则结点i没有左孩子；
// ② 当 2i+1 ≤ n 时，结点i的右孩子是 2i+1，否则结点i没有右孩子；
// ③ 当 i ≠ 1 时，结点i的双亲是结点 i/2；
// 
// 对于一般的二叉树，如果仍按照从上至下，从左到右的顺序将树中的结点顺序存储在一维数组中，
// 则数组元素下标之间的关系不能够反映二叉树中结点之间的逻辑关系。
// 这时假设将一般二叉树进行改造，增添一些并不存在的空结点，使之成为一棵完全二叉树的形式，
// 然后再用一维数组顺序存储。在二叉树中假设增添的结点在数组中所对应的元素值为"空"用^表示。
// 
//                    1-A
//        /                          \
//          2-B	                     3-O
//      /        \				   /     \
//     4-^ 	     5-^             6-M    7-^
//    /   \     /   \            /   \
//   8-^ 9-^  10-^ 11-^         12-^ 13-C


#include <string>
#include <iostream>
#include <vector>

class ArrayTree
{
public:
	ArrayTree()
	{
		m_arr.reserve(1024);
		// 0下标占位
		m_arr.emplace_back("");
	}
	~ArrayTree()
	{
	}

	// 从标准输入中读取
	// 按照从上到下从左到右的顺序读入
	void ReadStdIn()
	{
		std::string temp;
		while (std::cin >> temp)
		{
			if (temp == "null")
			{
				m_arr.emplace_back("^");
				continue;
			}
			m_arr.emplace_back(temp);
		}
	}
	// 判断二叉树是否为空
	bool IsEmpty()
	{
		return m_arr.size() <= 1;
	}
	// 返回根节点
	std::string GetRoot()
	{
		if (m_arr.size() > 1)
		{
			return m_arr[1];
		}

		return "^";
	}
	// 返回指定节点的父节点
	bool GetParent(size_t index, std::string& parent)
	{
		if (index < 1 || index > m_arr.size())
		{
			return false;
		}

		if (index == 1)
		{
			parent =  m_arr[1];
			return true;
		}

		parent = m_arr[index / 2];
		return true;
	}
	// 返回指定节点的左孩子
	bool GetLeftChild(size_t index, std::string& leftchild)
	{
		if (index < 1 || index > m_arr.size())
		{
			return false;
		}

		if (2 * index > m_arr.size())
		{
			leftchild = "";
			return true;
		}

		leftchild = m_arr[2 * index];
		return true;

	}
	// 返回指定节点的右孩子
	bool GetRightChild(size_t index, std::string& rightchild)
	{
		if (index < 1 || index > m_arr.size())
		{
			return false;
		}

		if (2 * index + 1 > m_arr.size())
		{
			rightchild = "";
			return true;
		}

		rightchild = m_arr[2 * index + 1];
		return true;
	}
	// 从上到下从左到右顺序比遍历打印
	void ToString()
	{
		if (IsEmpty())
		{
			std::cout << "" << std::endl;
			return;
		}

		int i = 0;
		for (const auto& elem : m_arr)
		{
			if(i == 0)
			{
				continue;
			}

			std::cout << i++ << "-" << elem << " ";
		}
		std::cout << "\n";
	}

private:
	// 动态数组
	// 按照送上到下从左到右的顺序存储
	std::vector<std::string> m_arr;
};

int main(int argc, char* argv[])
{
	ArrayTree tree;
	tree.ReadStdIn();

	std::cout << "This tree: ";
	tree.ToString();

	std::cout << "Tree root: " << tree.GetRoot() << std::endl;

	std::string parent;
	auto rst = tree.GetParent(13, parent);
	std::cout << "Tree 13 index of parent: " << parent << std::endl;

	rst = tree.GetParent(6, parent);
	std::cout << "Tree 6 index of parent: " << parent << std::endl;

	rst = tree.GetParent(3, parent);
	std::cout << "Tree 3 index of parent: " << parent << std::endl;

	rst = tree.GetParent(1, parent);
	std::cout << "Tree 1 index of parent: " << parent << std::endl;

	std::string leftchild;
	rst = tree.GetLeftChild(3, leftchild);
	std::cout << "Tree 3 index of leftchild: " << leftchild << std::endl;

	rst = tree.GetLeftChild(1, leftchild);
	std::cout << "Tree 1 index of leftchild: " << leftchild << std::endl;

	std::string rightchild;
	rst = tree.GetRightChild(3, rightchild);
	std::cout << "Tree 3 index of rightchild: " << rightchild << std::endl;

	rst = tree.GetRightChild(6, rightchild);
	std::cout << "Tree 6 index of rightchild: " << rightchild << std::endl;

	rst = tree.GetRightChild(1, rightchild);
	std::cout << "Tree 1 index of rightchild: " << rightchild << std::endl;

	return 0;
}