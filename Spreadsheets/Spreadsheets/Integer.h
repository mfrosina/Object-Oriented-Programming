#pragma once
#include "Cell.h"

class Integer : public Cell
{
public:
	Integer();
	Integer(const double&, const unsigned&, const unsigned&);
	Integer(const Integer&);
	Integer& operator=(const Integer&);
	~Integer(){}
	
	void print() const override;
	void saveInFile(std::ofstream&) override;
	
	Cell* clone() const override;

};
