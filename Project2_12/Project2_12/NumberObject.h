#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class NumberObject
{
public:
	NumberObject();
	NumberObject(string calculate);
	NumberObject(string numberator, string denominator)
	{
		this->numberator = numberator; 
		this->denominator = denominator;
	};
	string getNumberator() { return numberator; };
	string getDenominator() { return denominator; };
	NumberObject operator+( NumberObject &Number2);
	NumberObject operator*( NumberObject &Number2);
	NumberObject operator/(NumberObject &Number2);
	~NumberObject();
private:
	string numberator = "0";
	string denominator = "1";
};

