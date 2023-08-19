#include <iostream>
#include "Comic.h"
#include "Library.h"

int main()
{
	//PublishedEdition* p1 = new Periodical("Time", "Covers current events and politics from around the world", 2002, Periodicity::MONTHLY, 3);
	//PublishedEdition* c1 = new Comic("The Amazing Spider-Man", "Follows the adventures of Peter Parker, a high school student who gains superhuman powers", 2004, "Stan Lee", "Marvel Comics", Periodicity::MONTHLY, 4);
	//PublishedEdition* b1 = new Book("The Great Gatsby", "Novel widely regarded as a classic of American literature", 1923, "F.Scott Fitzgerald", "Charles Scribner's Sons");
	//PublishedEdition* b2 = new Book("The Lord of the Rings", "Epic fantasy novel series", 1950, "J.R.R. Tolkien", "Unwin");
	//PublishedEdition* p2 = new Periodical("Scientific American", "Covers a wide range of scientific topics, including physics, chemistry, and biology", 2014, Periodicity::WEEKLY, 1);
	//PublishedEdition* c2 = new Comic("Comicar", "Comics with magionics", 2001, "Polkovski S.", "ComComHaus", Periodicity::WEEKLY, 1);
	//PublishedEdition* b3 = new Book("To Kill a Mockingbird", "Seminal novel addressing racial inequality and injustice in the American South", 1960, "Harper Lee", "J. B. Lippincott & Co.");

	Library* library = new Library();

	//testing addPublishedEdition method
	//library->addPublishedEdition(p1, 3);
	//library->addPublishedEdition(c1, 1);
	//library->addPublishedEdition(b1, 2);
	//
	//library->addPublishedEdition(p2, 1);
	//library->addPublishedEdition(c2, 1);
	//library->addPublishedEdition(b2, 1);
	//library->addPublishedEdition(b3, 1);
	 
	////testing addUser method
	//User* user1 = new User("Sarah Johnson");
	//User* user2 = new User("John Smith");
	//User* user3 = new User("David Lee");
	//User* user4 = new User("Frosina Mulachka");
	//library->addUser(user1);
	//library->addUser(user2);
	//library->addUser(user3);
	//library->addUser(user4);

	library->publishedEditionsSortedInfo();
	std::cout << std::endl;

	//library->takePublishedEdition("Sarah Johnson", 1);
	//library->takePublishedEdition("Sarah Johnson", 2);
	//library->takePublishedEdition("John Smith", 3);
	//library->takePublishedEdition("Frosina Mulachka", 4);
	// 
	//library->returnPublishedEdition("Sarah Johnson", 2);
	//library->removePublishedEdition(3);
	//library->removeUser("John Smith");

	library->userInfoSortedByNumberOfReadings();
	std::cout << std::endl;

	library->userInfoWithTakenPEs(4);
	std::cout << std::endl;

	library->userInfoWithTakenPEs(7);
	return 0;
}
