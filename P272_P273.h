#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/2
@File: P272_P273.h
@Description: The seventh week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <stack>

using namespace std;

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
	~Tree();
	TreeNode<T> * GetRoot()
	{
		return root;
	}
	void InsertToLeft(TreeNode<T> *parent, T leftChild);
	void InsertToRight(TreeNode<T> *parent, T rightChild);

	int CountLeafNode();

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

/*
���¶�Ӧ��Ӣ����P272 1
��ʱ�临�Ӷȷ�������Ϊ���õ��Ƕ������ĺ������˼·��ʵ�ֵ�Ҷ�ӽڵ���Ŀͳ�ƣ�
	��ÿ���ڵ㶼��Ҫ����һ�Σ���ʱ�临�Ӷ�ΪO(n)��nΪ�������нڵ����
*/
template<class T>
int Tree<T>::CountLeafNode()
{
	int numOfLeaf = 0;

	stack<TreeNode<T> *> s;
	TreeNode<T> *currNode = this->GetRoot();
	TreeNode<T> *lastVisit = this->GetRoot();

	while (currNode != 0 || !s.empty())
	{
		while (currNode)
		{
			s.push(currNode);
			currNode = currNode->leftChild;
		}

		currNode = s.top();
		
		if (currNode->rightChild == 0 || lastVisit == currNode->rightChild)
		{
			if (currNode->rightChild == 0 && currNode->leftChild == 0)
			{
				numOfLeaf++;
			}
			s.pop();
			lastVisit = currNode;
			currNode = 0;
		}
		else
		{
			currNode = currNode->rightChild;
		}
	}

	return numOfLeaf;
}

/*
���¶�Ӧ��Ӣ����P273 4
��ʱ�临�Ӷȷ�������Ϊ���õ��Ƕ��������������˼·��ʵ�ִ�����������ɾ���ڵ㣬
	��ÿ���ڵ㶼��Ҫ��ջ����ջ��Ȼ��ɾ������ʱ�临�Ӷ�ΪO(n)��nΪ�������нڵ����
*/
template<class T>
Tree<T>::~Tree()
{
	stack<TreeNode<T> *> s;
	TreeNode<T> *currNode = this->GetRoot();
	TreeNode<T> *deleteNode = this->GetRoot();

	//��������������㷨�����δ�������ɾ���ڵ�
	while (currNode != 0 || !s.empty())
	{
		while (currNode)
		{
			s.push(currNode);
			currNode = currNode->leftChild;
		}

		if (!s.empty())
		{
			currNode = s.top();
			deleteNode = currNode;
			s.pop();
			currNode = currNode->rightChild;
			delete deleteNode;
			deleteNode = 0;
		}
	}
}

void run_P272_P273()
{
	Tree<char> binaryTree('A');
	binaryTree.InsertToLeft(binaryTree.GetRoot(), 'B');
	binaryTree.InsertToRight(binaryTree.GetRoot(), 'C');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetLeftChild(), 'D');
	binaryTree.InsertToRight(binaryTree.GetRoot()->GetLeftChild(), 'E');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetRightChild(), 'F');
	binaryTree.InsertToRight(binaryTree.GetRoot()->GetRightChild(), 'G');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetLeftChild()->GetLeftChild(), 'H');

	//P272 1
	cout << "��������Ҷ�ӽڵ�����Ϊ��" << binaryTree.CountLeafNode() << endl;
}