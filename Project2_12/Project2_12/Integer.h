#pragma once
#include <iostream>
#include "NumberObject.h"
using namespace std;

class Integer :public NumberObject
{
public:
	Integer() :
		NumberObject::NumberObject() { setName("Integer"); };
	Integer(string calculate) :
		NumberObject::NumberObject(calculate) { setName("Integer"); };
	Integer(string numberator, string denominator) :
		NumberObject(numberator, denominator)
	{
		setName("Integer");
	};
	~Integer();
	void print() { cout << "this is Integer"; };
private:
};
