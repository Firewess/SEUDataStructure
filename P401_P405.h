#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/12/15
@File: P401_P405.h
@Description: The twelfth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

//以下是为了便利而引入的Chain模板类的定义
#include <algorithm>
#include <iostream>

using namespace std;

/*
以下对应于英文书P194 3
*/
template<class T> class Chain;
template<class T> class ChainIterator;
template<class T> class Test;

template<class T>
class ChainNode
{
	friend class Chain<T>;
	friend class ChainIterator<T>;
	friend class Test<T>;
public:
	ChainNode(T element = 0, ChainNode<T> *next = 0)
	{
		data = element;
		link = next;
	}

	T GetData()
	{
		return data;
	}

	ChainNode<T> * GetNext()
	{
		return link;
	}

private:
	T data;
	ChainNode<T> *link;
};

template<class T>
class Chain
{
public:
	Chain()
	{
		first = 0;
	}
	~Chain()
	{
		ChainNode<T> *temp = first;
		while (first)
		{
			temp = first;
			first = first->link;
			delete temp;
		}
	}

	void Add(T element);

	int length();
	void Delete(ChainNode<T> *x);

	template<class T>
	friend ostream & operator <<(ostream &os, Chain<T> &linkList);

	ChainNode<T> * GetFirst()
	{
		return first;
	}

	void setFirst(ChainNode<T> *newFirst)	//为P201.h实现链式模板队列
	{
		first = newFirst;
	}

	ChainIterator<T> begin() { return ChainIterator<T>(first); }
	ChainIterator<T> end() { return ChainIterator<T>(0); }

private:
	ChainNode<T> *first;
};

template<class T>
void Chain<T>::Add(T element)
{
	if (first == 0)
	{
		first = new ChainNode<T>(element);
		return;
	}
	ChainNode<T> *temp = new ChainNode<T>(element);
	ChainNode<T> *p = first;
	while (p->link != 0)
	{
		p = p->link;
	}
	p->link = temp;
}

template<class T>
void Chain<T>::Delete(ChainNode<T> *x)
{
	if (x == first)
	{
		first = first->link;
		delete x;
		return;
	}
	ChainNode<T> *temp = first;
	while (temp)
	{
		if (temp->link == x)
			break;
		temp = temp->link;
	}
	temp = temp->link->link;
	delete x;
}

template<class T>
int Chain<T>::length()
{
	ChainNode<T> *temp = first;
	int count = 0;
	while (temp)
	{
		count++;
		temp = temp->link;
	}
	return count;
}

template<class T>
ostream & operator <<(ostream &os, Chain<T> &linkList)
{
	os << "当前链表存储情况为：";
	ChainNode<T> *temp = linkList.first;
	while (linkList.first)
	{
		os << linkList.first->GetData() << " ";
		linkList.first = linkList.first->GetNext();
	}
	linkList.first = temp;	//把头指针归位

	return os;
}

/*
以下对应于英文书P401 1
答：见P401-1.docx
*/

/*
以下对应于英文书P401 3
*/
template<class T>
class Test
{
private:
	Test();

public:
	static void LinklistInsertSort(Chain<T> &chain)
	{
		ChainNode<T> *before = chain.GetFirst();
		ChainNode<T> *temp = chain.GetFirst()->GetNext();
		ChainNode<T> *last = chain.GetFirst()->GetNext();
		ChainNode<T> *curr = temp->GetNext();

		bool changed = false;
		for (int i = 2; i < chain.length(); i++)
		{
			while (temp != curr)
			{
				if (temp->GetData() > curr->GetData())
				{
					before->link = curr;
					last->link = curr->GetNext();
					curr->link = temp;
					curr = last;
					changed = true;
					break;
				}
				before = before->GetNext();
				temp = temp->GetNext();
			}
			if (changed == false) last = last->GetNext();
			else changed = false;
			before = chain.GetFirst();
			temp = chain.GetFirst()->GetNext();
			curr = curr->GetNext();
		}
	}
};

/*
以下对应于英文书P405 1
答：见P405.docx
*/

/*
以下对应于英文书P405 2
答：见P405.docx
*/

/*
以下对应于英文书P405 5
答：见P405.docx
*/


void run_P401_P405()
{
	//以下对应于英文书P401 3
	Chain<int> chain;
	chain.Add(0);	//为了避免处理头节点的问题，这里保证第一个元素最小
	chain.Add(2);
	chain.Add(16);
	chain.Add(30);
	chain.Add(8);
	chain.Add(28);
	chain.Add(4);
	chain.Add(10);
	chain.Add(20);
	chain.Add(6);
	chain.Add(18);

	cout << "排序之前的链表：\n" << chain << endl;
	Test<int>::LinklistInsertSort(chain);
	cout << "排序之后的链表: \n" << chain << endl;
}