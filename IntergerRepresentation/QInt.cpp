﻿#include "QInt.h"
#include "myLib.h"

bool processFileandOutput(istream& inputFile, ostream& outputFile)
{
	// How to write
	string p1, p2, ptemp, opt, opr1, opr2;
	while (!inputFile.eof())
	{
		p1 = "", p2 = "", ptemp = "", opt = "", opr1 = "", opr2 = "";
		// Doc tung dong
		inputFile >> p1;
		inputFile >> ptemp;
		if (ptemp == "2" || ptemp == "10" || ptemp == "16") // thuc hien phep chuyen doi giua cac HE
		{
			p2 = ptemp;
			inputFile >> opr1;
			//xu li dong tai day voi bien opr1 la toan hang duy nhat cua dong
			/////////
		}
		else //thuc hien cac phep tinh #
		{
			opr1 = ptemp; //copy ptemp vao opr1(toan hang thu 1)
			inputFile >> opt; //doc toan tu
			inputFile >> opr2; //doc toan hang thu 2
			//xu li dong tai day voi 2 bien opr1, opr2 lan luot la 2 toan hang va opt la toan tu
			////////
		}

	}

	return false;
}

void ScanQInt(QInt &x)
{
	//Sau khi tính xong mỗi số nguyên trong mảng QInt sẽ có số bit theo thứ tự của số lớn Number
	string Number = "123456789798";
	unsigned int base10 = 0; // chứa số nguyên 4 byte
	int count = 0; // đếm mỗi 32 bit
	int index = 3; //Vị trí của mảng QInt

	while (Number.compare("0") != 0)
	{
		if (count < 32)
		{
			base10 += Number % 2 * pow(2, count);  //Lấy phần dư nhân 2^count để cộng vào base 10
			Number = Number / 2;
			count++;
		}
		else //Sau 32 bit sẽ lưu một số nguyên vào mảng QInt từ cuối lên đầu
		{
			x.data[index--] = base10;
			base10 = 0;
			count = 0;
		}
	}

	//Trường hợp đã chia xong nhưng chưa đủ 32 bit 
	//Lưu số nguyên đã tính được vô mảng QInt vị trí index
	if (count < 32)
		x.data[index] = base10;
}

bool *DecToBin(QInt x)
{
	// Allocate an array of bool (128B), every bool store a bit
	bool *bitArray = new bool[128];

	// Set các bit bằng 0
	for (int i = 0; i < 127; i++)
		bitArray[i] = false;

	// Biến tạm
	int temp, iterOnbitArray = 1;

	// Duyệt trên từng khối int của QInt (4 khối
	for (int iterOnQInt = 3; iterOnQInt >= 0; iterOnQInt--)
	{
		// Lưu tạm từng khối int để xử lý
		temp = x.data[iterOnQInt];

		// Lấy tất cả bit của một khối int, tạo vòng lặp
		// để chạy thôi
		for (int i = 1; i <= 32; i++)
		{
			bitArray[128 - iterOnbitArray] = (temp & 1);
			temp = temp >> 1;

			// Tăng giá trị biến đếm của mảng bitArray
			iterOnbitArray++;
		}
	}
	return bitArray;
}

QInt BinToDec(bool * bit)
{
	QInt tempStorage;

	// Biến tạm
	int bitforOR;

	// Duyệt trên mảng bool.
	for (int iterOnBit = 70; iterOnBit <= 127; iterOnBit++)
	{
		if (bit[iterOnBit]) {
			bitforOR = (1 << (31 - (iterOnBit % 32)));
			tempStorage.data[iterOnBit / 32] |= bitforOR;
		}
	}

	return tempStorage;
}
