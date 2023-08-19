#include "User.h"

void User::copy(const User& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	capacity = other.capacity;
	sizeReturned = other.sizeReturned;
	sizeTaken = other.sizeTaken;
	returned = new PublishedEdition*[capacity];
	taken = new PublishedEdition*[capacity];
	for (int i = 0; i < sizeReturned; i++)
	{
		returned[i] = other.returned[i]->clone();
	}
	for (int i = 0; i < sizeTaken; i++)
	{
		taken[i] = other.taken[i]->clone();
	}
}
void User::resize(int x)
{
	capacity *= 2;
	PublishedEdition** temp = new PublishedEdition*[capacity];
	if (x == 0)
	{
		for (unsigned i = 0; i < sizeReturned; i++)
		{
			temp[i] = returned[i]->clone();
		}
		returned = temp;
		for (unsigned i = 0; i < sizeReturned; i++)
		{
			delete temp[i];
		}
	}
	else if (x == 1)
	{
		for (unsigned i = 0; i < sizeTaken; i++)
		{
			temp[i] = taken[i]->clone();
		}
		taken = temp;
		for (unsigned i = 0; i < sizeTaken; i++)
		{
			delete temp[i];
		}
	}
	delete[]temp;
}
void User::destroy()
{
	delete[]name;
	for (unsigned i = 0; i < sizeReturned; i++)
	{
		delete returned[i];
	}
	delete[]returned;
	for (unsigned i = 0; i < sizeTaken; i++)
	{
		delete taken[i];
	}
	delete[]taken;
	sizeReturned = 0;
	sizeTaken = 0;
	capacity = 0;
}

User::User()
{
	name = new char[8];
	strcpy(name, "UNKNOWN");
	capacity = 8;
	returned = new PublishedEdition*[capacity];
	taken = new PublishedEdition*[capacity];
	sizeReturned = 0;
	sizeTaken = 0;
}
User::User(const char* name)
{
	if (name == nullptr)
	{
		throw std::invalid_argument("Invalid argument");
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->capacity = 8;
	this->returned = new PublishedEdition*[capacity];
	this->taken = new PublishedEdition*[capacity];
	this->sizeReturned = 0;
	this->sizeTaken = 0;
}
User::User(char* name, PublishedEdition** returned, PublishedEdition** taken, unsigned& sizeReturned, unsigned& sizeTaken)
{
	if (name == nullptr)
	{
		throw std::invalid_argument("Invalid argument");
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->capacity = sizeReturned * 2;
	this->returned = new PublishedEdition * [this->capacity];
	for (unsigned i = 0; i < sizeReturned; i++)
	{
		if (returned[i] != nullptr)
		{
			this->returned[i] = returned[i]->clone();
		}
	}
	this->sizeReturned = sizeReturned;
	this->capacity = sizeTaken * 2;
	this->taken = new PublishedEdition * [this->capacity];
	for (unsigned i = 0; i < sizeTaken; i++)
	{
		if (taken[i] != nullptr)
		{
			this->taken[i] = taken[i]->clone();
		}
	}
	this->sizeTaken = sizeTaken;
}
User::User(const User& other)
{
	copy(other);
}
User User::operator=(const User& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}
User::~User()
{
	destroy();
}

bool User::operator==(const User& other)
{
	return (strcmp(name, other.name) == 0);
}
bool User::operator!=(const User& other)
{
	return !(this == &other);
}

bool User::operator<(const User& other)
{
	return sizeReturned < other.sizeReturned;
}
bool User::operator>(const User& other)
{
	return !(this < &other);
}
bool User::operator<=(const User& other)
{
	return (this < &other || this == &other);
}
bool User::operator>=(const User& other)
{
	return (this > &other || this == &other);
}

int User::operator[](const int& libraryNumber)
{
	for (int i = 0; i < sizeReturned; i++)
	{
		if (returned[i]->getLibraryNumber() == libraryNumber)
		{
			return 1;
		}
	}
	for (int i = 0; i < sizeTaken; i++)
	{
		if (taken[i]->getLibraryNumber() == libraryNumber)
		{
			return 0;
		}
	}
	return -1;
}

User* User::operator+(PublishedEdition* toTake)
{
	if (sizeTaken >= capacity)
	{
		resize(1);
	}
	User* user = this;
	*user += toTake;
	return user;
}
User* User::operator+=(PublishedEdition* toTake)
{
	if (sizeTaken >= capacity)
	{
		resize(1);
	}
	taken[sizeTaken++] = toTake->clone();
	return this;

}
User* User::operator-(PublishedEdition* toReturn)
{
	for (int i = 0; i < sizeTaken; i++)
	{
		if (taken[i]->getLibraryNumber() == toReturn->getLibraryNumber())
		{
			if (sizeReturned >= capacity)
			{
				resize(0);
			}
			User* user = this;
			*user -= toReturn;
			return user;
		}
	}
	throw std::out_of_range("Edition not published yet");
}
User* User::operator-=(PublishedEdition* toReturn)
{
	for (int i = 0; i < sizeTaken; i++)
	{
		if (taken[i]->getLibraryNumber() == toReturn->getLibraryNumber())
		{
			if (sizeReturned >= capacity)
			{
				resize(0);
			}
			returned[sizeReturned++] = toReturn->clone();

			for (int j = i + 1; j < sizeTaken; j++)
			{
				taken[i] = taken[j];
				i++;
			}
			sizeTaken--;
			return this;
		}
	}
	throw std::out_of_range("Edition not published yet");
}

const unsigned User::getSizeOfTaken()const
{
	return sizeTaken;
}
const unsigned User::getSizeOfReturned()const
{
	return sizeReturned;
}
const char* User::getName()const
{
	return name;
}

void User::saveUserInfoToFile(const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	out << name << "\n";
	out << "//TAKEN:\n";
	out.close();
	for (int i = 0; i < sizeTaken; i++)
	{
		taken[i]->saveInFile(fileName);
	}
	out.open(fileName, std::ios::out | std::ios::app);
	out << "//\n";
	out << "\n++RETURNED:\n";
	out.close();
	for (int i = 0; i < sizeReturned; i++)
	{
		returned[i]->saveInFile(fileName);
	}
	out.open(fileName, std::ios::out | std::ios::app);
	out << "++\n";
	out << userDelimeter << '\n';
	out.close();
}