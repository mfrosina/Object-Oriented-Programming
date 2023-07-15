#pragma once
#include "Book.h"
#include "Periodical.h"

class Comic : public Book, public Periodical
{
public:
	Comic();
	Comic(const char* title, const char* description, const unsigned yearOfPublishing, const char* author, const char* publishingHouse, const Periodicity& periodicity, const unsigned& number);
	Comic(const Comic& other);
	Comic& operator=(const Comic& other);
	~Comic();

	void saveInFile(const char* fileName);

	const unsigned getNumber()const;

	PublishedEdition* clone()const override;
};
