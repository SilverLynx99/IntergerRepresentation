#include "QInt.h"
#include "UtilityFunc.h"


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
	// Nhập chuỗi
	string Number;
	cin >> Number;

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
			x.data[3 - (count / 32)] |= temp; // Or với temp để bật bit
		}

		Number = Number / 2;
		count++;
	}

	// Thực hiện chuyển đổi chuỗi bit dương thành âm, nếu số ban đầu là âm.
	if (sign) {
		doiDau(x);
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

char * DecToHex(QInt x)
{
	bool * ptrBool = DecToBin(x);
	char *ptrHexCode = BinToHex(ptrBool);
	delete[]ptrBool;
	return ptrHexCode;
}

QInt operator+(QInt a, QInt b)
{
	// Thực hiện bù 2
	// Tạo biến lưu kq, tất cả bit setted = 0
	QInt kq;

	int bit1 = b.data[3];
	int bit2 = a.data[3];
	bool ktDu = false; // Kiểm tra số dư

	// Duyệt trên các phần tử int của data
	for (int p = 3; p >= 0; p--)
	{
		// Duyệt trên từng bit của biến int
		for (int k = 32; k >= 1; k--)
		{
			// Lấy các bit tương ứng để cộng
			bit1 = (b.data[p] >> (32 - k)) & 1;
			bit2 = (a.data[p] >> (32 - k)) & 1;

			// Trường hợp không dư
			if (ktDu == false)
			{
				if (bit1 == 1 && bit2 == 1)
					ktDu = 1;
				else if ((bit1 == 1 && bit2 == 0) || (bit1 == 0 && bit2 == 1))
					kq.data[p] |= (1 << (32 - k));
			}
			else // Trường hợp dư
			{
				if (bit1 == 1 && bit2 == 1)
				{
					kq.data[p] |= (1 << (32 - k));
					ktDu = 1;
				}
				else if ((bit1 == 1 && bit2 == 0) || (bit1 == 0 && bit2 == 1))
				{
					ktDu = 1;
				}
				else if (bit1 == 0 && bit2 == 0)
				{
					kq.data[p] |= (1 << (32 - k));
					ktDu = 0;
				}
			}
		}
	}
	return kq;
}

QInt operator-(QInt a, QInt b)
{
	// Thực hiện đổi dấu b
	doiDau(b);

	// Thực hiện phép tính và return
	return a + b;
}

void doiDau(QInt&inp)
{
	// Tìm bit 1 đầu tiên từ cuối lên đầu.
	// How: Dịch bit của biến int sang phải và and với 1
	int storeBit,
		i = 3, j = 0; // 2 biến lưu tạm vtri của bit in data

	// Tìm bit đầu tiên từ cuối = 1
	for (; i >= 0; i--)
	{
		for (j = 0; j < 32; j++)
		{
			// Lấy bit để kiểm tra
			storeBit = (inp.data[i] >> j) & 1;
			if (storeBit == 1) {
				j++; // Tăng lên để nhảy đến bit tiếp theo
				break;
			}
		}
		if (storeBit == 1)
			break;
	}

	// Thực hiện đổi dấu phần còn lại
	// 2 vòng lặp ngoài để duyệt bit
	for (; i >= 0; i--)
	{
		for (; j < 32; j++)
		{
			// thực hiện xor để đổi dấu
			inp.data[i] ^= (1 << j); 
		}
		j = 0; // Set lại j để bắt đầu vòng lặp mới.
	}
}
