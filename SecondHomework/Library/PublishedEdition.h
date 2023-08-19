#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <stdexcept>
#include <fstream>

const char delimeter[64] = "----------------------------------------";
const char FILENAME_UNIQUE_LNS[32] = "unique_library_numbers.txt";

enum PEType
{
	UNKNOWN_TYPE = -1,
	BOOK,
	PERIODICAL,
	COMIC
};

const char* convertToStr(const PEType& type);
PEType convertToEnum(const char* type);

class PublishedEdition
{
protected:
	char* title;
	char* description;
	int libraryNumber;
	unsigned yearOfPublishing;
	PEType type;

	void copy(const PublishedEdition& other);
	void destroy();
	int assignUniqueLibraryNumber();
public:
	PublishedEdition();
	PublishedEdition(const char* _title, const char* _description, const unsigned _yearOfPublishing, const PEType& _type);
	PublishedEdition(const PublishedEdition& other);
	PublishedEdition& operator=(const PublishedEdition& other);
	virtual ~PublishedEdition();

	const char* getTitle()const;
	const char* getDescription()const;
	const int getLibraryNumber()const;
	const unsigned getYearOfPublishing()const;
	const PEType getPEType()const;
	virtual const unsigned getNumber()const;

	void setLibraryNumber(int ln);

	virtual void saveInFile(const char* fileName);

	virtual PublishedEdition* clone()const = 0;
};


