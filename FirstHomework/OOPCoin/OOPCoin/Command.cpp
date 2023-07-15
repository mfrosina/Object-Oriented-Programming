#include "Command.h"

void Command::createUserCmd()
{
	char name[128];
	double investment;
	std::cout << "Enter the name for the new user:\n";
	std::cin.getline(name, 128);
	std::cout << "Enter the amount of investment:\n";
	std::cin >> investment;
	std::cin.ignore();
	if (createUser(name, investment))
	{
		std::cout << "Successfully created user with name: " << name << "\n";
	}
	else
	{
		std::cout << "Can not create user...Try again!\n";
	}
}
void Command::removeUserCmd()
{
	char name[128];
	std::cout << "Enter the name for the user to be removed:\n";
	std::cin.getline(name, 128);
	if (removeUser(name))
	{
		std::cout << "Successfully removed user with name: " << name << "\n";
	}
	else
	{
		std::cout << "Can not remove user...Try again!\n";
	}
}
void Command::sendCoinsCmd()
{
	unsigned from;
	unsigned to;
	double amount;
	std::cout << "Enter the ID of the user who wants to send money:\n";
	std::cin >> from;
	std::cout << "Enter the ID of the user who will receive money:\n";
	std::cin >> to;
	std::cout << "Enter the amount of money:\n";
	std::cin >> amount;
	std::cin.ignore();
	if (from == 0 || to == 0)
	{
		std::cout << "Can not send or receive money from the system user. Try again with valid user ID!\n";
		return;
	}
	if (sendCoins(from, to, amount))
	{
		std::cout << "Successful transaction!\n";
	}
	else
	{
		std::cout << "Unsuccessful transaction!\n";
	}
}
void Command::verifyTransactionsCmd()
{
	int result = verifyTransactions();
	if (result == -1)
	{
		std::cout << "Correct transaction blocks!\n";
	}
	else
	{
		std::cout << "Transaction block with ID " << result << " is incorrect!\n";
	}
}
void Command::wealthiestUsersCmd()
{
	unsigned n;
	std::cout << "Enter positive number:\n";
	std::cin >> n;
	std::cin.ignore();
	if (wealthiestUsers(n))
	{
		std::cout << "First " << n << " wealthiest users successfully saved in txt file!\n";
	}
	else
	{
		std::cout << "Error while trying to find the first " << n << " wealthiest users.\n";
	}
}
void Command::biggestBlocksCmd()
{
	unsigned n;
	std::cout << "Enter positive number:\n";
	std::cin >> n;
	std::cin.ignore();
	if (biggestBlocks(n))
	{
		std::cout << "First " << n << " biggest blocks successfully saved in txt file!\n";
	}
	else
	{
		std::cout << "Error while trying to find the first " << n << " biggest blocks.\n";
	}
}

void Command::helpCmd()
{
	std::cout << "-------------------------------------------------------------------------------------------------------------\n";
	std::cout << "create-user(user-name,investment)			-> creates new user\n";
	std::cout << "remove-user(user-name)					-> removes user\n";
	std::cout << "send-coins(from-user,to-user,investment)		-> sends coins <from-user> <to-user>\n";
	std::cout << "verify-transactions()					-> verifies all of the transactions\n";
	std::cout << "wealthiest-users(number)				-> creates txt file with <number> wealthiest users\n";
	std::cout << "biggest-blocks(number)					-> creates txt file with <number> biggest blocks\n";
	std::cout << "exit()							-> exits the program\n";
	std::cout << "-------------------------------------------------------------------------------------------------------------\n";

}

void Command::exitCmd()
{
	std::cout << "Exiting the program... Bye!\n";

}
void Command::executeCommand(const char* cmd)
{
	if (cmd == nullptr)
	{
		std::cout << "Invalid cmd name!\n";
		return;
	}
	if (strcmp(cmd, "help") == 0)
	{
		helpCmd();
	}
	else if (strcmp(cmd, "create-user") == 0)
	{
		createUserCmd();
	}
	else if (strcmp(cmd, "remove-user") == 0)
	{
		removeUserCmd();
	}
	else if (strcmp(cmd, "send-coins") == 0)
	{
		sendCoinsCmd();
	}
	else if (strcmp(cmd, "verify-transactions") == 0)
	{
		verifyTransactionsCmd();
	}
	else if (strcmp(cmd, "wealthiest-users") == 0)
	{
		wealthiestUsersCmd();
	}
	else if (strcmp(cmd, "biggest-blocks") == 0)
	{
		biggestBlocksCmd();
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		exitCmd();
	}
	else
	{
		std::cout << "Invalid command!\n";
	}
}