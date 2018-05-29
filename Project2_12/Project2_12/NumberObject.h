#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#define MAX 10000

void inToPostfix(const char* infix, char* postfix);
int priority(char); // 運算子優先權
bool check(string &s);

string getResultString(string result_s);
string NumberSubtraction(string s1, string s2);
string NumberMultiplication(string s1, string s2);
string NumberAddition(string s1, string s2);

class NumberObject
{
public:
	NumberObject();
	NumberObject(string calculate);
	NumberObject(string numberator, string denominator);

	NumberObject operator+(NumberObject &Number2);
	NumberObject operator-(NumberObject &Number2);
	NumberObject operator*(NumberObject &Number2);
	NumberObject operator/(NumberObject &Number2);
	NumberObject operator^(NumberObject &Number2);
	friend ostream& operator<<(ostream&, NumberObject&);
	NumberObject factorial();
	//NumberObject operator=(NumberObject Number2);

	virtual void print() { cout << "this is NumberObject"; };
	long long int getInteger()
	{
		long long int result = 0;
		for (int i = 0; i < numberator.size(); i++)
		{
			result += (numberator[i] - '0') * pow(10, numberator.size() - i - 1);
		}
		long long int d = 0;
		for (int i = 0; i < denominator.size(); i++)
		{
			d += (denominator[i] - '0') * pow(10, denominator.size() - i - 1);
		}
		return result / d;
	};

	string getName() { return name; };
	string getNumberator() { return numberator; };
	string getDenominator() { return denominator; };
	string getSign() { return sign; };
	string getCalculate() { return calculate; };

	void setName(string name) { this->name = name; };
	void setNumberator(string num) { this->numberator = num; };
	void setDenominator(string den) { this->denominator = den; };
	void setSign(string sign) { this->sign = sign; };
	void setCalculate(string calculate) { this->calculate = calculate; };
	~NumberObject();
private:
	string numberator = "0";
	string denominator = "1";
	string sign = "";
	string calculate = "";
	string name = "";
};

int big_compare(NumberObject a, NumberObject b);