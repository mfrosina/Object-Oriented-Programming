// task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*Реализирайте структура от битови полета FilePermissions, даваща информация за правата на ползване върху файл или директория в операционната система. Тя трябва да съдържа по три полета (права за четене, писане и изпълнение) за текущия потребител, за групата и за всички останали. От стандартния вход прочете символен низ (с дължина 9), даващ информация за правата на ползване на някакъв файл, и според тази информация запълнете инстанция на вашата структура и изведете битовите маски на екрана.

Вход:
rwxr-xr-x

Обяснение:
Текущият потребител има право да чете, да пише и да изпълнява файла.
Групата има право за чете и да го изпълнява, но няма права да пише във файла.
Всички останали имат същите права като на групата.

Изход: (отпечатване на всички полета на структурата)
Owner permissions: 111
Group permissions: 101
Others permissions: 101*/
#include <iostream>

const std::size_t MAX_SIZE = 64;
struct FlagSet
{
    bool read : 1;
    bool write : 1;
    bool execute : 1;
};
struct FilePermissions
{
    FlagSet owner;
    FlagSet group;
    FlagSet others;
};
void fillFlagSet(FlagSet& flagSet, const char* permissions);

void init(FilePermissions& filePerm, const char* permissions)
{
    fillFlagSet(filePerm.owner, permissions);
    fillFlagSet(filePerm.group, permissions + 3);
    fillFlagSet(filePerm.others, permissions + 6);
}
void fillFlagSet(FlagSet& flagSet, const char* permissions)
{
    flagSet.read = permissions[0] == 'r';
    flagSet.write = permissions[1] == 'w';
    flagSet.execute = permissions[2] == 'x';
} 
void printFlagSet(const FlagSet& flagSet)
{
    std::cout << flagSet.read << flagSet.write << flagSet.execute << std::endl;
}
void printFilePermissions(const FilePermissions& filePermissions)
{
    std::cout << "Owner permissions: ";
    printFlagSet(filePermissions.owner);
    std::cout << "Group permissions: ";
    printFlagSet(filePermissions.group);
    std::cout << "Others permissions: ";
    printFlagSet(filePermissions.others);
}
int main()
{

    char permissions[MAX_SIZE + 1];
    std::cin >> permissions;

    FilePermissions filePermissions;
    init(filePermissions, permissions);

    printFilePermissions(filePermissions);

    return 0;
}

