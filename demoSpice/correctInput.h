#pragma once
#include<iostream>

using namespace std;
template<typename T>	//������������� ������� ������
void correctInput(T& value)	//������� ����������� ����� ������
{
	cin >> value;	//���� ���������
	while (cin.fail())	//�������� ������������ �����
	{
		cin.clear();	//������� ������ ������
		cin.ignore(32767, '\n');	//������������� ������� �������� �� ����� ������	
		cout << "�������� ����. ���������� ��� ���: ";
		cin >> value;	//��������� ���� ���������
	}
}