#include "Cell.h"

void Cell::copy(const Cell& other)
{
	if (other.row < 1 || other.col < 1)
	{
		throw std::invalid_argument("Invalid row or column");
	}
	this->convertedValue = other.convertedValue;
	this->stringValue = other.stringValue;
	this->type = other.type;
	this->row = other.row;
	this->col = other.col;
}

void Cell::destroy()
{
	this->convertedValue = 0;
	this->stringValue = "";
	this->type = CellType::UNKNOWN;
	this->row = 1;
	this->col = 1;
}

Cell::Cell()
{
	this->convertedValue = 0;
	this->stringValue = " ";
	this->type = CellType::UNKNOWN;
	this->row = 1;
	this->col = 1;
}
Cell::Cell(const double& convertedValue, const CellType& type, const unsigned& row, const unsigned& col)
{
	if (row < 1 || col < 1)
	{
		throw "Invalid row or column";
	}
	if (type == CellType::INTEGER)
	{
		this->convertedValue = (int)convertedValue;
	}
	else {
		this->convertedValue = convertedValue;
	}
	this->type = type;
	this->row = row;
	this->col = col;
}
Cell::Cell(const Cell& other)
{
	copy(other);
}
Cell& Cell::operator=(const Cell& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

const double Cell::getConvertedValue() const
{
	return this->convertedValue;
}
const CellType Cell::getCellType() const
{
	return this->type;
}
const unsigned Cell::getRow() const
{
	return this->row;
}
const unsigned Cell::getCol() const
{
	return this->col;
}

void Cell::changeConvertedValue(const double& newValue)
{
	this->convertedValue = newValue;
}

void Cell::changeStringValue(const std::string& str)
{
	this->stringValue = str;
}

const std::string& Cell::getStringValue() const
{
	return this->stringValue;
}