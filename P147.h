/**************************************************
@Author: Jie Feng
@Time: 2018/10/13 14:29
@File: P147.h
@Description: The third week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#pragma once
#include <iostream>

using namespace std;

/*
以下对应于英文书上 P147 1
*/
template<class T>
class Queue
{
public:
	Queue(int Capacity = 10);
	~Queue();
	bool IsEmpty() const;
	T & Front() const;
	T & Rear() const;
	void Push(const T & item);
	void Pop();
	template<class T>
	friend ostream & operator <<(ostream &os, Queue<T> & queue);
	Queue & Split();
	inline int GetFront()
	{
		return front;
	}
	inline int GetRear()
	{
		return rear;
	}

private:
	T *queue;
	int front, rear, capacity;
	bool lastOp;	//false表示"delete"，true表示"add"，默认为false
};

template<class T>
Queue<T>::Queue(int Capacity) : capacity(Capacity)
{
	if (capacity < 1) throw "Queue capacity must be > 0";
	queue = new T[capacity];
	front = 0;
	rear = 0;
	lastOp = false;
}

template<class T>
Queue<T>::~Queue()
{
	delete[] queue;
}

template<class T>
bool Queue<T>::IsEmpty() const
{
	if (front == rear && !lastOp)
	{
		return true;
	}
	return false;
}

template<class T>
T & Queue<T>::Front() const
{
	if (IsEmpty()) throw "Queue is empty. No front element.";
	return queue[front];
}

template<class T>
T & Queue<T>::Rear() const
{
	if (IsEmpty()) throw "Queue is empty. No front element.";
	return queue[rear];
}

template<class T>
void Queue<T>::Push(const T &item)
{
	if (rear % capacity == front && lastOp)
	{
		int loopTimes;
		T *temp = new T[capacity * 2];
		(front < rear) ? (loopTimes = rear) : (loopTimes = rear + capacity);
		for (int i = front; i < loopTimes; i++)
		{
			temp[i - front] = queue[i % capacity];
		}
		rear = loopTimes - front;
		front = 0;
		delete[] queue;
		queue = temp;
		capacity *= 2;
	}
	queue[rear] = item;
	rear = (rear + 1) % capacity;
	lastOp = true;
}

template<class T>
void Queue<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty. Cannot delete.";
	queue[front].~T();
	front = (front + 1) % capacity;
	lastOp = false;
}

template<class T>
ostream & operator <<(ostream &os, Queue<T> & queue)
{
	os << "当前队列的储存情况为：";
	if (queue.IsEmpty())
		return os;
	int loopTimes;
	(queue.front < queue.rear) ? (loopTimes = queue.rear) : (loopTimes = queue.rear + queue.capacity);
	for (int i = queue.front; i < loopTimes; i++)
	{
		cout << queue.queue[i % queue.capacity] << " ";
	}

	return os;
}

/*
以下对应于英文书上 P147 3
答：
	设n为被分割队列的元素个数，其中for循环的循环次数为n/2，其余操作均可在O(1)时间内完成，
	故时间复杂度为O(n)
*/
template<class T>
Queue<T> & Queue<T>::Split()
{
	int terms = rear + capacity;
	if (IsEmpty()) throw "Queue is empty. Cannot split.";

	int loopTimes;
	(front < rear) ? (loopTimes = rear) : (loopTimes = rear + capacity);
	if (loopTimes < 2) throw "Queue is too small to split.";

	static Queue<T> resultQueue(capacity);
	for (int i = 0; i < (loopTimes - front + i) / 2; i++)
	{
		int temp = Front();
		resultQueue.Push(temp);
		front = (front + 1) % capacity;
	}

	return resultQueue;
}

void run_P147()
{
	//P147 1
	Queue<int> queue(10);
	for (int i = 0; i < 10; i++)
	{
		queue.Push(i + 1);
	}
	queue.Pop();
	queue.Push(11);
	cout << "Queue Front = " << queue.GetFront() << " Queue Rear = " << queue.GetRear() << endl;
	cout << queue << endl;

	//P147 3
	cout << "\n分割后的队列为：\n";
	cout << queue.Split() << endl;
	cout << queue << endl;
}