#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/24
@File: P359.h
@Description: The tenth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include "P287.h"	//�����Զ����MinHEAP��

using namespace std;

/*
���¶�Ӧ��Ӣ����P359 1
*/
struct Edge
{
	int u; //�����ӵ�һ��������
	int v; //��������һ��������
	int w; //�ߵ�Ȩֵ

	Edge(int u = 0, int v = 0, int w = 0)
	{
		this->u = u;
		this->v = v;
		this->w = w;
	}

	friend bool operator>(const Edge& E1, const Edge& E2)
	{
		return E1.w > E2.w;
	}

	friend bool operator>=(const Edge& E1, const Edge& E2)
	{
		return E1.w >= E2.w;
	}

	friend bool operator<=(const Edge& E1, const Edge& E2)
	{
		return E1.w <= E2.w;
	}

	friend bool operator<(const Edge& E1, const Edge& E2)
	{
		return E1.w < E2.w;
	}
};


//�������鼯
void MakeSet(vector<int>& uset, int n)
{
	uset.assign(n, 0);
	for (int i = 0; i < n; i++)
		uset[i] = i;
}

//���ҵ�ǰԪ�����ڼ��ϵĴ���Ԫ
int FindSet(vector<int>& uset, int u)
{
	int i = u;
	while (uset[i] != i) i = uset[i];
	return i;
}

template<class T>
void Kruskal(MinHeap<T>& edges, int vNum, int eNum)
{
	vector<int> uset;
	vector<Edge> SpanTree;
	int Cost = 0, e1, e2;
	MakeSet(uset, vNum);
	for (int i = 0; i < eNum; i++)
	{
		Edge temp = edges.Top();	//��Ȩֵ��С�����˳��ȡ��
		e1 = FindSet(uset, temp.u);
		e2 = FindSet(uset, temp.v);
		edges.Pop();
		if (e1 != e2) //����ǰ�����ӵ���������ڲ�ͬ�����У�ѡȡ�ñ߲��ϲ�����������
		{
			SpanTree.push_back(temp);
			Cost += temp.w;
			uset[e1] = e2; //�ϲ���ǰ�����ӵ������������ڼ���
		}
	}
	cout << "----------------Result-------------\n";
	cout << "Cost: " << Cost << endl;
	cout << "Edges:\n";
	for (int j = 0; j < SpanTree.size(); j++)
		cout << "(" << SpanTree[j].u << ", " << SpanTree[j].v << ") Weight:" << SpanTree[j].w << endl;
}

void run_P359()
{
	ifstream in("data.txt");

	int vNum, eNum;
	in >> vNum >> eNum;
	MinHeap<Edge> edges;
	int u, v, w;
	for (int i = 0; i < eNum; i++)
	{
		in >> u >> v >> w;
		edges.Push(Edge(u, v, w));
	}
	
	Kruskal(edges, vNum, eNum);

	in.close();
}