#pragma once
#include <vector>
#include "UtilityFunc.h"

class Qfloat
{
private:
	// Đánh dấu bit 0 là bit đầu tiên của data[0] 
	// đi từ trái qua phải
	int Data[4];

public:
	Qfloat();
	Qfloat(const Qfloat &x);
	Qfloat &operator=(const Qfloat &x);
	void ScanQfloat(string numberFloat);
	void PrintQfloat();
	void BinToDec(bool *bit);
	bool *DecToBin();
};