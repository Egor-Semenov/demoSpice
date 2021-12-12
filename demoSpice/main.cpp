#include<iostream>
#include<vector>	//Использование контейнера библиотеки STL
#include<map>	//Использование контейнера библиотеки STL
#include"circuit.h"
#include"matrixOperations.h"
using namespace std;

template<typename T>	//Использование шаблона данных
void printMatrix(vector<vector<T>>& matrix)		//Функция вывода матрицы
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printResult(vector<vector<double>>& matrix, vector<vector<vector<double>>>& values)	//Функция вывода рассчитанных токов
{
	int counter = 0;	//Объявление счётчика
	for (int i = 0; i < values.size(); ++i)
	{
		for (int j = 0; j < values[i].size(); ++j)
		{
			if (values[i][j][0] != -1)
			{
				cout << i << "->" << j << ": I = " << matrix[counter++][0] << "A" << endl;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Ru");	//Использование кодировки русского языка
	Circuit circuit;	//Создание объекта схемы
	cin >> circuit;		//Ввод схемы
	circuit.fillContoursCoef();		//Заполнение контурных коэффициентов
	vector<vector<int>>& contoursCoef = circuit.getContoursCoef();	//Создание и заполнение матрицы главных контуров
	
	cout << "Матрица главных контуров:" << endl;

	for (int i = 0; i < contoursCoef.size(); ++i)	//Вывод матрицы главных контуров
	{
		for (int j = 0; j < contoursCoef[i].size(); ++j)
		{
			cout << contoursCoef[i][j] << " ";
		}
		cout << endl;
	}

	circuit.fillResistAndVolt();	//Заполнение матриц сопротивлений и напряжений
	cout << "Resistance: " << endl;
	printMatrix(circuit.getResistance());	//Вывод вывод матрицы сопротивлений
	cout << endl << endl;
	cout << "Voltage: " << endl;
	printMatrix(circuit.getVoltage());	//Вывод матрицы напряжений

	vector<vector<double>> currents = MatrixRez(circuit.getContoursCoef(), circuit.getResistance(), circuit.getVoltage());	
	//Создание и получение матрицы токов

	printResult(currents, circuit.getValues());		//Вывод значений искомых токов
	system("pause");	//Ожидание ввода символа для закрытия консоли
	return 0;
}