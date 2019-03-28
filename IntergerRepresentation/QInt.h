#pragma once
#include <iostream>
#include <sstream>
#include "UtilityFunc.h"
using namespace std;

class QInt
{
public:
	QInt();
	QInt(int inp);
	QInt(const QInt &src);

	QInt& operator= (const QInt &src);

	// -- TÍNH TOÁN
	// Cộng 2 số QInt, xuất ra ngoài QInt. 
	// Không xử lý tràn số.
	QInt operator+ (const QInt& b)const;
	QInt operator- (const QInt& b)const;
	QInt operator* (const QInt& b)const;
	QInt operator/ (const QInt& b)const; // Chưa viết.

	// -- TOÁN TỬ BIT
	QInt operator>>(int num) const;
	QInt operator<<(int num) const;
	QInt rol(int num)const;
	QInt ror(int num)const;

	QInt operator&(const QInt & b);
	QInt operator|(const QInt & b);
	QInt operator^(const QInt & b);
	QInt operator~()const;
	// ----

	// -- TOÁN TỬ SO SÁNH
	bool operator> (const QInt & a)const;
	bool operator< (const QInt & a)const;
	bool operator>= (const QInt & a)const;
	bool operator<= (const QInt & a)const;
	bool operator== (const QInt & a)const;
	//--

	// -- CHUYỂN ĐỔI GIỮA CÁC KIỂU DỮ LIỆU

	// Chuyển đổi từ QInt sang nhị phân và lưu mã nhị phân 
// bằng một mảng 128 bytes.
// Cách làm: chỉ cần lấy bit và lưu lại.
// LƯU Ý HỦY CẤP PHÁT MẢNG BOOL
	static bool *DecToBin(QInt x);

	// Chuyển đổi dãy nhị phân thành QInt
// WARNING: KHẢ NĂNG RẤT CAO LÀ BỊ LỖI Ở ĐÂY.
// LỖI LÀ : KHI TRẢ VỀ DỮ LIỆU KHÔNG ĐƯỢC SAO CHÉP MÀ LÀ REF
	static QInt BinToDec(bool * bit);

	// Chuyển đỗi dãy nhị phân thành mã hex
// Output: một chuỗi hex có 32 ký tự, có cả ký tự '0'
	static char * BinToHex(bool * bit);

	// Chuyển đổi QInt sang Hex
// Output: Một chuỗi hex có 32 ký tự, có cả ký tự '0'
	static char * DecToHex(QInt x);

	//--
	// Xử lý nhập liệu
	friend istream& operator>> (istream& is, QInt & inp)
	{
		// Xóa sạch dữ liệu của QInt inp trước khi nhập
		inp = QInt();

		// CHƯA XỬ LÝ CHUỖI NHẬP XUẤT CHỖ NÀY
		// Nhập chuỗi
		string Number;
		is >> Number;

		bool sign = false; // True = số âm, false là dương

		// Trường hợp chuỗi bit là âm
		if (Number[0] == '-')
		{
			// Bỏ dấu trừ
			Number.erase(0, 1);

			// Ky hieu dau am
			sign = true;
		}

		int count = 0;
		int temp; // biến tạm chứa chuỗi bit cần or

		// Chia đến khi kq bằng 0
		while (Number.compare("0") != 0)
		{
			// Nếu số dư bằng 1 thì bật bit tại vtri tương ứng
			if (Number % 2 == 1)
			{
				temp = 1;
				temp <<= (count % 32);
				inp.data[3 - (count / 32)] |= temp; // Or với temp để bật bit
			}

			Number = Number / 2;
			count++;
		}

		// Thực hiện chuyển đổi chuỗi bit dương thành âm, nếu số ban đầu là âm.
		if (sign) {
			inp = inp.doiDau();
		}

		return is;
	}

	//friend ostream& operator<< (ostream& os, const QInt& out)
	//{
	//	int temp;
	//	for (int j = 0; j < 4; j++) {
	//		for (int i = 31; i >= 0; i--)
	//		{
	//			temp = (out.data[j] >> i);
	//			os << (temp & 1);
	//			if (i % 8 == 0)
	//				os << " ";
	//		}
	//		os << endl;
	//	}
	//	return os;
	//}

	friend ostream& operator<< (ostream& os, const QInt& out)
	{
		// Lưu trữ tạm biến out để xử lý
		QInt temp(out);

		// Lưu dấu của biến out
		bool sign = false;

		// Trường hợp số âm
		if (temp.getBitAtIdx(0))
		{
			// Đổi dấu
			 temp = temp.doiDau();

			 // Đánh dấu
			 sign = true;
		}

		// Lưu kết quả
		string sumAll = "0";

		// Lưu kết quả của việc tính 2^i
		string sum = "1";

		int lastBit = 0;
		for (int i = 127; i >= 0; i--)
		{
			// Nếu bit đó bằng 1
			if (temp.getBitAtIdx(i))
			{
				// Tính 2 ^ i
				while (lastBit < (127 - i)) {
					sum = sum * "2";
					lastBit++;
				}

				// Cộng dồn
				sumAll = sumAll + sum;
			}
		}

		// Thêm dấu trừ vào nếu có
		if (sign)
			sumAll = "-" + sumAll;

		os << sumAll;

		return os;
	}

private:
	// Đánh dấu bit 0 là bit đầu tiên của data[0] 
	// đi từ trái qua phải

	// Bit là bit dấu. Số âm viết ở dạng bù 2.
	unsigned int data[4];


	//--- UTILITY FUNCTION FOR QINT

	// Đổi dấu một số QInt, thay đổi trên chính nó
	QInt doiDau() const;

	// Kiểm tra một số có phải là âm không ?
	bool ktAm() const;

	// idx >= 0 && idx <= 127
	// Chuỗi bit được đánh dấu từ 0 --> 127
	// Từ trái quá phải
	bool getBitAtIdx(int idx)const;

	void DichTraiDacBiet(QInt &a);
	// ---
};


// Chức năng: Xử lý stream in và xuất ra stream out
// Note: Stream in có thể là file, có thể là cin.
void processFileandOutput(istream& inputFile, ostream& outputFile);



