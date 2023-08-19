#pragma once
#include "Cell.h"

class String : public Cell
{
public:
	String();
	String(const double&, const unsigned&, const unsigned&, const std::string&);
	String(const String&);
	String& operator=(const String&);
	~String(){}

	void print() const override;
	void saveInFile(std::ofstream&) override;

	Cell* clone() const override;
};
