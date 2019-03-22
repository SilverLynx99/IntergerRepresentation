#include "QFloat.h"

void ScanQfloat(Qfloat &x)
{
	string NumberFloat = "-8123124.1241290294112903";
	string DECint;
	string DECfloat;
	int bias = pow(2, 14) - 1;
	int Change = 0;
	int SizeDECint = 0;
	int SizeDECfloat = 0;
	vector<int> BitInt;
	vector<int> BitFloat;
	int base10 = 0;
	int SignBit = 0;
	//Kiểm số âm or dương
	if (NumberFloat[0] == '-')
	{
		SignBit = 1;
		NumberFloat.erase(0, 1);
	}

	int index = NumberFloat.find('.'); //Tìm vị trí dấu thập phân
	//Tách phần nguyên và thập phân
	DECint = NumberFloat.substr(0, index);
	DECfloat = NumberFloat.substr(index);
	DECfloat.insert(0, 1, '0'); //Chèn thêm số 0 ở phần thập phân

	while (DECint != "0")
	{
		int temp = DECint % 2;
		BitInt.push_back(temp);
		DECint = DECint / 2;
	}
	int E = BitInt.size() - 1 + bias;

}
