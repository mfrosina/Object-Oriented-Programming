#pragma once
#include <iomanip>
#include "Row.h"
#include "String.h"
#include "Formula.h"
#include "Fractional.h"
#include "Integer.h"

class Spreadsheet
{
private:
	std::vector<Row*> rows;
	unsigned numberOfRows;
	unsigned numberOfColumns;
	std::string fileName;

	const unsigned MIN_WIDTH = 20;

	void copy(const Spreadsheet&);
	void destroy();

	std::string parseNumberString(std::ifstream&, const unsigned&);
	String* parseString(std::ifstream&, const unsigned&);
	Formula* parseFormula(std::ifstream&, const unsigned&);

	Cell* parseCell(std::ifstream&, unsigned&, unsigned&);
	Row* parseRow(std::ifstream&, unsigned&, unsigned&);
	Spreadsheet& parseSpreadsheet(std::ifstream&);
	
	void evaluateFormula(const unsigned&, const unsigned&);
	void evaluateFormulas();
	double findCellValue(const unsigned&, const unsigned&) const;

public:
	Spreadsheet(const std::string&);
	Spreadsheet(const Spreadsheet&);
	Spreadsheet& operator=(const Spreadsheet&);
	~Spreadsheet();

	Spreadsheet* parse();

	bool openFile(const std::string&);
	const void printSpreadsheet() const;
	bool editCell(const unsigned&, const unsigned&, Cell*);
	bool saveToFile(const std::string&);
};