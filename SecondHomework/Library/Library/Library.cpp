#include "Library.h"

void Library::resize(int x)//x = 0 -> resizing the editions; x = 1 -> resizing the users
{
	capacity *= 2;
	if (x == 0)
	{
		EditionCopies* temp = new EditionCopies[capacity];

		for (int i = 0; i < sizePublishedEditions; i++)
		{
			temp[i] = publishedEditions[i];
		}
		publishedEditions = temp;
		delete[]temp;
	}
	else if (x == 1)
	{
		User** temp = new User*[capacity];
		for (int i = 0; i < sizeReaders; i++)
		{
			temp[i] = new User();
			temp[i] = readers[i];
		}
		readers = temp;
		for (int i = 0; i < capacity; i++)
		{
			delete temp[i];
		}
		delete[]temp;
	}

}
void Library::destroy()
{

	for (int i = 0; i < sizePublishedEditions; ++i)
	{
		if (publishedEditions[i].edition != nullptr)
		{
			delete publishedEditions[i].edition;
		}
	}
	delete[] publishedEditions;

	for (unsigned i = 0; i < sizeReaders; ++i)
	{
		if (readers[i] != nullptr)
		{
		   delete readers[i];
		}
	}
	delete[] readers;
}

unsigned Library::findFileSize(const char* fileName, const char* delimeter)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		return 0;
	}
	unsigned counter = 0;
	while (!in.eof())
	{
		char buffer[128];
		in.getline(buffer, 128, '\n');
		if (strcmp(buffer, delimeter) == 0)
		{
			counter++;
		}

	}
	in.close();
	return counter;
}
bool Library::existsPE(PublishedEdition*& pe)
{
	for (int i = 0; i < sizePublishedEditions; i++)
	{
		if (pe->getLibraryNumber() == publishedEditions[i].edition->getLibraryNumber())
		{
			return true;
		}
	}
	return false;
}
unsigned Library::countPEOccurences(PublishedEdition** editions, unsigned size, PublishedEdition*& pe)
{
	unsigned counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (editions[i]->getLibraryNumber() == pe->getLibraryNumber())
		{
			counter++;
		}
	}
	return counter;
}

void Library::loadPublishedEditions(const unsigned& size)
{
	PublishedEdition** editions = readPEsFromFile();
	publishedEditions = new EditionCopies[size];
	for (int i = 0; i < size; i++)
	{
		publishedEditions[sizePublishedEditions].edition = publishedEditions[sizePublishedEditions].edition = editions[i];
		publishedEditions[sizePublishedEditions].copies = countPEOccurences(editions, size, editions[i]);
		sizePublishedEditions++;
	}

	delete[]editions;
	editions = nullptr;
}

PublishedEdition* Library::readPEFromFile(const char* fileName,unsigned& pos)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	in.seekg(pos);
	char bufferType[32];
	in.getline(bufferType, 32, '\n');
	PEType type = convertToEnum(bufferType);
	int lNum;
	in >> lNum;
	in.get();
	char bufferTitle[128], bufferDescr[128];
	in.getline(bufferTitle, 128, '\n');
	char* title = new char[strlen(bufferTitle) + 1];
	strcpy(title, bufferTitle);
	in.getline(bufferDescr, 128, '\n');
	char* descr = new char[strlen(bufferDescr) + 1];
	strcpy(descr, bufferDescr);
	int year;
	in >> year;

	if (type == PEType::BOOK)
	{
		in.get();
		char bufferAuthor[128], bufferHouse[128];
		in.getline(bufferAuthor, 128, '\n');
		char* author = new char[strlen(bufferAuthor) + 1];
		strcpy(author, bufferAuthor);
		in.getline(bufferHouse, 128, '\n');
		char* pHouse = new char[strlen(bufferHouse) + 1];
		strcpy(pHouse, bufferHouse);

		in.get();
		char bufferDelimeter[64];
		in.getline(bufferDelimeter, 64, '\n');

		pos = in.tellg();
		in.close();

		Book* b = new Book(title, descr, year, author, pHouse);
		b->setLibraryNumber(lNum);
		return b;
	}
	else if (type == PEType::PERIODICAL)
	{
		char bufferPeriodicity[128];
		int num;
		in >> bufferPeriodicity;
		in >> num;
		Periodicity per = convertPeriodicityToEnum(bufferPeriodicity);

		in.get();
		char bufferDelimeter[64];
		in.getline(bufferDelimeter, 64, '\n');

		pos = in.tellg();
		in.close();

		Periodical* p = new Periodical(title, descr, year, per, num);
		p->setLibraryNumber(lNum);
		return p;
	}
	else
	{
		in.get();
		char bufferAuthor[128], bufferHouse[128];
		in.getline(bufferAuthor, 128, '\n');
		char* author = new char[strlen(bufferAuthor) + 1];
		strcpy(author, bufferAuthor);
		in.getline(bufferHouse, 128, '\n');
		char* pHouse = new char[strlen(bufferHouse) + 1];
		strcpy(pHouse, bufferHouse);
		char bufferPeriodicity[128];
		int num;
		in >> bufferPeriodicity;
		in >> num;
		Periodicity per = convertPeriodicityToEnum(bufferPeriodicity);

		in.get();
		char bufferDelimeter[64];
		in.getline(bufferDelimeter, 64, '\n');

		pos = in.tellg();
		in.close();

		Comic* c = new Comic(title, descr, year, author, pHouse, per, num);
		c->setLibraryNumber(lNum);
		return c;
	}
}

