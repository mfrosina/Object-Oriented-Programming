#pragma once
#include "Cell.h"

class Fractional : public Cell
{
public:
	Fractional();
	Fractional(const double&, const unsigned&, const unsigned&);
	Fractional(const Fractional&);
	Fractional& operator=(const Fractional&);
	~Fractional(){}

	void print() const override;
	void saveInFile(std::ofstream&) override;

	Cell* clone() const override;

};