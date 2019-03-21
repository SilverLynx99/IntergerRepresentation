#pragma once


struct Qfloat
{
	// Bit đầu - bit dấu
	// 15 bit sau - bit exponent
	// 122 cuối - bit fraction
	// Lấy 1 nửa int đầu, phần còn lại là fraction
	int data[4];
};

void ScanQfloat(Qfloat &x);
void PrintQfloat(Qfloat x);
