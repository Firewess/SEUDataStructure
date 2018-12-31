#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/12/22
@File: P475.h
@Description: The fourteenth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <stack>

using namespace std;

/*
以下为自建的链表BST
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

	void Insert(const pair<K, E> &thePair);
	void Delete(const pair<K, E> &thePair);

	pair<K, E> & Get(const K &);
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
		else if (thePair.first > currNode->data.first) currNode = currNode->rightChild;
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
//这是用于处理要删除节点有两个孩子节点的情况的私有函数，
//tempRoot为搜索子树的根，delNode为要删除的元素
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

	if (!currNode) return;	//BST中未搜索到这个节点，退出

	//因为左子树的最大元素、右子树的最小元素，最多度为1，故只有两种情况
	//情况1，要删除的节点为叶子节点
	if (currNode->leftChild == 0 && currNode->rightChild == 0)
	{
		if (currNode == parentNode->leftChild)
			parentNode->leftChild = NULL;
		else
			parentNode->rightChild = NULL;
		delete currNode;
		currNode = NULL;
	}
	//情况2，要删除的节点只有一个孩子节点
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

	if (!currNode) return;	//BST中未搜索到这个节点，退出

	//情况1，要删除的节点为叶子节点
	if (currNode->leftChild == 0 && currNode->rightChild == 0)
	{
		if (currNode == parentNode->leftChild)
			parentNode->leftChild = NULL;
		else
			parentNode->rightChild = NULL;
		delete currNode;
		currNode = NULL;
	}
	//情况2，要删除的节点含有两个孩子节点
	else if (currNode->leftChild != 0 && currNode->rightChild != 0)
	{
		//判断左右子树的深度，把深度大的子树替换上来，以尽可能维持BST的平衡度
		int lTreeDepth = Depth(currNode->leftChild);
		int rTreeDepth = Depth(currNode->rightChild);
		if (lTreeDepth > rTreeDepth)
		{
			//找出左子树的最大元素
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
			//找出右子树的最小元素
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
	//情况3，要删除的节点只有一个孩子节点
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

template<class K, class E>
pair<K, E> & BST<K, E>::Get(const K &key)
{
	BstNode<K, E> *currNode = root, *temp = 0;
	while (currNode)
	{
		temp = currNode;
		if (key < currNode->data.first) currNode = currNode->leftChild;
		else if (key > currNode->data.first) currNode = currNode->rightChild;
		else
		{
			return currNode->data;
		}
	}

	return NULL;
}

/*
以下对应于英文书P475 6
*/
template<class K, class E>
class HashTable
{
public:
	HashTable();
	~HashTable()
	{
		if (array != NULL)
		{
			delete[] array;
			array = NULL;
		}
	}
	void Insert(const pair<K, E> &);
	void Delete(const pair<K, E> &);
	pair<K, E> & Get(const K &);
	bool IsEmpty() const;

private:
	int hash(const pair<K, E> &);
	int hash(const K &);

private:
	BST<K, E> *array;	//哈希散列地址的数组
	int size;
	int DIVISOR = 97;
};

template<class K, class E>
HashTable<K, E>::HashTable()
{
	array = new BST<K, E>[this->DIVISOR];
	this->size = 0;
}

template<class K, class E>
inline int HashTable<K, E>::hash(const pair<K, E> &pair)
{
	return pair.first % DIVISOR;
}

template<class K, class E>
inline int HashTable<K, E>::hash(const K & key)
{
	return key % DIVISOR;
}

template<class K, class E>
void HashTable<K, E>::Insert(const pair<K, E> &pair)
{
	int index = hash(pair);
	array[index].Insert(pair);
}

template<class K, class E>
void HashTable<K, E>::Delete(const pair<K, E> & pair)
{
	array[hast(pair)].Delete(pair);
}

template<class K, class E>
pair<K, E> & HashTable<K, E>::Get(const K &key)
{
	return array[hash(key)].Get(key);
}

template<class K, class E>
bool HashTable<K, E>::IsEmpty() const
{
	for (int i = 0; i < DIVISOR; i++)
	{
		if (array[i].root != NULL)
			return false;
	}

	return true;
}

void run_P475()
{
	HashTable<int, int> hashTable;
	for (int i = 0; i < 200; i++)
		hashTable.Insert(pair<int, int>(i, i));
}