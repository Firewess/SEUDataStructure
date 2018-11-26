#pragma once
/*
 *author: 奉捷 jiefeng
 *date: 2018/10/3 09:41
 *description: the second assignment of data structure
*/
#include <iostream>

using namespace std;

/*
以下对应于英文书上 P138 1
*/
template<class T>
class Stack
{
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	T & Top() const;
	void Push(const T & item);
	void Pop();
	inline int GetSize()
	{
		return top + 1;
	}

	template<class T>
	friend ostream & operator <<(ostream & os, const Stack<T> & stack);

	Stack<T> & Split();
	void Combine(Stack<T> stack);
private:
	T * stack;
	int top;
	int capacity;
};

template<class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template<class T>
inline bool Stack<T>::IsEmpty() const
{
	return (top == -1);
}

template<class T>
inline T & Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty.";
	return stack[top];
}

template<class T>
void Stack<T>::Push(const T & item)
{
	if (top == capacity - 1)
	{
		T *temp = new T[capacity * 2];
		for (int i = 0; i < capacity; i++)
		{
			temp[i] = stack[i];
		}
		delete stack;
		stack = temp;
		capacity *= 2;
	}
	stack[++top] = item;
}

template<class T>
void Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty.";
	stack[top--].~T();
}

template<class T>
ostream & operator <<(ostream & os, const Stack<T> & stack)
{
	if (stack.IsEmpty())
		cout << "目前栈为空！\n";
	cout << "目前栈内的储存情况：";
	for (int i = 0; i <= stack.top; i++)
	{
		cout << stack.stack[i] << " ";
	}

	return os;
}

template<class T>
Stack<T> & Stack<T>::Split()
{
	if (top < 1) throw "Stack is too small to split.";

	static Stack<T> newStack(capacity);
	int halfsize = (top + 1) / 2;

	for (int i = halfsize - 1; i >= 0; i--)
		newStack.Push(stack[top - i]);

	for (int i = 0; i < halfsize; i++)
		Pop();

	return newStack;
}

template<class T>
void Stack<T>::Combine(Stack<T> stack)
{
	if (capacity < (top + stack.top - 2))
		throw "Stack is too small to combine with the second stack.";
	if (stack.IsEmpty())
		throw "The second stack is empty.";

	for (int i = 0; i <= stack.top; i++)
		Push(stack.stack[i]);
}

/*
以下对应于英文书上 P138 2
*/
template<class T>
void PrintCombination(Stack<T> rightStack, Stack<T> verticalStack, Stack<T> leftStack, int size)
{
	if (rightStack.IsEmpty() && verticalStack.IsEmpty() && leftStack.GetSize() == size)
	{
		cout << leftStack << endl;
		return;
	}

	if (!rightStack.IsEmpty())
	{
		T temp = rightStack.Top();
		verticalStack.Push(temp);
		rightStack.Pop();
		PrintCombination(rightStack, verticalStack, leftStack, size);
		verticalStack.Pop();
		rightStack.Push(temp);
	}

	if (!verticalStack.IsEmpty())
	{
		T temp = verticalStack.Top();
		verticalStack.Pop();
		leftStack.Push(temp);
		PrintCombination(rightStack, verticalStack, leftStack, size);
		verticalStack.Push(temp);
		leftStack.Pop();
	}
	return;
}

void run_P138()
{
	//P138 1
	Stack<int> stack1(20);
	for (int i = 1; i <= 20; i++)
	{
		stack1.Push(i);
	}
	cout << stack1;
	cout << endl;

	Stack<int> stack2(10);
	for (int i = 1; i <= 10; i++)
	{
		stack2.Push(i);
	}
	cout << stack2;
	cout << endl << endl;

	cout << "分割后的栈：\n";
	cout << stack1.Split() << endl;
	cout << stack1 << endl << endl;

	cout << "合并后的栈：\n";
	stack1.Combine(stack2);
	cout << stack1 << endl;

	//P138 2
	cout << endl << "n = 3时可能的排列顺序为：\n";
	Stack<int> rightSatck(10);
	for (int i = 0; i < 3; i++)
	{
		rightSatck.Push(i + 1);
	}

	Stack<int> verticalStack(10);
	Stack<int> leftStack(10);

	PrintCombination(rightSatck, verticalStack, leftStack, rightSatck.GetSize());

	cout << endl << "n = 4时可能的排列顺序为：\n";
	rightSatck.Push(4);

	PrintCombination(rightSatck, verticalStack, leftStack, rightSatck.GetSize());
}