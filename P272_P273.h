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
以下对应于英文书P272 1
答：时间复杂度分析：因为采用的是二叉树的后序遍历思路来实现的叶子节点数目统计，
	故每个节点都需要搜索一次，故时间复杂度为O(n)，n为二叉树中节点个数
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
以下对应于英文书P273 4
答：时间复杂度分析：因为采用的是二叉树的中序遍历思路来实现从左至右依次删除节点，
	故每个节点都需要入栈、出栈、然后被删除，故时间复杂度为O(n)，n为二叉树中节点个数
*/
template<class T>
Tree<T>::~Tree()
{
	stack<TreeNode<T> *> s;
	TreeNode<T> *currNode = this->GetRoot();
	TreeNode<T> *deleteNode = this->GetRoot();

	//采用中序遍历的算法来依次从左至右删除节点
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
	cout << "二叉树中叶子节点数量为：" << binaryTree.CountLeafNode() << endl;
}