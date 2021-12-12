#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<map>

using namespace std;

class Circuit
{
public:
	Circuit() {}	//����������� �� ���������
	friend istream& operator>>(istream& in, Circuit& circuit);	//������������� ������� ���������� ��������� ������ ����� ������
	void fillContoursCoef();	//������� ��������� ��������� �������������
	vector<vector<int>>& getContoursCoef();		//������� ���������� ������� ������� ��������
	vector<vector<double>>& getResistance();	//��������� �������������  
	vector<vector<double>>& getVoltage();	//��������� ����������
	vector<vector<vector<double>>>& getValues();	//��������� ��������
	void fillResistAndVolt();	//������� ���������� ������ ������������� � ����������

private:
	vector<vector<vector<double>>> values;
	vector<vector<vector<char>>> elements;
	vector<vector<int>> tree;	//������ �����
	vector<vector<int>> chords; //����� �����
	map<pair<int, int>, int> edgesIndex;	//��������� ���� �����
	vector<vector<int>> contoursCoef; //������� B
	vector<vector<double>> resistance; //������� ������������� 
	vector<vector<double>> voltage;	//������� ����������
	
private:
	void fillEdgesIndex();	//��������� ���� �����
	int vertexDegree(int vertex, vector<vector<int>>& graph);	//������� �������
	void createTree();	//������� ���������� ������
	void getIndependentLoop(list<int>& path, int vStart, int vEnd);		//��������� ����������� ��������
	void printGraph();	//������� ������ �����
	void getLoopCoef(list<int>& path, vector<int>& countoursCoef);	//��������� ��������� �������������
};

istream& operator>>(istream& in, Circuit& circuit);		//�������� ������� ���������� ��������� ������ ����� ������