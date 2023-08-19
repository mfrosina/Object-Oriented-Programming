#pragma once
#include "PublishedEdition.h";

class Book : virtual public PublishedEdition
{
protected:
	char* author;
	char* publishingHouse;

	void copy(const Book& other);
	void destroy();

public:
	Book();
	Book(const char* _title, const char* _description, const unsigned _yearOfPublishing, const char* _author, const char* _publishingHouse/*??, const Genre& _genre*/);
	Book(const Book& other);
	Book& operator=(const Book& other);
	~Book();

	void saveInFile(const char* fileName);

	PublishedEdition* clone()const override;
};
