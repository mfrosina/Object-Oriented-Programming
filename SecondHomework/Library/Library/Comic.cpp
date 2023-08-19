#include "Comic.h"

Comic::Comic() : Book(), Periodical()
{
	type = PEType::COMIC;
}

Comic::Comic(const char* title, const char* description, const unsigned yearOfPublishing, const char* author, const char* publishingHouse, const Periodicity& periodicity, const unsigned& number)
	: PublishedEdition(title, description, yearOfPublishing, PEType::COMIC),
	Book(title, description, yearOfPublishing, author, publishingHouse),
	Periodical(title, description, yearOfPublishing, periodicity, number) {}

Comic::Comic(const Comic& other) : PublishedEdition(other), Book(other), Periodical(other) {}

Comic& Comic::operator=(const Comic& other)
{
	if (this != &other)
	{
		PublishedEdition::operator=(other);
		Book::operator=(other);
		Periodical::operator=(other);
	}
	return *this;
}

Comic::~Comic() {}

void Comic::saveInFile(const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	PublishedEdition::saveInFile(fileName);
	out << author << '\n' << publishingHouse << '\n' << convertToStr(periodicity) << " " << number << "\n";
	out << delimeter << '\n';

	out.close();
}

const unsigned Comic::getNumber()const
{
	return number;
}

PublishedEdition* Comic::clone()const
{
	return new Comic(*this);
}