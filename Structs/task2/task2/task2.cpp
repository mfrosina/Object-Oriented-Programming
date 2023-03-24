// task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*Реализирайте структура от битови полета RGB, съдържаща три полета, репрезентиращи трите основни цвята - червено, зелено и синьо. 
Полетата трябва да бъдат целочислени, приемащи стойности от 0 до 255. 
Създайте инстанция на структурата, представяща цвета жълто (255, 255, 0).*/
#include <iostream>

struct RGB
{
	int red: 8;
	int green: 8;
	int blue: 8;
};
void print(const RGB& rgb)
{
	std::cout << "(" << rgb.red << ", " << rgb.green << ", " << rgb.blue << ")";
}
int main()
{
	RGB yellow{ 255,255,0 };
	print(yellow);
	return 0;
}
