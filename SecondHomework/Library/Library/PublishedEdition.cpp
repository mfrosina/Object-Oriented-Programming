#include "PublishedEdition.h"

const char* convertToStr(const PEType& type)
{
	switch (type)
	{
	case 0: return "BOOK";
	case 1: return "PERIODICAL";
	case 2: return "COMIC";
	default:
		return "UNKNOWN";
	}
}

PEType convertToEnum(const char* type)
{
	if (strcmp(type, "BOOK") == 0)
	{
		return PEType::BOOK;
	}
	else if (strcmp(type, "PERIODICAL") == 0)
	{
		return PEType::PERIODICAL;
	}
	else if (strcmp(type, "COMIC") == 0)
	{
		return PEType::COMIC;
	}
	else
	{
		return PEType::UNKNOWN_TYPE;
	}
}

void PublishedEdition::copy(const PublishedEdition& other)
{
	if (other.title != nullptr && other.description != nullptr && other.yearOfPublishing > 1900)
	{
		title = new char[strlen(other.title) + 1];
		strcpy(title, other.title);
		description = new char[strlen(other.description) + 1];
		strcpy(description, other.description);
		libraryNumber = other.libraryNumber;
		yearOfPublishing = other.yearOfPublishing;
		type = other.type;
	}
	else
	{
		throw std::invalid_argument("Invalid data");
	}
}
void PublishedEdition::destroy()
{
	delete[]title;
	delete[]description;
	yearOfPublishing = 1900;
	libraryNumber = 0;
	type = PEType::UNKNOWN_TYPE;
}
void PublishedEdition::setLibraryNumber(int ln)
{
	libraryNumber = ln;
}

int PublishedEdition::assignUniqueLibraryNumber()
{
	std::ifstream lnsIn(FILENAME_UNIQUE_LNS);
	if (!lnsIn.is_open())
	{
		std::ofstream lnsOut(FILENAME_UNIQUE_LNS);
		if (!lnsOut.is_open())
		{
			return -1;
		}
		int ln = 0;
		lnsOut << ln << std::endl;
		lnsOut.close();
		lnsIn.open(FILENAME_UNIQUE_LNS);
		if (!lnsIn.is_open())
		{
			return -1;
		}
	}
	int ln;
	lnsIn >> ln;
	ln += 1;
	lnsIn.close();

	std::ofstream lnsOut(FILENAME_UNIQUE_LNS);
	if (!lnsOut.is_open())
	{
		return -1;
	}
	lnsOut << ln;
	lnsOut.close();

	return ln;
}

PublishedEdition::PublishedEdition()
{
	title = new char[8];
	strcpy(title, "UNKNOWN");
	description = new char[8];
	strcpy(description, "UNKNOWN");
	libraryNumber = -1;
	yearOfPublishing = 1900;
	type = PEType::UNKNOWN_TYPE;
}
PublishedEdition::PublishedEdition(const char* _title, const char* _description, const unsigned _yearOfPublishing, const PEType& _type)
{
	if (_title == nullptr || _description == nullptr || _yearOfPublishing < 1900)
	{
		throw std::invalid_argument("Invalid argument");
	}
	title = new char[strlen(_title) + 1];
	strcpy(title, _title);
	description = new char[strlen(_description) + 1];
	strcpy(description, _description);
	libraryNumber = assignUniqueLibraryNumber();
	yearOfPublishing = _yearOfPublishing;
	type = _type;
}
PublishedEdition::PublishedEdition(const PublishedEdition& other)
{
	copy(other);
}
PublishedEdition& PublishedEdition::operator=(const PublishedEdition& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}
PublishedEdition::~PublishedEdition()
{
	destroy();
}

const char* PublishedEdition::getTitle()const
{
	return title;
}
const char* PublishedEdition::getDescription()const
{
	return description;
}
const int PublishedEdition::getLibraryNumber()const
{
	return libraryNumber;
}
const unsigned PublishedEdition::getYearOfPublishing()const
{
	return yearOfPublishing;
}
const PEType PublishedEdition::getPEType()const
{
	return type;
}
const unsigned PublishedEdition::getNumber()const
{
	return 0;
}


void PublishedEdition::saveInFile(const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	out << convertToStr(type) << '\n';
	out << libraryNumber << '\n' << title << '\n' << description << '\n' << yearOfPublishing << '\n';

	out.close();
}