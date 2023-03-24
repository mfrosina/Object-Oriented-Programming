// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cassert>
/*TASK1
Гошо е най-големият купонджия в Студентски град - за него е по-важно да посещава редовно участията на любимите си изпълнители по
дискотеките, отколкото да посещава лекции и упражнения (на кого са му притрябвали ООП и Алгебра...). 
Гошо иска да си направи систематизиран график за текущата седмица, с помощта на който никога няма да пропусне участие 
(ако някога случайно изтърве участие на Галена, няма да може да си го прости). 
Помогнете му, като реализирате структура Performance, която съдържа име на изпълнител и място на участието 
(символни низове, заделени с точна големина), както и ден от седмицата, в който ще бъде участието. 
За да представите деня от седмицата, създайте подходящ изброим тип.

Бонус: Създайте масив от участия за текущата седмица и го сортирайте според деня от седмицата.*/

const std::size_t MAX_SIZE = 256;

enum DayOfTheWeek
{
	UNKNOWN,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
	COUNTER
};

struct Performance
{
	char* singerName;
	char* place;
	DayOfTheWeek day;

};

bool init(Performance& perf, const char* singer, const char* place, const DayOfTheWeek day)
{
	perf.singerName = new (std::nothrow) char[strlen(singer) + 1];
	if (!perf.singerName)
	{
		return false;
	}
	strcpy(perf.singerName, singer);
	perf.place = new (std::nothrow) char[strlen(place) + 1];
	if (!perf.place)
	{
		return false;
	}
	strcpy(perf.place, place);
	if (day <= DayOfTheWeek::UNKNOWN || day >= DayOfTheWeek::COUNTER)
	{
		delete[]perf.singerName;
		delete[]perf.place;
		return false;
	}
	perf.day = day;
	return true;
}
void deallocate(Performance* perf, std::size_t size)
{
	for (int i = 0; i < size; i++)
	{
		delete[]perf[i].singerName;
		delete[]perf[i].place;
	}
	delete[]perf;
}
void printWeekDay(DayOfTheWeek weekDay)
{
	assert(weekDay != DayOfTheWeek::UNKNOWN && weekDay != DayOfTheWeek::COUNTER);

	switch (weekDay)
	{
	case DayOfTheWeek::MONDAY:
		std::cout << "Monday";
		return;
	case DayOfTheWeek::TUESDAY:
		std::cout << "Tuesday";
		return;
	case DayOfTheWeek::WEDNESDAY:
		std::cout << "Wednesday";
		return;
	case DayOfTheWeek::THURSDAY:
		std::cout << "Thursday";
		return;
	case DayOfTheWeek::FRIDAY:
		std::cout << "Friday";
		return;
	case DayOfTheWeek::SATURDAY:
		std::cout << "Saturday";
		return;
	case DayOfTheWeek::SUNDAY:
		std::cout << "Sunday";
		return;
	}
}
void printPerformance(const Performance& performance)
{
	std::cout << performance.singerName << " " << performance.place << " ";
	printWeekDay(performance.day);
}

void sortArray(Performance*& perf, std::size_t size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (perf[i].day > perf[j].day)
			{
				Performance temp = perf[i];
				perf[i] = perf[j];
				perf[j] = temp;
			}
		}
	}
}
int main()
{
	//task1
	std::size_t size;
	std::cout << "Enter number of performances:\n";
	std::cin >> size;
	std::cin.ignore();

	Performance* perf = new Performance[size];
	char singer[MAX_SIZE];
	char place[MAX_SIZE];
	int day;
	for (std::size_t i = 0; i < size; i++)
	{
		std::cout << "Enter the name of the singer:\n";
		std::cin.getline(singer, MAX_SIZE);

		std::cout << "Enter the name of the place:\n";
		std::cin.getline(place, MAX_SIZE);

		std::cout << "Enter day of the week with numbers from 1-7:\n";
		std::cin >> day;
		std::cin.ignore();

		if (!init(perf[i], singer, place, (DayOfTheWeek)(day)))
		{
			std::cout << "Problem occured\n";
			deallocate(perf, i);
			return 1;
		}
	}
	for (std::size_t i = 0; i < size; i++)
	{
		printPerformance(perf[i]);
		std::cout << std::endl;
	}
	sortArray(perf, size);
	for (std::size_t i = 0; i < size; i++)
	{
		printPerformance(perf[i]);
		std::cout << std::endl;
	}

	deallocate(perf, size);
	return 0;
}

