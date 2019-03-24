#pragma warning (disable: 4996)
#include <iostream>
#include <string>

using namespace std;
string operator +(string num1, string num2);
string operator -(string num1, string num2);
string operator *(string num1, string num2);
string operator /(string num1, int num2);
int operator %(string num1, int num2);

//Số thực
struct REALNUM
{
	string num;
	int point;
};

string subReal(string num1, string num2);
string mulReal(string num1, int num2);