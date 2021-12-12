#pragma once
#include"circuitElement.h"
class VoltageSource : public CircuitElement		//Использование принципа объектно-ориентированного прогрммирования Наследование
{
public:
	VoltageSource(double value):	//Конструктор с параметрами
		CircuitElement(value) { }

	char type() const override 
	{ 
		return 'U'; 
	}
};