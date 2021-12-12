#pragma once
#include"circuitElement.h"
class Resistor : public CircuitElement
{
public:
	Resistor(double value):		//Конструктор с параметрами
		CircuitElement(value) {}

	char type() const override 
	{ 
		return 'R'; 
	}
};
