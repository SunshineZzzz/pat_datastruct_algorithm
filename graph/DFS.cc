#include <stdio.h>
#include <stdlib.h>

// 顶点节点
struct node
{
	// 顶点数组下标
	int vertex;
	// 邻接顶点链表
	struct node* next;
};
// 邻接表实现图
struct Graph
{
	// 顶点数
	int numVertices;
	// 访问栈
	bool* vistied;
	// 顶点指针数组
	struct node** adjLists;
};

// 创建图
struct Graph* CreateGraph(int vertices)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
	graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
	graph->vistied = (bool*)malloc(vertices * sizeof(bool));

	for (int i = 0; i < vertices; ++i)
	{
		graph->adjLists[i] = nullptr;
		graph->vistied[i] = false;
	}

	return graph;
}

// 创建顶点
struct node* CreateNode(int v)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = nullptr;

	return newNode;
}

// 增加边
void AddEdge(struct Graph* graph, int src, int dest)
{
	struct node* newNode = CreateNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;

	newNode = CreateNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
}

// 打印图
void PrintGraph(Graph* graph)
{
	for (int v = 0; v < graph->numVertices; ++v)
	{
		struct node* temp = graph->adjLists[v];
		printf("Adjacency list of vertex %d\n", v);
		while (true)
		{
			printf("%d -> ", temp->vertex);
			temp = temp->next;
			if (!temp)
			{
				printf("NULL");
				break;
			}
		}
		printf("\n");
	}
}

// 深度优先遍历
void DFS(struct Graph* graph, int vertex)
{
	struct node* temp = graph->adjLists[vertex];
	
	graph->vistied[vertex] = true;
	printf("Visited %d \n", vertex);

	while (temp != nullptr)
	{
		int connectedVertex = temp->vertex;

		if (graph->vistied[connectedVertex] == false)
		{
			DFS(graph, connectedVertex);
		}
		temp = temp->next;
	}
}

// 释放
void FreeGraph(struct Graph*& graph)
{
	if (graph == nullptr)
	{
		return;
	}

	for (int i = 0; i < graph->numVertices; ++i)
	{
		struct node* next = graph->adjLists[i];
		struct node* temp = nullptr;
		while (next)
		{
			temp = next;
			next = next->next;
			free(temp);
		}
	}

	free(graph->adjLists);
	free(graph->vistied);
	free(graph);
	graph = nullptr;
}

int main()
{
	struct Graph* graph = CreateGraph(4);

	AddEdge(graph, 0, 1);
	AddEdge(graph, 0, 2);
	AddEdge(graph, 1, 2);
	AddEdge(graph, 2, 3);

	PrintGraph(graph);

	// 下标顶点2作为入口进行深度优先遍历
	DFS(graph, 2);

	FreeGraph(graph);

	return 0;
}