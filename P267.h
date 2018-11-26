#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/2
@File: P267.h
@Description: The seventh week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <stack>
#include <iostream>

using namespace std;

/*
以下对应于英文书P267 4
*/
template<class T> class Tree;
template<class T> class InorderIterator;

template<class T>
class TreeNode
{
	friend class Tree<T>;
	friend class InorderIterator<T>;
public:
	TreeNode(T data)
	{
		this->data = data;
		leftChild = 0;
		rightChild = 0;
	}
	TreeNode<T> * GetLeftChild()
	{
		return leftChild;
	}
	TreeNode<T> * GetRightChild()
	{
		return rightChild;
	}

private:
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
};

template<class T>
class Tree
{
public:
	Tree(T node)
	{
		root = new TreeNode<T>(node);
	}
	//~Tree();	//此处没有实现析构函数释放空间，会造成内存泄漏，故在P272_P273.h中实现了中序遍历实现的析构函数
	TreeNode<T> * GetRoot()
	{
		return root;
	}
	void InsertToLeft(TreeNode<T> *parent, T leftChild);
	void InsertToRight(TreeNode<T> *parent, T rightChild);

	void NonrecPreorder();

private:
	TreeNode<T> *root;
};

template<class T>
void Tree<T>::InsertToLeft(TreeNode<T> *parent, T leftChild)
{
	if (!parent->leftChild)
	{
		parent->leftChild = new TreeNode<T>(leftChild);
	}
	else
	{
		parent->leftChild->data = leftChild;
	}
}

template<class T>
void Tree<T>::InsertToRight(TreeNode<T> *parent, T rightChild)
{
	if (!parent->rightChild)
	{
		parent->rightChild = new TreeNode<T>(rightChild);
	}
	else
	{
		parent->rightChild->data = rightChild;
	}
}

template<class T>
class InorderIterator
{
public:
	InorderIterator(TreeNode<T> * root)
	{
		currentNode = root;
	}
	T * Next();

private:
	stack<TreeNode<T> *> s;
	TreeNode<T> *currentNode;
};

template<class T>
T * InorderIterator<T>::Next()
{
	while (currentNode)
	{
		s.push(currentNode);
		currentNode = currentNode->leftChild;
	}
	if (s.empty())  return 0;
	currentNode = s.top();
	s.pop();
	T &temp = currentNode->data;
	currentNode = currentNode->rightChild;
	return &temp;
}

/*
以下对应于英文书P267 6
*/
template<class T>
void Tree<T>::NonrecPreorder()
{
	stack<TreeNode<T> *> s;
	TreeNode<T> *currNode = this->GetRoot();
	while (currNode != 0 || !s.empty())
	{
		while (currNode != 0)
		{
			cout << currNode->data << " ";
			s.push(currNode);
			currNode = currNode->leftChild;
		}

		if (!s.empty())
		{
			currNode = s.top();
			s.pop();
			currNode = currNode->rightChild;
		}
	}
}

void run_P267()
{
	//P267 4
	Tree<char> binaryTree('A');
	binaryTree.InsertToLeft(binaryTree.GetRoot(), 'B');
	binaryTree.InsertToRight(binaryTree.GetRoot(), 'C');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetLeftChild(), 'D');
	binaryTree.InsertToRight(binaryTree.GetRoot()->GetLeftChild(), 'E');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetRightChild(), 'F');
	binaryTree.InsertToRight(binaryTree.GetRoot()->GetRightChild(), 'G');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetLeftChild()->GetLeftChild(), 'H');

	InorderIterator<char> iterator(binaryTree.GetRoot());
	while (true)
	{
		char *result = iterator.Next();
		if (result)
		{
			cout << *result << " ";
		}
		else
		{
			break;
		}
	}

	//P267 6
	cout << endl;
	binaryTree.NonrecPreorder();
	cout << endl;
}