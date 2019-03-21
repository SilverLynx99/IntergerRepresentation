#pragma warning (disable: 4996)
#include <iostream>
#include <string>

using namespace std;

//Phép cộng 2 số dạng chuỗi
string operator +(string num1, string num2);

//Phép trừ ra kết quả là số dương
string operator -(string num1, string num2);

// Nhân 2 số dạng chuỗi
string operator *(string num1, string num2);

// Mục đích: Chia 2 số nguyên lấy phần nguyên
// Input: 1 chuỗi và một số
// Output: Kq 
string operator /(string num1, int num2);

// Mục đích: Chia 2 số nguyên lấy phần dư
// Input: 1 chuỗi và một số
// Output: Kq (kiểu int)
int operator %(string num1, int num2);