//#include <iostream>
//
//using namespace std;
//
//#define K 10
//#define MAX 65535
//int leaves[K + 1];
//int successTree[K];
//
///* 对于单个内部节点进行调整 */
//void adjust(int i)
//{
//	int m, n;
//	if (2 * i < K)               /* 获取它的左孩子结点 */
//		m = successTree[2 * i];
//	else
//		m = 2 * i - K + 1;
//	if (2 * i + 1 < K)                 /* 获取它的右孩子节点 */
//		n = successTree[2 * i + 1];
//	else
//		n = 2 * i + -K + 2;
//	successTree[i] = leaves[m] > leaves[n] ? n : m; /* 进行胜负判定 */
//}
//
///* 初始化叶子节点并对内部节点进行类似于堆的调整 */
//void initTree()
//{
//	for (int i = 0; i < K; i++)
//		cin >> leaves[i];
//	for (int i = K - 1; i > 0; i--)
//		adjust(i);
//}
//
///* 自下而上对胜者树进行调整 */
//void adjustToRoot(int i)
//{
//	int parent = (i + K - 1) / 2; /* 对从当前节点到根节点路径上的所有
//								   * 节点进行调整 */
//	while (parent > 0)
//	{
//		adjust(parent);
//		parent = parent / 2;
//	}
//}
//
//int main()
//{
//	initTree();
//	for (int i = 1; i < K + 1; i++)      /* 每次用最大值替换掉冠军节点，并对树
//								 * 进行调整,最终得到升序排序的序列 */
//	{
//		cout << leaves[successTree[1]];
//		leaves[successTree[1]] = MAX;
//		adjustToRoot(successTree[1]);
//	}
//	return 0;
//}