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
		// Tìm bit 1 đầu tiên từ cuối lên đầu.
		// How: Dịch bit của biến int sang phải và and với 1
		int idOfData, // vị trí ô nhớ trong mảng "data"
			numOfBit; // số lượng bit cần dịch

		int i = 127;
		do {
			idOfData = i / 32;
			numOfBit = 31 - (i % 32);
			i--;
		} while (!((x.data[idOfData] >> numOfBit) & 1));

		// Thực hiện bù
		// Bằng cách xor số int với số có bit được bật ở vtri numOfBit 
		do {
			i--;
			idOfData = i / 32;
			numOfBit = 31 - (i % 32); // Tính từ cuối lên đầu
			x.data[idOfData] ^= (1 << numOfBit);
		} while (i > 0);
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

//char * DecToHex(QInt x)
//{
//	bool * ptrBool = DecToBin(x);
//	char *ptrHexCode = BinToHex(ptrBool);
//	delete[]ptrBool;
//	return ptrHexCode;
//}

QInt operator+(QInt a, QInt b)
{
	int i = b.data[3];
	int j = a.data[3], temp = 0;
	QInt kq;
	for (int p = 3; p >= 0; p--)
	{
		for (int k = 32; k >= 1; k--)
		{
			i = (b.data[p] >> 32 - k) & 1;
			j = (a.data[p] >> 32 - k) & 1;

			if (temp == 0)
			{
				if (i == 1 && j == 1)
				{
					temp = 1;

				}
				if (i == 1 && j == 0 || i == 0 && j == 1)
				{
					kq.data[p] |= (1 << (32 - k));
					temp = 0;
				}
			
			}
			else
			{
				if (i == 1 && j == 1)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - k));
					temp = 1;
				}
				if (i == 1 && j == 0)
				{
					temp = 1;
				}
				if (i == 0 && j == 1)
				{
					//kq.data[p] = kq.data[p] | (1 << (32 - 1 - k));
					temp = 1;
				}
				if (i == 0 && j == 0)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - k));
					temp = 0;
				}
			}
		}
		cout << endl;
	}
	//cout<<(1<<31)
	//cout << kq.data[3]<<endl;
	//cout << kq.data[2];
	return kq;
}

QInt operator-(QInt a, QInt b)
{
	int i = b.data[3];
	int j = a.data[3], temp = 0;
	QInt kq;
	for (int p = 3; p >= 0; p--)
	{

		for (int k = 32; k >= 1; k--)
		{
			i = (a.data[p] >> 32 - k) & 1;
			j = (b.data[p] >> 32 - k) & 1;

			if (temp == 0)
			{
				if (i == 1 && j == 1)
				{
					//temp = 1;

				}
				if (i == 1 && j == 0)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - k));

				}
				if (i == 0 && j == 1)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - k));
					temp = 1;
				}
				/*if (i == 0 && j == 0)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - 1 - k));
					temp = 0;
				}
				*/
			}
			else
			{
				if (i == 1 && j == 1)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - k));
					temp = 1;
				}
				if (i == 1 && j == 0)
				{
					//kq.data[p] = kq.data[p] | (1 << (32 - 1 - k));
					temp = 0;
				}
				if (i == 0 && j == 1)
				{
					//kq.data[p] = kq.data[p] | (1 << (32 - 1 - k));
					temp = 1;
				}
				if (i == 0 && j == 0)
				{
					kq.data[p] = kq.data[p] | (1 << (32 - k));
					temp = 1;
				}
			}
		}
		cout << endl;

	}
	//cout<<(1<<31)
	/*cout << kq.data[3] << endl;
	cout << kq.data[2];
	cout << kq.data[1];
	cout << kq.data[0];
	*/
	return kq;
}

