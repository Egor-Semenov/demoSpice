#pragma once
#include"circuitElement.h"
class Resistor : public CircuitElement
{
public:
	Resistor(double value):
		CircuitElement(value) {}
	char type() const override { return 'R'; }
private:
};
