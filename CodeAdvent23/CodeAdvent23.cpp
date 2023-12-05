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
