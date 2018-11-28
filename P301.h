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
以下对应于英文书P301 1
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
	int getKey(int i);	//返回结点i指向的记录缓冲区中的关键字
	int getIndex(int i);	//返回结点i存放的记录缓冲区指针

private:
	int k;
	int *l;	//非叶节点
	Rec *buf;	//记录缓冲区
};

/*
以下对应于英文书P301 4
*/
LoserTree::LoserTree(int k)
{
	this->k = k;
	l = new int[k];	//非叶节点空间
	buf = new Rec[k];	//记录缓冲区空间
	for (int i = 0; i < k - 1; i++)
	{
		cout << "请输入一个整数:";
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
			l[i] = getIndex(2 * i);	//自下而上建立胜者树
	}
	l[0] = l[1];	//总胜者
	for (i = 1; i < k; i++)
	{
		if (l[i] == getIndex(2 * i))
			l[i] = getIndex(2 * i + 1);
		else
			l[i] = getIndex(2 * i);	//自下而上建立败者树
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