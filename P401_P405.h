#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/12/15
@File: P401_P405.h
@Description: The twelfth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include "P194.h"	//�����Զ����Chainģ����

/*
���¶�Ӧ��Ӣ����P401 1
�𣺼�P401-1.docx
*/

/*
���¶�Ӧ��Ӣ����P401 3
*/
template<class T>
void LinklistInsertSort(Chain<T> chain)
{
	for (int i = 2; i < chain.length(); i++)
	{
		
	}
}

/*
���¶�Ӧ��Ӣ����P405 1
*/

/*
���¶�Ӧ��Ӣ����P405 2
*/

/*
���¶�Ӧ��Ӣ����P405 5
*/

void run_P401_P405()
{
	Chain<int> chain;
	chain.Add(0);	//��Ϊ��Ҫ��֤��һ��Ԫ������С��
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

	cout << "����֮ǰ������\n" << chain << endl;
	LinklistInsertSort(chain);
	cout << "����֮�������: \n" << chain << endl;
}