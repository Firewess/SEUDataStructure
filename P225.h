#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/10/29
@File: P225.h
@Description: The sixth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

/*
以下对应于英文书P225 2
*/
class DblList;

class DblListNode
{
	friend class DblList;
private:
	int data;
	DblListNode *left, *right;
};

class DblList
{
public:
	void Concatenate(DblList m);

private:
	DblListNode *first;
};

//以下函数总有只有6步指针赋值操作，故时间复杂度为O(1)
void DblList::Concatenate(DblList m)
{
	//第一步，把*this的first的left节点与m的first的right节点相互连接
	this->first->left->right = m.first->right;
	m.first->right->left = this->first->left;

	//第二步，把m的first的left节点的right连接到*this的first，并把*this的left连接到m的first的left节点
	this->first->left = m.first->left;
	m.first->left->right = this->first;

	//第三步，把m链表置空
	m.first->left = 0;
	m.first->right = 0;
}