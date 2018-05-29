#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Integer.h"
#include "Decimal.h"
#include "NumberObject.h"
using namespace std;

#define MAX 10000

vector<NumberObject*> num;
int main()
{
	string line;
	Integer i1("1024");
	Decimal d1("2.5");
	NumberObject n1 = i1 ^ d1;
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
			char *postfix = new char[MAX] {'\0'};
			string s;
			int counter = 0;
			inToPostfix(line.c_str(), postfix);
			/*for (int i = 0; i < postfix.size(); i++)
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
			}*/
		}
	}
	
}
