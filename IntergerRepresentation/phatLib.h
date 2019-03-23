#pragma once
#include "QInt.h"

//ham chuyen tu he 16 sang he 2
string HexToBin(string hex);
//ham chep bit cua 1 ky tu trong ma HEXA vao chuoi BIT BINARY
void CopyBitHexaToBin(string &bit, string bitOfHexCode, int pos);
//ham chuyen day nhi phan thanh chuoi de so sanh
void ConvertBinToString(bool *bit, string &x);
//cac ham so sanh 2 chuoi dang nhi phan
bool operator<(string s1, string s2);
bool operator>(string s1, string s2);
bool operator<=(string s1, string s2);
bool operator>=(string s1, string s2);
bool operator==(string s1, string s2);
//const string operator=(const string &s1);