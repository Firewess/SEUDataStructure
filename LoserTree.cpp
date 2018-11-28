#include <iostream>

using namespace std;

#define K 10
#define MAX 65535

int loserTree[K];               /* �洢�м�ڵ�ֵ���±�0���洢�ھ��ڵ� */
int leaves[K + 1];                /* ���±�1��ʼ�洢Ҷ�ӽڵ�ֵ���±�0���洢һ����Сֵ�ڵ� */

void adjust(int i)
{
	int parent = (i + K - 1) / 2;      /* ������ڵ���±� */
	while (parent > 0)
	{
		if (leaves[i] > leaves[loserTree[parent]])
		{
			int temp = loserTree[parent];
			loserTree[parent] = i;
			/* iָ�������ʤ�� */
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