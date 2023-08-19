#pragma once
#include "Spreadsheet.h"

class Interaction
{
private: 
	Spreadsheet* spreadsheet;
	bool active;
	std::string fileName;

	Cell* parseParameter(const unsigned&, const unsigned&,std::string);

	void open();
	void print();
	void edit();
	void save();
	void saveAs();
	void close();
	void exit();
	void help();

public:
	Interaction();
	~Interaction();

	bool isActive() const;
	
	void executeCommand();
};
