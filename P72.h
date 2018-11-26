#pragma once
/*
 *author: 奉捷 jiefeng
 *date: 2018/10/3 09:41
 *description: the first week's assignment of data structure
*/
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

/*
以下对应于英文书上 P72 10
*/
int BinarySearch(int *a, const int x, const int n)
{
	int left = 0, right = n - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (x < a[middle])
		{
			right = middle - 1;
		}
		else if (x > a[middle])
		{
			left = middle - 1;
		}
		else
		{
			return middle;
		}
	}

	return -1;
}

void TimeSearch()
{
	int a[100], n[10];
	const long r[20] = { 300000, 300000, 200000, 200000, 100000, 100000, 100000, 80000,
		80000, 50000, 50000, 25000, 15000, 10000, 7500, 7000, 6000, 5000, 5000 };

	for (int i = 0; i < 100; i++)
	{
		a[i] = i + 1;
	}

	for (int i = 0; i < 10; i++)
	{
		n[i] = i * 10;
	}

	cout << "n     totalTime     runTime" << endl;

	for (int i = 0; i < 10; i++)
	{
		clock_t start, stop;
		start = clock();
		for (long temp = 0; temp < r[i]; temp++)
		{
			int k = BinarySearch(a, 0, n[i]);
		}
		stop = clock();
		double totalTime = (double)(stop - start) / CLOCKS_PER_SEC;
		double runTime = totalTime / (double)(r[i]);
		cout << n[i] << setw(10) << totalTime << setw(15) << runTime << endl;
	}

	cout << "Times are in hubredths of a second." << endl;
}

void run_P72()
{
	TimeSearch();
}