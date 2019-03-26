
#include "QInt.h"
#include "UtilityFunc.h"

QInt::QInt()
{
	int i = 0;
	while (i < 4)
		this->data[i++] = 0;
}

QInt::QInt(int inp)
{
	// Xử lý trường hợp số âm
	if (inp < 0)
	{
		int i = 0;
		while (i < 3)
			this->data[i++] = -1;
	}
	this->data[3] = inp;
}

QInt::QInt(const QInt & src)
{
	int i = 0;
	while (i < 4) {
		this->data[i] = src.data[i];
		i++;
	}
}

QInt & QInt::operator=(const QInt & src)
{
	if (this != &src)
	{
		// Copy data
		for (int i = 0; i < 4; i++)
			this->data[i] = src.data[i];
	}
	return *this;
}

QInt QInt::operator+(const QInt & b)const
{
	// Thực hiện bù 2
	// Tạo biến lưu kq, tất cả bit setted = 0
	QInt kq;

	int bit1 = b.data[3];
	int bit2 = this->data[3];
	bool ktDu = false; // Kiểm tra số dư

	// Duyệt trên các phần tử int của data
	for (int p = 3; p >= 0; p--)
	{
		// Duyệt trên từng bit của biến int
		for (int k = 32; k >= 1; k--)
		{
			// Lấy các bit tương ứng để cộng
			bit1 = (b.data[p] >> (32 - k)) & 1;
			bit2 = (this->data[p] >> (32 - k)) & 1;

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

QInt QInt::operator-(const QInt & b)const
{
	// Thực hiện đổi dấu b
	QInt temp = b.doiDau();

	// Thực hiện phép tính và return
	return *this + temp;
}

QInt QInt::operator*(const QInt & b) const
{
	QInt temp = *this, kq;

	int storeBit;
	for (int p = 3; p >= 0; p--)
	{
		for (int k = 32; k >= 1; k--)
		{
			// Lấy lần lượt các bit của b.data 
			storeBit = (b.data[p] >> (32 - k)) & 1;

			// So sánh với 1 để cộng dồn
			if (storeBit == 1)
				kq = kq + temp;

			// Thực hiện dịch trái bit này để
			// làm kq cho phép cộng tiếp theo
			temp = temp << 1;
		}
	}
	return kq;
}

QInt QInt::operator/(const QInt & b) const
{
	// Nếu số bị chia bé hơn số chia trả về 0
	if (*this < b)
		return QInt();

	QInt tempA(*this), tempB(b);
	QInt soDu;
	int temp = 0;

	// 3 câu lệnh if bên dưới kiểm tra xem có phải số âm không.
	// Nếu âm ta đổi dấu là lưu biến temp=1
	if (tempA.ktAm() && tempB.ktAm())
	{
		tempA = tempA.doiDau();
		tempB = tempB.doiDau();
	}
	else if (!tempA.ktAm() && tempB.ktAm())
	{
		tempB = tempB.doiDau();
		temp = 1;
	}
	else if (tempA.ktAm() && !tempB.ktAm())
	{
		tempA = tempA.doiDau();
		temp = 1;
	}

	int k = 128;
	// vòng lặp duyệt 128 bit kiểu Qint
	while (k > 0)
	{
		//ham dich trái bit từ kết quả sang số dư
		soDu.DichTraiDacBiet(tempA);
		soDu = soDu - b;//trừ số dư cho số chia
		if (((soDu.data[0] >> 31) & 1) == 0)//nếu số dư lớn hơn số chia thì bật bit cuối lên 1
		{
			tempA.data[3] |= 1;
		}
		else
		{
			soDu = soDu + tempB;//nếu số dư bé hơn số chia thì công lại
		}
		k--;
	}

	//đổi dấu kết quả cho phù hợp với dấu 2 số truyền vào
	if (temp == 1)
	{
		tempA = tempA.doiDau();
	}

	return tempA;
}

QInt QInt::doiDau() const
{
	// Sao chep dữ liệu để thao tác
	QInt temp(*this);

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
			storeBit = (this->data[i] >> j) & 1;
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
			temp.data[i] ^= (1 << j);
		}
		j = 0; // Set lại j để bắt đầu vòng lặp mới.
	}

	return temp;
}

bool QInt::ktAm() const
{
	return ((this->data[0] >> 31 & 1)) == 1 ? true : false;
}

bool QInt::getBitAtIdx(int idx)const
{
	int i = idx / 32, j = idx % 32;
	int bit = (this->data[i] >> j) & 1;
	return bit == 1 ? true : false;
}

void QInt::DichTraiDacBiet(QInt &a)
{
	if ((a.data[0] >> 32 & 1) == 1)
	{//kiem tra bit đầu của b
	//nếu là một dịch trái b và a sau đó bật bit cuối của a lên 1
		*this = *this << 1;
		a = a << 1;
		this->data[3] |= 1;
	}
	else
	{
		*this = *this << 1;
		a = a << 1;
	}
}

QInt QInt::operator>>(int num) const
{
	// Num nằm trong khoảng từ 0 đến 128. Khác khoảng này, trả về 0
	if (num <= 0 || num >= 128)
		return QInt(-1);

	// Tạo biến phụ để xử lý
	QInt tmp(*this);

	// Biến tạm để xét các phần bit cần dịch
	int i = num / 32, j = num % 32;

	// Tạo bit phụ để AND
	int bitAND = 0;
	for (int cnt = 0; cnt < j; cnt++)
		bitAND |= (1 << cnt);

	// Biến lưu trữ tạm thời phần bit đầu để copy
	// Kiểu unsiged để dịch phải luận lý (không giữ dấu)
	unsigned int storeBit;

	// Lưu trữ lại bit dấu
	bool sign = false; // false số âm; true số dương
	if ((tmp.data[0] >> 31) & 1)
		sign = true;

	for (int count = 3; ; count--)
	{
		// Sao chép các biến int, nếu có sự chênh lệch lớn
		tmp.data[count] = tmp.data[count - i];

		// dịch bit
		tmp.data[count] >>= j;

		// ĐIỀU KIỆN DỪNG
		// Đụng phần tử đầu cần dịch bit thì dừng
		if (count == i)
		{
			// Chuyển phần bit còn lại phía trước thành 0 hoặc 1 
			// tùy trường hợp
			int storeSign = (sign ? -1 : 0); // sign = true,số âm
			for (count--; count >= 0; count--)
				tmp.data[count] = storeSign;
			break;
		}

		// Chuyển bit từ int kế bên
			// sao chép vào biến storeBit
			// Bằng cách and nó với bitAND
		storeBit = (tmp.data[count - i - 1] & bitAND);
		// đẩy các bit của storeBit về phía sau 
		storeBit <<= (32 - j);
		// OR với int đang xét
		tmp.data[count] |= storeBit;
	}
	return tmp;
}

QInt QInt::operator<<(int num)const
{
	// Num nằm trong khoảng từ 0 đến 128. Khác khoảng này, trả về 0
	if (num <= 0 || num >= 128)
		return QInt();

	// Tạo biến phụ để xử lý
	QInt tmp(*this);

	// Biến tạm để xét các phần bit cần dịch
	int i = num / 32, j = num % 32;

	// Tạo bit để OR
	int bitAND = 0;
	for (int cnt = 0; cnt < j; cnt++)
		bitAND |= (1 << (31 - cnt));

	// Biến lưu trữ tạm thời phần bit đầu để copy
	// Kiểu unsiged để dịch phải luận lý (không giữ dấu)
	unsigned int storeBit;

	for (int count = 0; ; count++)
	{
		// Sao chép các biến int, nếu có sự chênh lệch lớn

		tmp.data[count] = tmp.data[count + i];

		// dịch bit
		tmp.data[count] <<= j;

		// Đụng phần tử cuối cần dịch bit thì dừng
		if ((count + 1) == (4 - i))
		{
			// Chuyển phần bit còn lại phía sau thành 0
			for (count++; count < 4; count++)
				tmp.data[count] = 0;
			break;
		}

		// Chuyển bit từ int kế bên
			// sao chép vào biến storeBit
			// Bằng cách and nó với bitAND

		storeBit = (tmp.data[count + i + 1] & bitAND);
		// đẩy các bit của storeBit về phía sau 
		storeBit >>= (32 - j);
		// OR với int đang xét
		tmp.data[count] |= storeBit;
	}
	return tmp;
}

QInt QInt::operator&(const QInt & b)
{
	QInt tmp;

	// Thực hiện AND trên từng int của QInt
	for (int i = 0; i < 4; i++) {
		tmp.data[i] = (this->data[i] & b.data[i]);
	}
	return tmp;
}

QInt QInt::operator|(const QInt & b)
{
	QInt tmp;

	// Thực hiện AND trên từng int của QInt
	for (int i = 0; i < 4; i++) {
		tmp.data[i] = this->data[i] | b.data[i];
	}
	return tmp;
}

QInt QInt::operator^(const QInt & b)
{
	QInt tmp;

	// Thực hiện AND trên từng int của QInt
	for (int i = 0; i < 4; i++) {
		tmp.data[i] = this->data[i] ^ b.data[i];
	}
	return tmp;
}

QInt QInt::operator~() const
{
	QInt tmp;

	// Thực hiện AND trên từng int của QInt
	for (int i = 0; i < 4; i++) {
		tmp.data[i] = ~this->data[i];
	}
	return tmp;
}

bool QInt::operator>(const QInt & a) const
{
	// Trường hợp khác dấu
	if (this->ktAm() != a.ktAm())
		return (this->ktAm() ? false : true);
	
	// Trường hợp cùng dấu.
	// Duyệt tìm sự sai khác bit.
	for (int i = 0; i < 128; i++)
		// Tìm thấy sự sai khác
		if (this->getBitAtIdx(i) != a.getBitAtIdx(i))
		{
			// Cả 2 đều âm
			if (this->getBitAtIdx(i - 1))
				// Nếu bit này = 1 --> *this < a (số âm) --> false
				return this->getBitAtIdx(i) ? false : true;
			else // Cả 2 đều dương
				// Nếu bit này = 1 --> *this > a (số dương) --> true
				return this->getBitAtIdx(i) ? true : false;
		}
		
	// Không tìm thấy sai khác
	return false;
}

bool QInt::operator<(const QInt & a) const
{
	// Trường hợp khác dấu
	if (this->ktAm() != a.ktAm())
		// Số *this là âm thì nhỏ hơn
		return (this->ktAm() ? true : false);

	// Trường hợp cùng dấu.
	// Duyệt tìm sự sai khác bit.
	for (int i = 0; i < 128; i++)
		// Tìm thấy sự sai khác
		if (this->getBitAtIdx(i) != a.getBitAtIdx(i))
		{
			// Cả 2 đều âm
			if (this->getBitAtIdx(i - 1))
				// Nếu bit này = 1 --> *this < a (số âm) --> true
				return this->getBitAtIdx(i) ? true : false;
			else // Cả 2 đều dương
				// Nếu bit này = 1 --> *this > a (số dương) --> false
				return this->getBitAtIdx(i) ? false : true;
		}

	// Không tìm thấy sai khác
	return false;
}

bool QInt::operator>=(const QInt & a) const
{
	return *this < a ? false : true;
}

bool QInt::operator<=(const QInt & a) const
{
	return *this > a ? false : true;
}

bool QInt::operator==(const QInt & a) const
{
	for (int i = 0; i < 128; i++)
		// Tìm thấy sự sai khác
		if (this->getBitAtIdx(i) != a.getBitAtIdx(i))
			return false;

	// Không tìm thấy sai khác
	return true;
}

bool * QInt::DecToBin(QInt x)
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

QInt QInt::BinToDec(bool * bit)
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
char * QInt::BinToHex(bool * bit)
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

char * QInt::DecToHex(QInt x)
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

QInt operator*(QInt a, QInt b)
{
	return QInt();
}

QInt operator/(QInt a, QInt b)
{
	return QInt();
}

bool operator<(const QInt & a, const QInt & b)
{
	return false;
}

bool operator>(const QInt & a, const QInt & b)
{
	return false;
}

bool operator>=(const QInt & a, const QInt & b)
{
	return false;
}

bool operator<=(const QInt & a, const QInt & b)
{
	return false;
}

bool operator==(const QInt & a, const QInt & b)
{
	return false;
}

QInt operator<<(const QInt & a, int b)
{
	return QInt();
}

QInt operator>>(const QInt & a, int b)
{
	return QInt();
}

QInt operator&(const QInt & a, int b)
{
	return QInt();
}

QInt operator|(const QInt & a, int b)
{
	return QInt();
}

QInt operator^(const QInt & a, int b)
{
	return QInt();
}

QInt operator~(const QInt & a)
{
	return QInt();
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

void PrintQInt(QInt x)
{
	string LastDEC = "0";
	string BinToDec = "1";
	int temp;
	int Count = 0;
	int LastBit = 1;
	bool Sign = false;
	if ((x.data[3] & (1 << 31)) == 1) // dịch phải 31 bit tìm bit dấu
	{
		doiDau(x);
		Sign = true;
	}
	for (int iterOnQInt = 3; iterOnQInt >= 0; iterOnQInt++)
	{
		temp = x.data[iterOnQInt];
		while (temp > 0)
		{
			int Bit = temp % 2;
			if (Bit == 1)
			{
				while (LastBit > Count) // LastBit là vị trí bit 1 trước đó, Count là vị trí bit 1 đang xét.
				{
					BinToDec = BinToDec * "2";
					LastBit++;
				}
				LastDEC = LastDEC + BinToDec; // tính giá trị từng bit 1 sau đó cộng vào chuỗi chính
			}
			Count++;
			temp = temp / 2;
		}
	}
	if (Sign == true)
	{
		// thêm dấu trừ vào đầu chuỗi LastDEC cho t nha t k biết thêm sao cho gọn :))
	}
	cout << LastDEC;
}