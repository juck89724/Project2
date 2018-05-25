#include "NumberObject.h"

string NumberMultiplication(string s1, string s2);
string NumberAddition(string s1, string s2);

NumberObject::NumberObject()
{

}

NumberObject::NumberObject(string calculate)
{
	numberator = calculate;
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
