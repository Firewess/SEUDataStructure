#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/12/15
@File: P401_P405.h
@Description: The twelfth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include "P194.h"	//引入自定义的Chain模板类

/*
以下对应于英文书P401 1
答：见P401-1.docx
*/

/*
以下对应于英文书P401 3
*/
template<class T>
void LinklistInsertSort(Chain<T> chain)
{
	for (int i = 2; i < chain.length(); i++)
	{
		
	}
}

/*
以下对应于英文书P405 1
*/

/*
以下对应于英文书P405 2
*/

/*
以下对应于英文书P405 5
*/

void run_P401_P405()
{
	Chain<int> chain;
	chain.Add(0);	//因为需要保证第一个元素是最小的
	chain.Add(2);
	chain.Add(16);
	chain.Add(30);
	chain.Add(8);
	chain.Add(28);
	chain.Add(4);
	chain.Add(10);
	chain.Add(20);
	chain.Add(6);
	chain.Add(18);

	cout << "排序之前的链表：\n" << chain << endl;
	LinklistInsertSort(chain);
	cout << "排序之后的链表: \n" << chain << endl;
}