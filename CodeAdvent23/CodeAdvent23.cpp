#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool IsKeyInString(string input, string key, int letterID);
vector<string> GetFileLines(string fileName);

int main()
{
	int runningTotal = 0;
	string keys[] = { "red",  "green" , "blue" };
	int keyLength = keys->size();
	vector<string> inputLines = GetFileLines("input.txt");
	//int keyMaxTotals[] = { 12, 13, 14 };

	int GameID = 0;
	for (string line : inputLines)
	{
		GameID++;
		int keyHighest[] = { 0,0,0 };
		int letterID = 0;
		for (char letter : line)
		{
			for (int iKey = 0; iKey < keyLength; iKey++)
			{
				if (!IsKeyInString(line, keys[iKey], letterID)) continue;
				string sDigit = line.substr(letterID - 3, 2);
				int digit = stoi(sDigit);
				/*if (digit > keyMaxTotals[iKey])
				{
					std::cout << GameID << " was a failure: " << keys[iKey] << endl;
					goto skip;
				}*/
				if (digit > keyHighest[iKey]) keyHighest[iKey] = digit;
			}
			letterID++;
		}
		runningTotal += (keyHighest[0] * keyHighest[1] * keyHighest[2]);
		//	skip: runningTotal = runningTotal;
	}
	std::cout << runningTotal << endl;
}

bool IsKeyInString(string input, string key, int letterID)
{
	int remainingSpace = input.size() - letterID;
	int keyLength = key.size();
	int substrLength = keyLength < remainingSpace ? keyLength : remainingSpace;
	string substr = input.substr(letterID, substrLength);
	if (substr == key) return true;
	else return false;
}

vector<string> GetFileLines(string fileName)
{
	ifstream myFile;
	vector<string> inputLines;

	myFile.open(fileName);
	if (myFile.is_open())
	{
		string line;
		while (getline(myFile, line))
		{
			inputLines.push_back(line);
		}
	}
	myFile.close();
	return inputLines;
}
