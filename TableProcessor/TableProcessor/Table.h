#pragma once

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::ostream;
using std::istream;
using std::endl;
using std::getline;
using std::cout;

class Table {
public:
	Table& processAllCells(void);

	friend ostream &operator<<(ostream &stream, Table table);
	friend istream &operator>>(istream &stream, Table &table);

private:
	// Constant values
	static const int CELL_WIDTH = 9;
	static const char SEPARATOR = '\t';
	static const string BAD_VALUE;

	vector<vector<string>> cells;
	
	int nRow;
	int nColumn;

	void processAssightmentCell( int i, int j );
	unsigned int getPositionFromLetter(char letter);
	unsigned int getPositionFromDigit(char digit);
};
