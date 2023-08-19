// task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

enum Gender
{
	UNKNOWN=-1,
	FEMALE,
	MALE
};
const char* findGenderInChar(const Gender& gender)
{
	switch (gender)
	{
	case 0: return "female"; break;
	case 1: return "male"; break;
	default: return "unknown"; break;
	}
}
Gender findGenderInEnum(const char* gender)
{
	if (strcmp(gender, "female") == 0)
	{
		return Gender::FEMALE;
	}
	else if (strcmp(gender, "male") == 0)
	{
		return Gender::MALE;
	}
	else
	{
		return Gender::UNKNOWN;
	}
}
class Person
{
private:
	char* firstName;
	char* secondName;
	Gender gender;
	unsigned birthYear;

	void copy(const Person& other)
	{
		this->firstName = new char[strlen(other.firstName) + 1];
		strcpy(this->firstName, other.firstName);
		this->secondName = new char[strlen(other.secondName) + 1];
		strcpy(this->secondName, other.secondName);
		this->gender = other.gender;
		this->birthYear = other.birthYear;
	}
	void destroy()
	{
		delete[]firstName;
		delete[]secondName;
	}
public:
	Person()
	{
		this->firstName = new char[10];
		strcpy(this->firstName, "UNKNOWN");
		this->secondName = new char[10];
		strcpy(this->secondName, "UNKNOWN");
		this->gender = Gender::UNKNOWN;
		this->birthYear = 1800;
	}
	Person(const char* firstName, const char* secondName, const Gender& gender, const unsigned& year)
	{
		if (firstName == nullptr || secondName == nullptr || year < 1800)
		{
			throw std::invalid_argument("Invalid person data");
		}
		this->firstName = new char[strlen(firstName) + 1];
		strcpy(this->firstName, firstName);
		this->secondName = new char[strlen(secondName) + 1];
		strcpy(this->secondName, secondName);
		this->gender = gender;
		this->birthYear = year;
	}
	Person(const Person& other)
	{
		copy(other);
	}
	Person& operator=(const Person& other)
	{
		if (this != &other)
		{
			destroy();
			copy(other);
		}
		return *this;
	}
	~Person()
	{
		destroy();
	}

	const char* getFirstName()const
	{
		return this->firstName;
	}
	const char* getSecondName()const
	{
		return this->secondName;
	}
	const Gender getGender()const
	{
		return this->gender;
	}
	const unsigned getBirthYear()const
	{
		return this->birthYear;
	}

	void saveInFile(const char* fileName)
	{
		std::ofstream out(fileName, std::ios::app);
		if (!out.is_open())
		{
			throw std::out_of_range("Can not open file");
		}
		char gender[32];
		strcpy(gender,findGenderInChar(this->gender));
		out << this->firstName << " " << this->secondName << " " << gender << " " << birthYear << " ";
		out.close();
	}
	Person readFromFile(const char* fileName, unsigned& pos)
	{
		std::ifstream in(fileName);
		if (!in.is_open())
		{
			throw std::out_of_range("Can not open file");
		}
		char buffer[128];
		in.getline(buffer, 128, ' ');
		char* fName = new char[strlen(buffer) + 1];
		strcpy(fName, buffer);
		char buffer1[128];
		in.getline(buffer1, 128, ' ');
		char* sName = new char[strlen(buffer1) + 1];
		strcpy(sName, buffer1);
		
		char buffer2[128];
		in.getline(buffer2, 128, ' ');
		char* gend = new char[strlen(buffer2) + 1];
		strcpy(gend, buffer2);
		Gender gender = findGenderInEnum(gend);
		unsigned year;
		in >> year;
	
		Person person(fName, sName, gender, year);
		in.seekg(std::ios::cur);
		pos = in.tellg();
		in.close();
	
		return person;
	
	}
};



class Car
{
private:
	char brand[128];
	Person owner;
	unsigned registrationYear;

	void copy(const Car& other)
	{
		strcpy(this->brand, other.brand);
		this->owner = other.owner;
		this->registrationYear = other.registrationYear;
	}
public:
	Car() = default;
	Car(const char* brand, const Person& owner, const unsigned& rYear)
	{
		if (brand == nullptr || strlen(brand) > 127 || rYear < 1800)
		{
			throw std::invalid_argument("Invalid car data");
		}
		strcpy(this->brand, brand);
		this->owner = owner;
		this->registrationYear = rYear;
	}
	Car(const Car& other)
	{
		copy(other);
	}
	Car& operator=(const Car& other)
	{
		if (this != &other)
		{
			copy(other);
		}
		return *this;
	}
	~Car() = default;

	const char* getBrand()const
	{
		return this->brand;
	}

	void saveInFile(const char* fileName)
	{
		std::ofstream out(fileName,std::ios::app);
		if (!out.is_open())
		{
			throw std::out_of_range("Can not open file");
		}
		this->owner.saveInFile(fileName);
		out << this->brand << " " << this->registrationYear << '\n';

		out.close();
	}
	Car readFromFile(const char* fileName)
	{
		std::ifstream in(fileName);
		if (!in.is_open())
		{
			throw std::out_of_range("Can not open file");
		}
		unsigned pos = 0;
		Person owner = this->owner.readFromFile(fileName, pos);
		in.seekg(pos);

		if (in.peek() == ' ' || in.peek() == '\t')
		{
			in.get();
		}

		char buffer[128];
		in.getline(buffer, 128, ' ');
		char brand[128];
		strcpy(brand, buffer);
		
		if (in.peek() == ' ' || in.peek() == '\t')
		{
			in.get();
		}
		unsigned rYear;
		in >> rYear;
	
		Car car(brand, owner, rYear);
	
		in.close();
		
		return car;
	}

};


void writeCarsToFile(Car* cars, unsigned size, const char* fileName)
{
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	for (unsigned i = 0; i < size; i++)
	{
		cars[i].saveInFile(fileName);
	}
	out.close();
}
unsigned findNumberOfCars(const char* fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	unsigned cnt = 0;
	while (!in.eof())
	{
		char buffer[1024];
		in.getline(buffer, 1024, '\n');
		cnt++;
	}
	in.close();
	return cnt;
}
Car* readCars(const char* fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	unsigned size = findNumberOfCars(fileName);
	in.seekg(0);
	Car* cars = new Car[size];
	for (unsigned i = 0; i < size; i++)
	{
		cars[i] = cars[i].readFromFile(fileName);
	}
	in.close();
	return cars;
}

int main()
{
	Car c1("audi", Person("Frosina", "Mulachka", Gender::FEMALE, 2002), 2020);
	Car c2("seat", Person("Frosina", "Mulachka", Gender::FEMALE, 2002), 2020);
	Car c3("bugatti", Person("Frosina", "Mulachka", Gender::FEMALE, 2002), 2020);

	Car* cars = new Car[3];
	cars[0] = c1;
	cars[1] = c2;
	cars[2] = c3;


	writeCarsToFile(cars,3,"cars.txt");
	delete[]cars;
	return 0;
}


