#include "String.h"
#include "Formula.h"
#include "Integer.h"
#include "Fractional.h"
#include "Spreadsheet.h"
#include "Helpers.h"

void Spreadsheet::copy(const Spreadsheet& other)
{
	try
	{
		for (unsigned i = 0; i < other.numberOfRows; i++)
		{
			this->rows[i] = other.rows[i];
		}
		this->numberOfRows = other.numberOfRows;
		this->numberOfColumns = other.numberOfColumns;
		this->fileName = other.fileName;
	}
	catch (...)
	{
		this->destroy();
	}
}

void Spreadsheet::destroy()
{
	for (unsigned i = 0; i < rows.size(); i++)
	{
		delete this->rows[i];
	}
	this->rows.clear();
	this->numberOfRows = this->numberOfColumns = 0;
	this->fileName = "";
}

//bool Spreadsheet::openFile(const std::string& fileName)
//{
//	std::ifstream in(fileName);
//	if (!in.is_open())
//	{
//		return false;
//	}
//	try
//	{
//		*this = parseSpreadsheet(in);
//	}
//	catch (...)
//	{
//		std::cout << "Can not parse the spreadsheet... Please, try again!\n";
//		in.close();
//		return false;
//	}
//	in.close();
//
//	return true;
//}

std::string Spreadsheet::parseNumberString(std::ifstream& in, const unsigned& cellNumber)
{
	std::string cellValue;
	char curr = in.get();
	cellValue += curr;

	while (in.peek() != EOF && in.peek() != ',' && in.peek() != '\n')
	{
		curr = in.peek();
		if (!Helpers::isDigit(in.peek()) && in.peek() != '.')
		{
			std::cout << "Invalid format! Unknown type of data on row " << numberOfRows + 1 << " before the symbol " << curr << "." << std::endl;
			throw std::invalid_argument("Invalid data");
		}
		curr = in.get();
		cellValue += curr;
		if (Helpers::isWhitespace(in.peek()))
		{
			Helpers::removeWhitespace(in);
			if (in.peek() != ',')
			{
				std::cout << "Invalid format! Missing comma on row " << numberOfRows + 1 << " before the symbol " << curr << "." << std::endl;
				throw  std::invalid_argument("Invalid format");
			}
			in.get();
		}
	}
	if (in.peek() != '\n')
	{
		in.get();
	}
	return cellValue;
}
String* Spreadsheet::parseString(std::ifstream& in, const unsigned& cellNumber)
{
	std::string cellValue;
	char curr;
	in.get();
	while (in.peek() != '"')
	{
		if (in.peek() == '\\')
		{
			curr = in.get();
			if (in.peek() == '"')
			{
				while (in.peek() != '\\')
				{
					curr = in.get();
					cellValue += curr;
				}
				in.get();
				if (in.peek() == '\"')
				{
					curr = in.get();
					cellValue += curr;
					if (in.peek() != '\"')
					{
						std::cout << "Invalid format! Missing \" on row " << numberOfRows + 1 << " before the symbol " << curr << "." << std::endl;
						throw  std::invalid_argument("Invalid format");
					}
					in.get();
					break;
				}
				else
				{
					std::cout << "Invalid format! Missing \" on row " << numberOfRows + 1 << " before the symbol " << curr << "." << std::endl;
					throw  std::invalid_argument("Invalid format");
				}
			}
			else
			{
				curr = in.get();
				cellValue += curr;
			}
		}
		curr = in.get();
		cellValue += curr;
	}
	if (in.peek() != '\n')
	{
		in.get();
	}
	Helpers::removeWhitespace(in);
	if (in.peek() != ',' && in.peek() != '\n')
	{
		std::cout << "Invalid format! Missing comma on row " << numberOfRows + 1 << " before the symbol " << curr << "." << std::endl;
		throw  std::invalid_argument("Invalid format");
	}
	if (in.peek() != '\n')
	{
		in.get();
	}
	if (Helpers::hasOnlyDigits(cellValue))
	{
		unsigned occurences = std::count(cellValue.begin(), cellValue.end(), '.');
		if (occurences <= 1)
		{
			double number = std::stod(cellValue);
			return new String(number, numberOfRows + 1, cellNumber + 1, cellValue);
		}
	}
	return new (std::nothrow) String(0, numberOfRows + 1, cellNumber + 1, cellValue);
}
Formula* Spreadsheet::parseFormula(std::ifstream& in, const unsigned& cellNumber)
{
	std::string cellValue;
	char curr;
	in.get();
	while (in.peek() != EOF && in.peek() != ',' && in.peek() != '\n')
	{
		if (!Helpers::isWhitespace(in.peek()))
		{
			curr = in.get();
			cellValue += curr;
		}
		else
		{
			Helpers::removeWhitespace(in);
		}
	}
	Helpers::removeWhitespace(in);
	if (in.peek() != EOF && in.peek() != ',' && in.peek() != '\n')
	{
		std::cout << "Invalid format! Missing comma on row " << numberOfRows + 1 << " after the symbol " << curr << "." << std::endl;
		throw  std::invalid_argument("Invalid format");
	}
	if (in.peek() != '\n')
	{
		in.get();
	}
	return new (std::nothrow) Formula(0, numberOfRows + 1, cellNumber + 1,cellValue);
}

