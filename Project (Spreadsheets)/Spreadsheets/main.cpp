#include <iostream>
#include "Interaction.h"

int main()
{
	Interaction* interaction = new (std::nothrow) Interaction();
	std::cout << "Program initiated!\n";

	while (interaction->isActive()) {
		std::cout << "\nEnter a command: Type 'help' to view available commands. \n";
		interaction->executeCommand();
	}
	delete interaction;
	return 0;
}