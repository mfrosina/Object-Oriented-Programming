#include "Row.h"

void Row::copy(const Row& other)
{
	this->numberOfCells = other.numberOfCells;
	for (unsigned i = 0; i < numberOfCells; i++)
	{
		try
		{
			this->cells[i] = other.cells[i]->clone();
		}
		catch (...)
		{
			destroy();
		}
	}
}
void Row::destroy()
{
	for (unsigned i = 0; i < numberOfCells; i++)
	{
		delete this->cells[i];
	}
	this->cells.clear();
	this->numberOfCells = 0;
}

Row::Row()
{
	numberOfCells = 0;
}
Row::Row(const Row& other)
{
	copy(other);
}
Row& Row::operator=(const Row& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}
Row::~Row()
{
	destroy();
}

const Cell* Row::operator[](const unsigned& index) const
{
	if (index >= numberOfCells)
	{
		throw "Invalid index";
	}
	return this->cells[index];
}

Cell*& Row::operator[](const unsigned& index)
{
	if (index >= numberOfCells)
	{
		throw "Invalid index";
	}
	return this->cells[index];
}

void Row::addCell(Cell* cell)
{
	if (cell != nullptr)
	{
		this->cells.push_back(cell);
		this->numberOfCells++;
		return;
	}
	throw "Invalid Cell!";
}

const unsigned Row::getNumberOfCells() const
{
	return this->numberOfCells;
}

Row* Row::clone() const
{
	return new (std::nothrow) Row(*this);
}