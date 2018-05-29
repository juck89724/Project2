#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Integer.h"
#include "Decimal.h"
#include "NumberObject.h"
using namespace std;

#define MAX 10000

NumberObject* calculateNumber(string line);
vector<NumberObject*> num;

int main()
{
	string line;
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
			NumberObject result = *calculateNumber(line);
			cout << result << endl;
			num.clear();
		}
	}
}


NumberObject* calculateNumber(string line)
{
	vector<string> text;
	char *postfix = new char[MAX] { '\0' };
	int counter = 0;
	stringstream ss;
	string s;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '+' || line[i] == '-')
		{
			if (i > 0)
			{
				if (!(line[i - 1] >= '0' && line[i - 1] <= '9'))
				{
					line.insert(line.begin() + i, '0');
					line.insert(line.begin() + i, '(');
					line.push_back(')');
				}
			}
			else
				line.insert(line.begin(), '0');
		}
	}

	inToPostfix(line.c_str(), postfix);
	ss << postfix;
	while (ss >> s)
	{
		text.push_back(s);
	}
	ss.clear();
	for (int i = 0; i < text.size(); i++)
	{
		string s = text[i];
		NumberObject *result = new NumberObject();
		if (priority(s[0]) != 0 && s.size() == 1)
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
			if (s != "!")
			{
				if (newNumber1.getName() == "Integer" && newNumber2.getName() == "Integer")
					num.push_back(new Integer(result->getSign() + result->getNumberator(), result->getDenominator()));
				else
					num.push_back(new Decimal(result->getSign() + result->getNumberator(), result->getDenominator()));
				num.erase(num.end() - 3);
				num.erase(num.end() - 2);
			}
			else
			{
				if (newNumber1.getName() == "Integer")
					num.push_back(new Integer(result->getSign() + result->getNumberator(), result->getDenominator()));
				else
					num.push_back(new Decimal(result->getSign() + result->getNumberator(), result->getDenominator()));
				num.erase(num.end() - 2);
			}
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
	if (num.size() == 1)
	{
		return num[0];
	}
	
}