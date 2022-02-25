#include "circuit.h"  
#include "resistor.h" 
#include "voltageSource.h" 
#include "correctInput.h"
#include <stack>
#include <list>

using namespace std;

istream& operator>>(istream& in, Circuit& circuit)	// Функция перегрузки оператора потока ввода данных
{
	cout << "Граф цепи: " << endl;
	cout << "Введите количество вершин графа: ";
	int nVertex;	//Переменная количества вершин графа
	in >> nVertex;		//Ввод графа
	circuit.values.resize(nVertex);		//Установление количества вершин для графа
	for (int i = 0; i < nVertex; ++i)
		circuit.values[i].resize(nVertex, vector<double>(1, -1));
	circuit.elements.resize(nVertex);
	for (int i = 0; i < nVertex; ++i)
		circuit.elements[i].resize(nVertex, vector<char>(1, '0'));

	cout << "Первая вершина -> вторая вершина -> (U/R) -> value" << endl;
	int fVertex = 0, sVertex = 0;	// Объявление первой и второй вершин для ввовда схемы
	double value = 0;	// Числовое значение вводимой физической величины
	char unit = '0';	// Символьное обозначение физической величины (u-voltage и r-resistance)

	while (true)	// Процесс ввода схемы
	{
		cout << "Введите первую вершину: ";
		correctInput(fVertex);	// Функция ввода данных, номера вершин начинать с нуля!!!
		cout << "Введите вторую вершину: ";
		correctInput(sVertex);
		if (fVertex < 0 || sVertex < 0)		// Проверка корректности ввода номера вершины графа
		{
			break;
		}

		cout << "Введите U - Voltage или R - Resistance: ";
		correctInput(unit);
		cout << "Введите значение физической величины: ";
		correctInput(value);
		if (fVertex >= nVertex || sVertex >= nVertex)	// Проверка возможности существования введённых вершин
		{
			cout << "Такие вершины не существуют. Попробуйте еще раз." << endl;
		}
		else
		{
			if (unit == 'U' || unit == 'u')		// Определение физической характеристики введённого символа 
			{
				if (circuit.elements[fVertex][sVertex][0] == '0') //Если до этого ничего не записывали, то меняем пустое значение
				{
					circuit.elements[fVertex][sVertex][0] = 'U';
					circuit.values[fVertex][sVertex][0] = value;
				}
				else
				{
					circuit.elements[fVertex][sVertex].push_back('U');	//Если до это записывали, то добавляем новый элемент
					circuit.values[fVertex][sVertex].push_back(value);
				}	
			}
			else if (unit == 'R' || unit == 'r')	// Определение физической характеристики введённого символа 
			{
				if (circuit.elements[fVertex][sVertex][0] == '0') //Если до этого ничего не записывали, то меняем пустое значение
				{
					circuit.elements[fVertex][sVertex][0] = 'R';
					circuit.values[fVertex][sVertex][0] = value;
				}
				else
				{
					circuit.elements[fVertex][sVertex].push_back('R');	//Если до это записывали, то добавляем новый элемент
					circuit.values[fVertex][sVertex].push_back(value);
				}
			}
			else	// Символ физической величины введён некорректно
			{
				cout << "Введен неверный элемент." << endl;
			}
		}
	}

	return in;
}



void printMatrix(vector<vector<int>>& matrix)	// Функция вывода матрицы
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

void Circuit::createTree()	// Функция создания дерева графа
{
	tree.resize(values.size());		//Установление количества вершин дерева
	for (int i = 0; i < tree.size(); ++i)
		tree[i].resize(values.size(), 0);
	chords.resize(values.size());	//Установление количества хорд графа
	for (int i = 0; i < chords.size(); ++i)
		chords[i].resize(values.size(), 0);
	int v = 0;
	// 0-белый цвет, 1-красный цвет, 2 - чёрный цвет
	vector<int> color(values.size(), 0);
	color[v] = 1;
	stack<int> stack;
	stack.push(v);
	while (!stack.empty())
	{
		v = stack.top();
		stack.pop();
		color[v] = 2;
		for (int i = 0; i < values.size(); ++i)
		{
			if (color[i] == 1)
			{
				if (values[v][i][0] != -1)
					chords[v][i] = 1;
				else if (values[i][v][0] != -1)
					chords[i][v] = 1;
			}
			else if (color[i] == 0)
			{
				if (values[v][i][0] != -1)
				{
					stack.push(i);
					tree[v][i] = 1;
					color[i] = 1;
				}
				else if (values[i][v][0] != -1)
				{
					stack.push(i);
					tree[i][v] = 1;
					color[i] = 1;
				}
				
			}
		}
	}
	cout << "Матрица смежности дерева графа: " << endl;
	printMatrix(tree);
	cout << endl;
	cout << "Матрица смености хорд графа: " << endl;
	printMatrix(chords);
}

int Circuit::vertexDegree(int vertex, vector<vector<int>>& graph)	//Степень вершины
{
	int counter = 0;
	for (int i = 0; i < graph.size(); ++i)
		if (graph[vertex][i] != 0 || graph[i][vertex] != 0)
			++counter;
	return counter;
}

void mergeLists(list<int>& fList, list<int>& sList)		//Слияние листов
{
	for (auto i : sList)
		fList.push_back(i);
}

