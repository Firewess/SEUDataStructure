#pragma once
/*
 *author: ��� jiefeng
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
	int *count;	//���ڴ���ذ屻��������������ָ�룬��Ϊnewһ����ά������Ҫȷ���У��ʲ���һά������д洢��
	int rows, cols;	//��ά��ͼ���������������
	int imove[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int jmove[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int ibug, jbug;	//��ǰС���λ��
	int currWalked;	//��ǰ�Ѿ��߹�������Ԫ�ص�����
};

RandomWalk::RandomWalk(int n, int m) :rows(n), cols(m), currWalked(0)
{
	count = new int[rows*cols];

	if (n <= 2 || m <= 1 || n > 40 || m > 20) throw "������ֵΥ�棡2 < n <= 40, 2 <= m <= 20";
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
		throw "��ʼλ�ò��������飡";

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

	cout << "�ܵ����ߴ���Ϊ��" << walkCount << endl;
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