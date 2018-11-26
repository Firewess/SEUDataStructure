#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/10
@File: P296.h
@Description: The seventh week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <stack>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

/*
���¶�Ӧ��Ӣ����P296 1
*/
template<class K, class E> class BST;

template<class K, class E>
class BstNode
{
	friend class BST<K, E>;
public:
	BstNode(pair<K, E> data)
	{
		this->data = data;
		leftChild = 0;
		rightChild = 0;
	}
	BstNode<K, E> * GetLeftChild()
	{
		return leftChild;
	}
	BstNode<K, E> * GetRightChild()
	{
		return rightChild;
	}

private:
	pair<K, E> data;
	BstNode<K, E> *leftChild;
	BstNode<K, E> *rightChild;
};

template<class K, class E>
class BST
{
public:
	BST()
	{
		root = 0;
	}
	BST(BstNode<K, E> *node)
	{
		root = node;
	}
	~BST()
	{
		stack<BstNode<K, E> *> s;
		BstNode<K, E> *currNode = this->root;
		BstNode<K, E> *deleteNode = this->root;

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

	void Insert(const pair<K, E> &thePair);
	void Delete(const pair<K, E> &thePair);
	int Depth(BstNode<K, E> * root);
	BstNode<K, E>* GetRoot()
	{
		return root;
	}

private:
	void Delete(BstNode<K, E> *tempRoot, BstNode<K, E> *delNode);

private:
	BstNode<K, E> *root;
};

template<class K, class E>
void BST<K, E>::Insert(const pair<K, E> &thePair)
{
	BstNode<K, E> *currNode = root, *temp = 0;
	while (currNode)
	{
		temp = currNode;
		if (thePair.first < currNode->data.first) currNode = currNode->leftChild;
		else if(thePair.first > currNode->data.first) currNode = currNode->rightChild;
		else
		{
			currNode->data.second = thePair.second;
			return;
		}
	}

	currNode = new BstNode<K, E>(thePair);
	if (root)
	{
		if (thePair.first < temp->data.first) temp->leftChild = currNode;
		else temp->rightChild = currNode;
	}
	else root = currNode;
}

template<class K, class E>
//�������ڴ���Ҫɾ���ڵ����������ӽڵ�������˽�к�����
//tempRootΪ���������ĸ���delNodeΪҪɾ����Ԫ��
void BST<K, E>::Delete(BstNode<K, E> *tempRoot, BstNode<K, E> *delNode)
{
	BstNode<K, E> *currNode = tempRoot, *parentNode = currNode;
	while (currNode && currNode->data.first != delNode->data.first)
	{
		parentNode = currNode;
		if (delNode->data.first < currNode->data.first) currNode = currNode->leftChild;
		else if (delNode->data.first > currNode->data.first) currNode = currNode->rightChild;
		else
		{
			if (delNode->data.second != currNode->data.second) return;
		}
	}

	if (!currNode) return;	//BST��δ����������ڵ㣬�˳�

	//��Ϊ�����������Ԫ�ء�����������СԪ�أ�����Ϊ1����ֻ���������
	//���1��Ҫɾ���Ľڵ�ΪҶ�ӽڵ�
	if (currNode->leftChild == 0 && currNode->rightChild == 0)
	{
		if (currNode == parentNode->leftChild)
			parentNode->leftChild = NULL;
		else
			parentNode->rightChild = NULL;
		delete currNode;
		currNode = NULL;
	}
	//���2��Ҫɾ���Ľڵ�ֻ��һ�����ӽڵ�
	else
	{
		if (currNode->leftChild != 0)
		{
			if (currNode == parentNode->leftChild)
				parentNode->leftChild = currNode->leftChild;
			else
				parentNode->rightChild = currNode->leftChild;
			delete currNode;
			currNode = NULL;
		}
		else
		{
			if (currNode == parentNode->leftChild)
				parentNode->leftChild = currNode->rightChild;
			else
				parentNode->rightChild = currNode->rightChild;
			delete currNode;
			currNode = NULL;
		}
	}
}

template<class K, class E>
void BST<K, E>::Delete(const pair<K, E> &thePair)
{
	BstNode<K, E> *currNode = root, *parentNode = currNode;
	while (currNode && currNode->data.first != thePair.first)
	{
		parentNode = currNode;
		if (thePair.first < currNode->data.first) currNode = currNode->leftChild;
		else if (thePair.first > currNode->data.first) currNode = currNode->rightChild;
		else
		{
			if (thePair.second != currNode->data.second) return;
		}
	}

	if (!currNode) return;	//BST��δ����������ڵ㣬�˳�

	//���1��Ҫɾ���Ľڵ�ΪҶ�ӽڵ�
	if (currNode->leftChild == 0 && currNode->rightChild == 0)
	{
		if (currNode == parentNode->leftChild)
			parentNode->leftChild = NULL;
		else
			parentNode->rightChild = NULL;
		delete currNode;
		currNode = NULL;
	}
	//���2��Ҫɾ���Ľڵ㺬���������ӽڵ�
	else if (currNode->leftChild != 0 && currNode->rightChild != 0)
	{
		//�ж�������������ȣ�����ȴ�������滻�������Ծ�����ά��BST��ƽ���
		int lTreeDepth = Depth(currNode->leftChild);
		int rTreeDepth = Depth(currNode->rightChild);
		if (lTreeDepth > rTreeDepth)
		{
			//�ҳ������������Ԫ��
			BstNode<K, E> *tempCurr = currNode->leftChild, *tempParent = tempCurr;
			while (tempCurr->rightChild)
			{
				parentNode = tempCurr;
				tempCurr = tempCurr->rightChild;
			}
			currNode->data = tempCurr->data;
			Delete(currNode->leftChild, tempCurr);
		}
		else
		{
			//�ҳ�����������СԪ��
			BstNode<K, E> *tempCurr = currNode->rightChild, *tempParent = tempCurr;
			while (tempCurr->leftChild)
			{
				parentNode = tempCurr;
				tempCurr = tempCurr->leftChild;
			}
			currNode->data = tempCurr->data;
			Delete(currNode->rightChild, tempCurr);
		}
	}
	//���3��Ҫɾ���Ľڵ�ֻ��һ�����ӽڵ�
	else
	{
		if (currNode->leftChild != 0)
		{
			if (currNode == parentNode->leftChild)
				parentNode->leftChild = currNode->leftChild;
			else
				parentNode->rightChild = currNode->leftChild;
			delete currNode;
			currNode = NULL;
		}
		else
		{
			if (currNode == parentNode->leftChild)
				parentNode->leftChild = currNode->rightChild;
			else
				parentNode->rightChild = currNode->rightChild;
			delete currNode;
			currNode = NULL;
		}
	}
}

template<class K, class E>
int BST<K, E>::Depth(BstNode<K, E> * root)
{
	if (root == NULL)
		return 0;
	int lTreeDepth = Depth(root->leftChild);
	int rTreeDepth = Depth(root->rightChild);
	return lTreeDepth > rTreeDepth ? lTreeDepth + 1 : rTreeDepth + 1;
}

/*
���¶�Ӧ��Ӣ����P296 2
*/
void DepthDivLogN(int n)	//��ÿ����������ֳɵ����ĺ�������ֹ�����������Ķѿռ䵼���ڴ治��
{
	default_random_engine random(time(NULL));	//�������������
	uniform_int_distribution<int> dis1(0, n);	//C++11�ṩ�ľ��ȷֲ�ģ���࣬��Ϊ�������ξ��ȷֲ��������ģ����

	//����n=100
	BST<int, int> bst_n;
	for (int i = 0; i < n; i++)
		bst_n.Insert(pair<int, int>(dis1(random), dis1(random)));
	int dep_n = bst_n.Depth(bst_n.GetRoot());
	cout << n << "��" << dep_n / (log(n) / log(2)) << endl;	//log(n) / log(2)Ϊ���׹�ʽ����Ϊ�˰���10Ϊ�׵Ķ���������2Ϊ�׵�
}

void fun_P292_2()
{
	DepthDivLogN(100);
	DepthDivLogN(500);
	DepthDivLogN(1000);
	DepthDivLogN(2000);
	DepthDivLogN(3000);
	DepthDivLogN(4000);
	DepthDivLogN(5000);
	DepthDivLogN(6000);
	DepthDivLogN(7000);
	DepthDivLogN(8000);
	DepthDivLogN(9000);
	DepthDivLogN(10000);
}


void run_P296()
{
	//���¶�Ӧ��Ӣ����P296 1
	BST<int, int> bst;
	for (int i = 0; i < 5; i++)
		bst.Insert(pair<int, int>((i + 1) * 2, 10 * (i + 1)));

	for (int i = 0; i < 5; i++)
		bst.Insert(pair<int, int>((i + 1) * 2 - 1, i + 1));
	//�˴�8��40��Ӧ������Ҷ�ӽڵ����������Ե��Բ鿴���ɵ������������ּ����δ���������������������ֱ��
	//�������Delete������ʱ�临�Ӷȣ�
	//����Delete�����Ĳ������Ϊh����Ҫɾ���ڵ��������Ϊn��˽��Delete�����Ĳ������Ϊ h-n
	//���ܵ�ɾ��������ʱ�临��Ϊ��O(2h - n)
	bst.Delete(pair<int, int>(8, 40));

	//���¶�Ӧ��Ӣ����P296 2
	fun_P292_2();
}