void Circuit::getIndependentLoop(list<int>& path, int vStart, int vEnd)		//Получение независимых контуров
{
	int v = vStart;
	path.push_back(v);
	list<int> tmp;
	// 0-белый цвет, 1-красный цвет, 2 - чёрный цвет
	vector<int> color(values.size(), 0);
	color[v] = 1;
	bool isEnd = false;
	while (true)
	{
		if (vertexDegree(vEnd, tree) <= 2)
		{
			tmp.push_front(vEnd);
			color[vEnd] = 2;
			if (vEnd == vStart)
			{
				path = tmp;
				isEnd = true;
			}

			for (int i = 0; i < tree.size(); ++i)
			{
				if (color[i] == 0 && (tree[i][vEnd] != 0 || tree[vEnd][i] != 0))
				{
					vEnd = i;
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	while (!isEnd)
	{
		if (color[v] != 1 && !path.empty())
		{
			v = path.back();
			path.pop_back();
		}
		else
		{
			color[v] = 2;
			if (v != vEnd)
			{
				for (int i = 0; i < tree.size(); i++)
				{
					if (color[i] == 0 && (tree[v][i] != 0 || tree[i][v] != 0))
					{
						if (vEnd == i)
						{
							color[vEnd] = 2;
							path.push_back(i);
							isEnd = true;
							break;
						}
						color[i] = 1;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	for (auto i = path.begin(); i != path.end(); ++i)
	{
		if (color[*i] == 1)
		{
			path.erase(i);
		}
	}
	mergeLists(path, tmp);
}


void Circuit::printGraph()		//Вывод на экран графа
{
	for (int i = 0; i < elements.size(); ++i)
	{
		for (int j = 0; j < elements[i].size(); ++j)
		{
			cout << elements[i][j][0] << " ";
		}

		cout << endl;
	}
}

void Circuit::getLoopCoef(list<int>& path, vector<int>& coef)	//Получение контурных коэффициентов 
{
	coef.resize(edgesIndex.size(), 0);
	auto i = path.begin();
	auto j = path.begin();
	++j;
	auto it = edgesIndex.begin();
	while (j != path.end())
	{
		it = edgesIndex.find(pair<int, int>(*i, *j));
		if (it == edgesIndex.end())
		{
			it = edgesIndex.find(pair<int, int>(*j, *i));
			coef[it->second] = -1;  //ребро направлено против направления обхода
		}
		else
		{
			coef[it->second] = 1;	//ребро направлено по направлению обхода
		}
		++i; ++j;
	}

	i = --path.end();
	j = path.begin();
	it = edgesIndex.find(pair<int, int>(*i, *j));
	if (it == edgesIndex.end())
	{
		it = edgesIndex.find(pair<int, int>(*j, *i));
		coef[it->second] = -1;  //ребро направлено против направления обхода
	}
	else
	{
		coef[it->second] = 1;  //ребро направлено по направлению обхода
	}

	for (auto& i : path) // Вывод матрицы независимых контуров
	{
		cout << i << " ";
	}

	cout << endl;
}

void Circuit::fillEdgesIndex()  //Нумеруем ребра графа
{
	int counter = 0;
	for (int i = 0; i < values.size(); ++i)
	{
		for (int j = 0; j < values.size(); ++j)
		{
			if (values[i][j][0] != -1)
			{
				edgesIndex.emplace(pair<int, int>(i, j), counter);
				++counter;
			}
		}
	}
}

void Circuit::fillContoursCoef()
{
	int counter = 0;	//Объявление счётчика
	createTree();	//Создание дерева
	fillEdgesIndex();	//Нумерация рёбер графа
	list<int> path;		//Создание списка путей обхода данных
	cout << "Матрица независимых коэффициентов" << endl;
	for (int i = 0; i < chords.size(); ++i)
	{
		for (int j = 0; j < chords[i].size(); ++j)
		{
			if (chords[i][j] == 1)
			{
				getIndependentLoop(path, i, j);
				contoursCoef.push_back(vector<int>(edgesIndex.size(), 0));
				getLoopCoef(path, contoursCoef[counter]);
				path.clear();
				++counter;
			}
		}
	}
		
}

vector<vector<int>>& Circuit::getContoursCoef()		//Получение контурных коэффициентов
{
	return contoursCoef;
}


vector<vector<double>>& Circuit::getResistance()	//Получение сопротивления
{
	return resistance;
}

vector<vector<double>>& Circuit::getVoltage()	//Получение напряжения
{
	return voltage;
}

vector<vector<vector<double>>>& Circuit::getValues()	//Получение значения
{
	return values;
}

void Circuit::fillResistAndVolt()	//Функция заполнения матриц сопротивлений и напряжений
{
	resistance.resize(edgesIndex.size());
	for (int i = 0; i < resistance.size(); ++i)
		resistance[i].resize(resistance.size(), 0);
	voltage.resize(edgesIndex.size(), vector<double>(1, 0));
	int resistCounter = 0;
	int voltageCounter = 0;
	double R = 0;
	double U = 0;
	for (int i = 0; i < values.size(); ++i)
	{
		for (int j = 0; j < values[i].size(); ++j)
		{
			if (values[i][j][0] != - 1)
			{
				for (int k = 0; k < values[i][j].size(); ++k)
				{
					if (elements[i][j][k] == 'R' || elements[i][j][k] == 'r')
						R += values[i][j][k];
					else
						U += values[i][j][k];
				}
				resistance[resistCounter][resistCounter] = R;
				voltage[voltageCounter][0] = U;
				R = 0;
				U = 0;
				++resistCounter;
				++voltageCounter;
			}
		}
	}
}