Cell* Spreadsheet::parseCell(std::ifstream& in, unsigned& pos, unsigned& rowNumber)
{
	in.seekg(pos);

	unsigned cellsInCurrRow = rows[rowNumber]->getNumberOfCells();

	Helpers::removeWhitespace(in);

	std::string cellValue;
	char curr = in.peek();

	if (curr == ',')
	{
		in.get();
		return new (std::nothrow) String(0, numberOfRows + 1, cellsInCurrRow + 1, " ");
	}
	else if (curr == '+' || curr == '-' || Helpers::isDigit(curr))
	{
		cellValue = parseNumberString(in, cellsInCurrRow);
		if (cellValue.find('.') != std::string::npos)
		{
			double fractNumber = std::stod(cellValue);
			return new (std::nothrow) Fractional(fractNumber, numberOfRows + 1, cellsInCurrRow + 1);
		}
		else
		{
			int intNumber = std::stoi(cellValue);
			return new (std::nothrow) Integer(intNumber, numberOfRows + 1, cellsInCurrRow + 1);
		}
	}
	else if (curr == '"')
	{
		return parseString(in, cellsInCurrRow);
	}
	else if (curr == '=')
	{
		return parseFormula(in, cellsInCurrRow);
	}
	else
	{
		std::cout << "Invalid cell value on row " << numberOfRows + 1 << " before the symbol " << curr << "." << std::endl;
		throw std::invalid_argument("Unknown data!");
	}
}
Row* Spreadsheet::parseRow(std::ifstream& in, unsigned& pos,unsigned& numRow)
{
	in.seekg(pos);

	while (!in.eof() && in.peek() != '\n')
	{
		Cell* cell = parseCell(in,pos,numRow); 
		if (cell != nullptr)
		{
			rows[numRow]->addCell(cell);
		}
		pos = in.tellg();
	}
	in.get();
	pos = in.tellg();
	return rows[numRow];
}

Spreadsheet& Spreadsheet::parseSpreadsheet(std::ifstream& in)
{
	unsigned pos = 0, temp;
	unsigned rowsNumber = Helpers::findFileSize(fileName);
	for (unsigned i = 0; i < rowsNumber; i++)
	{
		rows.push_back(new Row());
		rows[i] = parseRow(in, pos, i);
		numberOfRows++;
		temp = rows[i]->getNumberOfCells();
		if (numberOfColumns < temp)
		{
			numberOfColumns = temp;
		}
	}
	evaluateFormulas();
	return *this;
}

void Spreadsheet::evaluateFormula(const unsigned& row, const unsigned& col)
{
	double firstNum, secondNum;
	std::string operation;
	unsigned pos = 0;
	std::string stringValue = rows[row-1]->operator[](col-1)->getStringValue();
	Helpers::modifyString(stringValue);
	if (Helpers::isDigit(stringValue[0]))
	{
		firstNum = Helpers::findNumber(stringValue, pos);
		if (!Helpers::isOperator(stringValue[pos]))
		{
			std::cout << "Invalid formula! Can not evaluate formula.\n";
			throw  std::invalid_argument("Invalid formula");
		}
		else
		{
			while (Helpers::isOperator(stringValue[pos]))
			{
				operation += stringValue[pos];
				pos++;
			}
		}
		if (Helpers::isDigit(stringValue[pos]))
		{
			secondNum = Helpers::findNumber(stringValue, pos);
		}
		else if (stringValue[pos] == 'R')
		{
			std::vector<unsigned> indexes = Helpers::findCoordinatesOfCell(stringValue, pos);
			if (indexes.size() > 2)
			{
				std::cout << "Invalid formula! Can not evaluate formula.\n";
				throw std::invalid_argument("Invalid formula");
			}
			secondNum = findCellValue(indexes[0], indexes[1]);
		}
		else
		{
			std::cout << "Invalid formula! Can not evaluate formula.\n";
			throw std::invalid_argument("Invalid formula");
		}
	}
	else if (stringValue[0] == 'R')
	{
		std::vector<unsigned> indexes = Helpers::findCoordinatesOfCell(stringValue, pos);
		if (indexes.size() > 2)
		{
			std::cout << "Invalid formula! Can not evaluate formula.\n";
			throw std::invalid_argument("Invalid formula");
		}
		firstNum = findCellValue(indexes[0], indexes[1]);
		if (!Helpers::isOperator(stringValue[pos]))
		{
			std::cout << "Invalid formula! Can not evaluate formula.\n";
			throw std::invalid_argument("Invalid formula");
		}
		else
		{
			while (Helpers::isOperator(stringValue[pos]))
			{
				operation += stringValue[pos];
				pos++;
			}
		}
		if (Helpers::isDigit(stringValue[pos]))
		{
			secondNum = Helpers::findNumber(stringValue, pos);
		}
		else if (stringValue[pos] == 'R')
		{
			std::vector<unsigned> indexes = Helpers::findCoordinatesOfCell(stringValue, pos);
			if (indexes.size() > 2)
			{
				std::cout << "Invalid formula! Can not evaluate formula.\n";
				throw std::invalid_argument("Invalid formula");
			}
			secondNum = findCellValue(indexes[0], indexes[1]);
		}
		else
		{
			std::cout << "Invalid formula! Can not evaluate formula.\n";
			throw  std::invalid_argument("Invalid formula");
		}
	}
	double result = Helpers::evaluate(firstNum, secondNum, operation);
	rows[row-1]->operator[](col-1)->changeConvertedValue(result);
}

