#pragma once
#include<iostream>

using namespace std;
template<typename T>	//Использование шаблона данных
void correctInput(T& value)	//Функция корректного ввода данных
{
	cin >> value;	//Ввод параметра
	while (cin.fail())	//Проверка корректности ввода
	{
		cin.clear();	//Очистка флагов ошибки
		cin.ignore(32767, '\n');	//Игнорирование символа перехода на новую строку	
		cout << "Неверный ввод. Попробуйте еще раз: ";
		cin >> value;	//Повторный ввод параметра
	}
}