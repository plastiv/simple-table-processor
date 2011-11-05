#include "StdAfx.h"
#include "Table.h"

const string Table::BAD_VALUE = "#BV#";

Table& Table::processAllCells( void )
{
	for (int i=0; i != cells.size(); i++){
		for (int j=0; j != cells[i].size(); j++){
			switch(cells[i][j][0]){
			case '\'':
				// Left cell with the same string without symbol \'
				cells[i][j].erase(0,1);
				break;
			case '=':
				// Assign cell with another value by address =LetterColumn RowNumber
				processAssightmentCell(i, j);
				break;
			default:
				if (!isdigit(cells[i][j][0]))
				{
					cells[i][j] = BAD_VALUE;
				} 
				break;
			}
		}
	}
	return *this;
}

void Table::processAssightmentCell( int i, int j ) 
{
	if (cells[i][j].size()==3)
	{
		int rowIndex = getPositionFromDigit(cells[i][j][2]);
		int colIndex = getPositionFromLetter(cells[i][j][1]);
		cells[i][j] = cells[rowIndex][colIndex];
	} 
	else
	{
		cells[i][j] = BAD_VALUE;
	}
}

unsigned int Table::getPositionFromLetter(char letter)
{
	return letter - 'A';
}

unsigned int Table::getPositionFromDigit( char digit )
{
	return digit - '0' - 1;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	return split(s, delim, elems);
}


ostream &operator<<(ostream &stream, Table table)
{
	for (int i=0; i != table.cells.size(); i++) {
		for (int j=0; j != table.cells[i].size(); j++) {
			stream.width(Table::CELL_WIDTH);
			stream << table.cells[i][j];
		}
		stream << endl;
	}

	return stream;
}

istream &operator>>(istream &stream, Table &table)
{
	// interpreter first line as number of row and column
	stream >> table.nRow >> table.nColumn;

	// read table from stream
	string tmp_row;
	while (getline(stream, tmp_row))
		if (!tmp_row.empty())
		{
			table.cells.push_back(split(tmp_row, Table::SEPARATOR));
		}

	// TODO : provide good exception here
	if(table.nRow!=table.cells.size() || table.nColumn!=table.cells.at(0).size() )
		std::cout << "Error t.rowCount!=t.table.size() || t.colCount!=t.table[0].size() " << endl;

	return stream;
}




