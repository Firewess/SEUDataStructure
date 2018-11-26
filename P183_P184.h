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
���¶�Ӧ��Ӣ����P183 1
��ʱ�临�Ӷ�ΪO(length)������lengthΪChain��Ԫ�ظ���
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
���¶�Ӧ��Ӣ����P183 2
��ʱ�临�Ӷ�ΪO(k)������ k Ϊx��Chain������λ��
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
	os << "��ǰ����洢���Ϊ��";
	ChainNode *temp = linkList.first;
	while (linkList.first)
	{
		os << linkList.first->GetData() << " ";
		linkList.first = linkList.first->GetNext();
	}
	linkList.first = temp;	//��ͷָ���λ

	return os;
}

/*
���¶�Ӧ��Ӣ����P184 6
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
	cout << "��ǰ������Ϊ��" << linkList.length() << endl;

	//P183 2
	ChainNode *temp = linkList.GetFirst();
	linkList.Delete(temp);
	cout << "\nɾ��ͷ�ڵ�������Ϊ��\n" << linkList << endl;
}