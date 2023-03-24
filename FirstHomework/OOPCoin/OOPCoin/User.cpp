#include "User.h"
#include "Transaction.h"
#include "TransactionBlock.h"


const char IDS_FILE_NAME[28] = "unique-user-ids.txt";
unsigned numberOfUsers = 0;
User users[512];


unsigned generateUserID()
{
	std::ifstream idsIn(IDS_FILE_NAME);
	if (!idsIn.is_open())
	{
		std::cout << "Can not assign unique id to the user.\n";
		return 0;
	}
	unsigned id;
	idsIn >> id;
	id += 1;
	idsIn.close();

	std::ofstream idsOut(IDS_FILE_NAME);
	if (!idsOut.is_open())
	{
		std::cout << "Can not assign unique id to the user.\n";
		return 0;
	}
	idsOut << id;
	idsOut.close();

	return id;
}

void createSystemUser()
{
	User user;
	strcpy(user.name, "SystemUser");
	user.id = 0;
	users[numberOfUsers++] = user;

	std::ofstream idsOut(IDS_FILE_NAME);
	idsOut << user.id;
	idsOut.close();

	UsersDatFile::addUserToFile(user);
}
bool createUser(const char* name, const double investment)
{
	if (name == nullptr || strlen(name) >= 128)
	{
		std::cout << "Invalid name for user!\n";
		return false;
	}
	unsigned id = generateUserID();
	if (id == 0)
	{
		return false;
	}
	User user;
	user.id = id;
	strcpy(user.name, name);
	users[numberOfUsers] = user;
	numberOfUsers++;

	sendCoins("SystemUser", name, investment);
	if (UsersDatFile::addUserToFile(user))
	{
		std::cout << "Saved changes in file! (user is saved)\n";
	}
	else
	{
		std::cout << "There are unsaved changes in file! (user not saved)\n";
	}
	
}

bool existsUser(const char* name, User& user)
{
	if (name == nullptr || strlen(name) >= 128)
	{
		return false;
	}
	for (unsigned i = 0; i < numberOfUsers; i++)
	{
		if (strcmp(users[i].name, name) == 0)
		{
			user = users[i];
			return true;
		}
	}
	return false;
}

bool removeUser(const char* name)
{
	if (name == nullptr || strcmp(name,"SystemUser") == 0)
	{
		std::cout << "Invalid name for user and can not be removed!\n";
		return false;
	}
	User user;
	if (!existsUser(name, user))
	{
		std::cout << "User with the entered name does not exist and can not be removed!\n";
		return false;
	}
	for (unsigned i = 0; i < numberOfUsers; i++)
	{
		if (users[i].id == user.id)
		{
			double oopCoins = getUserCoins(user.id);
			sendCoins(user.name, "SystemUser",oopCoins);
			unsigned ind = i + 1;
			if (ind == numberOfUsers)
			{
				users[ind - 1] = users[ind];
			}
			else {
				for (unsigned j = i + 1; j <= numberOfUsers; j++)
				{
					users[j - 1] = users[j];
					i++;
				}
			}
		}
	}
	numberOfUsers--;
	if(UsersDatFile::removeUserFromFile(user.name))
	{
		std::cout << "Saved changes in file! (user is removed)\n";
	}
	else
	{
		std::cout << "There are unsaved changes in file! (user not removed)\n";
	}
	return true;
}

void print()
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		std::cout << users[i].name << " " << users[i].id << "\n";
	}
}

void swapUsers(User& user1, User& user2)
{
	User temp = user1;
	user1 = user2;
	user2 = temp;
}
void sortUsersByWealth()
{
	for (unsigned i = 0; i < numberOfUsers; i++)
	{
		for (unsigned j = i + 1; j < numberOfUsers; j++)
		{
			if (getUserCoins(users[i].id) < getUserCoins(users[j].id))
			{
				swapUsers(users[i], users[j]);
			}
		}
	}
}

void wealthiestUsers(unsigned number)
{
	if (number > numberOfUsers)
	{
		std::cout << "Too big number is entered. There are not that much users in the system!\n";
		return;
	}
	sortUsersByWealth();
	long long now = time(NULL);
	char time[128];
	sprintf(time, "%lld", now);
	char fileName[256];
	strcpy(fileName, "wealthiest-users-");
	strcat(fileName, time);
	strcat(fileName, ".txt");
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		std::cout << "Error: can not open txt file\n";
		return;
	}
	for (unsigned i = 0; i < number; i++)
	{
		if (users[i].id == 0)// skip the SystemUser, suppose that he can not be the wealthiest
		{
			number++;
			continue;
		}
		double userCoins = getUserCoins(users[i].id);
		std::cout << "UserName: " << users[i].name << " Coins: " << userCoins << std::endl;
		out << "UserName: " << users[i].name << " Coins: " << userCoins << '\n';
	}
	out.close();
}

void addUsers(const User* usersToAdd, const unsigned size)
{
	unsigned i;
	for (i = 0; i < size; i++)
	{
		users[numberOfUsers++] = usersToAdd[i];
	}
}

