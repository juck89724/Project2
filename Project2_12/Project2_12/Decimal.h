#pragma once
#include <iostream>
#include "NumberObject.h"
using namespace std;

class Decimal :public NumberObject
{
public:
	Decimal() : 
		NumberObject::NumberObject() {};
	Decimal(string calculate) : 
		NumberObject::NumberObject(calculate) {};
	Decimal(string numberator, string denominator) :
		NumberObject::NumberObject(numberator,denominator) {};
	~Decimal();

private:
};
