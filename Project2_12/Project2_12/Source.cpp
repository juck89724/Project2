#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "Integer.h"
#include "Decimal.h"
#include "NumberObject.h"
using namespace std;

#define MAX 10000

NumberObject* calculateNumber(string line);
vector<NumberObject*> num;
map<string, NumberObject*> valueMap;
void checkPower(string & line);

int main()
{
	string line;
	//NumberObject x = i1 ^ d1;
	cout << "請入運算式:" << endl;
	while (getline(cin, line))
	{
		line.substr(0, 3);
		if (line.size() < 1)
			continue;
		if (line.substr(0, 3) == "Set")
		{
			map<string, NumberObject*>::iterator it;
			if (line.find("Integer") != -1)
			{
				bool haveAssing = false;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == '=')
						haveAssing = true;
				}
				if (haveAssing)
				{
					it = valueMap.find(line.substr(12, line.find("=") - 13));
					if (it != valueMap.end())
						valueMap.erase(it);
					string name = line.substr(12, line.find("=") - 13);
					string value;
					value = line.substr(line.find("=") + 2);
					NumberObject *result = calculateNumber(value);
					num.clear();
					if (result != NULL)
					{
						valueMap.insert
						(pair<string, NumberObject*>
							(name, new Integer(result->getSign() + result->getNumberator(), result->getDenominator())));
					}
					//cout << *valueMap[name] << endl;
					//測試
				}
				else
				{
					string name = line.substr(12);
					if (name != "")
					{
						it = valueMap.find(name);
						if (it != valueMap.end())
							valueMap.erase(it);
						Integer i;
						valueMap.insert(pair<string, NumberObject*>(name, &i));
					}
				}
			}
			else if (line.find("Decimal") != -1)
			{
				bool haveAssing = false;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == '=')
						haveAssing = true;
				}
				if (haveAssing)
				{
					it = valueMap.find(line.substr(12, line.find("=") - 13));
					if (it != valueMap.end())
						valueMap.erase(it);
					string name = line.substr(12, line.find("=") - 13);
					string value;
					value = line.substr(line.find("=") + 2);
					NumberObject *result = calculateNumber(value);
					num.clear();
					if (result != NULL)
					{
						valueMap.insert
						(pair<string, NumberObject*>
							(name, new Decimal(result->getSign() + result->getNumberator(), result->getDenominator())));
					}
					//cout << *valueMap[name] << endl;
					//測試
				}
				else
				{
					string name = line.substr(12);
					if (name != "")
					{
						it = valueMap.find(name);
						if (it != valueMap.end())
							valueMap.erase(it);
						Decimal i;
						valueMap.insert(pair<string, NumberObject*>(name, &i));
					}
					else
						cout << "格式錯誤";
				}
			}
			else
				cout << "格式錯誤" << endl;
		}
		else
		{
			stringstream ss;
			string s;
			vector<string> text;
			string temp = line;
			ss << line;
			while (ss >> s)
			{
				text.push_back(s);
			}
			if (text.size() > 0)
			{
				map<string, NumberObject*>::iterator it;
				it = valueMap.find(text[0]);
				if (it != valueMap.end() && line.find("=") != -1)
				{
					string value;
					value = line.substr(line.find("=") + 2);
					NumberObject *result = calculateNumber(value);
					num.clear();
					if (result != NULL)
					{
						if (it->second->getName() == "Integer")
						{
							NumberObject*pointer = new Integer(result->getSign() + result->getNumberator(), result->getDenominator());
							it->second = pointer;
						}
						else
						{
							NumberObject*pointer = new Decimal(result->getSign() + result->getNumberator(), result->getDenominator());
							it->second = pointer;
						}
					}
				}
				else
				{
					NumberObject *result = calculateNumber(line);
					if (result != NULL)
					{
						cout << endl << "運算結果：" << endl;
						cout << *result;
					}
					num.clear();
				}
			}
			//upup is judge variable 改變數值
		}
		cout <<endl<< "請入運算式:" << endl;
	}
}

