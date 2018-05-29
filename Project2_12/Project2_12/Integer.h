#pragma once
#include <iostream>
#include "NumberObject.h"
#include "Decimal.h"
using namespace std;

class Integer :public NumberObject
{
public:
	Integer()
	{
		this->NumberObject::NumberObject();
		setName("Integer");
	};
	Integer(string calculate) 
	{
		this->NumberObject::NumberObject(calculate);
		setName("Integer"); 
		if (getDenominator() != "1")
		{
			NumberObject n(getNumberator());
			NumberObject p(getDenominator());
			NumberObject times("1");
			NumberObject one("1");
			NumberObject d = p * times;
			while (big_compare(n, d) >= 0)
			{
				times = times + one;
				d = p * times;
			}
			times = times - one;
			setNumberator(times.getNumberator());
			setDenominator(times.getDenominator());
			calculate = times.getNumberator();
		}
	};
	Integer(string numberator, string denominator) 
	{
		this->NumberObject::NumberObject(numberator, denominator);
		setName("Integer");
		if (getDenominator() != "1")
		{
			NumberObject n(getNumberator());
			NumberObject p(getDenominator());
			NumberObject times("1");
			NumberObject one("1");
			NumberObject d = p * times;
			while (big_compare(n, d) >= 0)
			{
				times = times + one;
				d = p * times;
			}
			times = times - one;
			setNumberator(times.getNumberator());
			setDenominator(times.getDenominator());
			setCalculate(times.getNumberator());
		}
	};
	~Integer();
	void print() { cout << "this is Integer"; };
private:
};
