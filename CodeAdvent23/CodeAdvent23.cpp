#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <regex>


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


string GetStringFromFile(const string fileName)
{ 	// Originally I did this in case there was any muls across multiple lines, no hate plz ;-;
	ifstream myFile;
	string inputLines;
	myFile.open(fileName);
	if (myFile.is_open()) { string line; while (getline(myFile, line)) { inputLines.append(line); } }
	myFile.close();
	return inputLines;
}
void GetIntsFromString(vector<int>& v, const string line, const char delimiter)
{ // aww ye I got to use a function from an earlier challenge
	int length = line.find(delimiter);
	v.push_back(stoi(line.substr(0, length)));
	if (length != -1) { return GetIntsFromString(v, line.substr(length + 1, line.size()), delimiter); }
}
bool CheckContentAcceptable(const string input, const char delimiter)
{ // This seems fine... I mean, unless there's any like mul(,00)
	for (int i = 0; i < input.size(); i++) { if (input[i] != delimiter && !isdigit(input[i])) return false; }
	return true;
}



void RunNextFunctionInString(string& line, const vector<string>& operations, bool& writing, int& runningTotal)
{ // OK we doing this - but next time we using regex's
	int start = -1;
	string nextOp;
	for (string op : operations)
	{
		int temp = line.find(op);
		if (temp < start || (start == -1 && temp != -1))
		{
			start = temp;
			nextOp = op;
		}
	}


	if (start == -1) return;

	line = line.substr(start + nextOp.size(), line.size());
	int end = line.find(")");
	if (end == -1) return;

	if (nextOp == "do(") 	writing = true;
	if (nextOp == "don't(") writing = false;

	if (nextOp == "mul(" && writing)
	{
		string content = line.substr(0, end);
		if (CheckContentAcceptable(content, ','))
		{
			vector<int> numbers;
			GetIntsFromString(numbers, content, ',');
			runningTotal += numbers[0] * numbers[1]; // what happens if mul(i,i,i)? Hope it doesn't happen...
		}
	}

	line = line.substr(end, line.size());

	
	return RunNextFunctionInString(line, operations, writing, runningTotal);
}
int main()
{
	string inputLines = GetStringFromFile("input.txt");
	vector<string> operations;
	int runningTotal = 0;

	vector <string> functions = { "mul(", "do(", "don't(" };
	bool writing = true;
	RunNextFunctionInString(inputLines, functions, writing, runningTotal);

	cout << runningTotal << endl;
}

