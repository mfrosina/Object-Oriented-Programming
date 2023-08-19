#include "Helpers.h"

bool Helpers::isWhitespace(char ch)
{
	return ch == ' ' || ch == '\t';
}

void Helpers::removeWhitespace(std::ifstream& in)
{
	while (in && isWhitespace(in.peek()))
	{
		in.get();
	}
}

bool Helpers::isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool Helpers::isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*'
		|| ch == '/' || ch == '<' || ch == '>'
		|| ch == '=';
}

bool Helpers::isCharacter(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool Helpers::hasOnlyDigits(const std::string str)
{
	unsigned counter = 0;
	for (char i = '0'; i <= '9'; i++)
	{
		counter += std::count(str.begin(), str.end(), i);
	}
	counter += std::count(str.begin(), str.end(), '.');
	return counter == (str.length() - 2) || counter == str.length();
}

double Helpers::evaluate(double firstNum, double secondNum, std::string operation)
{
	if (operation == "+")
	{
		return firstNum + secondNum;
	}
	else if (operation == "-")
	{
		return firstNum - secondNum;
	}
	else if (operation == "*")
	{
		return firstNum * secondNum;
	}
	else if (operation == "/")
	{
		if (secondNum != 0)
		{
			return (double)(firstNum / secondNum);
		}
		else
		{
			return (double)INT_MIN;
		}
	}
	else if (operation == "<")
	{
		return (firstNum < secondNum) ? 1 : 0;
	}
	else if (operation == ">")
	{
		return (firstNum > secondNum) ? 1 : 0;
	}
	else if (operation == "<=")
	{
		return (firstNum <= secondNum) ? 1 : 0;
	}
	else if (operation == ">=")
	{
		return (firstNum >= secondNum) ? 1 : 0;
	}
	return 0;
}

unsigned Helpers::findFileSize(const std::string& fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		return 0;
	}
	unsigned counter = 0;
	while (!in.eof())
	{
		char buffer[512];
		in.getline(buffer, 512, '\n');
		counter++;
	}
	in.close();

	return counter;
}

std::string Helpers::parseFileName(std::string& str)
{
	unsigned size = str.length();
	for (unsigned i = 0; i < size; i++)
	{
		if (str[i] == '\\')
		{
			unsigned index = i + 1;
			str = str.substr(index, size);
			i = index;
			if (str.find('\\') == std::string::npos)
			{
				return str;
			}
		}
	}
}

std::vector<unsigned> Helpers::findCoordinatesOfCell(const std::string& formula, unsigned& index)
{
	unsigned r, c;
	std::string temp;
	std::vector<unsigned> coordinates;
	unsigned i = index;
	while(i < formula.length())
	{
		if (Helpers::isOperator(formula[i]))
		{
			index = i;
			break;
		}
		i++;
		while (Helpers::isDigit(formula[i]))
		{
			temp += formula[i];
			i++;
			if (formula[i] == 'C')
			{
				r = std::stoi(temp);
				coordinates.push_back(r);
				temp = "";
				i++;
				while (Helpers::isDigit(formula[i]))
				{
					temp += formula[i];
					i++;
				}
				c = std::stoi(temp);
				coordinates.push_back(c);
			}
		}
	}
	return coordinates;
}

double Helpers::findNumber(const std::string& str, unsigned& pos)
{
	double num;
	std::string numTemp, operation;
	unsigned i = pos;
	while (Helpers::isDigit(str[i]))
	{
		numTemp += str[i];
		i++;
		pos = i;
	}
	num = std::stod(numTemp);
	return num;
}

void Helpers::modifyString(std::string& str)
{
	std::string temp = "";
	unsigned i;
	if (str[0] == '=')
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	for (i; i < str.length(); i++)
	{
		if (isWhitespace(str[i]))
		{
			continue;
		}
		temp += str[i];
	}
	str = temp;
}

