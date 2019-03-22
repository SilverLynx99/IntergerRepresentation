#include "QFloat.h"

void ScanQfloat(Qfloat &x)
{
	string NumberFloat = "-8123124.1241290294112903";
	string DECint; // chứa phân nguyên
	string DECfloat; // chứa phần thực
	int bias = pow(2, 14) - 1;
	int Change = 0;
	int SizeDECint = 0;
	int SizeDECfloat = 0;
	vector<int> BitInt; // chứa phần nguyên dạng bit
	vector<int> BitFloat; // chứa phần thực dạng bit
	int base10 = 0; // số nguyên 32 bit 
	int SignBit = 0; // bit dấu
	//Kiểm số âm or dương
	if (NumberFloat[0] == '-') // trường hợp chuỗi số âm
	{
		SignBit = 1;
		NumberFloat.erase(0, 1);
	}

	int index = NumberFloat.find('.'); //Tìm vị trí dấu thập phân
	//Tách phần nguyên và thập phân
	DECint = NumberFloat.substr(0, index);
	DECfloat = NumberFloat.substr(index);
	DECfloat.insert(0, 1, '0'); //Chèn thêm số 0 ở phần thập phân

	while (DECint != "0") // đổi phần nguyên sang dạng bit
	{
		int temp = DECint % 2;
		BitInt.push_back(temp);
		DECint = DECint / 2;
	}
	int E = BitInt.size() - 1 + bias;
	int bit;
	while (DECfloat != "1.0") //chuyển phần thực sang bit
	{
		mulReal(NumberFloat, 2);
		if (NumberFloat[0] == '1')
		{
			bit = 1;
		}
		else
			bit = 0;
		BitFloat.push_back(bit);
	}
	if (BitFloat.size() < 32) 
	{
		for (int i = BitFloat.size(); i < 32; i++)
		{
			BitFloat.push_back(0);
		}
	}
	BitInt.pop_back(); // xóa bit đầu tiên
	for (int i = 0; i < 14; i++) // đổi số E sang dạng bit
	{
		int temp = E % 2;
		BitInt.push_back(temp);
		E = E / 2;
	}
	BitInt.push_back(SignBit); // đưa bit dấu vào đầu
	///////////////////////////////
	int Base10 = 0;
	int Condition = 0;
	int Count = 0;
	int SizeX = 0;
	for (int i = 0; i < 32; i++) // đổi các bit phần nguyên và phần thực sang Qfloat
	{
		if (Condition == 0) // 32 bit đầu chia làm 2 phần, 16 bit phần BitInt và 16 bit phần BitFloat
		{
			if (i <= 15)
			{
				Base10 += pow(2, Count) * BitFloat[15 - i]; // ta chạy ngược từ cuối lên đầu
				Count++;
			}
			if (i > 15 && i < 32)
			{
				Base10 += pow(2, Count) * BitInt[31 - i];
				Count++;
				if (i == 31) // kết thúc 32 bit đầu
				{
					Condition = 1;
					Count = 0;
					x.Data[SizeX++] = Base10;
					Base10 = 0;
				}
			}
		}
		else
		{
			int temp = 32;
			while (temp < BitFloat.size()) // đưa các bit phần thực còn lại vào QFloat
			{
				Base10 += pow(2, 31 - Count) * BitFloat[temp - 16]; // 2^31 * BitFloat[16] + 2^30 * BitFloat[17] + 2^29 * BitFloat[18] + ... 2^0 * BitFloat[47].
				temp++;
				Count++;
				if (temp % 32 == 0) // 32 bit thì đưa vào QFloat
				{
					x.Data[SizeX++] = Base10;
					Base10 = 0;
					Count = 0;
				}
			}
			if (SizeX < 4)
			{
				x.Data[SizeX] = Base10;
			}
			break;
		}

	}
}
