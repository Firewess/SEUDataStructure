#pragma once
/*
 *author: ��� jiefeng
 *date: 2018/10/3 09:41
 *description: the second assignment of data structure
*/
#include <iostream>

using namespace std;

/*
���¶�Ӧ��Ӣ������ P107 1
��
��Ϊ���������
1����A[i][j]��ֵ��Ϊ0��
	��λ��ʱ�临�Ӷ�ΪO(Terms)
	�޸�ֵֻ��ֱ�ӰѶ�λ�õ���Ԫ���޸ļ��ɣ�
	�����޸�ֵ��ʱ�临�Ӷ�ΪO(1)
2����A[i][j]��ֵΪ0��
	��λ��ʱ�临�Ӷ�ΪΪO(Terms)
	ԭ��ֵΪ0����ô�޸�ֵ����Ҫ�²���Ԫ�أ��������Բ��ҵ�Ӧ��λ��k���룬����Ҫ�ƶ�Terms-k��Ԫ�أ�
	�ܵ��ƶ�����Ϊ(Terms - k + 1)*(Terms - k) / 2
	�ɴ˵��޸�ֵ��ʱ�临�Ӷ�Ϊ��O(Terms^2)
*/

/*
���¶�Ӧ��Ӣ������ P107 2
�𣺿����������ţ��о�ϡ�����Ĵ洢��ʽ���֣�ת��һ������ֻ��Ҫ�Ȱ��и��н�����Ȼ���վ�����н����ȶ����򼴿ɣ�
	������ɱ���ת����ɣ�Ŀǰƽ��ʱ�临�Ӷ���͵��ȶ�����ʽΪ�������򣬿�������O(n)��ʱ�临�Ӷȣ���O(Terms)
*/

/*
���¶�Ӧ��Ӣ������ P107 4
*/
class SparseMatrix;

class MatrixTerm
{
	friend class SparseMatrix;
public:
	int getRow()
	{
		return row;
	}
	int getCol()
	{
		return col;
	}
	int getValue()
	{
		return value;
	}
private:
	int row, col, value;
};

class SparseMatrix
{
public:
	SparseMatrix(int r, int c, int t, bool flag = true);	//flagΪtrue��ʾ��Ҫ�ֶ�������������ʼ��ϡ�����Ĭ��Ϊtrue
	~SparseMatrix();
	SparseMatrix & FastTranspose();

	friend ostream & operator <<(ostream & os, SparseMatrix & matrix);
private:
	int rows, cols, terms;
	MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix(int r, int c, int t, bool flag)
{
	this->rows = r;
	this->cols = c;
	this->terms = t;
	this->smArray = new MatrixTerm[terms];
	if (flag)
	{
		cout << "������ϡ�����ĸ���(һ����" << terms << "��)��\n";
		for (int i = 0; i < terms; i++)
		{
			cout << "������� " << i + 1 << " �����: ";
			cin >> smArray[i].row;
			cout << "������� " << i + 1 << " �����: ";
			cin >> smArray[i].col;
			cout << "������� " << i + 1 << " ���ֵ: ";
			cin >> smArray[i].value;
		}
	}
}

SparseMatrix::~SparseMatrix()
{
	delete[] smArray;
}

SparseMatrix & SparseMatrix::FastTranspose()
{
	static SparseMatrix b(cols, rows, terms, false);
	int *RowInfo = new int[cols];

	for (int i = 0; i < cols; i++)
	{
		RowInfo[i] = 0;
	}
	for (int i = 0; i < terms; i++)
	{
		RowInfo[smArray[i].col]++;
	}

	for (int i = cols - 1; i >= 0; i--)
	{
		RowInfo[i] = 0;
		for (int j = 0; j < i; j++)
		{
			RowInfo[i] += RowInfo[j];
		}
	}

	for (int i = 0; i < terms; i++)
	{
		int pos = RowInfo[smArray[i].col];

		b.smArray[pos].row = smArray[i].col;
		b.smArray[pos].col = smArray[i].row;
		b.smArray[pos].value = smArray[i].value;

		RowInfo[smArray[i].col]++;
	}

	delete[] RowInfo;

	return b;
}

ostream & operator <<(ostream & os, SparseMatrix & matrix)
{
	int count = 0;
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			if (j != 0 || j != matrix.cols)
				cout << " ";
			if (matrix.smArray[count].getRow() == i && matrix.smArray[count].getCol() == j)
			{
				cout << matrix.smArray[count++].getValue();
			}
			else
			{
				cout << 0;
			}
		}
		cout << endl;
	}

	return os;
}

void run_P107()
{
	SparseMatrix matrix(4, 3, 5);

	cout << matrix;

	cout << "ת�ú�ľ���Ϊ��\n";
	cout << matrix.FastTranspose();
}