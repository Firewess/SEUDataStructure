/**************************************************
@Author: Jie Feng
@Time: 2018/10/13 14:29
@File: P157.h
@Description: The third week's assignment of data structure of Mr. Jianhua Lv
**************************************************/

#pragma once
#include <iostream>
#include <stack>
#include "P138.h"	//引入自己创建的Stack数据结构，便于输出

using namespace std;

/*
以下对应于英文书上 P157 2
答：对于一个m*n的迷宫，path的长度最大则要尽可能的“绕路”，即让老鼠在迷宫内沿着行来回走是长度最大的，
	由此思想可得，path的最大长度为(m - m/2)*p + m/2，在m为奇数时可能取到最大 
*/


/*
以下对应于英文书上 P157 3
答：最坏的时间复杂度为：O(m * n)，因为最多递归调用 m * n次，而一次调用的while循环
	最多执行次数为8次，其时间复杂度为O(1)，所以最坏的时间复杂度为O(m * n * 1) = O(m * n)
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
		cout << "迷宫中不存在从入口到出口的路径" << endl;
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