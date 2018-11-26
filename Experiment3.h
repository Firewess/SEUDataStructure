#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/23
@File: Experiment3.h
@Description: The third experiment of data structure of Mr. Jianhua Lv
**************************************************/

//P267 10
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<class T> class BinaryTree;
template<class T> class InorderIterator;
template<class T> class PostorderIterator;
template<class T> class PreorderIterator;
template<class T> class LevelorderIterator;

//���ڵ���Ķ���
template<class T>
class TreeNode
{
	friend class BinaryTree<T>;
	friend class InorderIterator<T>;
	friend class PostorderIterator<T>;
	friend class PreorderIterator<T>;
	friend class LevelorderIterator<T>;
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
class BinaryTree
{
public:
	BinaryTree(T node)
	{
		root = new TreeNode<T>(node);
	}
	~BinaryTree()
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
	BinaryTree(BinaryTree & bt);
	TreeNode<T> * GetRoot()
	{
		return root;
	}
	void InsertToLeft(TreeNode<T> *parent, T leftChild);
	void InsertToRight(TreeNode<T> *parent, T rightChild);

private:
	TreeNode<T> *root;
};

template<class T>
BinaryTree<T>::BinaryTree(BinaryTree & bt)
{
	LevelorderIterator<T> iterator(bt.GetRoot());
	TreeNode<T> *temp = NULL;
	TreeNode<T> *newNode = NULL;

	while (true)
	{
		temp = iterator.GetCurrNode();
		iterator.Next();

		if (temp != NULL)
		{
			newNode = new TreeNode<T>(temp->data);
			newNode->leftChild = temp->leftChild;
			newNode->rightChild = temp->rightChild;
		}
		else break;
	}
}

template<class T>
void BinaryTree<T>::InsertToLeft(TreeNode<T> *parent, T leftChild)
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
void BinaryTree<T>::InsertToRight(TreeNode<T> *parent, T rightChild)
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

//����Ϊ��������������Ķ���
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

//����Ϊ��������������Ķ���
template<class T>
class PostorderIterator
{
public:
	PostorderIterator(TreeNode<T> * root)
	{
		currentNode = root;
		postorder();
	}
	T * Next();

private:
	void postorder();

private:
	queue<TreeNode<T> *> q;
	TreeNode<T> *currentNode;
};

template<class T>
//˽�к��������ڰѺ������������浽�����У�Next����ֱ��ȡfront���
void PostorderIterator<T>::postorder()
{
	stack<TreeNode<T> *> s;
	TreeNode<T> *temp = currentNode;
	TreeNode<T> *lastVisit = NULL;

	while (temp != NULL || !s.empty())
	{
		while (temp)
		{
			s.push(temp);
			temp = temp->leftChild;
		}

		temp = s.top();
		if (temp->rightChild == NULL || lastVisit == temp->rightChild)
		{
			s.pop();
			q.push(temp);
			lastVisit = temp;
			temp = NULL;
		}
		else
		{
			temp = temp->rightChild;
		}
	}
}

template<class T>
T * PostorderIterator<T>::Next()
{
	if (q.empty()) return 0;
	else
	{
		currentNode = q.front();
		q.pop();
		T &temp = currentNode->data;
		return &temp;
	}
}

//����Ϊǰ������������Ķ���
template<class T>
class PreorderIterator
{
public:
	PreorderIterator(TreeNode<T> * root)
	{
		currentNode = root;
		preorder();		//��ǰ������Ľ���洢��������
	}
	T * Next();

private:
	void preorder();

private:
	queue<TreeNode<T> *> q;
	TreeNode<T> *currentNode;
};

template<class T>
//˽�к��������ڰ�ǰ�����������浽�����У�Next����ֱ��ȡfront���
void PreorderIterator<T>::preorder()
{
	stack<TreeNode<T> *> s;
	TreeNode<T> *temp = currentNode;

	while (temp != 0 || !s.empty())
	{
		while (temp)
		{
			s.push(temp);
			q.push(temp);
			temp = temp->leftChild;
		}

		if (!s.empty())
		{
			temp = s.top();
			s.pop();
			temp = temp->rightChild;
		}
	}
}

template<class T>
T * PreorderIterator<T>::Next()
{
	if (q.empty()) return 0;
	else
	{
		currentNode = q.front();
		q.pop();
		T &temp = currentNode->data;
		return &temp;
	}
}

//����Ϊ��α����������Ķ���
template<class T>
class LevelorderIterator
{
public:
	LevelorderIterator(TreeNode<T> * root)
	{
		currentNode = root;
		q.push(root);	//��ʼ������Ĳ�α�������
	}
	T * Next();
	TreeNode<T>* GetCurrNode();

private:
	queue<TreeNode<T> *> q;
	TreeNode<T> *currentNode;
};

template<class T>
T * LevelorderIterator<T>::Next()
{
	if (q.empty()) return 0;
	if (currentNode->leftChild)
		q.push(currentNode->leftChild);
	if (currentNode->rightChild)
		q.push(currentNode->rightChild);
	
	currentNode = q.front();
	T &temp = currentNode->data;
	q.pop();
	if (!q.empty())
		currentNode = q.front();
	return &temp;
}

template<class T>
TreeNode<T>* LevelorderIterator<T>::GetCurrNode()
{
	return currentNode;
}

void run_exp3()
{
	BinaryTree<char> binaryTree('A');
	binaryTree.InsertToLeft(binaryTree.GetRoot(), 'B');
	binaryTree.InsertToRight(binaryTree.GetRoot(), 'C');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetLeftChild(), 'D');
	binaryTree.InsertToRight(binaryTree.GetRoot()->GetLeftChild(), 'E');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetRightChild(), 'F');
	binaryTree.InsertToRight(binaryTree.GetRoot()->GetRightChild(), 'G');
	binaryTree.InsertToLeft(binaryTree.GetRoot()->GetLeftChild()->GetLeftChild(), 'H');

	BinaryTree<char> copyTree(binaryTree);

	//�������������
	InorderIterator<char> inorder(binaryTree.GetRoot());
	while (true)
	{
		char *result = inorder.Next();
		if (result)
		{
			cout << *result << " ";
		}
		else
		{
			break;
		}
	}
	cout << endl;

	//�������������
	PostorderIterator<char> postorder(binaryTree.GetRoot());
	while (true)
	{
		char *result = postorder.Next();
		if (result)
		{
			cout << *result << " ";
		}
		else
		{
			break;
		}
	}
	cout << endl;

	//ǰ�����������
	PreorderIterator<char> preorder(binaryTree.GetRoot());
	while (true)
	{
		char *result = preorder.Next();
		if (result)
		{
			cout << *result << " ";
		}
		else
		{
			break;
		}
	}
	cout << endl;

	//��α���������
	LevelorderIterator<char> leverorder(binaryTree.GetRoot());
	while (true)
	{
		char *result = leverorder.Next();
		if (result)
		{
			cout << *result << " ";
		}
		else
		{
			break;
		}
	}
	cout << endl;
}