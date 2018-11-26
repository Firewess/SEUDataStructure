#pragma once
/*
 *author: 奉捷 jiefeng
 *date: 2018/10/3 09:41
 *description: the second assignment of data structure
*/
#include <iostream>

using namespace std;

/*
以下对应于英文书上 P93 2
*/
int CompareArrays(int A[], int lenOfA, int B[], int lenOfB)
{
	int temp;
	for (int i = 0; (i < lenOfA) && (i < lenOfB); i++)
	{
		if (A[i] == B[i])
		{
			if (lenOfA < lenOfB)
			{
				return -1;
			}
			else if (lenOfA > lenOfB)
			{
				return 1;
			}
			for (int j = i + 1; (i < lenOfA) && (j < lenOfB); j++)
			{
				if (A[j] < B[j])
				{
					return -1;
				}
			}
		}
	}
}

/*
以下对应于英文书上 P93 6
*/
class Polynomial;

class Term
{
	friend class Polynomial;
public:
	float getCoef()
	{
		return coef;
	}
	void setCoef(const float f)
	{
		coef = f;
	}
	int getExp()
	{
		return exp;
	}
	void setExp(const int exp)
	{
		this->exp = exp;
	}
private:
	float coef;
	int exp;
};

class Polynomial
{
public:
	Polynomial(Term *termArray = NULL, int capacity = 0, int terms = 0);
	~Polynomial();
	Polynomial Add(Polynomial poly);
	//Polynomial Mult(Polynomial poly);
	float Eval(const float f);
private:
	Term *termArray;	//储存系数为非0项的数组
	int capacity;		//数组的容量
	int terms;			//系数非0项的数目
	void newItem(const float theCoeff, const int theExp);
	friend ostream & operator <<(ostream &os, Polynomial &poly);
};

Polynomial::Polynomial(Term * termArray, int capacity, int terms)
{
	if (termArray == NULL)
	{
		this->capacity = 1;
		this->termArray = new Term[capacity];
		this->terms = 0;
	}
	else
	{
		this->termArray = termArray;
		this->capacity = capacity;
		this->terms = terms;
	}
}

Polynomial::~Polynomial()
{
	delete[] termArray;
}

float Polynomial::Eval(const float f)
{
	float result = 0;
	for (int i = 0; i < terms; i++)
	{
		result += termArray[i].coef * pow(f, termArray[i].exp);
	}

	return result;
}

ostream & operator<<(ostream &os, Polynomial &poly)
{
	os << "f(x) = ";
	for (int i = 0; i < poly.terms; i++)
	{
		if (i != 0 && poly.termArray[i].getCoef() > 0)
		{
			os << "+";
		}
		if (poly.termArray[i].getCoef() != 1)
		{
			if (poly.termArray[i].getCoef() != -1)
			{
				os << poly.termArray[i].getCoef();
			}
			else
			{
				os << "-";
			}
		}
		if (poly.termArray[i].getExp() != 0)
		{
			os << "x^" << poly.termArray[i].getExp();
		}
	}

	return os;
}

/*
以下对应于英文书上 P94 9
*/
class Polynomial_P94_9
{
public:
	Polynomial_P94_9(Term *termArray = NULL, int capacity = 0);
	//~Polynomial_P94_9();
	Polynomial_P94_9 &Add(Polynomial_P94_9 poly);
	Polynomial_P94_9 &Mult(Polynomial_P94_9 poly);
	float Eval(const float f);
	static void newItem(const float theCoeff, const int theExp);
private:
	static Term *termArray;	//储存系数为非0项的数组
	static int capacity;		//数组的容量
	static int free;
	int start, finish;
	friend istream & operator >>(istream &is, Polynomial_P94_9 &poly);
	friend ostream & operator <<(ostream &os, Polynomial_P94_9 &poly);
};

int Polynomial_P94_9::capacity = 100;
Term *Polynomial_P94_9::termArray = new Term[100];
int Polynomial_P94_9::free = 0;

Polynomial_P94_9::Polynomial_P94_9(Term *array, int length)
{
	this->start = free;
	this->finish = this->start - 1;
	for (int i = 0; i < length; i++)
	{
		termArray[i + start].setCoef(array[i].getCoef());
		termArray[i + start].setExp(array[i].getExp());
		this->finish++;
	}

	free = this->finish + 1;
}

Polynomial_P94_9 & Polynomial_P94_9::Add(Polynomial_P94_9 poly)
{
	static Polynomial_P94_9 temp;
	int thisPos = start, polyPos = poly.start;
	while ((thisPos <= finish) && (polyPos <= poly.finish))
	{
		if (termArray[thisPos].getExp() == poly.termArray[polyPos].getExp())
		{
			float t = termArray[thisPos].getCoef() + poly.termArray[polyPos].getCoef();
			if (t)
			{
				newItem(t, termArray[thisPos].getExp());
				temp.finish++;
				thisPos++;
				polyPos++;
			}
		}
		else if (termArray[thisPos].getExp() < poly.termArray[polyPos].getExp())
		{
			newItem(poly.termArray[polyPos].getCoef(), poly.termArray[polyPos].getExp());
			temp.finish++;
			polyPos++;
		}
		else
		{
			newItem(termArray[thisPos].getCoef(), termArray[thisPos].getExp());
			temp.finish++;
			thisPos++;
		}
	}
	for (; thisPos <= finish; thisPos++)
	{
		newItem(termArray[thisPos].getCoef(), termArray[thisPos].getExp());
		temp.finish++;
	}
	for (; polyPos <= poly.finish; polyPos++)
	{
		newItem(poly.termArray[polyPos].getCoef(), poly.termArray[polyPos].getExp());
		temp.finish++;
	}

	return temp;
}

