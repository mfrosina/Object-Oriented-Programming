#include "Fractional.h"


Fractional::Fractional() : Cell()
{
	this->type = CellType::FRACTIONAL;
}
Fractional::Fractional(const double& value, const unsigned& row, const unsigned& col) : Cell(value, CellType::FRACTIONAL, row, col)
{
	std::string converted = std::to_string(value);
	this->stringValue = converted;
}

Fractional::Fractional(const Fractional& other) : Cell(other){}

Fractional& Fractional::operator=(const Fractional& other)
{
	if (this != &other)
	{
		Cell::operator=(other);
	}
	return *this;
}

void Fractional::print() const
{
	std::cout << this->convertedValue;
}

void Fractional::saveInFile(std::ofstream& out)
{
	out << this->convertedValue;
}

Cell* Fractional::clone() const
{
	return new (std::nothrow) Fractional(*this);
}