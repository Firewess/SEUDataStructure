#pragma once
/*
 *author: 奉捷 jiefeng
 *date: 2018/10/7 17:12
 *description: the first experiment of data structure
*/
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

#define MAX_WALK_SIZE 50000

class RandomWalk
{
public:
	RandomWalk(int n, int m);
	~RandomWalk();
	bool IsDone();
	void Walk(int startI,int startJ);

private:
	int *count;	//用于储存地板被经过次数的数组指针，因为new一个二维数组需要确定列，故采用一维数组进行存储了
	int rows, cols;	//二维地图数组的行数、列数
	int imove[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int jmove[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int ibug, jbug;	//当前小虫的位置
	int currWalked;	//当前已经走过的数组元素的数量
};

RandomWalk::RandomWalk(int n, int m) :rows(n), cols(m), currWalked(0)
{
	count = new int[rows*cols];

	if (n <= 2 || m <= 1 || n > 40 || m > 20) throw "行列数值违规！2 < n <= 40, 2 <= m <= 20";
	for (int i = 0; i < rows*cols; i++)
		count[i] = 0;
}

RandomWalk::~RandomWalk()
{
	delete[] count;
}

inline bool RandomWalk::IsDone()
{
	return (currWalked == rows * cols);
}

void RandomWalk::Walk(int startI, int startJ)
{
	srand(time(0));
	if (startI >= rows || startJ >= cols || startI < 0 || startJ < 0)
		throw "开始位置不合理，请检查！";

	ibug = startI;
	jbug = startJ;
	count[ibug*cols + jbug]++;
	currWalked++;
	
	int walkCount = 0;
	for (; walkCount < MAX_WALK_SIZE; walkCount++)
	{
		if (IsDone())
			break;
		int k = rand() % 8;
		int tempIbug = ibug + imove[k];
		int tempJbug = jbug + jmove[k];
		while ( (tempIbug < 0) || (tempIbug >= rows) || (tempJbug < 0) || (tempJbug >= cols) )
		{
			k = rand() % 8;
			tempIbug = ibug + imove[k];
			tempJbug = jbug + jmove[k];
		}
		ibug = tempIbug;
		jbug = tempJbug;
		if (count[ibug*cols + jbug] == 0)
			currWalked++;
		count[ibug*cols + jbug]++;
	}

	cout << "总的行走次数为：" << walkCount << endl;
	for (int i = 0; i < rows*cols; i++)
	{
		if ((i % cols == 0) && i != 0)
			cout << endl;
		cout << setw(5)<< count[i] << " ";
	}
}

void run_experiment1()
{
	RandomWalk bug1(15, 15);
	bug1.Walk(9, 9);

	cout << endl << endl;

	RandomWalk bug2(39, 19);
	bug2.Walk(0, 0);
}