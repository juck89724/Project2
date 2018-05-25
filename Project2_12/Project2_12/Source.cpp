#include <iostream>
#include <string>
#include "Integer.h"
#include "Decimal.h"
#include "NumberObject.h"
using namespace std;

int main()
{
	string line;
	Integer int1("10");
	Decimal dec1("25","10");
	NumberObject number= int1 + dec1;
	NumberObject mnumber = int1 * dec1;
	NumberObject dmnumber = int1 / dec1;
	while (getline(cin, line))
	{
		/*設計變數*/
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

		}
	}
}