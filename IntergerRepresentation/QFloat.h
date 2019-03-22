#pragma once
#include <string>
#include <vector>
#include "myLib.h"


struct Qfloat
{
	// Đánh dấu bit 0 là bit đầu tiên của data[0] 
	// đi từ trái qua phải
	unsigned int Data[4] = { 0 };
};

void ScanQfloat(Qfloat &x);
