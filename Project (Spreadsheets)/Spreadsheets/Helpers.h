#pragma once
#include "Cell.h"

class Helpers
{
public:
	static bool isWhitespace(char);
	static void removeWhitespace(std::ifstream&);

	static bool isDigit(char);
	static bool isOperator(char);
	static bool isCharacter(char);
	static bool hasOnlyDigits(const std::string);

	static double evaluate(double, double, std::string);

	static unsigned findFileSize(const std::string&);
	static std::string parseFileName(std::string&);

	static std::vector<unsigned> findCoordinatesOfCell(const std::string&, unsigned&);

	static double findNumber(const std::string&, unsigned&);

	static void modifyString(std::string&);
};
