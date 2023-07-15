#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef USER_H
#define USER_H


#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>

#include "UsersDatFile.h"

struct User {
	unsigned id;
	char name[128];
};

unsigned generateUserID();
void createSystemUser();

bool createUser(const char* name, const double investment);
bool existsUser(const char* name, User& user);
bool existsUserById(const unsigned id);
bool removeUser(const char* name);

void swapUsers(User& user1, User& user2); //helper function to find the wealthiest users
void sortUsersByWealth(); //helper function to find the wealthiest users

bool wealthiestUsers(unsigned number);

void addUsers(const User* usersToAdd, const unsigned size);

#endif // !USER_H

