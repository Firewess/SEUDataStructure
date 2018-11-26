#pragma once
/*
 *author: 奉捷 jiefeng
 *date: 2018/10/3 09:41
 *description: the second assignment of data structure
*/
#include <iostream>

using namespace std;

/*
以下对应于英文书上 P107 1
答：
分为两种情况：
1）、A[i][j]的值不为0：
	则定位的时间复杂度为O(Terms)
	修改值只需直接把定位得到的元素修改即可，
	所以修改值的时间复杂度为O(1)
2）、A[i][j]的值为0：
	定位的时间复杂度为为O(Terms)
	原来值为0，那么修改值则需要新插入元素，假设线性查找到应在位置k插入，则需要移动Terms-k个元素，
	总的移动次数为(Terms - k + 1)*(Terms - k) / 2
	由此得修改值的时间复杂度为：O(Terms^2)
*/

/*
以下对应于英文书上 P107 2
答：可以做到更优，研究稀疏矩阵的存储方式后发现，转置一个矩阵只需要先把行跟列交换，然后按照矩阵的行进行稳定排序即可，
	排序完成便是转置完成，目前平均时间复杂度最低的稳定排序方式为基数排序，可以做到O(n)的时间复杂度，即O(Terms)
*/

/*
以下对应于英文书上 P107 4
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
	SparseMatrix(int r, int c, int t, bool flag = true);	//flag为true表示需要手动输入数据来初始化稀疏矩阵，默认为true
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
		cout << "请输入稀疏矩阵的各项(一共有" << terms << "项)：\n";
		for (int i = 0; i < terms; i++)
		{
			cout << "请输入第 " << i + 1 << " 项的行: ";
			cin >> smArray[i].row;
			cout << "请输入第 " << i + 1 << " 项的列: ";
			cin >> smArray[i].col;
			cout << "请输入第 " << i + 1 << " 项的值: ";
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

	cout << "转置后的矩阵为：\n";
	cout << matrix.FastTranspose();
}