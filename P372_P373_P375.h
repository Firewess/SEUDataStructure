#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/12/2
@File: P372_P373_P375.h
@Description: The eleventh week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <list>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

/*
以下对应于英文书P372 1
*/


/*
以下对应于英文书P373 2
*/
// 邻接表节点
class AdjListNode
{

private:
	int v;
	int weight;

public:
	AdjListNode(int v, int w)
	{
		this->v = v;
		weight = w;
	}

	int getV()
	{
		return v;
	}

	int getWeight()
	{
		return weight;
	}

};

// 图
class Graph
{

private:
	int V;    // 顶点个数
	list<AdjListNode> *adj;

public:
	Graph(int V);
	void addEdge(int u, int v, int weight);
	void shortestPath();
};

#define INF INT_MAX

Graph::Graph(int v)
{
	this->V = v;
	adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode node(v, weight);

	adj[u].push_back(node);
}

void Graph::shortestPath()
{
	int *dist = new int[V];
	fill(dist, dist + V, INF);
	dist[0] = 0;

	//循环遍历所有顶点和边,故时间复杂度为O(n+e)
	for (int j = 0; j < V; j++)
	{
		// 更新所有相邻的顶点
		list<AdjListNode>::iterator i;
		if (dist[j] != INF)
		{
			for (i = adj[j].begin(); i != adj[j].end(); ++i)
				if (dist[i->getV()] > dist[j] + i->getWeight())
					dist[i->getV()] = dist[j] + i->getWeight();
		}
	}

	// 打印结果
	for (int i = 0; i < V; i++)
	{
		cout << "0 -> " << i << " ";
		(dist[i] == INF) ? cout << "INFITE " : cout << dist[i];
		cout << endl;
	}

}

/*
以下对应于英文书P373 5
*/

/*
以下对应于英文书P375 17
*/
class MartixWDigraph
{
public:
	MartixWDigraph(int v = 0);
	void addEdge(int u, int v, int l);
	void AllLengths();
private:
	int** edgesList;
	int vertices;
	int edges;
};

MartixWDigraph::MartixWDigraph(int v)
{
	if (v < 0)
		throw "vertices cannot < 0";
	vertices = v;
	edgesList = new int*[vertices];
	edges = 0;
	for (int i = 0; i < vertices; i++)
	{
		edgesList[i] = new int[vertices];
		fill(edgesList[i], edgesList[i] + vertices, 0);
	}
}

void MartixWDigraph::addEdge(int u, int v, int l)
{
	edgesList[u][v] = l;
	edges++;
}

void MartixWDigraph::AllLengths()
{
	int** a = new int*[vertices];
	stack<int>** paths = new stack<int>*[vertices];
	for (int i = 0; i < vertices; i++)
	{
		a[i] = new int[vertices];
		paths[i] = new stack<int>[vertices];
		fill(a[i], a[i] + vertices, 0);
		for (int j = 0; j < vertices; j++)
		{
			a[i][j] = edgesList[i][j];
			paths[i][j].push(i);
			paths[i][j].push(j);
		}
	}

	for (int k = 0; k < vertices; k++)
	{
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				if ((a[i][k] + a[k][j]) < a[i][j] || (!a[i][j] && i != j))
				{
					a[i][j] = a[i][k] + a[k][j];
					paths[i][j].pop();
					paths[i][j].push(k);
					paths[i][j].push(j);
				}
			}
		}
	}

	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
			if (i != j && !a[i][j])
				cout << setw(5) << "∞";
			else
				cout << setw(5) << a[i][j];
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			if (i != j && !a[i][j])
				cout << i << " -> " << j << setw(5) << "∞" << endl << endl;
			else
			{
				stack<int> temp;
				while (!paths[i][j].empty())
				{
					temp.push(paths[i][j].top());
					paths[i][j].pop();
				}
				cout << i << " -> " << j << " total length " << a[i][j] << endl;
				while (!temp.empty()) {
					int u = temp.top();
					temp.pop();
					int v = temp.top();
					if (temp.size() == 1)
						temp.pop();
					cout << u << " -> " << v << " length " << edgesList[u][v] << endl;
				}
				cout << endl;
			}
		}
		cout << endl;
	}
}

void run_P372_P373_P375()
{
	Graph graph(6);
	graph.addEdge(0, 2, 6);
	graph.addEdge(0, 1, 2);
	graph.addEdge(1, 3, 4);
	graph.addEdge(1, 4, 2);
	graph.addEdge(1, 2, 7);
	graph.addEdge(2, 3, -1);
	graph.addEdge(3, 4, -2);

	graph.shortestPath();

	MartixWDigraph martix(3);
	martix.addEdge(0, 1, 4);
	martix.addEdge(0, 2, 11);
	martix.addEdge(1, 2, 2);
	martix.addEdge(1, 0, 6);
	martix.addEdge(2, 0, 3);

	martix.AllLengths();
}