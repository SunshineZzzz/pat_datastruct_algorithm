#include <stdio.h>
#include <stdlib.h>

// 顶点节点
struct node
{
	// 顶点数组的下标
	int vertex;
	// 邻接顶点链表
	struct node* next;
};
// 邻接表实现图
struct Graph
{
	// 顶点个数
	int numVertices;
	// 顶点数组，数组元素是 node*
	struct node** adjLists;
};

// 创建顶点
struct node* CreateNode(int v)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = nullptr;

	return newNode;
}

// 创建图
struct Graph* CreateAGraph(int vertices)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
	graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));

	for (int i = 0; i < vertices; ++i)
	{
		graph->adjLists[i] = nullptr;
	}

	return graph;
}

// 添加边，下标s与下标d顶点间的边
void AddEdge(struct Graph* graph, int s, int d)
{
	struct node* newNode = CreateNode(d);
	// 链表连起来
	newNode->next = graph->adjLists[s];
	// s - d
	graph->adjLists[s] = newNode;

	newNode = CreateNode(s);
	// 链表连起来
	newNode->next = graph->adjLists[d];
	// d - s
	graph->adjLists[d] = newNode;
}

// 打印图
void PrintGraph(struct Graph* graph)
{
	for (int v = 0; v < graph->numVertices; ++v)
	{
		struct node* temp = graph->adjLists[v];
		printf("Vertex %d\n: ", v);
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

// 释放图
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
	free(graph);
	graph = nullptr;
}

int main(int argc, char* argv[])
{
	struct Graph* graph = CreateAGraph(4);

	AddEdge(graph, 0, 1);
	AddEdge(graph, 0, 2);
	AddEdge(graph, 0, 3);
	AddEdge(graph, 1, 2);

	PrintGraph(graph);

	FreeGraph(graph);

	return 0;
}