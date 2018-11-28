//#include <iostream>
//
//using namespace std;
//
//#define K 10
//#define MAX 65535
//int leaves[K + 1];
//int successTree[K];
//
///* ���ڵ����ڲ��ڵ���е��� */
//void adjust(int i)
//{
//	int m, n;
//	if (2 * i < K)               /* ��ȡ�������ӽ�� */
//		m = successTree[2 * i];
//	else
//		m = 2 * i - K + 1;
//	if (2 * i + 1 < K)                 /* ��ȡ�����Һ��ӽڵ� */
//		n = successTree[2 * i + 1];
//	else
//		n = 2 * i + -K + 2;
//	successTree[i] = leaves[m] > leaves[n] ? n : m; /* ����ʤ���ж� */
//}
//
///* ��ʼ��Ҷ�ӽڵ㲢���ڲ��ڵ���������ڶѵĵ��� */
//void initTree()
//{
//	for (int i = 0; i < K; i++)
//		cin >> leaves[i];
//	for (int i = K - 1; i > 0; i--)
//		adjust(i);
//}
//
///* ���¶��϶�ʤ�������е��� */
//void adjustToRoot(int i)
//{
//	int parent = (i + K - 1) / 2; /* �Դӵ�ǰ�ڵ㵽���ڵ�·���ϵ�����
//								   * �ڵ���е��� */
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
//	for (int i = 1; i < K + 1; i++)      /* ÿ�������ֵ�滻���ھ��ڵ㣬������
//								 * ���е���,���յõ�������������� */
//	{
//		cout << leaves[successTree[1]];
//		leaves[successTree[1]] = MAX;
//		adjustToRoot(successTree[1]);
//	}
//	return 0;
//}