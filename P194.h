#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/10/21
@File: P194.h
@Description: The fifth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <algorithm>
#include <iostream>

using namespace std;

/*
以下对应于英文书P194 3
*/
template<class T> class Chain;
template<class T> class ChainIterator;

template<class T>
class ChainNode
{
	friend class Chain<T>;
	friend class ChainIterator<T>;
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

template<class T>
class ChainIterator : public std::iterator < std::forward_iterator_tag, T >	//本人在实践中发现，自定义迭代器需要继承自这个类
{
public:
	ChainIterator(ChainNode<T> *startNode = 0)
	{
		current = startNode;
	}
	T & operator *() const
	{
		return current->data;
	}
	T * operator ->() const
	{
		return &current->data;
	}
	ChainIterator & operator ++()
	{
		current = current->link;
		return *this;
	}
	ChainIterator operator ++(int)
	{
		ChainIterator<T> old = *this;
		current = current->link;
		return old;
	}
	//重载+运算，使得可以直接让迭代器加上一个整数偏移量
	ChainIterator operator +(int a)
	{
		ChainIterator<T> temp = *this;
		if (a <= 0)
			throw "Invalid offset! Offset must be > 0.";
		int count = 0;
		while (count < a && temp.current != 0)
		{
			count++;
			temp.current = temp.current->link;
		}
		return temp;
	}
	bool operator !=(ChainIterator right) const
	{
		return (current != right.current);
	}
	bool operator ==(ChainIterator right) const
	{
		return (current == right.current);
	}

private:
	ChainNode<T> *current;
};

/*
以下对应于英文书P194 4
*/

void run_P194()
{
	//P194 3
	Chain<int> templateList;
	for (int i = 0; i < 10; i++)
		templateList.Add(i);

	cout << templateList << endl;

	int arraylist[10] = { 0 };
	ChainIterator<int> iterator = templateList.begin();
	//下面使用STL函数copy和自定义的迭代器来实现拷贝链表到数组
	copy(iterator, iterator + 10, arraylist);
	cout << "拷贝后的数组为：";
	for (int i = 0; i < 10; i++)
		cout << arraylist[i] << " ";
	cout << endl;

	//P194 4
	ChainIterator<int> leftIterator, rightIterator;
	Chain<int> newList;
	int count;
	cout << "请输入您想输入的数字个数：";
	cin >> count;
	while (count <= 5)
	{
		cout << "输入错误，请输入一个大于5的整数：";
		cin >> count;
	}
	for (int i = 0; i < count; i++)
	{
		int temp;
		cout << "请输入数字：";
		cin >> temp;
		newList.Add(temp);
	}
	cout << "您输入的链表为：";
	for (iterator = newList.begin(); iterator != newList.end(); iterator++)
		cout << *(iterator.operator->()) << " ";
	cout << endl;

	leftIterator = newList.begin();
	rightIterator = newList.begin();
	for (int i = 0; i < 5; rightIterator++, i++);

	int result = 0;
	while (rightIterator != newList.end())
	{
		result += *(leftIterator.operator->()) * *(rightIterator.operator->());
		rightIterator++;
		leftIterator++;
	}
	cout << "结果为：" << result << endl;
} 