#include"circuit.h"  //������� �������� �� ���������� ����
#include"resistor.h" //�� ��������� ������ �����������, ��� ������������ ����� ���� ������� ���� � ��������, � ������ ����� 4-�� ������ ������
#include"voltageSource.h" //����� ����� �������� �� enum
#include"correctInput.h"
#include<stack>
#include<list>

using namespace std;

istream& operator>>(istream& in, Circuit& circuit)// ������� ���������� ��������� ������ ����� ������
{
	cout << "���� ����: " << endl;
	cout << "������� ���������� ������ �����: ";
	int nVertex;	//���������� ���������� ������ �����
	in >> nVertex;		//���� �����
	/*if (nVertex <= 0) //�������� ���������� �������� �� ������������ ���-�� ������
		return in;*/
	circuit.values.resize(nVertex);
	for (int i = 0; i < nVertex; ++i)
		circuit.values[i].resize(nVertex, vector<double>(1, -1));
	circuit.elements.resize(nVertex);
	for (int i = 0; i < nVertex; ++i)
		circuit.elements[i].resize(nVertex, vector<char>(1, '0'));

	cout << "������ ������� -> ������ ������� -> (U/R) -> value" << endl;
	int fVertex = 0, sVertex = 0;
	double value = 0;
	char unit = '0';

	while (true)
	{
		cout << "������� ������ �������: ";
		correctInput(fVertex);
		cout << "������� ������ �������: ";
		correctInput(sVertex);
		if (fVertex < 0 || sVertex < 0)
		{
			break;
		}

		cout << "������� U - Voltage ��� R - Resistance: ";
		correctInput(unit);
		cout << "������� �������� ���������� ��������: ";
		correctInput(value);
		if (fVertex >= nVertex || sVertex >= nVertex)
		{
			cout << "����� ������� �� ����������. ���������� ��� ���." << endl;
		}
		else
		{
			if (unit == 'U' || unit == 'u')
			{
				if (circuit.elements[fVertex][sVertex][0] == '0') //���� �� ����� ������ �� ����������, �� ������ ������ ��������
				{
					circuit.elements[fVertex][sVertex][0] = 'U';
					circuit.values[fVertex][sVertex][0] = value;
				}
				else
				{
					circuit.elements[fVertex][sVertex].push_back('U');	//���� �� ��� ����������, �� ��������� ����� �������
					circuit.values[fVertex][sVertex].push_back(value);
				}	
			}
			else if (unit == 'R' || unit == 'r')
			{
				if (circuit.elements[fVertex][sVertex][0] == '0') //���� �� ����� ������ �� ����������, �� ������ ������ ��������
				{
					circuit.elements[fVertex][sVertex][0] = 'R';
					circuit.values[fVertex][sVertex][0] = value;
				}
				else
				{
					circuit.elements[fVertex][sVertex].push_back('R');	//���� �� ��� ����������, �� ��������� ����� �������
					circuit.values[fVertex][sVertex].push_back(value);
				}
			}
			else
			{
				cout << "������ �������� �������." << endl;
			}
		}
	}
	return in;
}



void printMatrix(vector<vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void Circuit::createTree()
{
	tree.resize(values.size());
	for (int i = 0; i < tree.size(); ++i)
		tree[i].resize(values.size(), 0);
	chords.resize(values.size());
	for (int i = 0; i < chords.size(); ++i)
		chords[i].resize(values.size(), 0);
	int v = 0;
	// 0-����� ����, 1-������� ����, 2 - ������ ����
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
	cout << "Tree: " << endl;
	printMatrix(tree);
	cout << endl;
	cout << "C: " << endl;
	printMatrix(chords);
}

int Circuit::vertexDegree(int vertex, vector<vector<int>>& graph)
{
	int counter = 0;
	for (int i = 0; i < graph.size(); ++i)
		if (graph[vertex][i] != 0 || graph[i][vertex] != 0)
			++counter;
	return counter;
}

void mergeLists(list<int>& fList, list<int>& sList)
{
	for (auto i : sList)
		fList.push_back(i);
}

void Circuit::getIndependentLoop(list<int>& path, int vStart, int vEnd)
{
	int v = vStart;
	path.push_back(v);
	list<int> tmp;
	// 0-����� ����, 1-������� ����, 2 - ������ ����
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
		else break;
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
						//path.push_back(i);
						color[i] = 1;
					}
				}
			}
			else break;
		}
	}
	for (auto i = path.begin(); i != path.end(); ++i)
	{
		if (color[*i] == 1)
			path.erase(i);
	}
	//S.merge(P);
	mergeLists(path, tmp);
}


void Circuit::printGraph()
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

void Circuit::getLoopCoef(list<int>& path, vector<int>& coef) //��� - ��� ��������
{
	
	coef.resize(edgesIndex.size(), 0);
	//int direction = 1;
	auto i = path.begin();
	auto j = path.begin();
	++j;
	//int index = 0;
	auto it = edgesIndex.begin();
	while (j != path.end())
	{
		it = edgesIndex.find(pair<int, int>(*i, *j));
		if (it == edgesIndex.end())
		{
			it = edgesIndex.find(pair<int, int>(*j, *i));
			coef[it->second] = -1;  //����� ���������� ������ ����������� ������
		}
		else
		{
			coef[it->second] = 1;	//����� ���������� �� ����������� ������
		}
		++i; ++j;
	}
	i = --path.end();  //��������, ����� ������ ��������� ���������, �� ������ ������ ����� ��������� -> ������
	j = path.begin();
	it = edgesIndex.find(pair<int, int>(*i, *j));
	if (it == edgesIndex.end())
	{
		it = edgesIndex.find(pair<int, int>(*j, *i));
		coef[it->second] = -1;  //����� ���������� ������ ����������� ������
	}
	else
	{
		coef[it->second] = 1;  //����� ���������� �� ����������� ������
	}
	for (auto& i : path)
	{
		cout << i << " ";
	}
	cout << endl;
}

void Circuit::fillEdgesIndex()  // �������� ����� �����
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
	int counter = 0;	//���������� ��������
	createTree();	//�������� ������
	fillEdgesIndex();	//��������� ���� �����
	list<int> path;		//�������� ������ ����� ������ ������
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

vector<vector<int>>& Circuit::getContoursCoef()
{
	return contoursCoef;
}


vector<vector<double>>& Circuit::getResistance()
{
	return resistance;
}

vector<vector<double>>& Circuit::getVoltage()
{
	return voltage;
}

vector<vector<vector<double>>>& Circuit::getValues()
{
	return values;
}

void Circuit::fillResistAndVolt() //�� �������� 
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