#pragma once
/*
 *author: ��� jiefeng
 *date: 2018/10/3 09:41
 *description: the second assignment of data structure
*/
#include <iostream>

using namespace std;

/*
���¶�Ӧ��Ӣ������ P118 1
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
	int *firstFindPosition;	//���ڴ���ÿ���ַ���һ�γ��ֵ�λ��
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
			cout << "�ַ�" << str[i] << "���ֵĴ���Ϊ��" << frequency[i] << endl;

	delete[] frequency;
}

/*
���¶�Ӧ��Ӣ������ P119 7
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
���¶�Ӧ��Ӣ������ P119 9
(1)
��j		0  1  2  3  4  5  6  7  8  9
	pat		a  b  c  a  b  c  a  c  a  b
	f	   -1 -1 -1 -1 -1 -1  0 -1 -1  1

(2)
���ɹ��Ϻ����µĶ����֪�������ӵĶ���ֻ�����Ǹ�Ϊ�ϸ�������˹��ϵ������
	ֻ�Ǹı���һЩ�ַ��Ĺ��Ϻ���ֵ�������Ϊ��-1��������ԭ���Ϻ�����һ�£����Զ�
	��FastFind()�������ԣ�ֻ��whileѭ����posP���ܱ�Ϊ0�����������ѣ���������
	������Ӱ��ֻ��whileѭ���Ĵ����仯���ѣ������㷨����ȷ�Բ���Ӱ�죬ֻ��Ч
	�����˱仯����Ϊ����ԭ���Ϻ�����FastFind()�����ѱ�֤��Ϊ��ȷ�ģ��ʲ����µ�
	���Ϻ�����FastFind()����������ȷ��

(4)
�𣺴���ģʽʹ�ñ�ԭ����FastFind()Ҫ�������˸о������ô���ģʽʹ�ò����¹��Ϻ�����FastFind()��ԭ����
	(i)�������¹��Ϻ���������ʵ������������н�����Կ�������run�����е�String a��b��c�����ַ�����
		���µĹ��Ϻ����£�ֻ���ڱ�Ϊ-1��ֵ��������ĳЩֵ��ԭ���Ϻ����õ���fֵ���������ζ�ţ���
		whileѭ����ֻ��������ѭ��������fֵ�������ڼ���ѭ��������fֵ��������whileѭ���Ĵ���ֻ�����࣬
		�ʲ����¹��Ϻ�������
	(ii)�������¹��Ϻ��������ʵ������δ����
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
	cout << "�ַ���Ϊ��" << test << endl;
	test.Frequency();
	cout << endl;

	//P119 7
	char str[] = "aaaab";
	String a(str, sizeof(str) / sizeof(char) - 1);
	cout << "�ַ���Ϊ��" << str << endl;
	cout << "ʧ�ܺ���Ϊ��";
	a.FailureFunction();
	cout << endl;
	a.newFailFunction();
	cout << endl << endl;

	char str1[] = "ababaa";
	String b(str1, sizeof(str1) / sizeof(char) - 1);
	cout << "�ַ���Ϊ��" << str1 << endl;
	cout << "ʧ�ܺ���Ϊ��";
	b.FailureFunction();
	cout << endl;
	b.newFailFunction();
	cout << endl << endl;

	char str2[] = "abaabaabb";
	String c(str1, sizeof(str2) / sizeof(char) - 1);
	cout << "�ַ���Ϊ��" << str2 << endl;
	cout << "ʧ�ܺ���Ϊ��";
	c.FailureFunction();
	cout << endl;
	c.newFailFunction();
	cout << endl << endl;

	//P119 9
	char newstr[] = "abcabcacab";
	String newfail(newstr, sizeof(newstr) / sizeof(char) - 1);
	cout << "�ַ���Ϊ��" << newfail << endl;
	cout << "ʧ�ܺ���Ϊ��";
	newfail.newFailFunction();
	cout << endl << endl;
}