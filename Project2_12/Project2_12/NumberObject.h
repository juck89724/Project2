#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void inToPostfix(vector<string>, vector<string>&); // 中序轉後序 
int priority(char); // 運算子優先權
string NumberMultiplication(string s1, string s2);
string NumberAddition(string s1, string s2);

class NumberObject
{
public:
	NumberObject();
	NumberObject(string calculate);
	NumberObject(string numberator, string denominator)
	{
		this->numberator = numberator; 
		this->denominator = denominator;
	};
	string getName() { return name; };
	string getNumberator() { return numberator; };
	string getDenominator() { return denominator; };
	NumberObject operator+( NumberObject &Number2);
	NumberObject operator*( NumberObject &Number2);
	NumberObject operator/(NumberObject &Number2);
	virtual void print() { cout << "this is NumberObject"; };
	void setName(string name) { this->name = name; };
	~NumberObject();
private:
	string numberator = "0";
	string denominator = "1";
	string calculate = "";
	string name = "";
};

