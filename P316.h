#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/17
@File: P316.h
@Description: The ninth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <cstring>

using namespace std;

/*
���¶�Ӧ��Ӣ����P316 3
*/
class Sets
{
public:
	Sets(int num);

	void SimpleUnion(int i, int j);
	int SimpleFind(int i);

	void WeightedUnion(int i, int j);
	int CollapsingFind(int i);

private:
	int *parent;
	int n;
};

Sets::Sets(int num)
{
	if (num < 2) throw "Must be at least 2 elements.";
	n = num;
	parent = new int[n];
	memset(parent, -1, n);
}

void Sets::SimpleUnion(int i, int j)
{
	parent[i] = j;
}

int Sets::SimpleFind(int i)
{
	while (parent[i] >= 0)
		i = parent[i];

	return i;
}

void Sets::WeightedUnion(int i, int j)
{
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j])
	{
		parent[i] = j;
		parent[j] = temp;
	}
	else
	{
		parent[j] = i;
		parent[i] = temp;
	}
}

int Sets::CollapsingFind(int i)
{
	int r = i;
	for (; parent[r] >= 0; r = parent[r]);
	while (i != r)
	{
		int s = parent[i];
		parent[i] = r;
		i = s;
	}

	return r;
}

void run_P316()
{

}