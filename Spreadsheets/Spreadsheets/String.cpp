#include "String.h"

String::String() : Cell()
{
	this->type = CellType::STRING;
}
String::String(const double& convertedValue, const unsigned& row, const unsigned& col,const std::string& value) : Cell(convertedValue,CellType::STRING, row, col)
{
	this->stringValue = value;
}
String::String(const String& other) : Cell(other) {}
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		Cell::operator=(other);
	}
	return *this;
}

void String::print() const
{
	std::cout << this->stringValue;
}

void String::saveInFile(std::ofstream& out)
{
	if (this->stringValue != " " && this->stringValue[0] != '\"')
	{
		out << "\"" << this->stringValue << "\"";
	}
	else if (this->stringValue[0] == '\"')
	{
		out << "\"" << "\\" << this->stringValue <<  "\\" << "\"";
	}
}

Cell* String::clone() const
{
	return new (std::nothrow) String(*this);
}