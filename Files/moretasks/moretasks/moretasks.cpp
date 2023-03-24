// moretasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

/*Да се създаде структура pair, която представя наредена двойка от естествени числа.
Да се създаде структура, която представя релация. В релацията има най-много 25 наредени двойки и структурата пази текущия си размер.
Да се създаде функция writeRelationToFile(...), която записва релацията във файл с име "relation.txt"и readRelationFromFile(...), която чете релацията от файла.
Следните функции ще ви бъдат полезни:

CreatePair()
initPair()
readPairFromFile()
writePairToFile()
addPairToRelation()*/


const size_t MAX_PAIR_SIZE = 25;
const size_t BUFFER_SIZE = 256;

struct Pair
{
	int x;
	int y;
};
struct Relation
{
	Pair pairs[MAX_PAIR_SIZE];
	size_t currentSize;
};
Pair initPair(const int& x, const int& y)
{
	Pair pair{ x,y };
	return pair;
}

Pair createPair()
{
	std::cout << "Enter two numbers:\n";
	int n1, n2;
	std::cin >> n1 >> n2;
	return initPair(n1, n2);
}
void writePairToFile(const Pair& pair, const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		std::cout << "Error\n";
		return;
	}
	out << pair.x << " " << pair.y;
	out << '\n';
	out.close();
}
Pair readPairFromFile(std::ifstream& in)
{
	if (!in.is_open())
	{
		std::cout << "Error\n";
		return Pair{};
	}
	int x, y;
	in >> x >> y;
	Pair pair{ x,y };
	return pair;
}
void addPairToRelation(const Pair& pair, Relation& rel)
{
	size_t size = rel.currentSize;
	if (size >= MAX_PAIR_SIZE)
	{
		std::cout << "Cannot add\n";
		return;
	}
	rel.pairs[size] = pair;
	rel.currentSize++;
}

void writeRelationToFile(const Relation& rel, const char* fileName)
{
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		std::cout << "Error\n";
		return;
	}
	for (size_t i = 0; i < rel.currentSize; i++)
	{
		writePairToFile(rel.pairs[i], fileName);
	}
	out.close();
}
size_t countFileLines(const char* fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		std::cout << "Error\n";
		return 0;
	}
	size_t count = 0;
	char buff[BUFFER_SIZE];
	while (in.getline(buff, BUFFER_SIZE))
	{
		count++;
	}
	in.close();
	return count;
}
Relation readRelationFromFile(const char* fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		std::cout << "Error\n";
		return Relation{};
	}
	size_t size = countFileLines(fileName);
	Relation relation{};
	for (int i = 0; i < size; i++)
	{
		Pair pair = readPairFromFile(in);
		addPairToRelation(pair, relation);
	}
	in.close();
	return relation;
}
void printPair(const Pair& p)
{
	std::cout << p.x << " " << p.y << std::endl;
}
void printRelation(const Relation& rel)
{
	for (int i = 0; i < rel.currentSize; i++)
	{
		printPair(rel.pairs[i]);
	}
}

/*Реализирайте структура User, която да съдържа име, имейл и парола на даден потребител. Всяко поле е с максимална дължина 128 символа. Създайте възможност за записване и четене на потребител в текстов файл.

Реализирайте структура System, която има масив от User-и. Системата поддържа максимално 100 потребители. Създайте методи за запазване и прочитане на обект от тип System от файл. (Помислете за подходящ формат за записването на данните)

Имплементирайте проста login система, която поддържа възможност за регистриране на нов потребител и вход в системата.

След спиране на програмата и повторно пускане, трябва да се запази възможността вече регистрирани потребители да влизат в системата с имейла и паролата си.*/

const size_t MAX_FIELD_SIZE = 128;
const size_t MAX_USER_SIZE = 100;
struct User
{
	char* name;
	char* email;
	char* pw;
};
User initUser(const char* name, const char* email,
		const char* pw)
{
	if (name == nullptr ||
		email == nullptr 
		|| pw == nullptr || 
		strlen(name) > MAX_FIELD_SIZE ||
		strlen(email) > MAX_FIELD_SIZE ||
		strlen(pw) > MAX_FIELD_SIZE)
	{
		throw std::invalid_argument("Invalid input");
	}
	User user{};
	user.name = new char[strlen(name) + 1];
	if (!user.name)
	{
		throw std::invalid_argument("Invalid input");
	}
	strcpy(user.name, name);
	user.email = new char[strlen(email) + 1];
	if (!user.email)
	{
		throw std::invalid_argument("Invalid input");
	}
	strcpy(user.email, email);
	user.pw = new char[strlen(pw) + 1];
	if (!user.pw)
	{
		throw std::invalid_argument("Invalid input");
	}
	strcpy(user.pw, pw);
	return user;
}
void writeUserToFile(const User& user, const char* fileName)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out.is_open())
	{
		std::cout << "Error\n";
		return;
	}
	out.write(user.name, strlen(user.name));
	out << " - ";
	out.write(user.email, strlen(user.email));
	out << " - ";
	out.write(user.pw, strlen(user.pw));
	out << '\n';
	out.close();
}

