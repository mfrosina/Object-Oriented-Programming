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
bool removeUser(const char* name);

void print(); //to test

void swapUsers(User& user1, User& user2);
void sortUsersByWealth();

void wealthiestUsers(unsigned number);

void addUsers(const User* usersToAdd, const unsigned size);

#endif // !USER_H

