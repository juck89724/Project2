#pragma once
#include <iostream>
#include "NumberObject.h"
using namespace std;

class Decimal :public NumberObject
{
public:
	Decimal()
	{
		this->NumberObject::NumberObject();
		setName("Decimal");
	};
	Decimal(string calculate)
		: NumberObject::NumberObject(calculate)
	{
		setName("Decimal");
	};
	Decimal(string numberator, string denominator)
		:NumberObject::NumberObject(numberator, denominator)
	{
		setName("Decimal");
	};
	~Decimal();
private:
};
