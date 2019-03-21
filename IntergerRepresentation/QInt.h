#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;
struct QInt
{
	// Đánh dấu bit 0 là bit đầu tiên của data[0] 
	// đi từ trái qua phải
	int data[4] = { 0 };
};

// Chức năng: Xử lý stream in và xuất ra stream out
// Note: Stream in có thể là file, có thể là cin.
bool processFileandOutput(istream& inputFile, ostream& outputFile);

// Xử lý nhập liệu
void ScanQInt(int *ArrayDataQInt);


// Xử lý chuyển đổi

// Chuyển đổi từ QInt sang nhị phân và lưu mã nhị phân 
// bằng một mảng 128 bytes.
// Cách làm: chỉ cần lấy bit và lưu lại.
// LƯU Ý HỦY CẤP PHÁT MẢNG BOOL
bool *DecToBin(QInt x);

// Chuyển đổi dãy nhị phân thành QInt
// WARNING: KHẢ NĂNG RẤT CAO LÀ BỊ LỖI Ở ĐÂY.
// LỖI LÀ : KHI TRẢ VỀ DỮ LIỆU KHÔNG ĐƯỢC SAO CHÉP MÀ LÀ REF
QInt BinToDec(bool *bit);
QInt operator+( QInt a,QInt b);
QInt operator-(QInt a, QInt b);
QInt operator*(QInt a, QInt b);
QInt operator/(QInt a, QInt b);
QInt ShiftLeft1(QInt &a);
QInt ShiftLeftChia(QInt &a,QInt &b);