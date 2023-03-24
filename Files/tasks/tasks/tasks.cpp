// tasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
/*От стандартния вход се прочитат три числа. Запишете във файл "result.txt"сумата и произведението им.
Направете функция, която извежда на стандартния изход разликата на сумата и произведението, прочетени от файла "result.txt".
Коректността на данните във файла, който четете, е гарантирана.*/

void difference(const char* fileName)
{
    std::ifstream in(fileName);
    if (!in.is_open())
    {
        std::cout << "Error\n";
        return;
    }
    int sum, prod;
    in >> sum >> prod;
    std::cout << sum - prod;
    in.close();
}

/*Да се напише подходящо параметризирана функция lengthOfFile(...) която връща колко символа има в текстов файл.*/
int lengthOfFile(const char* fileName)
{
    std::ifstream in(fileName);
    if (!in.is_open())
    {
        std::cout << "Error";
        return -1;
    }
    int length = 0;
    char c;
    while (in.get(c))
    {
        length++;
    }
    in.close();
    return length;
}

/*Да се напише програма за работа с шаблони (placeholders) в текстов файл.

Програмата трябва да прочете даден файл и да направи копие, в което шаблоните са заменени с конкретни стойности.

Бонус конкретните стойности се зареждат от друг файл със следния формат:*/
const size_t MAX_SIZE = 256;

struct Pair
{
    char templateName[MAX_SIZE];
    char templateValue[MAX_SIZE];

};

void readFiles(const char* source, const char* dest, const char* fileName)
{
    //reading concrete values from file
    std::ifstream in(fileName);
    if (!in.is_open())
    {
        std::cout << "Error\n";
        return;
    }
    Pair pairs[28];
    int ind = 0;
    while (!in.eof())
    {
        char templateName[MAX_SIZE];
        in >> templateName;
        char valueName[MAX_SIZE];
        in.getline(valueName, MAX_SIZE);
        strcpy(pairs[ind].templateName, templateName);
        strcpy(pairs[ind].templateValue, valueName);
        ind++;
    }
    in.close();
    std::ifstream so(source);
    std::ofstream de(dest);
    if (!so.is_open() || !de.is_open())
    {
        std::cout << "Error\n";
        return;
    }
    ind = 0;
    while (!so.eof())
    {
        char c = so.peek();
        if (so.peek() == ' ')
        {
            so.get();
        }
        if (so.peek() == '\n')
        {
            while (so.peek() == '\n')
            {
                de << '\n';
                so.get();
            }
        }
        if (so.peek() == '{')
        {
            char templateName[MAX_SIZE];
            so >> templateName;
            char templateVal[MAX_SIZE];
            strcpy(templateVal, pairs[ind].templateValue);
            ind++;
            de << templateVal << " ";
        }
        else
        {
            char word[MAX_SIZE];
            so >> word;
            de << word << " ";
        }
    }
    de.close();
    so.close();
}


int main()
{
    //task1
    //std::cout << "Enter three numbers:\n";
    //int n1, n2, n3;
    //std::cin >> n1 >> n2 >> n3;
    //int sum = n1 + n2 + n3;
    //int prod = n1 * n2 * n3;
    //
    //std::ofstream out("result.txt", std::ios::out);
    //out << sum << " ";
    //out << prod;
    //out.close();
    //difference("result.txt");
    // 
    //task2
    //char text[] = "frosina mulachka fros";
    //std::ofstream out("text.txt");
    //out << text;
    //out.close();
    //int l = lengthOfFile("text.txt");
    //std::cout << l;
    // 
    //testin sthg
    //std::ifstream in("text.txt");
    //while (!in.eof())
    //{
    //    char c[MAX_SIZE];
    //    in >> c;
    //    std::cout << c;
    //    char str[MAX_SIZE];
    //    in.getline(str, MAX_SIZE);
    //    std::cout << "\n" << str;
    //}
    //in.close();
    // 
    //task3
    //readFiles("template.txt", "modified.txt", "concrete.txt");


    return 0;
}

