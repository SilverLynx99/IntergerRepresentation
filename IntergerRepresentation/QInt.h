#pragma once
#include <iostream>


using namespace std;
struct QInt
{
	// Đánh dấu bit 0 là bit đầu tiên của data[0] 
	// đi từ trái qua phải

	// Bit là bit dấu. Số âm viết ở dạng bù 2.
	int data[4] = { 0 };
};

// Chức năng: Xử lý stream in và xuất ra stream out
// Note: Stream in có thể là file, có thể là cin.
bool processFileandOutput(istream& inputFile, ostream& outputFile);

// Xử lý nhập liệu
void ScanQInt(QInt &x);


// --- XỬ LÝ CHUYỂN ĐỔI

// Chuyển đổi từ QInt sang nhị phân và lưu mã nhị phân 
// bằng một mảng 128 bytes.
// Cách làm: chỉ cần lấy bit và lưu lại.
// LƯU Ý HỦY CẤP PHÁT MẢNG BOOL
bool *DecToBin(QInt x);

// Chuyển đổi dãy nhị phân thành QInt
// WARNING: KHẢ NĂNG RẤT CAO LÀ BỊ LỖI Ở ĐÂY.
// LỖI LÀ : KHI TRẢ VỀ DỮ LIỆU KHÔNG ĐƯỢC SAO CHÉP MÀ LÀ REF
QInt BinToDec(bool *bit);

// Chuyển đỗi dãy nhị phân thành mã hex
// Output: một chuỗi hex có 32 ký tự, có cả ký tự '0'
char * BinToHex(bool *bit);

// Chuyển đổi QInt sang Hex
// Output: Một chuỗi hex có 32 ký tự, có cả ký tự '0'
char * DecToHex(QInt x);
// ---

// -- TÍNH TOÁN
// Cộng 2 số QInt, xuất ra ngoài QInt. 
// Không xử lý tràn số.
QInt operator+( QInt a,QInt b);


QInt operator-(QInt a, QInt b);
QInt operator*(QInt a, QInt b);
QInt operator/(QInt a, QInt b);
QInt operator<< (QInt a, int b);
QInt operator>> (QInt a, int b);

// ---


//--- UTILITY FUNCTION FOR QINT

// Đổi dấu một số QInt, thay đổi trên chính nó
void doiDau(QInt &inp);

// ---