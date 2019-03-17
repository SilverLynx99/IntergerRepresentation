#include "QInt.h"

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

void ScanQInt(int * ArrayDataQInt)
{
	string Number = "123456789798";
	int BitSum = 0; // chứa 32 số bit
	int Base10 = 0; // chứa số nguyên 4 byte
	int CountArray = 0; // đếm phần tử mảng
	int Count = 0; // đếm số bit trong trường hợp chưa đủ 32 bit
	int stop = 0; // lệnh dừng trong trường hợp đi hết string Number nhưng chưa đủ 128 bit
	for (int i = 1; i <= 128; i++)
	{
		Count++;
		if (Number > "0")
		{
			BitSum = BitSum + pow(10, i - 1) * (Number % 2); // mỗi lần chia string Number cho 2 thì BitSum tăng 1 phần tử
		}
		else
			stop = 1;
		if (i % 32 == 0 || stop == 1) // mỗi 32 bit hoặc có điều kiện dừng
		{
			int idx = 0;
			int temp = 0;
			while (idx < 32) // chuyển BitSum sang hệ 10
			{
				if (BitSum < 1) { // chạy hết BitSum
					break;
				}
				temp = BitSum % 10;
				BitSum = BitSum / 10;
				Base10 += pow(2, idx) * temp;
				idx++;
			}
			ArrayDataQInt[CountArray] = Base10; // đưa số nguyên 4byte vào mảng
			CountArray++; // đếm đến phần tử mảng tiếp theo
			Base10 = 0;
			BitSum = 0;
			Count = 0;
			if (stop == 1) { // dừng vòng for khi string Number đã hết
				break;
			}
		}
		// Number / "2"; ??
	}
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
