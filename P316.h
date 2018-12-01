#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/11/17
@File: P316.h
@Description: The ninth week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

/*
以下对应于英文书P316 3
*/
class Sets
{
public:
	Sets(int num);
	~Sets()
	{
		if(parent) delete[] parent;
	}

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
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

void Sets::SimpleUnion(int i, int j)
{
	parent[i] = j;
}

int Sets::SimpleFind(int i)
{
	try
	{
		while (parent[i] >= 0)
			i = parent[i];
		return i;
	}
	catch(...)
	{
		return 0;
	}
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
	srand(time(0));

	Sets simpleSet(5000);
	clock_t start, stop;
	start = clock();
	for (int i = 0; i < 10000; i++)
		simpleSet.SimpleFind(rand() % 5000);
	for (int i = 0; i < 1000; i++)
		simpleSet.SimpleUnion(rand() % 5000, rand() % 5000);
	stop = clock();
	double totalTime = (double)(stop - start) / CLOCKS_PER_SEC;

	cout << "Simple" << setw(10) << totalTime << setw(15) << endl;

	Sets weightedSets(5000);
	start = clock();
	for (int i = 0; i < 10000; i++)
		simpleSet.CollapsingFind(rand() % 5000);
	for (int i = 0; i < 1000; i++)
		simpleSet.WeightedUnion(rand() % 5000, rand() % 5000);
	stop = clock();
	totalTime = (double)(stop - start) / CLOCKS_PER_SEC;

	cout << "Weighted" << setw(10) << totalTime << setw(15) << endl;
}