User readUserFromFile(std::ifstream& in)
{
	if (!in.is_open())
	{
		throw std::invalid_argument("Error");
	}
	User user{};
	char* name = new char[MAX_FIELD_SIZE];
	in >> name;
	if (in.peek() == ' ')
	{
		in.get();
	}
	if (in.peek() != '-')
	{
		char* familyName = new char[MAX_FIELD_SIZE];
		in >> familyName;
		if (familyName != nullptr)
		{
			user.name = new char[strlen(name) + strlen(familyName) + 2];
			strcpy(user.name, name);
			strcat(user.name, " ");
			strcat(user.name, familyName);
		}
	}
	else
	{
		in.get();
		if (name != nullptr)
		{
			user.name = new char[strlen(name) + 1];
			strcpy(user.name, name);
		}
		else
		{
			throw std::invalid_argument("Error");
		}
	}
	if (in.peek() == ' ')
	{
		in.get();
	}
	if (in.peek() == '-')
	{
		in.get();
	}
	if (in.peek() == ' ')
	{
		in.get();
	}
	char* email = new char[MAX_FIELD_SIZE];
	in >> email;
	if (email != nullptr)
	{
		user.email = new char[strlen(email) + 1];
		strcpy(user.email, email);
	}
	else
	{
		throw std::invalid_argument("Error");
	}
	if (in.peek() == ' ')
	{
		in.get();
	}
	if (in.peek() == '-')
	{
		in.get();
	}
	if (in.peek() == ' ')
	{
		in.get();
	}
	char* pw = new char[MAX_FIELD_SIZE];
	in >> pw;
	if (pw != nullptr)
	{
		user.pw = new char[strlen(pw) + 1];
		strcpy(user.pw, pw);
	}
	else
	{
		throw std::invalid_argument("Error");
	}
	return user;
}
void printUser(const User& user)
{
	std::cout << user.name << " " << user.email <<
		" " << user.pw << "\n";
}
struct System
{
	User users[MAX_USER_SIZE];
	size_t size;
};
void addUser(const User& user, System& sys)
{
	if (sys.size >= MAX_USER_SIZE)
	{
		throw std::out_of_range("Cannot add");
	}
	sys.users[sys.size] = user;
	sys.size++;
}
void writeToFile(const System& sys, const char* fileName)
{
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		throw std::invalid_argument("Cannot open file");
	}
	for (int i = 0; i < sys.size; i++)
	{
		writeUserToFile(sys.users[i], fileName);
	}
	out.close();
}
System readFromFile(const char* fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		throw std::invalid_argument("Error");
	}
	System sys{};
	int count = countFileLines(fileName);
	for (size_t i = 0; i < count; i++)
	{
		User user = readUserFromFile(in);
		addUser(user, sys);
	}
	sys.size = count;
	in.close();
	return sys;
}
void printSystem(const System& sys)
{
	for (int i = 0; i < sys.size; i++)
	{
		printUser(sys.users[i]);
	}
}
int main()
{
	//Relation rel{};
	//for (int i = 0; i < 3; i++)
	//{
	//	Pair pair = createPair();
	//	addPairToRelation(pair, rel);
	//}
	//writeRelationToFile(rel, "pairs.txt");
	//Relation readedRel = readRelationFromFile("pairs.txt");
	//printRelation(readedRel);

	User user = initUser("Frosina Mulachka",
		"frosinaaa@yahoo.com", "frossss");
	User user1 = initUser("Ana Milev", "amil@gmail.com",
		"milevvv");
	User user2 = initUser("Joana K", "joni@gmail.com",
		"joaaaaakkheheh8282");
	System sys{};
	addUser(user, sys);
	addUser(user1, sys);
	addUser(user2, sys);
	//writeToFile(sys,"system.txt");
	System read = readFromFile("system.txt");
	printSystem(read);
	return 0;
}