QInt ShiftLeft1(QInt & a)
{
	if ((a.data[3] >> 31 & 1) == 1)
	{
		a.data[3] = a.data[3] << 1;
		if ((a.data[2] >> 31 & 1) == 1)
		{
			a.data[2] = a.data[2] << 1;
			a.data[2] = a.data[2] | 1;
			if ((a.data[1] >> 31 & 1) == 1)
			{
				a.data[1] = a.data[1] << 1;
				a.data[1] = a.data[1] | 1;
				a.data[0] = a.data[0] << 1;
				a.data[0] = a.data[0] | 1;
			}
			else
			{
				a.data[1] = a.data[1] << 1;
				a.data[1] = a.data[1] | 1;
				a.data[0] = a.data[0] << 1;


			}
		}
		else
		{
			a.data[2] = a.data[2] << 1;
			a.data[2] = a.data[2] | 1;
			if ((a.data[1] >> 31 & 1) == 1)
			{
				a.data[1] = a.data[1] << 1;
				a.data[0] = a.data[0] << 1;
				a.data[0] = a.data[0] | 1;
			}
			else
			{
				a.data[1] = a.data[1] << 1;
				a.data[0] = a.data[0] << 1;
			}
		}
	}
	else
	{
		a.data[3] = a.data[3] << 1;
		if ((a.data[2] >> 31 & 1) == 1)
		{
			a.data[2] = a.data[2] << 1;
			if ((a.data[1] >> 31 & 1) == 1)
			{
				a.data[1] = a.data[1] << 1;
				a.data[1] = a.data[1] | 1;
				a.data[0] = a.data[0] << 1;
				a.data[0] = a.data[0] | 1;
			}
			else
			{
				a.data[1] = a.data[1] << 1;
				a.data[1] = a.data[1] | 1;
				a.data[0] = a.data[0] << 1;
			}
		}
		else
		{
			a.data[2] = a.data[2] << 1;
			if ((a.data[1] >> 31 & 1) == 1)
			{
				a.data[1] = a.data[1] << 1;
				a.data[0] = a.data[0] << 1;
				a.data[0] = a.data[0] | 1;
			}
			else
			{
				a.data[1] = a.data[1] << 1;
				a.data[0] = a.data[0] << 1;
			}
		}
	}


	return QInt();
}

QInt ShiftLeftChia(QInt & b, QInt &a)
{
	if ((a.data[0] >> 31 & 1) == 1)
	{
		ShiftLeft1(b);
		b.data[3] = b.data[3] | 1;
		ShiftLeft1(a);
	}
	else
	{
		ShiftLeft1(b);
		ShiftLeft1(a);
	}
	return QInt();
}

/*QInt ShiftRight(QInt & a)
{
	if((a.data[0] & 1) == 1)
	{
		a.data[1] = a.data[1] | 1 << 31;
	}
	if((a.data[1] & 1) == 1)
	{
		a.data[2] = a.data[2] | 1 << 31;
	}
	if((a.data[2] & 1) == 1)
	{
		a.data[3] = a.data[3] | 1 << 31;
	}
	return a;
}
*/


QInt operator*(QInt a, QInt b)
{
	QInt kq;
	QInt tam = a;
	for (int p = 3; p >= 0; p--)
	{

		for (int k = 32; k >= 1; k--)
		{
			if ((b.data[p] >> (32 - k) & 1) == 1)
			{
				kq = (kq + tam);
				ShiftLeft1(tam);
			}
			else
			{
				ShiftLeft1(tam);
			}
		}
	}
	return kq;
}

/*QInt operator/(QInt a, QInt b)
{
	QInt kq=a;
	QInt tam;
	if (a.data[0] >> 31 & 1 == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			tam.data[i] = -1;
		}
	}
	int k = 128;
	while (k > 0)
	{
		QInt tam1;
		ShiftLeftChia(tam, kq);
		tam1 = tam - b;
		if (tam1.data[0] >> 31 & 1 == 0)
		{
			kq.data[3] = kq.data[3] | 1;
			tam = tam - b;
		}
		k--;
	}
	//cout << tam.data[3]<<endl;
	return kq;
}
*/
