#pragma once
#include <vector>
#include "UtilityFunc.h"

struct Qfloat
{
	// Đánh dấu bit 0 là bit đầu tiên của data[0] 
	// đi từ trái qua phải
	unsigned int Data[4] = { 0 };
};

void ScanQfloat(Qfloat &x);
void PrintQfloat(Qfloat x);

Qfloat BinToDec(bool *bit);
bool *DecToBin(Qfloat x);