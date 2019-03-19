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

	// Biến lưu lại chuỗi bit để thực hiện phép OR
	int bitforOR;

	// Duyệt trên mảng bool.
	for (int iterOnBit = 0; iterOnBit <= 127; iterOnBit++)
	{
		// Nếu đúng, bật bit tại đúng vị trí của tempStorage
		if (bit[iterOnBit]) {
			bitforOR = (1 << (31 - (iterOnBit % 32)));
			tempStorage.data[iterOnBit / 32] |= bitforOR;
		}
	}

	return tempStorage;
}

// Mảng được tạo để truy xuất ký tự hexa
char arrOfHexCode[] = { '0', '1', '2', '3',
						'4', '5', '6', '7',
						'8', '9', 'A', 'B',
						'C', 'D', 'E', 'F' };
char * BinToHex(bool * bit)
{
	// Tạo một mảng bit phụ
	bool *tempBit = new bool[128];
	for (int i = 0; i < 128; i++) {
		tempBit[i] = bit[i];
	}

	// Số dương : sign = false, dương sign = true
	bool sign = false;

	// Nếu là số âm, thực hiện bù 2 phần đuôi
	if (tempBit[0]) {
		// tìm bit 1 đầu tiên từ cuối
		int i = 127;
		while (!tempBit[i]) {
			i--;
		}

		// Thực hiện bù
		do {
			i--;
			tempBit[i] = !tempBit[i];
		} while (i > 0);

		// Đánh dấu chuỗi bit này là chuỗi âm
		sign = true;
	}

	// Cấp phát vùng nhớ để lưu chuỗi Hex
	// 34 ký tự bao gồm dấu và phần giá trị
	char SL_CapPhat = 34;
	char *hexChar = new char[SL_CapPhat];
	
	int tempSum;
	int heSoNhan[] = { 1, 2, 4, 8 };

	// Duyệt trên mảng tempBit
	for (int i = 127; i >= 0;)
	{
		// Biến tạm tính tổng
		tempSum = 0;
		
		// Duyệt trên từng cụm 4bit để chuyển thành ký tự
		for (int j = 0; j < 4; j++)
		{
			if (tempBit[i])	tempSum += heSoNhan[j];
			i--;
		}

		// Đẩy ký tự vào mảng char. 
		// Biểu thức (i + 1) / 4 để tính vị trí để 
		// lưu ký tự vào mảng hex, và được cộng thêm
		// 1 vì có một bit dấu ở ô 0
		hexChar[((i + 1) / 4) + 1] = arrOfHexCode[tempSum];
	}
	
	// Đánh dấu kết thúc chuỗi
	hexChar[SL_CapPhat - 1] = '\0';

	// Chèn thêm dấu vào đầu chuỗi hex code
	hexChar[0] = (sign ? '-' : '+');

	delete[]tempBit;
	return hexChar;
}

// hello
// hello 1
