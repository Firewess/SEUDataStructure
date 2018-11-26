#pragma once
/*
 *author: 奉捷 jiefeng
 *date: 2018/10/3 09:41
 *description: the second assignment of data structure
*/
#include <iostream>

using namespace std;

/*
以下对应于英文书上 P118 1
*/
class String
{
public:
	String(char *init, int m);
	~String();
	bool operator ==(String t);
	bool operator !();
	int Length();
	String Concat(String t);
	String Substr(int i, int j);
	int Find(String pat);

	friend ostream & operator <<(ostream & os, String & str);
	void Frequency();
	void FailureFunction();
	void PositionFunction();
	void newFailFunction();
private:
	char *str;
	int length;
	int *failure;
	int *firstFindPosition;	//用于储存每个字符第一次出现的位置
};

String::String(char *init, int m)
{
	str = init;
	length = m;
	failure = new int[length];
	firstFindPosition = new int[length];
}

String::~String()
{
	delete[] failure;
	delete[] firstFindPosition;
}

ostream & operator <<(ostream & os, String & str)
{
	for (int i = 0; i < str.length; i++)
		os << str.str[i];

	return os;
}

void String::PositionFunction()
{
	firstFindPosition[0] = 0;
	for (int i = 1; i < length; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (str[i] == str[j])
			{
				firstFindPosition[i] = j;
				break;
			}
		}
	}
}

void String::Frequency()
{
	PositionFunction();
	int *frequency = new int[length];
	for (int i = 0; i < length; i++)
		frequency[i] = 0;

	for (int i = 0; i < length; i++)
		frequency[firstFindPosition[i]]++;

	for (int i = 0; i < length; i++)
		if (frequency[i] > 0)
			cout << "字符" << str[i] << "出现的次数为：" << frequency[i] << endl;

	delete[] frequency;
}

/*
以下对应于英文书上 P119 7
*/
void String::FailureFunction()
{
	failure[0] = -1;
	for (int i = 1; i < length; i++)
	{
		int j = failure[i - 1];
		while ((str[i] != str[j + 1]) && j >= 0)
		{
			j = failure[j];
		}
		if (str[i] == str[j + 1])
		{
			failure[i] = j + 1;
		}
		else
		{
			failure[i] = -1;
		}
	}

	for (int i = 0; i < length; i++)
		cout << failure[i] << " ";
}

/*
以下对应于英文书上 P119 9
(1)
答：j		0  1  2  3  4  5  6  7  8  9
	pat		a  b  c  a  b  c  a  c  a  b
	f	   -1 -1 -1 -1 -1 -1  0 -1 -1  1

(2)
答：由故障函数新的定义可知，新增加的定义只不过是更为严格的限制了故障的情况，
	只是改变了一些字符的故障函数值，让其变为了-1，其余与原故障函数均一致，所以对
	于FastFind()函数而言，只是while循环中posP可能变为0的情况增多而已，对于整个
	函数的影响只有while循环的次数变化而已，所以算法的正确性不受影响，只是效
	率有了变化，因为采用原故障函数的FastFind()函数已被证明为正确的，故采用新的
	故障函数的FastFind()函数仍是正确的

(4)
答：存在模式使得比原来的FastFind()要慢，个人感觉不觉得存在模式使得采用新故障函数的FastFind()比原来快
	(i)、采用新故障函数更慢的实例：如程序运行结果可以看出，我run函数中的String a、b、c三个字符串，
		在新的故障函数下，只存在变为-1的值，不存在某些值比原故障函数得到的f值更大，这就意味着，在
		while循环中只存在增加循环次数的f值，不存在减少循环次数的f值，故总体while循环的次数只会增多，
		故采用新故障函数更慢
	(ii)、采用新故障函数更快的实例：暂未发现
*/
//(3)
void String::newFailFunction()
{
	failure[0] = -1;
	for (int i = 1; i < length; i++)
	{
		int j = failure[i - 1];
		while ((str[i] != str[j + 1] && j > 0) && str[j + 2] == str[i + 1])
			j = failure[j];

		if (str[i] == str[j + 1] && str[j + 2] != str[i + 1])
			failure[i] = j + 1;
		else
			failure[i] = -1;
	}

	for (int i = 0; i < length; i++)
		cout << failure[i] << " ";
}


void run_P118_P119()
{
	//P118 1
	char temp[] = "abcabcadade";
	String test(temp, sizeof(temp) / sizeof(char) - 1);
	cout << "字符串为：" << test << endl;
	test.Frequency();
	cout << endl;

	//P119 7
	char str[] = "aaaab";
	String a(str, sizeof(str) / sizeof(char) - 1);
	cout << "字符串为：" << str << endl;
	cout << "失败函数为：";
	a.FailureFunction();
	cout << endl;
	a.newFailFunction();
	cout << endl << endl;

	char str1[] = "ababaa";
	String b(str1, sizeof(str1) / sizeof(char) - 1);
	cout << "字符串为：" << str1 << endl;
	cout << "失败函数为：";
	b.FailureFunction();
	cout << endl;
	b.newFailFunction();
	cout << endl << endl;

	char str2[] = "abaabaabb";
	String c(str1, sizeof(str2) / sizeof(char) - 1);
	cout << "字符串为：" << str2 << endl;
	cout << "失败函数为：";
	c.FailureFunction();
	cout << endl;
	c.newFailFunction();
	cout << endl << endl;

	//P119 9
	char newstr[] = "abcabcacab";
	String newfail(newstr, sizeof(newstr) / sizeof(char) - 1);
	cout << "字符串为：" << newfail << endl;
	cout << "失败函数为：";
	newfail.newFailFunction();
	cout << endl << endl;
}