void Spreadsheet::evaluateFormulas()
{
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		for (unsigned j = 0; j < rows[i]->getNumberOfCells(); j++)
		{
			if (rows[i]->operator[](j)->getCellType() == CellType::FORMULA)
			{
				evaluateFormula(i + 1, j + 1);
			}
		}
	}
}

double Spreadsheet::findCellValue(const unsigned& row, const unsigned& col) const
{
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		for (unsigned j = 0; j < rows[i]->getNumberOfCells(); j++)
		{
			if (rows[i]->operator[](j)->getRow() == row &&
				rows[i]->operator[](j)->getCol() == col)
			{
				return rows[i]->operator[](j)->getConvertedValue();
			}
		}
	}
	return 0;
}

Spreadsheet::Spreadsheet(const std::string& fileName) : numberOfRows(0), numberOfColumns(0), fileName(fileName) {}

Spreadsheet::Spreadsheet(const Spreadsheet& other)
{
	copy(other);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

Spreadsheet::~Spreadsheet()
{
	destroy();
}

Spreadsheet* Spreadsheet::parse()
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		return nullptr;
	}
	try
	{
		*this = parseSpreadsheet(in);
		in.close();
		return this;
	}
	catch (...)
	{
		in.close();
		return nullptr;
	}
}

const void Spreadsheet::printSpreadsheet() const
{
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		unsigned rowCellsNumber = rows[i]->getNumberOfCells();
		for (unsigned j = 0; j < rowCellsNumber; j++)
		{
			if (rows[i]->operator[](j)->getConvertedValue() == (double)INT_MIN)
			{
				std::cout << std::setw(MIN_WIDTH) << "ERROR" << "|";
			}
			else if(rows[i]->operator[](j) != nullptr)
			{
				std::cout << std::setw(MIN_WIDTH);
				rows[i]->operator[](j)->print();
				std::cout << "|" << std::setw(MIN_WIDTH);
			}
		}
		if (rows[i]->getNumberOfCells() < numberOfColumns)
		{
			unsigned counter = rows[i]->getNumberOfCells();
			while (counter < numberOfColumns)
			{
				std::cout << std::setw(MIN_WIDTH+1) << "|" << std::setw(MIN_WIDTH+1);
				counter++;
			}
		}
		std::cout << std::endl;
	}
}

bool Spreadsheet::editCell(const unsigned& row, const unsigned& col, Cell* cell)
{
	if (row > numberOfRows || col > numberOfColumns)
	{
		return false;
	}
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		for (unsigned j = 0; j < rows[i]->getNumberOfCells(); j++)
		{
			if (rows[i]->operator[](j)->getRow() == row)
			{
				if (col > rows[i]->getNumberOfCells() && col <= numberOfColumns)
				{
					unsigned temp = rows[i]->getNumberOfCells();
					while (temp < col - 1)
					{
						rows[i]->addCell(new (std::nothrow) String());
						temp++;
					}
					rows[i]->addCell(cell);
					if (cell->getCellType() == CellType::FORMULA)
					{
						evaluateFormula(cell->getRow(),cell->getCol());
					}
					else
					{
						evaluateFormulas();
					}
					return true;
				}
			}
			if (rows[i]->operator[](j)->getRow() == row
				&& rows[i]->operator[](j)->getCol() == col)
			{
				if (rows[i]->operator[](j)->getCellType() != cell->getCellType())
				{
					rows[i]->operator[](j) = cell;
					if (cell->getCellType() == CellType::FORMULA)
					{
						evaluateFormula(cell->getRow(), cell->getCol());
					}
					else
					{
						evaluateFormulas();
					}
					return true;
				}
				rows[i]->operator[](j)->changeConvertedValue(cell->getConvertedValue());
				rows[i]->operator[](j)->changeStringValue(cell->getStringValue());
				evaluateFormulas();

				return true;
			}
		}
	}
	return false;
}

bool Spreadsheet::saveToFile(const std::string& fileName)
{
	std::ofstream out(fileName, std::ios::trunc);
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		unsigned rowCellsNumber = rows[i]->getNumberOfCells();
		for (unsigned j = 0; j < rowCellsNumber; j++)
		{
			if (rows[i]->operator[](j) != nullptr)
			{
				rows[i]->operator[](j)->saveInFile(out);
				if (j != rowCellsNumber - 1)
				{
					out << ", ";
				}
			}
		}
		if (i != numberOfRows - 1)
		{
			out << '\n';
		}
	}
	out.close();
	return true;
}
