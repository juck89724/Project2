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
	{
		this->NumberObject::NumberObject(calculate);
		setName("Decimal");
	};
	Decimal(string numberator, string denominator)
	{
		this->NumberObject::NumberObject(numberator, denominator);
		setName("Decimal");
	};
	~Decimal();
	void print() { cout << "this is Decimal"; };
private:
};
