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
		:NumberObject::NumberObject(calculate)
	{
		setName("Integer"); 
		
		if (getDenominator() != "1")
		{
			string result;
			string num = getNumberator();
			bool c = false;
			string mod;
			for (int i = 0; i < num.size(); i++)
			{
				mod += num[i];
				NumberObject nmod(mod);
				NumberObject d(getDenominator());
				if (mod.size() >= getDenominator().size())
				{
					NumberObject p(getDenominator());
					NumberObject times("1");
					NumberObject one("1");
					while (big_compare(nmod, d) >= 0)
					{
						times = times + one;
						d = p * times;
					}
					times = times - one;
					d = p * times;
					mod = (nmod - d).getNumberator();
					if (times.getNumberator() != "0")
						c = true;
					if (c)
						result+= times.getNumberator();
				}
			}
			if (!c)
				result = "0";
			setNumberator(result);
			setDenominator("1");
		}
	};
	Integer(string numberator, string denominator) 
		:NumberObject::NumberObject(numberator, denominator)
	{
		setName("Integer");
		if (getDenominator() != "1")
		{
			string result;
			string num = getNumberator();
			bool c = false;
			string mod;
			for (int i = 0; i < num.size(); i++)
			{
				mod += num[i];
				NumberObject nmod(mod);
				NumberObject d(getDenominator());
				if (mod.size() >= getDenominator().size())
				{
					NumberObject p(getDenominator());
					NumberObject times("1");
					NumberObject one("1");
					while (big_compare(nmod, d) >= 0)
					{
						times = times + one;
						d = p * times;
					}
					times = times - one;
					d = p * times;
					mod = (nmod - d).getNumberator();
					if (times.getNumberator() != "0")
						c = true;
					if (c)
						result += times.getNumberator();
				}
			}
			if (!c)
				result = "0";
			setNumberator(result);
			setDenominator("1");
		}
	};
 	
	~Integer();
private:
};
