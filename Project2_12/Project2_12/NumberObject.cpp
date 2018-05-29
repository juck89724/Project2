#include "NumberObject.h"

bool checkSign(NumberObject number)
{
	if (number.getSign() == "-")
	{
		return false;
	}
	return true;
};


NumberObject::NumberObject()
{

}

NumberObject::NumberObject(string calculate)
{
	this->calculate = calculate;
	if (!check(calculate)) sign = "-";
	if (calculate.find(".") == -1)
	{
		numberator = calculate;
	}
	else
	{
		for (int i = calculate.find(".") + 1; i < calculate.size(); i++)
		{
			denominator += "0";
		}
		calculate.erase(calculate.begin()+calculate.find("."));
		numberator = calculate;
	}
}

NumberObject::NumberObject(string numberator, string denominator)
{
	if (!check(numberator)) sign = "-";
	this->numberator = numberator;
	this->denominator = denominator;
}


NumberObject::~NumberObject()
{
}

NumberObject NumberObject::operator+(NumberObject &Number2)
{
	string newDenominator;
	string newNumberator1;
	string newNumberator2;
	string addition;
	if ((sign == "-" && Number2.sign == "-") || (sign == "" && Number2.sign == ""))
	{
		newDenominator = NumberMultiplication(denominator, Number2.denominator);
		newNumberator1 = NumberMultiplication(numberator, Number2.denominator);
		newNumberator2 = NumberMultiplication(denominator, Number2.numberator);
		addition = sign + NumberAddition(newNumberator1, newNumberator2);
	}
	return NumberObject(addition, newDenominator);
}

NumberObject NumberObject::operator*(NumberObject &Number2)
{
	string newSign = "-";
	if ((checkSign(*this) && checkSign(Number2)) || (!checkSign(*this) && !checkSign(Number2)))
		newSign = "";
	string newDenominator = NumberMultiplication(denominator, Number2.denominator);
	string newNumberator = newSign + NumberMultiplication(numberator, Number2.numberator);
	return NumberObject(newNumberator, newDenominator);
}

NumberObject NumberObject::operator/(NumberObject & Number2)
{
	string newSign = "-";
	if ((checkSign(*this) && checkSign(Number2)) || (!checkSign(*this) && !checkSign(Number2)))
		newSign = "";
	string newNumberator = newSign + NumberMultiplication(numberator, Number2.denominator);
	string newDenominator = NumberMultiplication(denominator, Number2.numberator);
	return NumberObject(newNumberator, newDenominator);
}
NumberObject plus2("2");
NumberObject NumberObject::operator^(NumberObject & Number2)
{
	Number2 = Number2 * plus2;
	long long int l= Number2.getInteger();
	NumberObject result("1");
	for (int i = 0; i < l; i++)
	{
		result = result * (*this);
	}

	NumberObject x ("1");
	for (int i = 0; i < 100; i++)//誤差為小數點後一百位
	{
		x.denominator + "0";
	}
	NumberObject high;
	NumberObject low;
	NumberObject one("1");
	NumberObject zero("0");
	if (big_compare(result,one) < 0) 
	{
		low = zero; 
		high = one;  // 若 0 < x < 1 則其平方根必然介於 0 與 1之間。
	}
	else 
	{
		low = one; 
		high = result;  // 若 x > 1 , 則其平方根必然介於 1 與 x 之間。
	}
	while (big_compare(high - low,x) > 0)  // 不斷逼近，直到範圍夠小為止。
	{
		NumberObject mid = (low + high) / plus2;
		if (big_compare(mid*mid,x) > 0)          // 解小於 mid , 將上限調為 mid
			high = mid;
		else
			low = mid;              // 解大於 mid , 將下限調為 mid
	}

	return NumberObject(low.numberator,low.denominator);
}

bool check(string &s)
{
	if (s[0] == '-')
	{
		s.erase(s.begin());
		return false;
	}
	return true;
}

string NumberMultiplication(string s1, string s2)
{
	int size = s1.size() + s2.size() - 1;
	if ((s1[0] - '0')*(s2[0] - '0') >= 10)
		size++;
	int *result = new int[size] { 0 };
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = 0; j < s2.size(); j++)
			result[i + j] += (s1[s1.size() - i - 1] - '0')*(s2[s2.size() - j - 1] - '0');
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
	string result_s = ss.str();
	ss.clear();
	reverse(result_s.begin(), result_s.end());
	return result_s;
}

string NumberAddition(string s1, string s2)
{
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
	int count = 0;
	stringstream ss;
	while (count < size)
	{
		if (result[count] >= 10)
		{
			result[count + 1] += result[count] / 10;
			result[count] %= 10;
		}
		ss << result[count];
		count++;
	}
	string result_s = ss.str();
	ss.clear();
	reverse(result_s.begin(), result_s.end());
	return result_s;
}

string NumberSubtraction(string s1, string s2)
{
	return string();
}


void inToPostfix(const char* infix, char* postfix)
{
	char stack[10000] = { '\0' };
	int i, j, top;
	for (i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch (infix[i])
	{
	case '(':              // 運算子堆疊 
		stack[++top] = infix[i];
		break;
	case '+': case '-': case '*': case '/':
		while (priority(stack[top]) >= priority(infix[i]))
		{
			postfix[j++] = stack[top--];
		}
		stack[++top] = infix[i]; // 存入堆疊 
		break;
	case ')':
		while (stack[top] != '(')
		{ // 遇 ) 輸出至 ( 
			postfix[j++] = stack[top--];
		}
		top--;  // 不輸出 ( 
		break;
	default:  // 運算元直接輸出 
		postfix[j++] = infix[i];
	}
	while (top > 0)
	{
		postfix[j++] = stack[top--];
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
	default:            return 0;
	}
}
int big_compare(NumberObject a, NumberObject b)
{
	string ad = a.getDenominator();
	string bd = b.getDenominator();
	while (ad.length() != bd.length())
	{
		if (ad.length() < bd.length())
		{
			a.setDenominator(a.getDenominator() + "0");
			a.setNumberator(a.getNumberator() + "0");
		}
		if (ad.length() > bd.length())
		{
			b.setDenominator(b.getDenominator() + "0");
			b.setNumberator(b.getNumberator() + "0");
		}
		ad = a.getDenominator();
		bd = b.getDenominator();
	}
	int a_size = a.getNumberator().length();
	int b_size = b.getNumberator().length();
	if (a_size > b_size)
		return 1;
	else if (b_size > a_size)
		return -1;
	else
	{
		for (int i = 0; i < a_size; i++)
		{
			if (a.getNumberator()[i] != b.getNumberator()[i])
				return a.getNumberator()[i] - b.getNumberator()[i];
		}
		return 0;
	}
}