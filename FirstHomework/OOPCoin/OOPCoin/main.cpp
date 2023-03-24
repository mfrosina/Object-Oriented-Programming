#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "User.h"
#include "Transaction.h"
#include "TransactionBlock.h"
#include "Command.h"

int main()
{

	unsigned numberOfExistingUsers = UsersDatFile::findNumberOfSavedUsers();
	if (numberOfExistingUsers == 0)
	{
		createSystemUser();
	}
	else if(numberOfExistingUsers > 1)
	{
		User* readedUsers = new User[numberOfExistingUsers];
		readedUsers = UsersDatFile::readUsersFromFile();
		addUsers(readedUsers, numberOfExistingUsers);

		unsigned numberOfExistingBlocks = BlocksDatFile::findNumberOfSavedBlocks();
		TransactionBlock* readedBlocks = new TransactionBlock[numberOfExistingBlocks];
		readedBlocks = BlocksDatFile::readBlocksFromFile();
		addBlocks(readedBlocks, numberOfExistingBlocks);
	}
	std::cout << "Enter one of the following commands:\n";
	Command::executeCommand("help");
	char cmd[128];
	do
	{
		std::cin.getline(cmd, 128);
		Command::executeCommand(cmd);

		if(strcmp(cmd,"exit") != 0)
			std::cout << "Enter command. Type <help> for help; <exit> to exit the program...\n";

	} while (strcmp(cmd, "exit") != 0);

	return 0;
}
