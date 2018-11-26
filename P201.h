#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/10/29
@File: P201.h
@Description: The sixth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include "P194.h"	//引入自定义的模板类Chain

/*
以下对应于英文书P201 2
*/
template<class T>
class LinkedQueue
{
public:
	LinkedQueue()
	{
		myChain = new Chain<T>();
	}
	~LinkedQueue()
	{
		myChain->~Chain();
		delete myChain;
	}
	void Push(const T &e);
	void Pop();
	bool IsEmpty();

	template<class T>
	friend ostream & operator <<(ostream & os, LinkedQueue<T> & queue);

private:
	Chain<T> *myChain;
};

template<class T>
void LinkedQueue<T>::Push(const T &e)
{
	myChain->Add(e);
}

template<class T>
void LinkedQueue<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty. Cannot delete.";
	ChainNode<T> *delNode = myChain->GetFirst();
	myChain->setFirst(myChain->GetFirst()->GetNext());
	delete delNode;
}

template<class T>
bool LinkedQueue<T>::IsEmpty()
{
	return (myChain->GetFirst() == 0);
}

template<class T>
ostream & operator <<(ostream & os, LinkedQueue<T> & queue)
{
	os << *(queue.myChain);
	
	return os;
}

void run_P201()
{
	LinkedQueue<int> myQueue;
	for (int i = 0; i < 10; i++)
		myQueue.Push(i);

	cout << myQueue << endl;

	myQueue.Pop();
	myQueue.Push(0);
	cout << myQueue << endl;
}