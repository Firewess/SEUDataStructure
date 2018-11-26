#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/10/29
@File: P225.h
@Description: The sixth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

/*
���¶�Ӧ��Ӣ����P225 2
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

//���º�������ֻ��6��ָ�븳ֵ��������ʱ�临�Ӷ�ΪO(1)
void DblList::Concatenate(DblList m)
{
	//��һ������*this��first��left�ڵ���m��first��right�ڵ��໥����
	this->first->left->right = m.first->right;
	m.first->right->left = this->first->left;

	//�ڶ�������m��first��left�ڵ��right���ӵ�*this��first������*this��left���ӵ�m��first��left�ڵ�
	this->first->left = m.first->left;
	m.first->left->right = this->first;

	//����������m�����ÿ�
	m.first->left = 0;
	m.first->right = 0;
}