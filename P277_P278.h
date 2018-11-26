#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/10
@File: P277_P278.h
@Description: The eighth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

/*
以下对应于英文书P277 1
*/
#include <stack>
#include <iostream>

using namespace std;

/*
以下对应于英文书P267 4
*/
template<class T> class ThreadedTree;
template<class T> class ThreadedInorderIterator;

template<class T>
class ThreadTreeNode
{
	friend class ThreadedTree<T>;
	friend class ThreadedInorderIterator<T>;
public:
	ThreadTreeNode(T data)
	{
		this->data = data;
		leftChild = this;
		rightChild = this;
		leftThread = true;
		rightThread = false;
	}
	ThreadTreeNode<T> * GetLeftChild()
	{
		return leftChild;
	}
	ThreadTreeNode<T> * GetRightChild()
	{
		return rightChild;
	}

private:
	bool leftThread;
	bool rightThread;
	T data;
	ThreadTreeNode<T> *leftChild;
	ThreadTreeNode<T> *rightChild;
};

template<class T>
class ThreadedTree
{
public:
	ThreadedTree(T node)
	{
		root = new ThreadTreeNode<T>(node);
	}
	//析构函数，回收线索二叉树占用的空间
	~ThreadedTree()
	{
		ThreadTreeNode<T> *currNode = root;
		ThreadTreeNode<T> *deleteNode = NULL;

		while (true)
		{
			deleteNode = currNode;
			if (!currNode->rightThread)
				while (!deleteNode->leftThread) deleteNode = deleteNode->leftChild;
			currNode = deleteNode->rightChild;
			if (deleteNode == root || currNode == root)
				break;
			else
				delete deleteNode;
			//因为采用中序遍历的方法删除节点，故currNode始终为当前二叉树中序遍历的第一个节点，
			//故currNode的线索指向root头节点
			currNode->leftThread = true;
			currNode->leftChild = root;
		}

		delete root;
	}
	ThreadTreeNode<T> * GetRoot()
	{
		return root;
	}

	ThreadTreeNode<T>* InorderSucc(const ThreadTreeNode<T> *node) const;
	ThreadTreeNode<T>* InorderBefore(const ThreadTreeNode<T> *node) const;
	void InsertRight(ThreadTreeNode<T> *s, ThreadTreeNode<T> *r);
	void InsertLeft(ThreadTreeNode<T> *s, ThreadTreeNode<T> *r);

private:
	ThreadTreeNode<T> *root;
};

template<class T>
//返回node的中序后继
ThreadTreeNode<T>* ThreadedTree<T>::InorderSucc(const ThreadTreeNode<T> *node) const
{
	stack<ThreadTreeNode<T> *> nodeStack;
	ThreadTreeNode<T>* currNode = root;

	ThreadTreeNode<T>* lastVisit = NULL;

	while (currNode || !nodeStack.empty())
	{
		while (currNode && currNode->leftThread != true)
		{
			nodeStack.push(currNode);
			currNode = currNode->leftChild;
		}

		if(currNode) nodeStack.push(currNode);

		if (!nodeStack.empty())
		{
			currNode = nodeStack.top();
			nodeStack.pop();
			if (lastVisit == node)
			{
				return currNode;
			}
			lastVisit = currNode;
			if (currNode->rightThread)
			{
				currNode = NULL;
			}
			else
			{
				currNode = currNode->rightChild;
			}
		}
	}
}

template<class T>
//返回node的中序前驱
ThreadTreeNode<T>* ThreadedTree<T>::InorderBefore(const ThreadTreeNode<T> *node) const
{
	stack<ThreadTreeNode<T> *> nodeStack;
	ThreadTreeNode<T>* currNode = root;
	nodeStack.push(root);

	ThreadTreeNode<T>* lastVisit = NULL;

	while (currNode || !nodeStack.empty())
	{
		while (currNode && currNode->leftThread != true)
		{
			nodeStack.push(currNode->leftChild);
			currNode = currNode->leftChild;
		}

		if (!nodeStack.empty())
		{
			currNode = nodeStack.top();
			nodeStack.pop();
			if (currNode == node)
			{
				//因为存在头节点，故无需考虑node为中序遍历的第一个节点从而不存在中序前驱的情况
				return lastVisit;
			}
			lastVisit = currNode;
			if (currNode->rightThread)
			{
				currNode = NULL;
			}
			else
			{
				currNode = currNode->rightChild;
			}
		}
	}
}

template<class T>
void ThreadedTree<T>::InsertRight(ThreadTreeNode<T> *s, ThreadTreeNode<T> *r)
{
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = true;
	s->rightChild = r;
	s->rightThread = false;

	if (!r->rightThread)
	{
		ThreadTreeNode<T> *temp = InorderSucc(r);
		temp->leftChild = r;
	}
}

template<class T>
void ThreadedTree<T>::InsertLeft(ThreadTreeNode<T> *s, ThreadTreeNode<T> *r)
{
	r->leftChild = s->leftChild;
	r->leftThread = s->leftThread;
	r->rightChild = s;
	r->rightThread = true;
	s->leftChild = r;
	s->leftThread = false;

	if (!r->leftThread)
	{
		ThreadTreeNode<T> *temp = InorderBefore(r);
		temp->rightChild = r;
	}
}

/*
以下对应于英文书P278 2
*/
template<class T>
class ThreadedInorderIterator
{
public:
	ThreadedInorderIterator(ThreadTreeNode<T> * node)
	{
		root = node;
		currentNode = root;
	}
	T * Next();

private:
	stack<ThreadTreeNode<T> *> s;
	ThreadTreeNode<T> *currentNode;
	ThreadTreeNode<T> *root;
};

template<class T>
T * ThreadedInorderIterator<T>::Next()
{
	ThreadTreeNode<T> *temp = currentNode->rightChild;
	if (!currentNode->rightThread)
		while (!temp->leftThread) temp = temp->leftChild;
	currentNode = temp;
	if (currentNode == root)
		return 0;
	else
		return &currentNode->data;
}

void run_P77_P278()
{
	//以下对应于英文书P278 1
	ThreadedTree<int> tbt(-1);
	tbt.InsertLeft(tbt.GetRoot(), new ThreadTreeNode<int>(1));

	//往第一个节点左边插入节点，此时被插入节点无子树
	tbt.InsertRight(tbt.GetRoot()->GetLeftChild(), new ThreadTreeNode<int>(2));

	//往第一个节点右边插入节点，此时被插入节点无子树
	tbt.InsertLeft(tbt.GetRoot()->GetLeftChild(), new ThreadTreeNode<int>(3));

	//往第一个节点左边插入节点，此时被插入节点存在子树，会调用InorderBefore查询中序前驱
	tbt.InsertLeft(tbt.GetRoot()->GetLeftChild(), new ThreadTreeNode<int>(4));

	//往第一个节点右边插入节点，此时被插入节点存在子树，会调用InorderSucc查询中序后继
	tbt.InsertRight(tbt.GetRoot()->GetLeftChild(), new ThreadTreeNode<int>(5));

	//以下对应于英文书P278 2
	ThreadedInorderIterator<int> iterator(tbt.GetRoot());
	for (int *data = iterator.Next(); data; data = iterator.Next())
		cout << *data << " ";
	cout << endl;
}