PublishedEdition** Library::readPEsFromFile()
{
	unsigned size = findFileSize(FILENAME_PE,delimeter);
	unsigned pos = 0;
	if (size != 0)
	{
		PublishedEdition** editions = new PublishedEdition * [size];
		for (int i = 0; i < size; i++)
		{
			editions[i] = readPEFromFile(FILENAME_PE,pos);
		}
		return editions;
	}
	std::cout << "Not published any editions yet...\n";
	
}

void Library::removePEFromFile(PublishedEdition*& toRemove)
{
	for (int i = 0; i < sizePublishedEditions; i++)
	{
		if (publishedEditions[i].edition->getLibraryNumber() != toRemove->getLibraryNumber())
		{
			publishedEditions[i].edition->saveInFile("temp.txt");
		}
	}
	std::remove(FILENAME_PE);
	std::rename("temp.txt", FILENAME_PE);
}
bool Library::markPEAsTaken(const int& libraryNumber)
{
	for (int i = 0; i < sizePublishedEditions; i++)
	{
		if (publishedEditions[i].edition->getLibraryNumber() == libraryNumber)
		{
			if (publishedEditions[i].copies == 0)
			{
				return false;
			}
			publishedEditions[i].copies--;
			break;
		}
	}
	return true;
}

void Library::swapPEs(PublishedEdition*& first, PublishedEdition*& second)
{
	PublishedEdition* temp = first;
	first = second;
	second = temp;
}
void Library::sortPEsByYearAndTitle()
{
	for (int i = 0; i < sizePublishedEditions; i++)
	{
		for (int j = i + 1; j < sizePublishedEditions; j++)
		{
			if (publishedEditions[i].edition->getYearOfPublishing() > publishedEditions[j].edition->getYearOfPublishing())
			{
				swapPEs(publishedEditions[i].edition, publishedEditions[j].edition);
			}
			else if (publishedEditions[i].edition->getYearOfPublishing() == publishedEditions[j].edition->getYearOfPublishing())
			{
				if (strncmp(publishedEditions[i].edition->getTitle(), publishedEditions[j].edition->getTitle(), 1) > 0)
				{
					swapPEs(publishedEditions[i].edition, publishedEditions[j].edition);
				}
				else if (strncmp(publishedEditions[i].edition->getTitle(), publishedEditions[j].edition->getTitle(), 1) == 0
					&& publishedEditions[i].edition->getPEType() == PEType::PERIODICAL
					&& publishedEditions[j].edition->getPEType() == PEType::PERIODICAL)
				{
					swapPEs(publishedEditions[i].edition, publishedEditions[j].edition);

				}

			}
		}
	}
}

bool Library::existsUser(const char* name)
{
	for (int i = 0; i < sizeReaders; i++)
	{
		if (strcmp(readers[i]->getName(), name) == 0)
		{
			return true;
		}
	}
	return false;
}

