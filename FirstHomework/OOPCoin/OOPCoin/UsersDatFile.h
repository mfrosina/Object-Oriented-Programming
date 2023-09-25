#pragma once

#ifndef USERSDATFILE_H
#define USERSDATFILE_H


#include <fstream>
#include <cstring>
#include "User.h"

struct User; 

struct UsersDatFile
{
private:
	constexpr static const char FILE_NAME[16] = "users.dat";

public:
	static unsigned findNumberOfSavedUsers();
	static User* readUsersFromFile();
	static bool addUserToFile(const User&);
	static bool removeUserFromFile(const char* name);
};

#endif // !USERSDATFILE_H