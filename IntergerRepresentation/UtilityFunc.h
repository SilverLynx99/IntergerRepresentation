#pragma warning (disable: 4996)
#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----------- Phép toán cho dạng chuỗi

////Thêm số 0 vào chuỗi ngắn hơn cho bằng nhau
//void standard2String(string &s1, string &s2);
//
////Phép nhân một chuỗi với số nguyên
//string mulWith1Int(string s1, int num);
//
////So sánh 2 số dạng chuỗi
//int compare2String(const string &s1, const string &s2);

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

// -----------



// ----------- Hàm chức năng cho QFloat

struct REALNUM
{
	string num;
	int point;
};

REALNUM convertToRealNum(const string &s);
string convertToString(const REALNUM &num);
int max(int a, int b);

//Thêm số 0 vào cuối phần thập phân cho độ dài bằng nhau
void standardRealNum(REALNUM &num1, REALNUM &num2);

string subReal(string num1, string num2);
string mulReal(string num1, int num2);

// -----------
// ----- Phat Function

////ham chuyen tu he 16 sang he 2
//string HexToBin(string hex);
////ham chep bit cua 1 ky tu trong ma HEXA vao chuoi BIT BINARY
//void CopyBitHexaToBin(string &bit, string bitOfHexCode, int pos);
////ham chuyen day nhi phan thanh chuoi de so sanh
//void ConvertBinToString(bool *bit, string &x);
////cac ham so sanh 2 chuoi dang nhi phan
//bool operator<(string s1, string s2);
//bool operator>(string s1, string s2);
//bool operator<=(string s1, string s2);
//bool operator>=(string s1, string s2);
//bool operator==(string s1, string s2);
////const string operator=(const string &s1);

// ------------------