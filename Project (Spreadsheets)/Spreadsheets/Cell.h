#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Helpers.h"

enum CellType
{
	UNKNOWN = -1,
	INTEGER,
	FRACTIONAL,
	STRING,
	FORMULA
};

class Cell
{
protected:
	double convertedValue;
	std::string stringValue;
	CellType type;
	unsigned row;
	unsigned col;

	void copy(const Cell&);
	void destroy();

public:
	Cell();
	Cell(const double&, const CellType&, const unsigned&, const unsigned&);
	Cell(const Cell&);
	Cell& operator=(const Cell&);
	virtual ~Cell(){}

	const double getConvertedValue() const;
	const CellType getCellType() const;
	const unsigned getRow() const;
	const unsigned getCol() const;

	void changeConvertedValue(const double&);
	virtual void changeStringValue(const std::string&);
	virtual const  std::string& getStringValue() const;

	virtual void print() const = 0;
	virtual void saveInFile(std::ofstream&) = 0;

	virtual Cell* clone() const = 0;
};