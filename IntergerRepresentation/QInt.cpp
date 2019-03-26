
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
	return false;
}

bool QInt::operator<(const QInt & a) const
{
	return false;
}

bool QInt::operator>=(const QInt & a) const
{
	return false;
}

bool QInt::operator<=(const QInt & a) const
{
	return false;
}

bool QInt::operator==(const QInt & a) const
{
	return false;
}
