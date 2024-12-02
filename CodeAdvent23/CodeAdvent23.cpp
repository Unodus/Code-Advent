#include <fstream>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

void bubbleSort(vector<int>& v)
{
	int n = v.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (v[j] > v[j + 1])	swap(v[j], v[j + 1]);
		}
	}
}

int GetIntFromString(const string line, const int begin, const int end)
{
	string tempString = "";
	for (int iChar = begin; iChar < end; iChar++)
	{
		if (isdigit(line[iChar]))		{			tempString += line[iChar];		}
	}
	return stoi(tempString);
}

int main()
{
	ifstream myFile;
	vector<string> inputLines;
	myFile.open("input.txt");
	if (myFile.is_open())
	{
		string line;
		while (getline(myFile, line))		{ inputLines.push_back(line); }
	}
	myFile.close();

	vector<int> list1;
	vector<int> list2;

	string tempString;
	for (const string line : inputLines)
	{
		list1.push_back( GetIntFromString(line, 0, line.find_first_of(" ") ));
		list2.push_back( GetIntFromString(line, line.find_last_of(" "), line.size() ));
	}

	bubbleSort(list1);
	bubbleSort(list2);

	int totalDistance = 0;

	for (const int i : list1)
	{
		int count = 0;
		for (int j : list2)
		{
			if (i == j) count++;
		}
		totalDistance += i * count;
	}

	std::cout << totalDistance;

}

