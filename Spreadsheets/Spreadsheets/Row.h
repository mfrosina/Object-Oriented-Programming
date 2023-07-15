#pragma once
#include "Cell.h"

class Row
{
private:
	std::vector<Cell*> cells;
	unsigned numberOfCells;

	void copy(const Row& other);
	void destroy();
public:
	Row();
	Row(const Row&);
	Row& operator=(const Row&);
	~Row();

	const Cell* operator[](const unsigned&) const;
	Cell*& operator[](const unsigned&);

	void addCell(Cell* cell);
	const unsigned getNumberOfCells() const;

	Row* clone() const;
};