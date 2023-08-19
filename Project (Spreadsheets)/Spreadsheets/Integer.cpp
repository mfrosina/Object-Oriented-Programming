#include "Integer.h"

Integer::Integer() : Cell()
{
	this->type = CellType::INTEGER;
}
Integer::Integer(const double& value, const unsigned& row, const unsigned& col) : Cell(value, CellType::INTEGER, row, col)
{
	std::string converted = std::to_string(value);
	this->stringValue = converted;
}
Integer::Integer(const Integer& other) : Cell(other) {}

Integer& Integer::operator=(const Integer& other)
{
	if (this != &other)
	{
		Cell::operator=(other);
	}
	return *this;
}

void Integer::print() const
{
	std::cout << this->convertedValue;
}

void Integer::saveInFile(std::ofstream& out)
{
	out << this->convertedValue;
}

Cell* Integer::clone() const
{
	return new (std::nothrow) Integer(*this);
}