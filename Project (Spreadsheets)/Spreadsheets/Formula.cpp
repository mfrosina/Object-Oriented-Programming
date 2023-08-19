#include "Formula.h"

Formula::Formula() : Cell()
{
	this->type = CellType::FORMULA;
}
Formula::Formula(const double& convertedValue, const unsigned& row, const unsigned& col, const std::string& formula) : Cell(convertedValue,CellType::FORMULA, row, col)
{
	this->type = CellType::FORMULA;
	this->stringValue = formula;
}
Formula::Formula(const Formula& other) : Cell(other) {}
Formula& Formula::operator=(const Formula& other)
{
	if (this != &other)
	{
		Cell::operator=(other);
	}
	return *this;
}

void Formula::print() const
{
	std::cout << this->convertedValue;
}

void Formula::saveInFile(std::ofstream& out)
{
	out << "=" << this->stringValue;
}

Cell* Formula::clone() const
{
	return new (std::nothrow) Formula(*this);
}
