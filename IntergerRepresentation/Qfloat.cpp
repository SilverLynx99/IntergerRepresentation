﻿#include "QFloat.h"
#include "UtilityFunc.h"

void ScanQfloat(Qfloat &x)
{
	string NumberFloat = "0.392578125";
	string DECint; // chứa phần nguyên
	string DECfloat; // chứa phần thực
	vector<char> bitFract; // chứa bit phần định trị
	int SignBit = 0; // bit dấu

	//Kiểm số âm or dương
	if (NumberFloat[0] == '-') // trường hợp chuỗi số âm
	{
		SignBit = 1;
		NumberFloat.erase(0, 1); //Xóa dấu trừ
	}

	//////////////////////////////////////////////////////
	//Tách phần nguyên và thập phân
	int index = NumberFloat.find('.'); //Tìm vị trí dấu thập phân
	//Tách phần nguyên và thập phân 
	if (index != -1) //Nếu có dấu thập phân
	{
		DECint = NumberFloat.substr(0, index);
		DECfloat = NumberFloat.substr(index);
		DECfloat.insert(0, 1, '0'); //Chèn thêm số 0 ở phần thập phân
	}
	else
		DECint = NumberFloat;

	/////////////////////////////////////////////
	//Chuyển sang bit
	//Chuyển phần nguyên sang dạng bit
	int i, E;
	bool check = false; //Kiểm tra xem phần nguyên có khác 0
	while (DECint.compare("0") != 0)
	{
		bitFract.push_back((DECint % 2) + '0');
		DECint = DECint / 2;
	}

	if (bitFract.size() != 0) //Phần nguyên khác 0
	{
		bitFract.pop_back(); // xóa bit đầu tiên của phần nguyên tức là bit cuối của mảng
		E = bitFract.size() + 16383; //Mũ bằng số phần tử phần nguyên trừ 1 cộng 2^14 - 1
		reverse(bitFract.begin(), bitFract.end()); //Đảo lại thứ tự bit
	}
	else
		check = true;

	//Chuyển phần thực sang bit
	while ((DECfloat != ".0") && (DECfloat.size() != 0))
	{
		DECfloat = mulReal(DECfloat, 2);
		if (DECfloat[0] == '1')
		{
			bitFract.push_back('1');
			DECfloat = subReal(DECfloat, "1");

			if (check) //Xét đc bit 1 đầu tiên trong trường hợp phần nguyên bằng 0
			{
				E = 16383 - bitFract.size(); //Mũ âm do phần nguyên bằng 0 rồi cộng cho 2^14 - 1
				check = false; //Đổi lại trạng thái sau khi xét được bit 1 đầu tiên
				//Lấy hết bit trước đó ra
				while (!bitFract.empty())
					bitFract.pop_back();
			}
		}
		else
			bitFract.push_back('0');
	}

	//Chuyển mũ sang bit và chèn bit dấu ở đầu
	//Đẩy bit trực tiếp vào x.Data[0]
	int temp; //Biến chứa bit để sử dung các toán tử bật bit
	int count; //Biến đếm
	count = 16;
	while (E != 0) //16 bit đầu
	{
		temp = E % 2;
		if (temp == 1)
		{
			temp <<= count;
			x.Data[0] |= temp;
		}
		E /= 2;
		count++;
	}

	//Chèn bit dấu ở đầu
	if (SignBit == 1)
	{
		SignBit <<= 31;
		x.Data[0] |= SignBit;
	}

	///////////////////////////////
	count = 15; //Đầu tiên xét tiếp 16 bit còn lại của x.Data[0]
	index = 0;
	for (i = 0; i < bitFract.size(); i++) // đổi các bit phần nguyên và phần thực sang Qfloat
	{
		// kết thúc mỗi 32 bit thì tăng index và set count trở về ban đầu
		if (count == -1)
		{
			index++;
			count == 31; //Sau khi xong 32 bit đầu set count = 31 để sang x.Data[1]
		}

		temp = bitFract[i] - '0';
		if (temp == 1)
			temp <<= count;
		x.Data[index] |= temp;
		count--;
	}
}



Qfloat BinToDec(bool *bit)
{
	Qfloat tempStorage;

	// Biến lưu lại chuỗi bit để thực hiện phép OR
	int bitforOR;

	// Duyệt trên mảng bool.
	for (int iterOnBit = 0; iterOnBit <= 127; iterOnBit++)
	{
		// Nếu đúng, bật bit tại đúng vị trí của tempStorage
		if (bit[iterOnBit]) {
			bitforOR = (1 << (31 - (iterOnBit % 32)));
			tempStorage.Data[iterOnBit / 32] |= bitforOR;
		}
	}

	return tempStorage;
}


bool *DecToBin(Qfloat x)
{
	// Allocate an array of bool (128B), every bool store a bit
	bool *bitArray = new bool[128];

	// Set các bit bằng 0
	for (int i = 0; i < 127; i++)
		bitArray[i] = false;

	// Biến tạm
	int temp, iterOnbitArray = 1;

	// Duyệt trên từng khối int của Qfloat (4 khối
	for (int iterOnQInt = 3; iterOnQInt >= 0; iterOnQInt--)
	{
		// Lưu tạm từng khối int để xử lý
		temp = x.Data[iterOnQInt];

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


void printQFloat(Qfloat x)
{
	string LastFloat = "0";
	string QFloatToFloat = "1";
	string QfloatToBin;
	bool sign = false;
	int E = 0;
	int DEC;
	int Mu;
	int LastBit;
	for (int iterOnQFloat = 0; iterOnQFloat < 4; iterOnQFloat++)
	{
		int temp = x.Data[iterOnQFloat];
		LastBit = 0;              // là vị trí của bit 1 trước đó so với bit 1 đang xét trong phần tính thập phân
		for (int i = 0; i <= 31; i++)
		{
			int Bit = temp >> i;
			if (iterOnQFloat == 0)
			{
				if (Bit == 1 && i == 0)
				{
					sign = true;
					continue;
				}
				if (i <= 15) // tìm E
				{
					E += pow(2, 15 - i) * Bit;
				}
				if (i == 16) // tìm Mũ
				{
					Mu = E - pow(2, 14) + 1;
					DEC = pow(2, Mu); // đây là giá trị bit 1 đầu tiên của phần nguyên
				}
				if (i > 16)
				{
					while (Mu > 0) // tìm giá trị của phần nguyên
					{
						DEC += pow(2, 16 + Mu - i);
						Mu--;
						i++;
						LastBit = i; // nhớ bit đầu cho phần thập phân
						Bit = temp >> i;
					}
					if (Bit == 1) 
					{
						while (LastBit <= i) // chạy từ bit trước đó đến bit tại vị trí i
						{
							QFloatToFloat = QFloatToFloat / 2;
							LastBit++;
						}
						LastFloat = LastFloat + QFloatToFloat; // + vô kết quả cuối
					}
				}
			}
			else
			{
				if (Bit == 1)
				{
					while (LastBit <= i)
					{
						QFloatToFloat = QFloatToFloat / 2;
						LastBit++;
					}
					LastFloat = LastFloat + QFloatToFloat;
				}
			}
		}
	}
	LastFloat = LastFloat + to_string(DEC);
	cout << LastFloat;
}