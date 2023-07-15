#pragma once
#include "Cell.h"

class Formula : public Cell
{
public:
	Formula();
	Formula(const double&,const unsigned&, const unsigned&, const std::string&);
	Formula(const Formula&);
	Formula& operator=(const Formula&);
	~Formula(){}

	void print() const override;
	void saveInFile(std::ofstream&) override;

	Cell* clone() const override;

};
