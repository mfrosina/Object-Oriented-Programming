#include "Book.h"

void Book::copy(const Book& other)
{
	if (other.author != nullptr && other.publishingHouse != nullptr)
	{
		author = new char[strlen(other.author) + 1];
		strcpy(author, other.author);
		publishingHouse = new char[strlen(other.publishingHouse) + 1];
		strcpy(publishingHouse, other.publishingHouse);
	}
	else
	{
		throw std::invalid_argument("Invalid data");
	}
}
void Book::destroy()
{;
	delete[]author;
	delete[]publishingHouse;
}
Book::Book()
{
	author = new char[8];
	strcpy(author, "UNKNOWN");
	publishingHouse = new char[8];
	strcpy(publishingHouse, "UNKNOWN");
	type = PEType::BOOK;
}

Book::Book(const char* _title, const char* _description, const unsigned _yearOfPublishing, const char* _author, const char* _publishingHouse) : PublishedEdition(_title, _description, _yearOfPublishing, PEType::BOOK)
{
	if (_author == nullptr || _publishingHouse == nullptr)
	{
		throw std::invalid_argument("Invalid arguments");
	}
	author = new char[strlen(_author) + 1];
	strcpy(author, _author);
	publishingHouse = new char[strlen(_publishingHouse) + 1];
	strcpy(publishingHouse, _publishingHouse);
}
Book::Book(const Book& other) : PublishedEdition(other)
{
	copy(other);
}
Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		PublishedEdition::operator=(other);
		destroy();
		copy(other);
	}
	return *this;
}
Book::~Book()
{
	destroy();
}

void Book::saveInFile(const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	PublishedEdition::saveInFile(fileName);
	out << author << '\n' << publishingHouse << '\n';
	out << delimeter << '\n';

	out.close();
}

PublishedEdition* Book::clone()const
{
	return new Book(*this);
}