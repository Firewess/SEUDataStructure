#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/24
@File: P352.h
@Description: The tenth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include "P194.h"	//引入自定义的模板链表类Chain
#include <queue>

using namespace std;

class Graph
{
	friend istream & operator >>(istream &is, Graph &graph);
	friend ostream & operator <<(ostream &os, Graph &graph);
public:
	Graph() :n(0), e(0) { visited = NULL; }
	Graph(ifstream &is) :n(0), e(0)
	{
		visited = NULL;
		int vNum;
		is >> vNum;
		for (int i = 0; i < vNum; i++)
			this->InsertVertex(i);
		int eNum;
		is >> eNum;
		int from, to;
		for (int i = 0; i < eNum; i++)
		{
			is >> from >> to;
			this->InsertEdge(from, to);
		}
	}
	//~Graph();
	bool IsEmpty() const
	{
		return n == 0;
	}
	int NumberOfVertices() const
	{
		return n;
	}
	int NumberOfEdges() const
	{
		return e;
	}
	void InsertVertex(int v);
	void InsertEdge(int u, int v);
	//void DeleteVertex(int v);
	//void DeleteEdge(int u, int v);

	void DFS();
	void BFS(int v);

	void Components();

private:
	void DFS(const int v);
	void DFSforComponent(const int v);

private:
	int n;	//顶点数	
	int e;	//边数
	//因为对于图，只有在建立的时候插入操作较多，其余操作主要为定位元素，
	//故选用vector，没有选用list
	vector<Chain<int>*> adjList;

	bool *visited;
};

void Graph::InsertVertex(int v)
{
	adjList.push_back(new Chain<int>());
	adjList.at(adjList.size() - 1)->Add(v);
	n++;
}

void Graph::InsertEdge(int u, int v)
{
	adjList.at(u)->Add(v);
	e++;
}

istream & operator >>(istream & is, Graph &graph)
{
	cout << "请输入顶点数：";
	int vNum;
	is >> vNum;
	for (int i = 0; i < vNum; i++)
		graph.InsertVertex(i);
	cout << "请输入边数：";
	int eNum;
	is >> eNum;
	int from, to;
	for (int i = 0; i < eNum; i++)
	{
		cout << "请输入边(出发顶点 到达顶点)：";
		is >> from >> to;
		graph.InsertEdge(from, to);
	}

	return is;
}

ostream & operator <<(ostream &os, Graph &graph)
{
	for (int i = 0; i < graph.adjList.size(); i++)
	{
		Chain<int> *list = graph.adjList.at(i);
		ChainIterator<int> iterator;
		iterator = list->begin();
		iterator++;
		for (; iterator != list->end(); iterator++)
			cout << "(" << (list->GetFirst())->GetData() << ", " << *(iterator.operator->()) << ") ";
		cout << endl;
	}

	return os;
}
/*
以下对应于英文书P352 3
*/
void Graph::DFS()
{
	visited = new bool[n];
	fill(visited, visited + n, false);
	DFS(0);
	delete[] visited;
	visited = NULL;
}

void Graph::DFS(const int v)
{
	visited[v] = true;
	cout << v << " ";
	ChainIterator<int> iterator;
	Chain<int>* list = adjList.at(v);
	iterator = list->begin();
	iterator++;	//链表头节点存放的为顶点自身，故让迭代器自增一次
	for (; iterator != list->end(); iterator++)
	{
		if (!visited[*(iterator.operator->())])
			DFS(*(iterator.operator->()));
	}
}

void Graph::DFSforComponent(const int v)
{
	bool *temp = new bool[this->n];
	fill(temp, temp + n, false);
	temp[v] = true;
	cout << v << " ";
	ChainIterator<int> iterator;
	Chain<int>* list = adjList.at(v);
	iterator = list->begin();
	iterator++;	//链表头节点存放的为顶点自身，故让迭代器自增一次
	for (; iterator != list->end(); iterator++)
	{
		if (!temp[*(iterator.operator->())])
			DFS(*(iterator.operator->()));
	}
	cout << endl;
	delete[] temp;
	temp = NULL;
}

/*
以下对应于英文书P352 5
*/
void Graph::BFS(int v)
{
	visited = new bool[n];
	fill(visited, visited + n, false);
	visited[v] = true;
	cout << v << " ";
	queue<int> q;
	q.push(v);
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		ChainIterator<int> iterator;
		Chain<int>* list = adjList.at(v);
		iterator = list->begin();
		iterator++;	//链表头节点存放的为顶点自身，故让迭代器自增一次
		for (; iterator != list->end(); iterator++)
		{
			if (!visited[*(iterator.operator->())])
			{
				q.push(*(iterator.operator->()));
				visited[*(iterator.operator->())] = true;
				cout << *(iterator.operator->()) << " ";
			}
		}
	}
	delete[] visited;
	visited = NULL;
}

/*
以下对应于英文书P352 6
*/
void Graph::Components()
{
	visited = new bool[n];
	fill(visited, visited + n, false);
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			DFSforComponent(i);
		}
	}

	delete[] visited;
	visited = NULL;
}

void run_P352()
{
	//以下对应于英文书P352 3
	ifstream is("graph.txt");	//使用了从文件中读取输入的构造函数
	Graph graph(is);
	//cin >> graph;
	graph.DFS();
	cout << endl;

	//以下对应于英文书P352 5
	graph.BFS(0);
	cout << endl;

	graph.Components();
}