/**************************************************
@Author: Jie Feng
@Time: 2018/10/13 14:29
@File: P157.h
@Description: The third week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#pragma once
#include <iostream>
#include <stack>
#include "P138.h"	//�����Լ�������Stack���ݽṹ���������

using namespace std;

/*
���¶�Ӧ��Ӣ������ P157 2
�𣺶���һ��m*n���Թ���path�ĳ��������Ҫ�����ܵġ���·���������������Թ����������������ǳ������ģ�
	�ɴ�˼��ɵã�path����󳤶�Ϊ(m - m/2)*p + m/2����mΪ����ʱ����ȡ����� 
*/


/*
���¶�Ӧ��Ӣ������ P157 3
�����ʱ�临�Ӷ�Ϊ��O(m * n)����Ϊ���ݹ���� m * n�Σ���һ�ε��õ�whileѭ��
	���ִ�д���Ϊ8�Σ���ʱ�临�Ӷ�ΪO(1)���������ʱ�临�Ӷ�ΪO(m * n * 1) = O(m * n)
*/
struct Items
{
	int x, y, dir;
};

struct offsets
{
	int a, b;
};
enum directions { N, NE, E, SE, S, SW, W, NW };

offsets move[8] = { {-1, 0} ,{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

void Path(int m, int p, Stack<Items> myStack, int **maze, int **mark)
{
	if (myStack.IsEmpty())
	{
		cout << "�Թ��в����ڴ���ڵ����ڵ�·��" << endl;
		return;
	}
	Items temp = myStack.Top();
	myStack.Pop();
	int i = temp.x, j = temp.y, d = temp.dir;
	while (d < 8)
	{
		int currX = i + ::move[d].a;
		int currY = j + ::move[d].b;
		if (currX == m && currY == p)
		{
			cout << myStack;
			cout << i << " ," << j << " ," << d << endl;
			cout << m << " ," << p << endl;
			return;
		}
		if ((!maze[currX][currY]) && (!mark[currX][currY]))
		{
			mark[currX][currY] = 1;
			temp.x = i;
			temp.y = j;
			temp.dir = d + 1;
			myStack.Push(temp);
			i = currX;
			j = currY;
			d = N;
		}
		else d++;
	}
	Path(m, p, myStack, maze, mark);
}