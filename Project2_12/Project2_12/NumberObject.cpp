#include "NumberObject.h"


NumberObject::NumberObject()
{

}

NumberObject::NumberObject(string calculate)
{
	this->calculate = calculate;
	if (calculate.find(".") == -1)
	{
		numberator = calculate;
	}
	else
	{
		for (int i = calculate.size() - 1; i >= 0; i--)
		{
			if (calculate[i] == '.')
			{
				calculate.erase(calculate.begin() + i);
				break;
			}
			denominator += "0";
		}
		numberator =calculate;
	}
}


NumberObject::~NumberObject()
{
}

NumberObject NumberObject::operator+(NumberObject &Number2)
{
	string newDenominator = NumberMultiplication(denominator, Number2.denominator);
	string newNumberator1 = NumberMultiplication(numberator, Number2.denominator);
	string newNumberator2 = NumberMultiplication(denominator, Number2.numberator);
	string addition = NumberAddition(newNumberator1, newNumberator2);
	return NumberObject(addition, newDenominator);
}

NumberObject NumberObject::operator*(NumberObject &Number2)
{
	string newDenominator = NumberMultiplication(denominator, Number2.denominator);
	string newNumberator = NumberMultiplication(numberator, Number2.numberator);
	return NumberObject(newNumberator,newDenominator);
}

NumberObject NumberObject::operator/(NumberObject & Number2)
{
	string newNumberator = NumberMultiplication(numberator, Number2.denominator);
	string newDenominator = NumberMultiplication(denominator, Number2.numberator);
	return NumberObject(newNumberator, newDenominator);
}

bool check(string &s)
{
	if (s[0] == '-')
	{
		s = &s[1];
		return false;
	}
	return true;
}

string NumberMultiplication(string s1, string s2)
{
	string sign = "";
	if (check(s1) != check(s2))
		sign = "-";
	int size = s1.size() + s2.size() - 1;
	if ((s1[0] - '0')*(s2[0] - '0') >= 10)
		size++;
	int *result = new int[size] { 0 };
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = 0; j < s2.size(); j++)
		{
			result[i + j] += (s1[s1.size() - i - 1] - '0')*(s2[s2.size() - j - 1] - '0');
		}
	}
	int count = 0;
	stringstream ss;
	while (count <= size - 1)
	{
		if (result[count] >= 10)
		{
			result[count + 1] += result[count] / 10;
			result[count] %= 10;
		}
		ss << result[count];
		count++;
	}
	ss << sign;
	string result_s = ss.str();
	ss.clear();
	reverse(result_s.begin(), result_s.end());
	return result_s;
}

string NumberAddition(string s1, string s2)
{
	string sign = "";
	if ((!check(s1)) && (!check(s2)))
		sign = "-";
	int size = fmax(s1.size(), s2.size());
	if ((s1[0] - '0') + (s2[0] - '0') >= 10)
		size++;
	int counter = 0;
	int *result = new int[size] { 0 };
	int s1_count = s1.size() - 1, s2_count = s2.size() - 1;
	int number1, number2;
	while (counter < size)
	{
		if (s1_count >= 0)
			number1 = (s1[s1_count] - '0');
		if (s2_count >= 0)
			number2 = (s2[s2_count] - '0');

		result[counter] = number1 + number2;

		s1_count -= 1; s2_count -= 1;
		number1 = 0; number2 = 0;
		counter++;
	}
	int count = size - 1;
	stringstream ss;
	while (count >= 0)
	{
		if (result[count] >= 10)
		{
			result[count - 1] += result[count] / 10;
			result[count] %= 10;
		}
		ss << result[count];
		count--;
	}
	ss << sign;
	string result_s = ss.str();
	ss.clear();
	return result_s;
}

string NumberSubtraction(string s1, string s2)
{
	return string();
}


void inToPostfix(vector<string> infix, vector<string> &postfix)
{
	vector<string> stack;
	int i;
	for (i = 0; i < infix.size(); i++)
	{
		if (infix[i] == "(")
		{
			stack.push_back(infix[i]);
			continue;
		}
		if (infix[i] == "+" ||
			infix[i] == "-" ||
			infix[i] == "*" ||
			infix[i] == "/" ||
			infix[i] == "^" ||
			infix[i] == "!")
		{
			if (stack.size()> 0)
			{
				while (priority(stack[stack.size() - 1][0]) >= priority(infix[i][0]))
				{
					postfix.push_back(stack[stack.size() - 1]);
					stack.pop_back();
					if (stack.size() == 0)
						break;
				}
			}
			stack.push_back(infix[i]); // 存入堆疊 
			continue;
		}
		if (infix[i] == ")")
		{
			if (stack.size() > 0)
			{
				while (stack[stack.size() - 1] != "(")
				{ // 遇 ) 輸出至 ( 
					postfix.push_back(stack[stack.size() - 1]);
					stack.pop_back();
					if (stack.size() == 0)
						break;
				}
				stack.pop_back();
			}// 不輸出 ( 
			continue;
		}
		postfix.push_back(infix[i]);
	}
	while (stack.size() > 0)
	{
		postfix.push_back(stack[stack.size() - 1]);
		stack.pop_back();
	}
}

int priority(char op)
{
	switch (op)
	{
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		case '^': return 3;
		case '!': return 4;
		case '(': case ')': return 5;
		default:
			return 0;
	}
}
