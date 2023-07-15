#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <cstring>
#include "User.h"
#include "TransactionBlock.h"

struct Command
{
private:
	static void createUserCmd();
	static void removeUserCmd();
	static void sendCoinsCmd();
	static void verifyTransactionsCmd();
	static void wealthiestUsersCmd();
	static void biggestBlocksCmd();
	static void helpCmd();
	static void exitCmd();

public:
	static void executeCommand(const char* cmd);	
};


#endif // !COMMANDS_H

