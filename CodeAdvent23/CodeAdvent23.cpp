#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool IsKeyInString(string input, string key, int letterID);
vector<string> GetFileLines(string fileName);

struct StringCoord {
	int x = 0;
	int y = 0;
	string Content = "";
	StringCoord(int newX, int newY) { x = newX; y = newY; };
};

int main() {
	int runningTotal = 0;
	vector<string> inputLines = GetFileLines("input.txt");
	vector<StringCoord*> allCoords;
	vector<StringCoord*> allGears;

	for (int y = 0; y < inputLines.size(); y++) {
		for (int x = 0; x < inputLines[y].size(); x++) {

			bool creatingCoord = false;
			StringCoord* coordContent = new StringCoord(x, y);

			if (inputLines[y][x] == '*')
			{
				coordContent->Content.append({ "*" });
				allGears.push_back(coordContent);
				continue;
			}


			do {
				char currentChar = inputLines[y][x];
				creatingCoord = isdigit(currentChar);
				if (creatingCoord)
				{
					coordContent->Content.append({ currentChar });
					x++; // skip to next digit, see if its also a number to add on the string
				}
			} while (creatingCoord && x < inputLines[y].size()); // an actual use case for Do While? Wow .o.

		
			if (coordContent->Content.size() > 0) allCoords.push_back(coordContent);



		}

	}

	for (StringCoord* sCoord : allCoords) {
		// check all neighbours for symbols. If there is a symbol, add it!
		bool foundSymbol = false;

		int coordSize = sCoord->Content.size();

		for (int y = -1; y <= 1; y++) {
			for (int x = -1; x <= coordSize; x++) {
				int searchY = y + sCoord->y;
				int searchX = x + sCoord->x;
				if (searchY < 0 || searchX < 0 || searchY >= inputLines.size() || searchX >= inputLines[searchY].size()) continue; // don't check out of bounds
				if (y == 0 && searchX >= sCoord->x && (searchX < sCoord->x + coordSize)) { continue; } // don't check "inner layer
				
				
				if (inputLines[searchY][searchX] == '*')
				{
					// this is a gear! Find it in the list, and put the number in it.

					for (StringCoord* gear : allGears)
					{
						if (gear->x == searchX && gear->y == searchY)
						{
							if (gear->Content == "*") gear->Content = sCoord->Content;
							else gear->Content = to_string( stoi(sCoord->Content) * stoi(gear->Content) );		
							break;
						}
					}

				}
			}
		}


	}

	for (StringCoord* gear : allGears)
	{
		cout << gear->x << "-" << gear->y << ": " << gear->Content << endl;
		runningTotal += stoi(gear->Content);
	}

	cout << runningTotal << endl;
	for (StringCoord* coord : allCoords) { delete coord; }
	for (StringCoord* gear : allGears) { delete gear; }

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
