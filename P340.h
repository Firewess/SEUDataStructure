#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/24
@File: P340.h
@Description: The tenth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <vector>

using namespace std;

/*
���¶�Ӧ��Ӣ����P340 5
�𣺼�P340.docx
*/

/*
���¶�Ӧ��Ӣ����P340 9
*/
class Node
{
	friend class Graph;
public:
	Node(int data = 0)
	{
		this->data = data;
		link = NULL;
	}

private:
	int data;
	Node *link;
};

class Graph
{
	friend istream & operator >>(istream &is, Graph &graph);
	friend ostream & operator <<(ostream &os, Graph &graph);
public:
	Graph():n(0), e(0){}
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

private:
	int n;	//������	
	int e;	//����
	//��Ϊ����ͼ��ֻ���ڽ�����ʱ���������϶࣬���������ҪΪ��λԪ�أ�
	//��ѡ��vector��û��ѡ��list
	vector<Node*> adjList;
};

void Graph::InsertVertex(int v)
{
	adjList.push_back(new Node(v));
	n++;
}

void Graph::InsertEdge(int u, int v)
{
	adjList.at(u);
	e++;
}

istream & operator >>(istream & is, Graph &graph)
{
	cout << "�����붥������";
	int vNum;
	is >> vNum;
	for (int i = 0; i < vNum; i++)
		graph.InsertVertex(i);
	cout << "�����������";
	int eNum;
	is >> eNum;
	int from, to;
	for (int i = 0; i < eNum; i++)
	{
		cout << "�������(�������� ���ﶥ��)��";
		is >> from >> to;
		graph.InsertEdge(from, to);
	}

	return is;
}

ostream & operator <<(ostream &os, Graph &graph)
{
	

	return os;
}

void run_P340()
{
	Graph graph;
	cin >> graph;
	cout << graph;
}