#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/10
@File: P287.h
@Description: The eighth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>

using namespace std;

/*
以下对应于英文书P287 2
*/
template<class T>
class MinPQ
{
public:
	virtual ~MinPQ() {}
	virtual bool IsEmpty() const = 0;
	virtual const T & Top() const = 0;
	virtual void Push(const T &) = 0;
	virtual void Pop() = 0;
};

template<class T>
class MinHeap : public MinPQ<T>
{
public:
	MinHeap(int capacity = 10);
	~MinHeap()
	{
		delete[] heap;
	}

	bool IsEmpty() const;
	const T & Top() const;
	void Push(const T &);
	void Pop();
	
	template<class T>
	friend ostream & operator <<(ostream & os, MinHeap<T> & minheap);

private:
	void ChangeSize(T *heap, int oldCapacity, int newCapacity);

private:
	T *heap;
	int heapSize;
	int capacity;
};

template<class T>
MinHeap<T>::MinHeap(int capacity)
{
	if (capacity < 1) throw "Capacity must be >= 1.";
	this->capacity = capacity;
	heapSize = 0;
	heap = new T[this->capacity + 1];
	heap[0] = -1;
}

template<class T>
bool MinHeap<T>::IsEmpty() const
{
	return (heapSize == 0);
}

template<class T>
const T & MinHeap<T>::Top() const
{
	return heap[1];
}

template<class T>
void MinHeap<T>::Push(const T & e)
{
	if (heapSize == capacity)
	{
		ChangeSize(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currNode = ++heapSize;
	while (currNode != 1 && heap[currNode / 2] > e)
	{
		heap[currNode] = heap[currNode / 2];
		currNode /= 2;
	}
	heap[currNode] = e;
}

template<class T>
void MinHeap<T>::Pop()
{
	if (IsEmpty()) throw "Heap is empty. Cannot delete.";
	heap[1].~T();

	T lastE = heap[heapSize--];

	int currNode = 1;
	int child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] > heap[child + 1])
			child++;

		if (lastE <= heap[child]) break;

		heap[currNode] = heap[child];
		currNode = child;
		child *= 2;
	}
	heap[currNode] = lastE;
}

template<class T>
void MinHeap<T>::ChangeSize(T *heap, int oldCapacity, int newCapacity)
{
	T *temp = new T[newCapacity];
	for (int i = 0; i < oldCapacity; i++)
		temp[i] = heap[i];

	delete heap;
	heap = temp;
}

template<class T>
ostream & operator <<(ostream & os, MinHeap<T> & minheap)
{
	for (int i = 1; i <= minheap.heapSize; i++)
		os << minheap.heap[i] << " ";
	
	return os;
}

/*
以下对应于英文书P287 3
*/


void run_P287()
{
	MinHeap<int> minheap(20);
	for (int i = 0; i < 10; i++)
		minheap.Push(i);

	minheap.Push(25);
	minheap.Push(35);

	cout << minheap << endl;
}