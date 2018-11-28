#include <iostream>

using namespace std;

#define K 10
#define MAX 65535

int loserTree[K];               /* 存储中间节点值，下标0处存储冠军节点 */
int leaves[K + 1];                /* 从下标1开始存储叶子节点值，下标0处存储一个最小值节点 */

void adjust(int i)
{
	int parent = (i + K - 1) / 2;      /* 求出父节点的下标 */
	while (parent > 0)
	{
		if (leaves[i] > leaves[loserTree[parent]])
		{
			int temp = loserTree[parent];
			loserTree[parent] = i;
			/* i指向的是优胜者 */
			i = temp;
		}
		parent = parent / 2;
	}
	loserTree[0] = i;
}

void initLoserTree()
{
	int i;
	for (i = 1; i < K + 1; i++)
		scanf("%d", &leaves[i]);
	leaves[0] = MIN;
	for (int i = 0; i < K; i++)
		loserTree[i] = 0;
	for (int i = K; i > 0; i--)
		adjust(i);
}