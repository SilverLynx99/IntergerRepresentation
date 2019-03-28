
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
	int bit = (this->data[i] >> (31 - j)) & 1;
	return bit == 1 ? true : false;
}

void QInt::DichTraiDacBiet(QInt &a)
{
	if (a.getBitAtIdx(0))
	{
		//kiem tra bit đầu của b
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

QInt QInt::rol(int num) const
{
	// Num nằm trong khoảng từ 0 đến 128. Khác khoảng này, trả về 0
	if (num <= 0 || num >= 128)
		return QInt();

	// Tạo biến phụ để xử lý
	QInt tmp(*this);

	//sao chép biến temp để | với biến sau khi dịch
	QInt temp(*this);

	// xử lí nếu bít đầu bằng 1
	if (temp.data[0] >> 31 == 1)
	{
		temp = temp >> 1;
		temp.data[0] = temp.data[0] | (1 << 31);

		//công lên 1 để giảm dịch 1 bit vì đã dịch ở trên
		num++;
	}

	// Biến tạm để xét các phần bit cần dịch
	// dịch trái biến tmp
	tmp = tmp << num;

	//dịch phải biến temp biến 
	temp = temp >> (128 - num);

	//  OR biến temp với tmp để ra kết quả
	tmp = tmp | temp;
	return tmp;
}

QInt QInt::ror(int num) const
{
	// Num nằm trong khoảng từ 0 đến 128. Khác khoảng này, trả về 0
	if (num <= 0 || num >= 128)
		return QInt();

	// Tạo biến phụ để xử lý
	QInt tmp(*this);

	//sao chép biến temp để | với biến sau khi dịch
	QInt temp(*this);

	// xử lí nếu bít đầu bằng 1
	if (temp.data[0] >> 31 == 1)
	{
		temp = temp >> 1;
		temp.data[0] = temp.data[0] | (1 << 31);

		//công lên 1 để giảm dịch 1 bit vì đã dịch ở trên
		num++;
	}

	// Biến tạm để xét các phần bit cần dịch
	// dịch phải biến tmp
	tmp = tmp >> num;

	//dịch trái biến temp biến 
	temp = temp >> (128 - num);

	//  OR biến temp với tmp để ra kết quả
	tmp = tmp | temp;
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
	for (int i = 0; i < 128; i++) {
		// Tìm thấy sự sai khác
		if (this->getBitAtIdx(i) != a.getBitAtIdx(i))
		{
			// Nếu bit này = 1 --> *this > a (số âm) --> true
			// Nếu bit này = 1 --> *this > a (số dương) --> true
			return this->getBitAtIdx(i) ? true : false;
		}
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
	for (int i = 0; i < 128; i++) {
		// Tìm thấy sự sai khác
		if (this->getBitAtIdx(i) != a.getBitAtIdx(i))
		{
			// Nếu bit này = 1 --> *this > a (số âm) --> false

			// Nếu bit này = 1 --> *this > a (số dương) --> false
			return this->getBitAtIdx(i) ? false : true;
		}
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
	hexChar[0] = sign ? '-' : '0';

	// Tìm vị trí của ký tự hex bên trái nhất của chuỗi
	int cntTemp = 1;
	for (; cntTemp < SL_CapPhat - 1; cntTemp++)
		if (hexChar[cntTemp] != '0')
			break;

	// Thực hiện dịch chuỗi đó về đầu
	int k = 0;
	if (sign) k = 1;
	for (; k + cntTemp < SL_CapPhat; k++)
	{
		hexChar[k] = hexChar[k + cntTemp];
	}

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


bool KiemTraOperator(vector<string> optList, string x)
{
	int i;
	for (i = 0; i < optList.size(); i++)
	{
		if (x == optList[i])
			return true;
	}
	return false;
}

// ham chuan hoa chuoi Binary khi do dai khong du 128 bit
void standardStrBin(string &opr)
{
	string tmp = "";
	int i = 0;
	while (i < 128 - opr.length())
	{
		tmp.push_back('0');
		i++;
	}
	tmp += opr;
	opr = tmp;
}

//chuyen doi chuoi ve bool * bin
void str_Bin(bool *opr_bin, string s)
{
	int i;
	for (i = 0; i <= 127; i++)
	{
		if (s[i] == '1')
			opr_bin[i] = 1;
		else
			opr_bin[i] = 0;
	}
}

//chuyen doi bool * ve string
void str_Bool(bool *opr_bin, string &s)
{
	// TH số âm thì copy hết
	if (opr_bin[0])
	{
		int i = 0;
		while (i < 128)
		{
			s.push_back(opr_bin[i] ? '1' : '0');
			i++;
		}
	}
	else
	{
		int i = 0;
		while (i < 128)
		{
			if (opr_bin[i])
				break;
			i++;
		}

		while (i < 128)
		{
			s.push_back(opr_bin[i] ? '1' : '0');
			i++;
		}
	}
}

void CopyBitHexaToBin(string &bit, string bitOfHexCode, int pos)
{
	int i;
	for (i = 3; i >= 0; i--)
	{
		bit[pos] = bitOfHexCode[i];
		pos--;
	}
}

//Chuyen HEXA ve BINARY
string HexToBin(string hex)
{
	string bit;
	bit.resize(128);
	int i;
	for (i = 0; i < 128; i++)
	{
		bit[i] = '0';
	}
	vector<string> listBitOfHexCode;
	listBitOfHexCode.push_back("0000");
	listBitOfHexCode.push_back("0001");
	listBitOfHexCode.push_back("0010");
	listBitOfHexCode.push_back("0011");
	listBitOfHexCode.push_back("0100");
	listBitOfHexCode.push_back("0101");
	listBitOfHexCode.push_back("0110");
	listBitOfHexCode.push_back("0111");
	listBitOfHexCode.push_back("1000");
	listBitOfHexCode.push_back("1001");
	listBitOfHexCode.push_back("1010");
	listBitOfHexCode.push_back("1011");
	listBitOfHexCode.push_back("1100");
	listBitOfHexCode.push_back("1101");
	listBitOfHexCode.push_back("1110");
	listBitOfHexCode.push_back("1111");

	int j = hex.length() - 1;
	int lenOfBitHex = 128 - 4 * hex.length();
	for (i = 127; i >= lenOfBitHex; i -= 4)
	{
		if (hex[j] >= 48 && hex[j] <= 57)
		{
			CopyBitHexaToBin(bit, listBitOfHexCode[hex[j] - 48], i);
		}
		else if (hex[j] >= 65 && hex[j] <= 70)
		{
			CopyBitHexaToBin(bit, listBitOfHexCode[hex[j] - 55], i);
		}
		j = j - 1;
	}

	return bit;
}

void processFileandOutput(istream& inputFile, ostream& outputFile)
{
	// opr1 : Toán hạng 1
	// opr2 : Toán hạng 2
	// opt : Toán tử
	string p1, p2, opt, opr1, opr2, ptemp, ptemp2;

	// Tạo DS các toán tử để so sánh với kq thu được từ input file
	vector<string> optList = { "+", "-", "*", "/", "<", ">", "<=", ">=", "==", "=", "<<", ">>", "rol", "ror", "&", "|", "^", "~" };

	while (!inputFile.eof())
	{
		// Gán mặc định cho các tp
		p1 = "", p2 = "", ptemp = "", ptemp2 = "", opt = "", opr1 = "", opr2 = "";

		// Đọc cơ số đầu tiên vào p1
		// Đọc số tiếp theo vào ptemp để kiểm tra
		inputFile >> p1;
		inputFile >> ptemp;

		// Thực hiện phép chuyển đổi giữa các hệ
		if (ptemp == "2" || ptemp == "10" || ptemp == "16")
		{
			// Đọc tiếp để kiểm tra thành phần phía sau là toán tử hay số
			inputFile >> ptemp2;

			// Trường hợp nếu ptemp2 không là toán tử thì ta thực hiện chuyển đổi cơ số
			if (KiemTraOperator(optList, ptemp2) == false)
			{
				// Lúc này t chuyển cơ số vào p2 và toán hạng chuyển đổi vào opr1
				p2 = ptemp;
				opr1 = ptemp2;

				// Xử lý chuỗi để đưa vào hàm
				// Trường hợp chuỗi đầu vào là nhị phân
				bool * opr1_Bin = new bool[128];
				if ((p1 == "2") && (opr1.length() < 128))
				{
					standardStrBin(opr1);
					// PHÁT VIẾT CHỖ NÀY, DÙNG VÒNG LẶP HA
					// Chuyển đỗi chuỗi về dạng mảng bool * gồm 128 byte
					// Sử dụng cấp phát động và nhớ hủy vùng nhớ bên dưới
					// Sử dụng mảng bool này để đưa vào hàm BinToDec và BinToHex

					str_Bin(opr1_Bin, opr1);
				}

				// Trường hợp chuỗi đầu vào là thập phân
				// Ta dùng stringstream để đưa nó vào QInt
				// NOTE CHO PHÁT: LÚC NÀY T DÙNG BIẾN  oper1 để input vào
				// các hàm chuyển đổi còn lại
				QInt oper1;
				if (p1 == "10")
				{
					// CHUYỂN LẠI THÀNH STRINGSTREAM
					stringstream operator1(opr1);

					operator1 >> oper1;
				}

				//xu li dong tai day voi bien opr1 la toan hang duy nhat cua dong
				if (p1 == "10" && p2 == "2")
				{
					//thuc hien chuyen doi DecToBin
					bool * bin = QInt::DecToBin(oper1);
					
					string temp;
					str_Bool(bin, temp);

					outputFile <<temp << endl;
					delete[] bin;
				}
				else if (p1 == "2" && p2 == "10")
				{
					//thuc hien chuyen doi BinToDec
					QInt res;
					res = QInt::BinToDec(opr1_Bin);
					outputFile << res << endl;
					delete[] opr1_Bin;
				}
				else if (p1 == "2" && p2 == "16")
				{
					//thuc hien chuyen doi BinToHex
					QInt res;
					char *rs = res.BinToHex(opr1_Bin);
					outputFile << rs << endl;
					delete[] opr1_Bin;
				}
				else
				{
					//thuc hien chuyen doi DecToHex
					QInt res;
					char *rs = res.DecToHex(oper1);
					outputFile << rs << endl;
				}
			}

			// ptemp2 là toán tử, ta đọc tiếp toán hạng thứ 2
			else
			{
				opr1 = ptemp;
				opt = ptemp2;

				// Đọc toán hạng thứ 2
				if (opt != "~")
					inputFile >> opr2;

				// Thực hiện chuẩn hóa chuỗi nếu cả 2 toán hạng đều là chuỗi nhị phân
				if ((p1 == "2") && (opr1.length() < 128))
				{
					standardStrBin(opr1);
				}
				if ((p1 == "2") && (opr2.length() < 128))
				{
					standardStrBin(opr2);
				}
			}
		}

		// Thuc hien doc tiep cac thong tin 
		// cua cac dong co toan tu (+, - , *, /, <, >, ...)
		else
		{
			opr1 = ptemp; //copy ptemp vao opr1(toan hang thu 1)
			inputFile >> opt; //doc toan tu

			if (opt != "~")
				inputFile >> opr2; //doc toan hang thu 2

			if ((p1 == "2") && (opr1.length() < 128))
			{
				standardStrBin(opr1);
			}
			if ((p1 == "2") && (opr2.length() < 128))
			{
				standardStrBin(opr2);
			}
		}

		// Tạo thêm 2 biến kiểu QInt để thực hiện phép toán
		QInt oper1, oper2;
		if (opt != "")
		{

			if (p1 == "2") {
				// Thực hiện đưa thẳng các bit này vào QInt luôn, bằng tay
				bool *str_bin1 = new bool[128];
				bool *str_bin2 = new bool[128];
				str_Bin(str_bin1, opr1);
				str_Bin(str_bin2, opr2);
				oper1 = oper1.BinToDec(str_bin1);
				oper2 = oper2.BinToDec(str_bin2);
				delete[] str_bin1;
				delete[] str_bin2;
			}

			if (p1 == "16")
			{
				// Chuyển chuỗi này về dạng chuỗi thập phân rồi đưa vào QInt luôn
				string b1, b2;
				b1 = HexToBin(opr1);
				b2 = HexToBin(opr2);
				bool *str_bin1 = new bool[128];
				bool *str_bin2 = new bool[128];
				str_Bin(str_bin1, b1);
				str_Bin(str_bin2, b2);
				oper1 = oper1.BinToDec(str_bin1);
				oper2 = oper2.BinToDec(str_bin2);
				delete[] str_bin1;
				delete[] str_bin2;
			}

			if (p1 == "10")
			{
				// Đưa thẳng chuỗi này về dạng QInt bằng stringstream
				stringstream ss1(opr1), ss2(opr2);
				ss1 >> oper1;
				ss2 >> oper2;
			}
		}

		// Biên lưu lại kq
		QInt result;

		// THỰC HIỆN cac dong co toan tu (+, -, *, /, <, >, ...)
		if (opt != "")
		{
			if (opt == "+")
			{
				//thuc hien toan tu CONG
				result = oper1 + oper2;

			}

			else if (opt == "-")
			{
				//thuc hien toan tu TRU
				result = oper1 - oper2;

			}
			else if (opt == "*")
			{
				//thuc hien toan tu NHAN
				result = oper1 * oper2;

			}
			else if (opt == "/")
			{
				//thuc hien toan tu CHIA
				result = oper1 / oper2;

			}
			else if (opt == "<" || opt == ">" || opt == "<=" || opt == ">=" || opt == "==")
			{
				// Tạo biến lưu kq
				bool resultComparison = false;

				if (opt == "<")
				{
					//thuc hien so sanh BE HON
					resultComparison = oper1 < oper2;
				}
				else if (opt == ">")
				{
					//thuc hien so sanh LON HON
					resultComparison = oper1 > oper2;
				}
				else if (opt == "<=")
				{
					//thuc hien so sanh BE BANG
					resultComparison = oper1 <= oper2;
				}
				else if (opt == ">=")
				{
					resultComparison = oper1 >= oper2;
				}
				else if (opt == "==")
				{
					//thuc hien so sanh BANG
					resultComparison = oper1 == oper2;
				}
				if (resultComparison == true)
					outputFile << "True" << endl;
				else
					outputFile << "False" << endl;
			}
			else if (opt == "&")
			{
				//thuc hien toan tu AND
				result = oper1 & oper2;

			}
			else if (opt == "|")
			{
				//thuc hien toan tu OR
				result = oper1 | oper2;

			}
			else if (opt == "^")
			{
				//thuc hien toan tu XOR
				result = oper1 ^ oper2;

			}
			else if (opt == "~")
			{
				//thuc hien toan tu NOT
				result = ~oper1;

			}
			else if (opt == "<<" || opt == ">>" || opt == "rol" || opt == "ror")
			{
				stringstream ss(opr2);
				int num;
				ss >> num;
				if (opt == "<<")
				{
					//thuc hien toan tu DICH TRAI
					result = oper1 << num;

				}
				else if (opt == ">>")
				{
					//thuc hien toan tu DICH PHAI
					result = oper1 >> num;

				}
				else if (opt == "rol")
				{
					//thuc hien toan tu XOAY TRAI
					result = oper1.rol(num);

				}
				else if (opt == "ror")
				{
					//thuc hien toan tu XOAY PHAI
					result = oper1.ror(num);

				}
			}
		}

		// Nếu p1 bằng 16, chuyển đổi result về dạng hex
		if (opt == "+" || opt == "-" || opt == "*" || opt == "/" || opt == "&"
			|| opt == "|" || opt == "^" || opt == "~" || opt == ">>" || opt == "<<" || opt == "ror" || opt == "rol") {
			if (p1 == "16")
			{
				string temp(QInt::DecToHex(result));

				outputFile << temp << endl;
			}
			else if (p1 == "2")
			{
				bool * ptrBool = QInt::DecToBin(result);
				string temp;

				// Chuyển đổi từ chuỗi bool sang string 
				str_Bool(ptrBool, temp);
				// ---

				outputFile << temp << endl;
				delete[]ptrBool;
			}
			else if (p1 == "10")
			{
				outputFile << result << endl;
			}
		}
	}
}
