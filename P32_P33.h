/*
 *author: 奉捷 jiefeng
 *date: 2018/9/24 21:31
 *description: the first week's assignment of data structure
 *functions:
	1、BoolCombiantion
		*description: Print all combinations of values for a boolean array of length N
		*paramater: @string array[], the boolean array
					@int curr, current index of array
					@int length, the length of boolean array

	2、ComputePowerset
		*description: Calculate all the subsets of a specific set
		*paramater: @char array[], the specific set
					@int curr, current index of array
					@int length, the length of this specific set
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//以下对应于英文书上P32 2
int count;
void BoolCombination(string array[], int curr, int length)
{
	int i;
	if (curr == length)
	{
		for (i = 0; i < length; i++)
		{
			cout << array[i] << " ";
		}
		cout << "\n";
		::count++;
	}
	else
	{
		array[curr] = string("true ");
		BoolCombination(array, curr + 1, length);
		array[curr] = string("false");
		BoolCombination(array, curr + 1, length);
	}
}

//以下对应于英文书 P33 14
struct subset
{
	vector<char> set;
};

vector<subset> ComputePowerset(char array[], int curr, int length)
{
	vector<subset> powerset;
	if (curr == length)
	{
		subset temp;
		temp.set.push_back('\0');
		powerset.push_back(temp);
	}
	else
	{
		vector<subset> halfSubset = ComputePowerset(array, curr + 1, length);

		//{a, b}的子集 = {b}的子集 + ( {b}的子集中每个元素添加a，以此类推 )

		vector<subset> temp;
		//添加array[curr + 1]与其之后元素的子集
		for (int i = 0; i < halfSubset.size(); i++)
		{
			temp.push_back(halfSubset.at(i));
		}

		//在array[curr + 1]与其之后元素的子集的每个集合中添加元素array[curr]
		char currChar = array[curr];
		halfSubset.at(0).set.erase(halfSubset.at(0).set.begin());
		for (int i = 0; i < halfSubset.size(); i++)
		{
			temp.push_back(halfSubset.at(i));
		}
		for (int i = halfSubset.size(); i < temp.size(); i++)
		{
			temp.at(i).set.push_back(currChar);
		}

		//形成最终的array[curr]与其之后元素的子集
		for (int i = 0; i < temp.size(); i++)
		{
			powerset.push_back(temp.at(i));
		}
	}
	return powerset;
}

void PrintPowerset(vector<subset> powerset)
{
	for (int i = 0; i < powerset.size(); i++)
	{
		cout << "(";
		for (int j = 0; j < powerset.at(i).set.size(); j++)
		{
			cout << powerset.at(i).set.at(j);
			if (j != powerset.at(i).set.size() - 1)
			{
				cout << ",";
			}
		}
		cout << ")\n";
	}
}

void run_P32_P33()
{
	//P32 2
	string array[4];
	BoolCombination(array, 0, sizeof(array)/sizeof(string));
	cout << "所有的排列情况有：" << ::count << "种\n";

	//P33 14
	char temp[] = { 'a', 'b', 'c', 'd'};

	PrintPowerset(ComputePowerset(temp, 0, sizeof(temp) / sizeof(char)));

}