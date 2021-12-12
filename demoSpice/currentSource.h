#pragma once
#include"circuitElement.h"
class CurrentSource : public CircuitElement
{
public:
	CurrentSource(double value):
		CircuitElement(value) { }

	char type() const override
	{ 
		return 'I';
	}
};