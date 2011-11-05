// TableProcessor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Table.h"
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <string>
#include <sstream>
#include <stdexcept>

using std::cin;
using std::cout;

// Error message function for TableProcessor
void error(const char* why, const char* what="")
{
	std::cerr << why << ' ' << what << endl;
	cout << "The program has terminated!" << endl;
	exit(1);
}

int main(int argc, char* argv[])
{
	// Expected 2 parameters inputFileName.txt outputFileName.txt
	if (argc != 3 ) error ("wrong number of arguments");

	cout << "Read table from file "  << argv[1]<< endl;
	std::ifstream inputFile(argv[1]);	//open input file stream
	if (!inputFile) error ("cannot open input file", argv[1]);

	Table table;
	inputFile >> table;
	cout << table << endl;

	try
	{
		table.processAllCells();
	}
	catch (std::out_of_range& oor)
	{
		error("Out of Range error: ", oor.what() );
	}

	cout << "Processed table" << endl << table << endl;
	cout << "Write table to file " << argv[2] << endl;

	std::ofstream outputFile(argv[2]);	//open output file stream
	if (!outputFile) error ("cannot open output file", argv[2]);
	outputFile << table;

	//int wait;
	//cin >> wait;
	return 0;
}

