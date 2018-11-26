#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/10/21
@File: P183_P184.h
@Description: The fifth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>

using namespace std;

/*
以下对应于英文书P183 1
答：时间复杂度为O(length)，其中length为Chain中元素个数
*/
class ChainNode
{
	friend class Chain;
public:
	ChainNode(int element = 0, ChainNode *next = 0)
	{
		data = element;
		link = next;
	}

	int GetData()
	{
		return data;
	}

	ChainNode * GetNext()
	{
		return link;
	}

private:
	int data;
	ChainNode *link;
};

class Chain
{
public:
	Chain(int element = 0)
	{
		first = new ChainNode(element);
	}
	~Chain()
	{
		ChainNode *temp = first;
		while (first)
		{
			temp = first;
			first = first->link;
			delete temp;
		}
	}

	void Add(int element);

	int length();
	void Delete(ChainNode *x);
	friend ostream & operator <<(ostream &os, Chain &linkList);
	ChainNode * GetFirst()
	{
		return first;
	}
	void ReverseRight(ChainNode* l, ChainNode* r, int n);
	void ReverseLeft(ChainNode* l, ChainNode* r, int n);

private:
	ChainNode *first;
};

void Chain::Add(int element)
{
	ChainNode *temp = new ChainNode(element);
	ChainNode *p = first;
	while (p->link != 0)
	{
		p = p->link;
	}
	p->link = temp;
}

int Chain::length()
{
	ChainNode *temp = first;
	int count = 0;
	while (temp)
	{
		count++;
		temp = temp->link;
	}
	return count;
}

/*
以下对应于英文书P183 2
答：时间复杂度为O(k)，其中 k 为x在Chain中所在位置
*/
void Chain::Delete(ChainNode *x)
{
	if (x == first)
	{
		first = first->link;
		delete x;
		return;
	}
	ChainNode *temp = first;
	while (temp)
	{
		if (temp->link == x)
			break;
		temp = temp->link;
	}
	temp = temp->link->link;
	delete x;
}

ostream & operator <<(ostream &os, Chain &linkList)
{
	os << "当前链表存储情况为：";
	ChainNode *temp = linkList.first;
	while (linkList.first)
	{
		os << linkList.first->GetData() << " ";
		linkList.first = linkList.first->GetNext();
	}
	linkList.first = temp;	//把头指针归位

	return os;
}

/*
以下对应于英文书P184 6
*/
void Chain::ReverseRight(ChainNode* l, ChainNode* r, int n)
{
	int i = 0;
	while (r->link && i++ < n)
	{
		l = r;
		r = r->link;
	}
	if (!r->link)
	{
		l = r;
		r = 0;
	}
}

void Chain::ReverseLeft(ChainNode* l, ChainNode* r, int n)
{
	int i = 0;
	while (l->link && i++ < n)
	{
		r = l;
		l = l->link;
	}
	if (!l->link)
	{
		r = l;
		l = 0;
	}
}

void run_P183_P184()
{
	//P183 1
	Chain linkList(0);
	for (int i = 0; i < 10; i++)
		linkList.Add(i + 1);
	cout << linkList << endl;
	cout << "当前链表长度为：" << linkList.length() << endl;

	//P183 2
	ChainNode *temp = linkList.GetFirst();
	linkList.Delete(temp);
	cout << "\n删除头节点后的链表为：\n" << linkList << endl;
}