#pragma once
#include "PublishedEdition.h"

enum Periodicity
{
	UNKNOWN = -1,
	WEEKLY,
	MONTHLY,
	ONCEAYEAR
};

const char* convertToStr(const Periodicity& p);
Periodicity convertPeriodicityToEnum(const char* p);

class Periodical : virtual public PublishedEdition
{
protected:
	Periodicity periodicity;
	unsigned number;

	void copy(const Periodical& other);
public:
	Periodical();
	Periodical(const char* _title, const char* _description, const unsigned _yearOfPublishing, const Periodicity& _periodicity, const unsigned _number);
	Periodical(const Periodical& other);
	Periodical& operator=(const Periodical& other);
	~Periodical();

	void saveInFile(const char* fileName);

	const unsigned getNumber()const;

	PublishedEdition* clone()const override;
};
