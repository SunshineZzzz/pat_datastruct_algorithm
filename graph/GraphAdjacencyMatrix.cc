#include <iostream>

// 无向图
class Graph
{
private:
	// 矩阵
	bool** adjMatrix;
	// 顶点数
	int numVertices;

public:
	Graph(int numVertices)
	{
		this->numVertices = numVertices;
		this->adjMatrix = new bool*[numVertices];
		for (int i = 0; i < numVertices; ++i)
		{
			this->adjMatrix[i] = new bool[numVertices];
			for (int j = 0; j < numVertices; ++j)
			{
				this->adjMatrix[i][j] = false;
			}
		}
	}
	~Graph()
	{
		for (int i = 0; i < numVertices; ++i)
		{
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
	}

	// 增加边
	void AddEdge(int i, int j)
	{
		if (i >= numVertices || j >= numVertices) 
		{
			return;
		}

		adjMatrix[i][j] = true;
		adjMatrix[j][i] = true;
	}
	// 移除边
	void RemoveEdge(int i, int j)
	{
		if (i >= numVertices || j >= numVertices)
		{
			return;
		}

		adjMatrix[i][j] = false;
		adjMatrix[j][i] = false;
	}
	// 打印
	void toString()
	{
		for (int i = 0; i < numVertices; ++i)
		{
			for (int j = 0; j < numVertices; ++j)
			{
				std::cout << "[ " << i << ", " << j << " ]"
					<< " = " << adjMatrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

int main() 
{
	Graph g(4);

	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(1, 2);
	g.AddEdge(2, 0);
	g.AddEdge(2, 3);

	g.toString();

	return 0;
}