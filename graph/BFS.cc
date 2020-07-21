#include <iostream>
#include <list>

class Graph
{
private:
	// 顶点个数
	int numVertices;
	// 邻接表实现，adjLists是一个数组，元素为list<int>*
	std::list<int>* adjLists;
	// 访问标记数组
	bool* visited;

public:
	Graph(int vertices) :
		numVertices(vertices)
	{
		adjLists = new std::list<int>[numVertices];
		visited = new bool[numVertices];
		for (int i = 0; i < numVertices; ++i)
		{
			visited[i] = false;
		}
	}
	~Graph()
	{
		delete[] adjLists;
		adjLists = nullptr;
		delete[] visited;
		visited = nullptr;
	}

	// 插入边
	void addEdge(int src, int dest)
	{
		adjLists[src].push_back(dest);
		adjLists[dest].push_back(src);
	}
	// 广度优先搜索
	void Graph::BFS(int startVertex) 
	{
		// 队列
		std::list<int> queue;

		visited[startVertex] = true;
		queue.push_back(startVertex);
		while (!queue.empty())
		{
			int currVertex = queue.front();
			std::cout << "Visited " << currVertex << " ";
			queue.pop_front();

			for (const auto& adjVertex : adjLists[currVertex])
			{
				if (!visited[adjVertex])
				{
					visited[adjVertex] = true;
					queue.push_back(adjVertex);
				}
			}
		}
	}
};

int main()
{
	Graph g(4);
	
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	g.BFS(2);

	return 0;
}