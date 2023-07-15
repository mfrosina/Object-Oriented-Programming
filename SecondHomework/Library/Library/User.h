#pragma once
#include "PublishedEdition.h"

const char userDelimeter[64] = "****************************************";

class User
{
private:
	char* name;
	PublishedEdition** returned;
	PublishedEdition** taken;
	unsigned sizeReturned;
	unsigned sizeTaken;
	unsigned capacity;

	void copy(const User& other);
	void resize(int x); //x = 0 -> resizing returned; x = 1 -> resizing taken
	void destroy();

public:
	User();
	User(const char*);
	User(char*, PublishedEdition**,PublishedEdition**, unsigned&, unsigned&);
	User(const User& other);
	User operator=(const User& other);
	~User();

	bool operator==(const User& other);
	bool operator!=(const User& other);

	bool operator<(const User& other);
	bool operator>(const User& other);
	bool operator<=(const User& other);
	bool operator>=(const User& other);

	int operator[](const int& libraryNumber); //-1 never taken; 0 taken; 1 taken&returned

	User* operator+(PublishedEdition* toTake);
	User* operator+=(PublishedEdition* toTake);
	User* operator-(PublishedEdition* toReturn);
	User* operator-=(PublishedEdition* toTake);

	const unsigned getSizeOfTaken()const;
	const unsigned getSizeOfReturned()const;
	const char* getName()const;

	void saveUserInfoToFile(const char* fileName);
};