Polynomial_P94_9 & Polynomial_P94_9::Mult(Polynomial_P94_9 poly)
{
	static Polynomial_P94_9 temp;
	int thisPos = start, polyPos = poly.start;
	int thisLength = finish - start + 1;
	int polyLength = poly.finish - poly.start + 1;

	/*
	*用于暂存相乘获得的多项式，因为相乘会出现指数相同的情况
	*如果直接在二重循环中线性搜索、合并重复指数的系数，会把时间复杂度升为O(n^3)
	*相当于用空间换取时间
	*/
	Term *tempArray = new Term[thisLength*polyLength];

	for (int i = 0; i < thisLength; i++)
	{
		for (int j = 0; j < polyLength; j++)
		{
			tempArray[i*polyLength + j].setCoef(
				termArray[i + start].getCoef()*termArray[j + poly.start].getCoef());
			tempArray[i*polyLength + j].setExp(
				termArray[i + start].getExp() + termArray[j + poly.start].getExp());
		}
	}

	/*
	*冒泡排序，保证按照指数降序的顺序存入termArray
	*/
	Term tempTerm;
	for (int i = 0; i < thisLength*polyLength; i++)
	{
		for (int j = i + 1; j < thisLength*polyLength; j++)
		{
			if (tempArray[i].getExp() < tempArray[j].getExp())
			{
				tempTerm.setCoef(tempArray[i].getCoef());
				tempTerm.setExp(tempArray[i].getExp());

				tempArray[i].setCoef(tempArray[j].getCoef());
				tempArray[i].setExp(tempArray[j].getExp());

				tempArray[j].setCoef(tempTerm.getCoef());
				tempArray[j].setExp(tempTerm.getExp());
			}
		}
	}

	for (int i = 0; i < thisLength*polyLength; i++)
	{
		for (int j = i + 1; j < thisLength*polyLength; j++)
		{
			if ((tempArray[i].getExp() == tempArray[j].getExp()) && tempArray[j].getCoef() != 0)
			{
				tempArray[i].setCoef(tempArray[i].getCoef() + tempArray[j].getCoef());
				tempArray[j].setCoef(0);	//把系数置0，表示这一项已经合并到前面的与其指数相同的另一项
			}
		}
	}

	for (int i = 0; i < thisLength*polyLength; i++)
	{
		if (tempArray[i].getCoef() != 0)
		{
			newItem(tempArray[i].getCoef(), tempArray[i].getExp());
			temp.finish++;
		}
	}

	return temp;
}

void Polynomial_P94_9::newItem(const float theCoff, const int theExp)
{
	if (free == capacity)
	{
		capacity *= 2;
		Term *temp = new Term[capacity];
		for (int i = 0; i < free; i++)
		{
			temp[i].setCoef(termArray[i].getCoef());
			temp[i].setExp(termArray[i].getExp());
		}
		delete[]termArray;
		termArray = temp;
	}

	termArray[free].setCoef(theCoff);
	termArray[free].setExp(theExp);
	free++;
}

float Polynomial_P94_9::Eval(const float f)
{
	float result = 0;
	for (int i = start; i <= finish; i++)
	{
		result += termArray[i].getCoef() * pow(f, termArray[i].getExp());
	}

	return result;
}

istream & operator >>(istream &is, Polynomial_P94_9 &poly)
{
	cout << "请输入您想输入的多项式的项数：";
	int length;
	is >> length;
	int coff, exp;
	for (int i = 0; i < length; i++)
	{
		cout << "请输入第 " << i + 1 << " 项的系数：";
		is >> coff;
		cout << "请输入第 " << i + 1 << " 项的指数：";
		is >> exp;
		Polynomial_P94_9::newItem(coff, exp);
		poly.finish++;
	}

	return is;
}

ostream & operator <<(ostream &os, Polynomial_P94_9 &poly)
{
	os << "f(x) = ";
	for (int i = poly.start; i <= poly.finish; i++)
	{
		if (i != poly.start && poly.termArray[i].getCoef() > 0)
		{
			os << "+";
		}
		if (poly.termArray[i].getCoef() != 1)
		{
			if (poly.termArray[i].getCoef() != -1)
			{
				os << poly.termArray[i].getCoef();
			}
			else
			{
				os << "-";
			}
		}
		if (poly.termArray[i].getExp() != 0)
		{
			os << "x";
			if (poly.termArray[i].getExp() != 1)
			{
				os << "^" << poly.termArray[i].getExp();
			}
		}
	}

	return os;
}

void run_P93_P94()
{
	//P93 2
	Term *termArray = new Term[3];
	termArray[0].setCoef(2);
	termArray[0].setExp(3);
	termArray[1].setCoef(1);
	termArray[1].setExp(2);
	termArray[2].setCoef(4);
	termArray[2].setExp(0);

	//P93 6
	Polynomial poly(termArray, 3, 3);
	cout << poly << "	";
	cout << "f(1.1) = " << poly.Eval(1.1) << endl;

	//P94 9
	Polynomial_P94_9 poly_p94_9(termArray, 3);
	cout << poly_p94_9 << "	";
	cout << "f(1.1) = " << poly_p94_9.Eval(1.1) << endl;

	Polynomial_P94_9 poly_p94_9_2;
	cin >> poly_p94_9_2;
	cout << poly_p94_9.Add(poly_p94_9_2) << endl;
	cout << poly_p94_9.Mult(poly_p94_9_2) << endl;
}