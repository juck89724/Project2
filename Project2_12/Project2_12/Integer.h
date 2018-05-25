#pragma once
#include <iostream>
#include "NumberObject.h"
using namespace std;

class Integer :public NumberObject
{
public:
	Integer() :
		NumberObject::NumberObject() {};
	Integer(string calculate) :
		NumberObject::NumberObject(calculate) {};
	~Integer();
private:
};
