#pragma once
#include "Book.h"
#include "Comic.h"
#include "Periodical.h"
#include "User.h"

#include <iostream>

const char FILENAME_PE[28] = "published_editions.txt";
const char FILENAME_USERS[28] = "readers.txt";

class Library
{
private:

	struct EditionCopies
	{
		PublishedEdition* edition;
		unsigned copies;
	};

	EditionCopies* publishedEditions;
	User** readers;
	unsigned sizePublishedEditions;
	unsigned sizeReaders;
	unsigned capacity;

	void resize(int x); //x = 0 -> resizing the editions; x = 1 -> resizing the users
	void destroy();

	unsigned findFileSize(const char* fileName, const char*);
	bool existsPE(PublishedEdition*& pe);
	unsigned countPEOccurences(PublishedEdition** editions, unsigned size, PublishedEdition*& pe);

	void loadPublishedEditions(const unsigned& size);

	PublishedEdition* readPEFromFile(const char*,unsigned&);
	void removePEFromFile(PublishedEdition*& toRemove);
	PublishedEdition** readPEsFromFile();
	bool markPEAsTaken(const int& libraryNumber);
	void swapPEs(PublishedEdition*& first, PublishedEdition*& second);
	void sortPEsByYearAndTitle();

	bool existsUser(const char* name);
	unsigned findNumberOfPEsForUser(const char*, unsigned&, char);
	User* readUserFromFile(const char*,unsigned&);
	User** readUsers();
	void removeUserFromFile(User*& toRemove);
	void sortUsersByNumberOfReadings();


public:
	Library();
	Library(const Library& other) = delete;
	Library& operator=(const Library& other) = delete;
	~Library();

	void addPublishedEdition(PublishedEdition*& toAdd, unsigned copies);
	bool removePublishedEdition(const int& libraryNumber);
	void publishedEditionsSortedInfo();

	void addUser(User*& toAdd);
	bool removeUser(const char* name);

	void userInfoWithTakenPEs(const int& libraryNumber);
	void userInfoSortedByNumberOfReadings();

	bool takePublishedEdition(const char* userName, const int& libraryNumber);
	bool returnPublishedEdition(const char* userName, const int& libraryNumber);



};