unsigned Library::findNumberOfPEsForUser(const char* fileName, unsigned& pos, char symbol)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	char buffer[264] = "\0";
	unsigned counter = 0;
	in.seekg(pos);
	while (buffer[0] != symbol)
	{
		in.getline(buffer, 264, '\n');
		if (strcmp(buffer, delimeter) == 0)
		{
			counter++;
		}
	}
	pos = in.tellg();
	in.close();
	return counter;
}
User* Library::readUserFromFile(const char* fileName, unsigned& pos)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	in.seekg(pos);
	char bufferDelimeter[64];

	char bufferName[128];
	in.getline(bufferName, 128, '\n');
	char* name = new char[strlen(bufferName) + 1];
	strcpy(name, bufferName);

	in.get();// \n
	in.getline(bufferDelimeter, 64, '\n');
	pos = in.tellg();

	unsigned savePos = pos;
	unsigned numberOfTaken = findNumberOfPEsForUser(fileName, pos, '/');
	pos = savePos;
	PublishedEdition** taken = new PublishedEdition * [numberOfTaken];
	for (unsigned i = 0; i < numberOfTaken; i++)
	{
		taken[i] = readPEFromFile(FILENAME_USERS,pos);
	}
	in.seekg(pos);
	in.getline(bufferDelimeter, 64, '\n');
	in.getline(bufferDelimeter, 64, '\n');

	in.getline(bufferDelimeter, 64, '\n');

	pos = in.tellg();
	unsigned numberOfReturned = findNumberOfPEsForUser(fileName, pos, '+');
	PublishedEdition** returned = new PublishedEdition * [numberOfReturned];
	for (unsigned i = 0; i < numberOfReturned; i++)
	{
		returned[i] = readPEFromFile(FILENAME_USERS,pos);
	}
	in.seekg(pos);
	char bufferDelim[64];
	in.getline(bufferDelim, 64, '\n');

	pos = in.tellg();
	in.close();

	User* u = new User(name, returned, taken, numberOfReturned, numberOfTaken);

	return u;
}
User** Library::readUsers()
{
	unsigned size = findFileSize(FILENAME_USERS,userDelimeter);
	unsigned pos = 0;
	if (size != 0)
	{
		User** users = new User*[size];
		for (int i = 0; i < size; i++)
		{
			users[i] = readUserFromFile(FILENAME_USERS, pos);
		}
		sizeReaders = size;
		return users;
	}
	else
	{
		std::cout << "Not found users...\n";
	}
}
void Library::removeUserFromFile(User*& toRemove)
{
	for (unsigned i = 0; i < sizeReaders; i++)
	{
		if (strcmp(readers[i]->getName(),toRemove->getName()) != 0)
		{
			readers[i]->saveUserInfoToFile("temp.txt");
		}
	}
	std::remove(FILENAME_USERS);
	std::rename("temp.txt", FILENAME_USERS);
}
void Library::sortUsersByNumberOfReadings()
{
	if (sizeReaders == 0)
	{
		std::cout << "No registered users yet...\n";
		return;
	}
	for (int i = 0; i < sizeReaders; i++)
	{
		for (int j = i + 1; j < sizeReaders-1; j++)
		{
			if (readers[i] < readers[j])
			{
				User* temp = readers[i];
				readers[i] = readers[j];
				readers[j] = temp;
			}
		}
	}
}

Library::Library()
{
	unsigned size = findFileSize(FILENAME_PE,delimeter);
	if (size != 0)
	{
		capacity = size * 2;
		loadPublishedEditions(size);
	}
	else
	{
		capacity = 8;
		publishedEditions = new EditionCopies[capacity];
		sizePublishedEditions = 0;
	}
	size = findFileSize(FILENAME_USERS,userDelimeter);
	if (size != 0)
	{
		readers = readUsers();
	}
	else
	{
		capacity = 8;
		readers = new User*[capacity];
		sizeReaders = 0;
	}
}
Library::~Library()
{
	destroy();
}

void Library::addPublishedEdition(PublishedEdition*& toAdd, unsigned copies)
{
	if (sizePublishedEditions >= capacity)
	{
		resize(0);
	}
	if (!existsPE(toAdd))
	{
		publishedEditions[sizePublishedEditions].edition = toAdd;
		publishedEditions[sizePublishedEditions].copies = copies;
		sizePublishedEditions++;
		toAdd->saveInFile(FILENAME_PE);
	}
	else
	{
		for (int i = 0; i < sizePublishedEditions; i++)
		{
			if (toAdd->getLibraryNumber() == publishedEditions[i].edition->getLibraryNumber())
			{
				publishedEditions[i].copies += copies;
				break;
			}
		}
	}
}
bool Library::removePublishedEdition(const int& libraryNumber)
{
	if (sizePublishedEditions == 0)
	{
		std::cout << "No available published editions yet... Can not remove!\n";
		return false;
	}
	for (int i = 0; i < sizePublishedEditions; i++)
	{
		if (libraryNumber == publishedEditions[i].edition->getLibraryNumber())
		{
			if (publishedEditions[i].copies > 1)
			{
				publishedEditions[i].copies--;
			}
			else
			{
				removePEFromFile(publishedEditions[i].edition);
				for (int j = i + 1; j < sizePublishedEditions; j++)
				{
					publishedEditions[i] = publishedEditions[j];
					i++;
				}
			}
			sizePublishedEditions--;
			return true;
		}

	}
	return false;
}
void Library::publishedEditionsSortedInfo()
{
	if (sizePublishedEditions == 0)
	{
		std::cout << "No available published editions yet...\n";
		return;
	}
	sortPEsByYearAndTitle();
	std::cout << "Published Editions available in the Library:\n";
	for (int i = 0; i < sizePublishedEditions; i++)
	{
		std::cout << "\t" << convertToStr(publishedEditions[i].edition->getPEType()) << "\nLibrary number : " << publishedEditions[i].edition->getLibraryNumber() << "\nTitle : " << publishedEditions[i].edition->getTitle() << "\nShort Description : " << publishedEditions[i].edition->getDescription() << std::endl;
	}
}

