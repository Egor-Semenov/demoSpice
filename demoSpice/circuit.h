#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<map>

using namespace std;

class Circuit
{
public:
	Circuit() {}	//Конструктор по умолчанию
	friend istream& operator>>(istream& in, Circuit& circuit);	//Дружественная функция перегрузки оператора потока ввода данных
	void fillContoursCoef();	//Функция заполения контурных коэффициентов
	vector<vector<int>>& getContoursCoef();		//Функция заполнения матрицы главных контуров
	vector<vector<double>>& getResistance();	//Получение сопротивления  
	vector<vector<double>>& getVoltage();	//Получение напряжения
	vector<vector<vector<double>>>& getValues();	//Получение значения
	void fillResistAndVolt();	//Функция заполнения матриц сопротивлений и напряжений

private:
	vector<vector<vector<double>>> values;
	vector<vector<vector<char>>> elements;
	vector<vector<int>> tree;	//Дерево графа
	vector<vector<int>> chords; //Хорды графа
	map<pair<int, int>, int> edgesIndex;	//Нумерация рёбер графа
	vector<vector<int>> contoursCoef; //Матрица B
	vector<vector<double>> resistance; //Матрица сопротивлений 
	vector<vector<double>> voltage;	//Матрица напряжений
	
private:
	void fillEdgesIndex();	//Нумерация ребр графа
	int vertexDegree(int vertex, vector<vector<int>>& graph);	//Степень вершины
	void createTree();	//Функция построения дерева
	void getIndependentLoop(list<int>& path, int vStart, int vEnd);		//Получение независимых контуров
	void printGraph();	//Функция вывода графа
	void getLoopCoef(list<int>& path, vector<int>& countoursCoef);	//Получение контурных коэффициентов
};

istream& operator>>(istream& in, Circuit& circuit);		//Прототип функция перегрузки оператора потока ввода данных