// ZUZI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*Всички сме чували за информационната система на IMF - ZUZI.
Имплементирайте модул от ZUZI, който трябва да се грижи

за обработката и съхраняването на информация за избираемите дисциплини.

Една избираема дисциплина трябва да съдържа следната информация:

ID
Име
Категория - {OKN, M, PM, PR, Other}
Брой кредити, които носи.
Вид на изпита - { Exam, Course Project, Test }
Обърнете внимание, че изпитът на една дисциплина може да бъде и съчетание от горните три.
От конзолата да се приема път към файл, в който ще се записват данните.

Важно условие е форматът на файла да бъде CSV.

Първият ред трябва да съдържа заглавните полета (атрибути).

За CSV (comma-separated values) формата може да прочетете повече тук: 

Модулът трябва да покрива минимално следните изисквания:

Данните да могат да се съхраняват в подходящ файл.
Данните да могат да се зареждат от подходящ файл.
Да може да се добавя избираема дисциплина.
Ако подаденото ID на дисциплина вече е заето, то да се презаписва информацията за старата дисциплина.
Да може да се премахва избираема дисциплина по ID.
Възможност за извършване на следните справки:
Търсене на избираема дисциплина по ID и отпечатване.
Да се извеждат всички избираеми дисциплини по селектирана категория.
Да се извеждат всички избираеми дисциплини по даден затворен интервал [minC, maxC], където minC e минимален брой кредити, а maxC е максимален брой кредити, които избираемата носи.*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

const size_t MAX_SIZE = 256;
enum Category
{
    UNKNOWN = -1,
    OKN,
    M,
    PM,
    PR,
    OTHER,
    COUNTER
};
enum ExamType
{
    UNKNOWN1 = -1,
    EXAM,
    COURSE_PROJECT,
    TEST,
    ECT,
    COUNTER1
};

struct ElectiveDiscipline
{
    size_t id;
    char* name;
    Category category;
    size_t credits;
    ExamType examType;

};

ElectiveDiscipline init(size_t id, const char* name, const Category& cat,
    const size_t& credits, const ExamType& examType)
{
    if (name == nullptr)
    {
        throw std::invalid_argument("Invalid input");
    }
    ElectiveDiscipline elective{};
    elective.id = id;
    elective.name = new char[strlen(name) + 1];
    strcpy(elective.name, name);
    elective.category = cat;
    elective.credits = credits;
    elective.examType = examType;
    return elective;
}
void findCategory(const Category& cat, std::ostream& out)
{
    switch (cat)
    {
    case 0: out << "OKN" << ", "; break;
    case 1: out << "M" << ", "; break;
    case 2: out << "PM" << ", "; break;
    case 3: out << "PR" << ", "; break;
    case 4: out << "Other" << ", "; break;
    }
}
void findExamType(const ExamType& type, std::ostream& out)
{
    switch (type)
    {
    case 0: out << "Exam"; break;
    case 1: out << "Course_Project"; break;
    case 2: out << "Test"; break;
    case 3: out << "Exam-CourseProject-Test"; break;
    }
}
char* modifiedChar(char* str)
{
    int size = strlen(str) - 1;
    char* newStr = new char[size + 1];
    int i;
    for (i = 0; i < size; i++)
    {
        newStr[i] = str[i];
    }
    newStr[i] = '\0';
    delete[]str;
    return newStr;
}
void writeToFile(const ElectiveDiscipline& elDisc, const char* fileName)
{
    std::ofstream out(fileName);
    if (!out.is_open())
    {
        throw std::invalid_argument("Cannot open");
    }
    out << elDisc.id << ", " << elDisc.name << ", ";
    findCategory(elDisc.category, out);
    out << elDisc.credits << ", ";
    findExamType(elDisc.examType, out);
    out << "\n";
}
Category findCategoryFromGivenStr(const char* cat)
{
    if (strcmp(cat, "OKN"))
    {
        return Category::OKN;
    }
    else if (strcmp(cat, "M"))
    {
        return Category::M;
    }
    else if (strcmp(cat, "PM"))
    {
        return Category::PM;
    }
    else if (strcmp(cat, "PR"))
    {
        return Category::PR;
    }
    else if (strcmp(cat, "Other"))
    {
        return Category::OTHER;
    }
}
ExamType findTypeFromGivenStr(const char* cat)
{
    if (strcmp(cat, "Exam") == 0)
    {
        return ExamType::EXAM;
    }
    else if (strcmp(cat, "Course_Project") == 0)
    {
        return ExamType::COURSE_PROJECT;
    }
    else if (strcmp(cat, "Test") == 0)
    {
        return ExamType::TEST;
    }
    else if (strcmp(cat, "Exam-CourseProject-Test") == 0)
    {
        return ExamType::ECT;
    }
    
}
ElectiveDiscipline readFromFile(const char* fileName)
{
    std::ifstream in(fileName);
    if (!in.is_open())
    {
        throw std::invalid_argument("Cannot open");
    }
    ElectiveDiscipline elective{};
    size_t id;
    in >> id;
    elective.id = id;
    if (in.peek() == ',')
    {
        in.get();
    }
    char* name = new char[MAX_SIZE];
    in >> name;
    if (name == nullptr)
    {
        throw std::invalid_argument("Nullptr");
    }
    char* modName = modifiedChar(name);
    elective.name = new char[strlen(modName) + 1];
    strcpy(elective.name, modName);
    if (in.peek() == ',')
    {
        in.get();
    }
    char* cat = new char[MAX_SIZE];
    in >> cat;
    if (cat == nullptr)
    {
        throw std::invalid_argument("Nullptr");
    }
    char* modCat = modifiedChar(cat);
    elective.category = findCategoryFromGivenStr(modCat);
    size_t cred;
    in >> cred;
    elective.credits = cred;
    if (in.peek() == ',')
    {
        in.get();
    }
    char* type = new char[MAX_SIZE];
    in >> type;
    if (type == nullptr)
    {
        throw std::invalid_argument("Nullptr");
    }
    elective.examType = findTypeFromGivenStr(type);
    return elective;
}
void printED(const ElectiveDiscipline ed)
{
    std::cout << ed.id << "," << ed.name << ",";
    findCategory(ed.category, std::cout);
    std::cout << ed.credits<<",";
    findExamType(ed.examType, std::cout);
}
int main()
{
    ElectiveDiscipline ed = init(1,"Fraktali", Category::PM, 7, ExamType::COURSE_PROJECT);
   // writeToFile(ed, "fraktali.txt");
    ElectiveDiscipline readEd = readFromFile("fraktali.txt");
    printED(readEd);
    return 0;
}

