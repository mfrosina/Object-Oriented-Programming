#include "UsersDatFile.h"

unsigned UsersDatFile::findNumberOfSavedUsers()
{
	std::ifstream binFile(FILE_NAME, std::ios::binary);
	if (!binFile.is_open())
	{
		std::cout << "Error: users.dat file can not be opened! There are not existing users in the system.\n";
		return 0;
	}
	binFile.seekg(0, std::ios::end);
	unsigned usersNumber = binFile.tellg() / sizeof(User);
	binFile.close();
	return usersNumber;
}
User* UsersDatFile::readUsersFromFile()
{
	std::ifstream binFile(FILE_NAME, std::ios::binary);
	if (!binFile.is_open())
	{
		std::cout << "Error: users.dat file can not be opened!\n";
		return{};
	}
	User readUsers[512];
	unsigned usersNumber = findNumberOfSavedUsers();
	for (unsigned i = 0; i < usersNumber; i++)
	{
		binFile.read((char*)&readUsers[i], sizeof(User));
	}
	binFile.close();
	return readUsers;
}
bool UsersDatFile::addUserToFile(const User& user)
{
	std::ofstream binFile(FILE_NAME, std::ios::binary | std::ios::app);
	if (!binFile.is_open())
	{
		std::cout << "Error: users.dat file can not be opened!\n";
		return false;
	}
	binFile.write((const char*)&user, sizeof(User));
	binFile.close();
	return true;
}

bool UsersDatFile::removeUserFromFile(const char* name)
{
	unsigned usersNumber = findNumberOfSavedUsers();
	User users[512];
	std::fstream in(FILE_NAME, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		std::cout << "Error: users.dat file can not be opened!\n";
		return false;
	}
	for (unsigned i = 0; i < usersNumber; i++)
	{
		in.read((char*)&users[i], sizeof(User));
	}
	in.close();

	std::ofstream out(FILE_NAME, std::ios::out | std::ios::binary);
	if (!out.is_open())
	{
		std::cout << "Error: users.dat file can not be opened!\n";
		return false;
	}
	for (unsigned i = 0; i < usersNumber; i++)
	{
		if (strcmp(users[i].name,name) != 0)
		{
			out.write((const char*)&users[i], sizeof(User));
		}
	}
	out.close();
	return true;
}