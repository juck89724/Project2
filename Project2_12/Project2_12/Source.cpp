#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Integer.h"
#include "Decimal.h"
#include "NumberObject.h"
using namespace std;

#define MAX 1000

vector<NumberObject*> num;
int main()
{

	string line;
	Integer int1("1");
	Decimal dec1("7");
	NumberObject number = int1 + dec1;
	NumberObject mnumber = int1 * dec1;
	NumberObject dmnumber = int1 / dec1;
	while (getline(cin, line))
	{
		stringstream ss;
		ss << line;
		if (line.substr(0, 3) == "Set")
		{
			if (line.find("Integer") != -1)
			{

			}
			else if (line.find("Decimal") != -1)
			{

			}
		}
		else
		{
			vector<string> infix;
			vector<string> postfix;

			string s;
			int counter = 0;
			while (ss >> s)
			{
				infix.push_back(s);
				counter++;
			}
			inToPostfix(infix, postfix);
			for (int i = 0; i < postfix.size(); i++)
			{
				string s= postfix[i];
				NumberObject *result=new NumberObject();
				if (priority(s[0]) != 0 && s.size()==1)
				{
					NumberObject newNumber1 = *num[num.size() - 2];
					NumberObject newNumber2 = *num[num.size() - 1];
					if (s == "+")
						*result = newNumber1 + newNumber2;
					if (s == "*")
						*result = newNumber1 * newNumber2;
					if (s == "/")
						*result = newNumber1 / newNumber2;
					if (newNumber1.getName() == "Integer" && newNumber2.getName() == "Integer")
						num.push_back(new Integer(result->getNumberator(), result->getDenominator()));
					else
						num.push_back(new Decimal(result->getNumberator(), result->getDenominator()));
				}
				else
				{
					NumberObject *newNumber;
					if (s.find(".") == -1)
						newNumber = new Integer(s);
					else
						newNumber = new Decimal(s);
					newNumber->print();
					num.push_back(newNumber);
				}
			}
		}
	}
}
