#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/17
@File: P301.h
@Description: The ninth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

/*
���¶�Ӧ��Ӣ����P301 1
*/
template<class T>
class WinnerTree
{
public:
	WinnerTree(T array[], int length);

private:
	void adjust(int i);
	void adjustToRoot();

private:
	int capacity;
	T *tree;
};

template<class T>
class LoserTree
{
public:
	LoserTree(T array[], int length);

private:
	void adjust(int i);

private:
	int capacity;
	T *tree;
};

/*
���¶�Ӧ��Ӣ����P301 4
*/
