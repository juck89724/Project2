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
	vector<string> text;
	Integer i1("89.5");
	Decimal d1("0.5");
	//NumberObject x = i1 ^ d1;
	while (getline(cin, line))
	{

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
			char *postfix = new char[MAX] { '\0' };
			int counter = 0;
			stringstream ss;
			string s;
			inToPostfix(line.c_str(), postfix);
			ss << postfix;
			while (ss >> s)
			{
				text.push_back(s);
			}
			ss.clear();
			for (int i = 0; i < text.size(); i++)
			{
				string s= text[i];
				NumberObject *result=new NumberObject();
				if (priority(s[0]) != 0 && s.size()==1)
				{
					NumberObject newNumber1;
					NumberObject newNumber2;
					if (s != "!")
					{
						newNumber1 = *num[num.size() - 2];
						newNumber2 = *num[num.size() - 1];
					}
					else
						newNumber1 = *num[num.size() - 1];

					if (s == "+")
						*result = newNumber1 + newNumber2;
					else if (s == "-")
						*result = newNumber1 - newNumber2;
					else if (s == "*")
						*result = newNumber1 * newNumber2;
					else if (s == "/")
						*result = newNumber1 / newNumber2;
					else if (s == "^")
						*result = newNumber1 ^ newNumber2;
					else if (s == "!")
						*result = newNumber1.factorial();

					if (newNumber1.getName() == "Integer" && newNumber2.getName() == "Integer")
						num.push_back(new Integer(result->getNumberator(), result->getDenominator()));
					else
						num.push_back(new Decimal(result->getNumberator(), result->getDenominator()));

					if (s != "!")
					{
						num.erase(num.end() - 3);
						num.erase(num.end() - 2);
					}
					else
						num.erase(num.end() - 2);
				}
				else
				{
					NumberObject *newNumber;
					if (s.find(".") == -1)
						newNumber = new Integer(s);
					else
						newNumber = new Decimal(s);
					num.push_back(newNumber);
				}
			}

			text.clear();
			num.clear();
		}
	}

}