NumberObject* calculateNumber(string line)
{
	vector<string> text;
	char *postfix = new char[MAX] { '\0' };
	int counter = 0;
	stringstream ss;
	string s;

	bool check = false;
	int count = 0;
	
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '+' || line[i] == '-')
		{
			if (i > 0)
			{
				char c = line[i - 1];
				if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(')
				{
					line.insert(line.begin() + i, '0');
					if (c != '(')
					{
						line.insert(line.begin() + i, '(');
						check = false;
						count = 0;
						int j = 0;
						for (j = i + 3; j < line.size(); j++)
						{
							if (priority(line[j]) == 0)
								check = true;
							if (check)
							{
								if (line[j] == '(') count++;
								if (line[j] == ')') count--;
							}
							if (((priority(line[j]) < 3 && priority(line[j]) > 0 && check) || line[j] == ')') && count < 1)
								break;
						}
						if(j < line.size())
							line.insert(line.begin() + j, ')');
						else
							line.push_back(')');
					}
				}
			}
			else
				line.insert(line.begin(), '0');
		}
	}
	checkPower(line);
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
			{
				if (newNumber2.getNumberator() == "0")
				{
					cout << "不能除以0" << endl;
					return NULL;
				}
				*result = newNumber1 / newNumber2;
			}
			else if (s == "^")
			{
				NumberObject two("2", "1");
				if ((newNumber2*two).isInteger())
				{
					if (!newNumber2.isInteger() && newNumber1.getSign() == "-")
					{
						cout << "負數無法開根號" << endl;
						return NULL;
					}
					else
					{
						*result = newNumber1 ^ newNumber2;
						NumberObject test = newNumber2 / two;
						if (!((newNumber2 / two).isInteger()) && newNumber1.getSign() == "-")
							result->setSign("-");
					}
				}
				else
				{
					cout << "次方數必為0.5的倍數" << endl;
					return NULL;
				}
			}
			else if (s == "!")
			{
				if (newNumber1.isInteger() && newNumber1.getSign() != "-")
					*result = newNumber1.factorial();
				else
				{
					cout << "數字不為正整數跟0" << endl;
					return NULL;
				}
			}
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
			NumberObject *newNumber = new NumberObject();
			map<string, NumberObject*>::iterator it;
			it = valueMap.find(s);
			if (it != valueMap.end())
				*newNumber = *it->second;
			else
			{
				for (int i = 0; i < s.size(); i++)
				{
					if ((s[i]<'0' || s[i]>'9') && s[i] != '.')
					{
						cout << "非法字元" << endl;
						return NULL;
					}
				}
				if (s.find(".") == -1)
					newNumber = new Integer(s);
				else
					newNumber = new Decimal(s);
			}
			num.push_back(newNumber);
		}
	}
	text.clear();
	if (num.size() == 1)
	{
		return num[0];
	}
}

void checkPower(string & line)
{
	bool check = false;
	int count = 0;
	bool isTime = false;
	int many = 0;
	int checkleft = 0;
	for (int i = 0; i < line.size(); i++)
	{
		char c = line[i];
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
		{
			if ((c == ')'|| c == '+' || c == '-' || c == '*' || c == '/') && checkleft <1)
			{
				for (int j = 0; j < many; j++)
					line.insert(line.begin() + i, ')');
				many = 0;
				isTime = false;
			}
			if (isTime)
			{
				if (line[i] == '(')checkleft++;
				if (line[i] == ')')checkleft--;
			}
			if (c == '^')
			{
				check = true;
				int j;
				for (j = i - 1; j > 0; j--)
				{
					if (priority(line[j]) == 0)
						isTime = true;
					if (isTime)
					{
						if (line[j] == ')') count++;
						if (line[j] == '(') count--;
					}
					if (((priority(line[j]) < 4 && priority(line[j]) > 0 && check) || line[j] == '(') && count < 1)
						break;
				}
				if(j!=0)
					line.insert(line.begin() + j + 1, '(');
				else
					line.insert(line.begin() + j, '(');
				isTime=true;
				i++;
				many++;
			}
		}
	}
	if (many != 0)
	{
		for (int j = 0; j < many; j++)
			line.push_back(')');
	}
}