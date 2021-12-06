#pragma once
#include"circuitElement.h"
class VoltageSource : public CircuitElement
{
public:
	VoltageSource(double value):
		CircuitElement(value) { }
	char type() const override { return 'U'; }
private:

};