#pragma once
/**************************************************
@Author: Jie Feng
@Time: 2018/10/31
@File: Experiment2.h
@Description: The second experiment of data structure of Mr. Jianhua Lv
**************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template<class T> class CircularList;

template<class T>
class ChainNode
{
	friend class CircularList<T>;
public:
	ChainNode(T element, ChainNode<T> *next = 0)
	{
		data = element;
		link = next;
	}

	T GetData()
	{
		return data;
	}

	ChainNode<T> * GetNext()
	{
		return link;
	}

private:
	T data;
	ChainNode<T> *link;
};

struct Term
{
	int coef;
	int exp;
	Term(int c = 0, int e = 0)
	{
		coef = c;
		exp = e;
	}
	Term Set(int c, int e)
	{
		coef = c;
		exp = e;
		return *this;
	}
};

template<class T>
class CircularList
{
public:
	CircularList()
	{
		first = new ChainNode<T>(T());
		first->link = first;
		last = first;
	}
	~CircularList()
	{
		while (last != first)
		{
			ChainNode<T> *temp = first;
			first = first->link;
			temp->link = av;
			av = temp;
		}
		first->link = last;
		last = first;
	}

	void Add(const T &e);
	ChainNode<T> * GetNode();
	void ResetNode(ChainNode<T> * x);
	ChainNode<T> * GetFirst()
	{
		return first;
	}
	ChainNode<T> * GetLast()
	{
		return last;
	}

private:
	ChainNode<T> *first;
	ChainNode<T> *last;
	ChainNode<T> *av;
};

template<class T>
void CircularList<T>::Add(const T &e)
{
	ChainNode<T> *temp = GetNode();
	*temp = e;
	last->link = temp;
	last = temp;
	last->link = first;
}

template<class T>
ChainNode<T> * CircularList<T>::GetNode()
{
	ChainNode<T> *x;
	if (!av)
	{
		x = new ChainNode<T>(T());
	}
	else
	{
		x = av;
		av = av->link;
	}
	return x;
}

template<class T>
void CircularList<T>::ResetNode(ChainNode<T> *x)
{
	x->link = av;
	av = x;
}

class Polynomial
{
public:
	Polynomial();
	~Polynomial();
	Polynomial(const Polynomial & poly);

	friend istream & operator >>(istream & is, Polynomial & poly);
	friend ostream & operator <<(ostream & os, Polynomial & poly);
	const Polynomial & operator =(const Polynomial &poly);
	Polynomial operator +(const Polynomial &poly) const;
	Polynomial operator -(const Polynomial &poly) const;
	Polynomial operator *(const Polynomial &poly) const;
	float Evaluate(float x) const;

private:
	CircularList<Term> *poly;
};

Polynomial::Polynomial()
{
	poly = new CircularList<Term>();
}

Polynomial::~Polynomial()
{
	poly->~CircularList();
}

Polynomial::Polynomial(const Polynomial & poly)
{
	this->poly = new CircularList<Term>();
	ChainNode<Term> *temp = poly.poly->GetFirst()->GetNext();
	while (temp != poly.poly->GetFirst())
	{
		this->poly->Add(temp->GetData());
		temp = temp->GetNext();
	}
}

istream & operator >>(istream & is, Polynomial & poly)
{
	cout << "请按照n(多项式项数) c1 e1 c2 e2 ...的格式输入：";
	vector<int> inputs;
	int n = 0, k = 0;
	int num;
	cin >> num;
	inputs.push_back(num);
	while (cin.get() != '\n') {
		cin >> num;
		inputs.push_back(num);
	}
	for (int i = 0; i < inputs.at(0); i++)
	{
		poly.poly->Add(Term(inputs.at(i * 2 + 1), inputs.at(i * 2 + 2)));
	}

	return is;
}

ostream & operator <<(ostream & os, Polynomial &poly)
{
	os << "多项式为：";
	ChainNode<Term> *temp = poly.poly->GetFirst()->GetNext();
	while (temp != poly.poly->GetFirst())
	{
		os << temp->GetData().coef;
		if (temp->GetData().exp != 0)
		{
			os << "*x^" << temp->GetData().exp;
		}
		if (temp->GetNext()->GetData().coef > 0 && temp->GetNext() != poly.poly->GetFirst())
		{
			os << "+";
		}
		temp = temp->GetNext();
	}

	return os;
}

const Polynomial & Polynomial::operator =(const Polynomial &poly)
{
	this->poly->~CircularList();
	ChainNode<Term> *temp = poly.poly->GetFirst()->GetNext();
	while (temp != poly.poly->GetFirst())
	{
		this->poly->Add(temp->GetData());
		temp = temp->GetNext();
	}
	return *this;
}

Polynomial Polynomial::operator +(const Polynomial &b) const
{
	Polynomial result;
	ChainNode<Term> *thisIterator = poly->GetFirst()->GetNext();
	ChainNode<Term> *bIterator = b.poly->GetFirst()->GetNext();
	while (thisIterator != poly->GetFirst() && bIterator != b.poly->GetFirst())
	{
		if (thisIterator->GetData().exp > bIterator->GetData().exp)
		{
			result.poly->Add(thisIterator->GetData());
			thisIterator = thisIterator->GetNext();
		}
		else if (thisIterator->GetData().exp == bIterator->GetData().exp)
		{
			result.poly->Add(Term(thisIterator->GetData().coef + bIterator->GetData().coef,
				thisIterator->GetData().exp));
			thisIterator = thisIterator->GetNext();
			bIterator = bIterator->GetNext();
		}
		else
		{
			result.poly->Add(bIterator->GetData());
			bIterator = bIterator->GetNext();
		}
	}
	if (thisIterator != poly->GetFirst())
	{
		while (thisIterator != poly->GetFirst())
		{
			result.poly->Add(thisIterator->GetData());
			thisIterator = thisIterator->GetNext();
		}
	}
	if (bIterator != b.poly->GetFirst())
	{
		while (bIterator != b.poly->GetFirst())
		{
			result.poly->Add(bIterator->GetData());
			bIterator = bIterator->GetNext();
		}
	}
	return result;
}

Polynomial Polynomial::operator -(const Polynomial &b) const
{
	Polynomial result;
	ChainNode<Term> *thisIterator = poly->GetFirst()->GetNext();
	ChainNode<Term> *bIterator = b.poly->GetFirst()->GetNext();
	while (thisIterator != poly->GetFirst() && bIterator != b.poly->GetFirst())
	{
		if (thisIterator->GetData().exp > bIterator->GetData().exp)
		{
			result.poly->Add(thisIterator->GetData());
			thisIterator = thisIterator->GetNext();
		}
		else if (thisIterator->GetData().exp == bIterator->GetData().exp)
		{
			result.poly->Add(Term(thisIterator->GetData().coef - bIterator->GetData().coef,
				thisIterator->GetData().exp));
			thisIterator = thisIterator->GetNext();
			bIterator = bIterator->GetNext();
		}
		else
		{
			result.poly->Add(Term(-bIterator->GetData().coef, bIterator->GetData().exp));
			bIterator = bIterator->GetNext();
		}
	}
	if (thisIterator != poly->GetFirst())
	{
		while (thisIterator != poly->GetFirst())
		{
			result.poly->Add(thisIterator->GetData());
			thisIterator = thisIterator->GetNext();
		}
	}
	if (bIterator != b.poly->GetFirst())
	{
		while (bIterator != b.poly->GetFirst())
		{
			result.poly->Add(Term(-bIterator->GetData().coef, bIterator->GetData().exp));
			bIterator = bIterator->GetNext();
		}
	}
	return result;
}

bool Descending(Term &a, Term &b)	//用于STL函数sort的比较函数，此处为按指数大小降序排列
{
	return a.exp > b.exp;
}

Polynomial Polynomial::operator *(const Polynomial &b) const
{
	vector<Term> polyterms;
	Polynomial result;
	ChainNode<Term> *thisIterator = poly->GetFirst()->GetNext();
	ChainNode<Term> *bIterator = b.poly->GetFirst()->GetNext();
	//把各项分别相乘，时间复杂度为O(m*n)，m和n分别为两个多项式的项数
	while (thisIterator != poly->GetFirst())
	{
		while (bIterator != b.poly->GetFirst())
		{
			polyterms.push_back(Term(thisIterator->GetData().coef * bIterator->GetData().coef,
				thisIterator->GetData().exp + bIterator->GetData().exp));
			bIterator = bIterator->GetNext();
		}
		bIterator = b.poly->GetFirst()->GetNext();	//把bIterator归零
		thisIterator = thisIterator->GetNext();
	}

	//STL排序函数，把多项式按指数大小降序排序
	sort(polyterms.begin(), polyterms.end(), Descending);

	//以下循环用于合并相乘后相同系数的项，时间复杂度为O(m*n)，m和n分别为两个多项式的项数
	for (int i = 0; i < polyterms.size();)
	{
		if (i != polyterms.size() - 1 && polyterms.at(i).exp == polyterms.at(i + 1).exp)
		{
			polyterms.at(i + 1).coef += polyterms.at(i).coef;
			polyterms.erase(polyterms.begin() + i);
		}
		else
		{
			i++;
		}
	}

	for (int i = 0; i < polyterms.size(); i++)
		result.poly->Add(polyterms.at(i));

	return result;
}

float Polynomial::Evaluate(float x) const
{
	float result = 0;
	ChainNode<Term> *temp = poly->GetFirst()->GetNext();
	while (temp != poly->GetFirst())
	{
		result += temp->GetData().coef*pow(x, temp->GetData().exp);
		temp = temp->GetNext();
	}
	return result;
}

void run_Exp2()
{
	Polynomial mypoly;
	cin >> mypoly;
	cout << mypoly << endl;

	Polynomial copyPoly(mypoly);
	cout << "通过拷贝构造函数构造的多项式：\n" << copyPoly << endl << endl;

	Polynomial testPoly;
	cin >> testPoly;
	copyPoly = testPoly;
	cout << "通过赋值运算后的新的多项式：\n" << copyPoly << endl;

	cout << "请输入您要计算的值：";
	int x;
	cin >> x;
	cout << mypoly << ": f(" << x << ") = " << mypoly.Evaluate(x) << endl;
	Polynomial temp = mypoly + copyPoly;
	cout << "两个多项式相加：" << temp << endl;
	temp = mypoly - copyPoly;
	cout << "两个多项式相减：" << temp << endl;
	temp = mypoly * copyPoly;
	cout << "两个多项式相乘：" << temp << endl;
}