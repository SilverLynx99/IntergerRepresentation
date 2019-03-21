#include "QInt.h"
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
	//Lưu số âm dưới dạng bù 2
	//Sau khi tính xong mỗi số nguyên trong mảng QInt sẽ có số bit theo thứ tự của số lớn Number
	string Number = "-123";

	unsigned int base10 = 0; // chứa số nguyên 4 byte
	int count = 0; // đếm mỗi 32 bit
	int index = 3; //Vị trí của mảng QInt
	int condition = 0; //0 nếu dương và 1 nếu âm
	int mod, firstBit1 = 0; //Nếu tìm thấy bit 1 đầu tiên sẽ chuyển sang 1

	if (Number[0] == '-')
	{
		condition = 1;
		Number.erase(0, 1);
		for (int i = 0; i < 4; i++)
			x.data[i] = 4294967295;
	}

	while (Number.compare("0") != 0)
	{
		if (count < 32)
		{
			mod = Number % 2;

			//Nếu là số âm thì mới thực hiện các thao tác ở dưới
			if (condition == 1)
			{
				if (firstBit1 == 1)
				{
					if (mod == 1)
						mod = 0;
					else
						mod = 1;
				}

				//Tìm bit 1 đầu tiên từ phải sang
				if ((mod == 1) && (firstBit1 == 0))
					firstBit1 = 1; //Đổi trạng thái
			}

			base10 += mod * pow(2, count);  //Lấy phần dư nhân 2^count để cộng vào base 10
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
	{
		//Nếu là số âm và chưa hết 32 bit thì tiếp tục đổi những bit còn lại thành 1
		if (condition == 1)
		{
			while (count < 32)
			{
				base10 += pow(2, count);
				count++;
			}
		}

		x.data[index] = base10;
	}
}

void ScanQIntBin(QInt &x)
{
	string NumberBit = "10110001100100011110011110011111000111110001111110000111100001";

	unsigned int base10 = 0; // chứa số nguyên 4 byte
	int count = 0; // đếm mỗi 32 bit
	int index = 3; //Vị trí của mảng QInt
	int i, size = NumberBit.length() - 1;
	for (i = size; i >= 0; i--)
	{
		if (count < 32)
		{
			base10 += NumberBit[i] * pow(2, count);  //Lấy phần dư nhân 2^count để cộng vào base 10
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

void ScanQIntHex(QInt &x)
{
	string NumberHex = "40F";
	//Tạo 2 chuỗi để đổi từ hex sang bin qua thuật toán đổi từ kí tự sang bin rồi ghép lại
	string hex = "0123456789ABCDEF";
	vector<string> hexToBIn = { "0000", "0001","0010" ,"0011" ,"0100" ,"0101" ,
		"0110" ,"0111" ,"1000" ,"1001" ,"1010" ,"1011" ,"1100" ,"1101", "1110", "1111" };

	int i, index, size = NumberHex.length() - 1;
	int j, index2 = 3, count = 0;
	unsigned int base10 = 0;
	//Duyệt từ cuối lên đầu của chuỗi NumberHex
	for (i = size; i >= 0; i--)
	{
		//Tìm vị trí chuỗi NumberHex trong chuỗi hex
		//Vị trí này cũng chính là vị trí nhị phân trong mảng chuỗi hexToBin
		index = hex.find(NumberHex[i]);

		//Chạy từ cuối lên đầu chuỗi nhị phân 4 kí tự trong mảng chuỗi hexToBin
		for (j = 3; j >= 0; j--)
		{
			if (count < 32)
			{
				base10 += (hexToBIn[index][j] - '0') * pow(2, count);
				count++;
			}
			else //Sau 32 bit cập nhật vào data của QInt
			{
				x.data[index2--] = base10;
				count = 0;
				base10 = 0;
			}
		}
	}

	if (count < 32)
		x.data[index2] = base10;
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
