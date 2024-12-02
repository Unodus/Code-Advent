#include <fstream>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

void bubbleSort(vector<int>& v)
{ // sorts a vector of ints from small to large
	int n = v.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (v[j] > v[j + 1])	swap(v[j], v[j + 1]);
		}
	}
}


vector<string> GetStringsFromFile(const string fileName)
{ // Yes yes, I know this isn't an optimal use of strings... 
	ifstream myFile;
	vector<string> inputLines;
	myFile.open(fileName);
	if (myFile.is_open())
	{
		string line;
		while (getline(myFile, line)) { inputLines.push_back(line); }
	}
	myFile.close();

	return inputLines;
}


void GetIntsFromString(vector<int>& v, const string line, const char delimiter)
{ // recursively searches string for all numbers  - yes, I know this probably isn't optimal...
	int length = line.find(delimiter);
	v.push_back(stoi(line.substr(0, length)));
	if (length != -1) { return GetIntsFromString(v, line.substr(length + 1, line.size()), delimiter); }
}

bool NoProblemFinder(vector<int> numbers, int tolerance)
{ // Guess we doin' recursion now... (Is this neccesary? Probably not!)
	bool ascending = false; bool descending = false; bool unsafe = false;
	int unalignedTotal = 0;	int alignedTotal = 0;
	for (int i = 0; i < numbers.size() - 1; i++)
	{
		int difference = numbers[i] - numbers[i + 1];
		unalignedTotal += difference;
		alignedTotal += abs(difference);
		if (abs(difference) > 3 || difference == 0 || abs(unalignedTotal) != alignedTotal)	unsafe = true;
		if (unsafe)
		{
			if (tolerance > 0)
			{
				bool solutionFound;
				for (int j = 0; j < numbers.size(); j++)
				{
					vector<int> copy = numbers;
					copy.erase(copy.begin() + j);
					solutionFound = NoProblemFinder(copy, tolerance - 1);
					if (solutionFound) return true;
				}
			}
			return false;
		}
	}
	return true;
}

int main()
{
	vector<string> inputLines = GetStringsFromFile("input.txt");
	int safeThreads = 0;
	for (string line : inputLines)
	{
		vector<int> numbers;
		GetIntsFromString(numbers, line, ' ');
		if (NoProblemFinder(numbers, 2)) 			safeThreads++;
	}
	cout << safeThreads << endl;
}

