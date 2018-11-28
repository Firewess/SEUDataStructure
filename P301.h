#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/17
@File: P301.h
@Description: The ninth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>

using namespace std;

/*
���¶�Ӧ��Ӣ����P301 1
*/
class WinnerTree
{
public:
	WinnerTree(int array[], int length);

private:
	void adjust(int i);
	void adjustToRoot();

private:
	int capacity;
	int *tree;
};

struct Rec
{
	int key;
};

class LoserTree
{
public:
	LoserTree(int k);
	~LoserTree()
	{
		delete[] l;
		delete[] buf;
	}
	void Build();
	void print();

private:
	int getKey(int i);	//���ؽ��iָ��ļ�¼�������еĹؼ���
	int getIndex(int i);	//���ؽ��i��ŵļ�¼������ָ��

private:
	int k;
	int *l;	//��Ҷ�ڵ�
	Rec *buf;	//��¼������
};

/*
���¶�Ӧ��Ӣ����P301 4
*/
LoserTree::LoserTree(int k)
{
	this->k = k;
	l = new int[k];	//��Ҷ�ڵ�ռ�
	buf = new Rec[k];	//��¼�������ռ�
	for (int i = 0; i < k - 1; i++)
	{
		cout << "������һ������:";
		cin >> buf[i].key;
	}
}

void LoserTree::Build()
{
	int i;
	for (i = k - 1; i > 0; i--)
	{
		if (getKey(2 * i) > getKey(2 * i + 1))
			l[i] = getIndex(2 * i + 1);
		else
			l[i] = getIndex(2 * i);	//���¶��Ͻ���ʤ����
	}
	l[0] = l[1];	//��ʤ��
	for (i = 1; i < k; i++)
	{
		if (l[i] == getIndex(2 * i))
			l[i] = getIndex(2 * i + 1);
		else
			l[i] = getIndex(2 * i);	//���¶��Ͻ���������
	}
}

int LoserTree::getKey(int i)
{
	if (i < k)
		return buf[l[i]].key;
	else
		return buf[i - k].key;
}

int LoserTree::getIndex(int i)
{
	if (i < k)
		return l[i];
	else
		return (i - k);
}

void LoserTree::print()
{
	for (int i = 0; i < k; i++)
		cout << l[i] << " ";
}

void run_P301()
{
	LoserTree lt(10);
	lt.Build();
	lt.print();
}