#include "Periodical.h"

const char* convertToStr(const Periodicity& p)
{
	switch (p)
	{
	case 0: return "WEEKLY"; 
	case 1: return "MONTHLY"; 
	case 2: return "ONCEAYEAR"; 
	default:
		return "UNKNOWN";
	}
}

Periodicity convertPeriodicityToEnum(const char* p)
{
	if (strcmp(p, "WEEKLY") == 0)
	{
		return Periodicity::WEEKLY;
	}
	else if (strcmp(p, "MONTHLY") == 0)
	{
		return Periodicity::MONTHLY;
	}
	else if (strcmp(p, "ONCEAYEAR") == 0)
	{
		return Periodicity::ONCEAYEAR;
	}
	else
	{
		return Periodicity::UNKNOWN;
	}
}

void Periodical::copy(const Periodical& other)
{
	periodicity = other.periodicity;
	number = other.number;
}
Periodical::Periodical()
{
	periodicity = Periodicity::UNKNOWN;
	number = 0;
	type = PEType::PERIODICAL;
}
Periodical::Periodical(const char* _title, const char* _description, const unsigned _yearOfPublishing, const Periodicity& _periodicity, const unsigned _number) : PublishedEdition(_title, _description, _yearOfPublishing, PEType::PERIODICAL)
{
	if (_number <= 0)
	{
		throw std::invalid_argument("Invalid argument");
	}
	periodicity = _periodicity;
	number = _number;
}
Periodical::Periodical(const Periodical& other) : PublishedEdition(other)
{
	copy(other);
}
Periodical& Periodical::operator=(const Periodical& other)
{
	if (this != &other)
	{
		PublishedEdition::operator=(other);
		copy(other);
	}
	return *this;
}
Periodical::~Periodical()
{
	periodicity = Periodicity::UNKNOWN;
	number = 0;
}

void Periodical::saveInFile(const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	PublishedEdition::saveInFile(fileName);
	out << convertToStr(periodicity) << " " << number << "\n";
	out << delimeter << '\n';

	out.close();
}

const unsigned Periodical::getNumber()const
{
	return number;
}

PublishedEdition* Periodical::clone()const
{
	return new Periodical(*this);
}