void Library::addUser(User*& toAdd)
{
	for (unsigned i = 0; i < sizeReaders; i++)
	{
		if (strcmp(readers[i]->getName(), toAdd->getName()) == 0)
		{
			std::cout << "User with name " << toAdd->getName() << " already exists!\n";
			return;
		}
	}
	if (sizeReaders >= capacity)
	{
		resize(1);
	}
	readers[sizeReaders] = toAdd;
	sizeReaders++;
	toAdd->saveUserInfoToFile(FILENAME_USERS);
}

bool Library::removeUser(const char* name)
{
	if (sizeReaders == 0)
	{
		std::cout << "No registered users yet... Can not remove!\n";
		return false;
	}
	for (int i = 0; i < sizeReaders; i++)
	{
		if (strcmp(readers[i]->getName(), name) == 0)
		{
			removeUserFromFile(readers[i]);
			for (int j = i + 1; j < sizeReaders; j++)
			{
				readers[i] = readers[j];
				i++;
			}
			sizeReaders--;
			return true;
		}
	}
	return false;
}

void Library::userInfoWithTakenPEs(const int& libraryNumber)
{
	if (sizeReaders == 0)
	{
		std::cout << "No registered users yet...\n";
		return;
	}
	std::cout << "Users that have taken a published edition with library number: " << libraryNumber << std::endl;
	bool flag = false;
	for (int i = 0; i < sizeReaders; i++)
	{
		if (readers[i]->operator[](libraryNumber) == 0)
		{
			std::cout << readers[i]->getName() << std::endl;
			flag = true;
		}
	}
	if (!flag)
	{
		std::cout << "None.\n";
	}
}
void Library::userInfoSortedByNumberOfReadings()
{
	if (sizeReaders == 0)
	{
		std::cout << "No registered users yet...\n";
		return;
	}
	sortUsersByNumberOfReadings();
	for (int i = 0; i < sizeReaders; i++)
	{
		std::cout << readers[i]->getName() << " " << readers[i]->getSizeOfReturned() << " books. " << std::endl;
	}
}

bool Library::takePublishedEdition(const char* userName,const int& libraryNumber)
{
	if (!existsUser(userName))
	{
		return false;
	}
	for (int i = 0; i < sizeReaders; i++)
	{
		if (strcmp(userName, readers[i]->getName()) == 0)
		{
			if (readers[i]->getSizeOfTaken() >= 5)
			{
				return false;
			}
			for (int j = 0; j < sizePublishedEditions; j++)
			{
				if (publishedEditions[j].edition->getLibraryNumber() == libraryNumber)
				{
					try
					{
						if (markPEAsTaken(libraryNumber))
						{
							User* temp = readers[i];
							temp = temp->operator+=(publishedEditions[j].edition);
							readers[i] = temp;
							removeUserFromFile(readers[i]);
							readers[i]->saveUserInfoToFile(FILENAME_USERS);
							return true;
						}
					}
					catch (const std::exception& e)
					{
						std::cout << e.what() << std::endl;
						return false;
					}
				}
			}
		}
	}
	return false;
}

bool Library::returnPublishedEdition(const char* userName,const int& libraryNumber)
{
	if (!existsUser(userName))
	{
		return false;
	}
	for (int i = 0; i < sizeReaders; i++)
	{
		if (strcmp(userName, readers[i]->getName()) == 0)
		{
	
			if (readers[i]->operator[](libraryNumber) == 0)
			{
				for (int j = 0; j < sizePublishedEditions; j++)
				{
					if (publishedEditions[j].edition->getLibraryNumber() == libraryNumber)
					{
						try
						{
							publishedEditions[j].copies++;
							User* temp = readers[i];
							temp = temp->operator-=(publishedEditions[j].edition);
							readers[i] = temp;
							removeUserFromFile(readers[i]);
							readers[i]->saveUserInfoToFile(FILENAME_USERS);
							return true;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							return false;
						}
					}
					
				}
				
			}
			
		}
	}
	return false;
}