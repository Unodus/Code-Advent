#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ifstream myFile;
	vector<string> inputLines;

	myFile.open("input.txt");
	if (myFile.is_open())
	{
		string line;
		while (getline(myFile, line))
		{
			inputLines.push_back(line);
		}
	}
	myFile.close();
	int runningTotal = 0;
	string numbers[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	for (string line : inputLines)
	{
		char startFlag = 0;
		char endFlag = 0;

		for (int iChar = 0; iChar < line.size(); iChar++)
		{
			if (isdigit(line[iChar]))
			{
				if (startFlag == 0) startFlag = line[iChar];
				endFlag = line[iChar];
			}
			else 
			{
				for (int iNum = 0 ; iNum < 10; iNum++)
				{
					int substrLength = numbers[iNum].size() < line.size() - iChar ? numbers[iNum].size() : line.size() - iChar;

					string substr = line.substr(iChar, substrLength);
					if (substr == numbers[iNum])
					{
						if (startFlag == 0) startFlag = to_string(iNum)[0];
						endFlag = to_string(iNum)[0];
					}
				}
			}
		}
		string compound = { startFlag, endFlag };
		int number = stoi(compound);
		runningTotal += number;
	}

	std::cout << runningTotal << endl;

}

