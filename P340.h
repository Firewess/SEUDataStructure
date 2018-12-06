#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/24
@File: P340.h
@Description: The tenth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include "P194.h"	//�����Զ����ģ��������Chain

using namespace std;

/*
���¶�Ӧ��Ӣ����P340 5
�𣺼�P340.docx
*/

/*
���¶�Ӧ��Ӣ����P340 9
*/
class Graph
{
	friend istream & operator >>(istream &is, Graph &graph);
	friend ostream & operator <<(ostream &os, Graph &graph);
public:
	Graph():n(0), e(0){}
	Graph(ifstream &is) :n(0), e(0)
	{
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

private:
	int n;	//������	
	int e;	//����
	//��Ϊ����ͼ��ֻ���ڽ�����ʱ���������϶࣬���������ҪΪ��λԪ�أ�
	//��ѡ��vector��û��ѡ��list
	vector<Chain<int>*> adjList;
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

void run_P340()
{
	ifstream is("graph.txt");	//ʹ���˴��ļ��ж�ȡ����Ĺ��캯��
	Graph graph(is);
	//cin >> graph;
	cout << graph;
}