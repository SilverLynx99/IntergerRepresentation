#include "QFloat.h"
#include "UtilityFunc.h"

void ScanQfloat(Qfloat &x)
{
	string NumberFloat = "-8123124.5869140625";
	string DECint; // chứa phần nguyên
	string DECfloat; // chứa phần thực
	vector<int> bitSignAndExp; // chứa bit dấu và mũ
	vector<int> bitFract; // chứa bit phần định trị
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

	while (DECint != "0") //Chuyển phần nguyên sang dạng bit
	{
		int temp = DECint % 2;
		bitFract.push_back(temp);
		DECint = DECint / 2;
	}
	bitFract.pop_back(); // xóa bit đầu tiên của phần nguyên tức là bit cuối của mảng
	int i, E = bitFract.size() + 16383; //Mũ bằng số phần tử phần nguyên trừ 1 cộng 2^14 - 1
	reverse(bitFract.begin(), bitFract.end()); //Đảo lại thứ tự bit

	while (DECfloat != ".0") //Chuyển phần thực sang bit
	{
		DECfloat = mulReal(DECfloat, 2);
		if (DECfloat[0] == '1')
		{
			bitFract.push_back(1);
			DECfloat = subReal(DECfloat, "1");
		}
		else
			bitFract.push_back(0);
	}

	//Nếu không đủ 112 bit phần định trị thì chèn thêm bit 0
	if (bitFract.size() < 112)
		for (i = bitFract.size(); i < 112; i++)
			bitFract.push_back(0);

	//Chuyển mũ sang bit
	while (E != 0)
	{
		bitSignAndExp.push_back(E % 2);
		E /= 2;
	}

	//Nếu không đủ 15 bit phần mũ thì chèn thêm bit 0
	if (bitSignAndExp.size() < 15)
		for (i = bitSignAndExp.size(); i < 15; i++)
			bitFract.push_back(0);

	bitSignAndExp.push_back(SignBit); // đưa bit dấu vào đầu
	reverse(bitSignAndExp.begin(), bitSignAndExp.end()); //Đảo lại thứ tự bit của dấu và mũ
	///////////////////////////////
	unsigned int Base10 = 0; // số nguyên 32 bit 
	int count = 0;
	index = 0;
	for (i = 0; i < 128; i++) // đổi các bit phần nguyên và phần thực sang Qfloat
	{
		// kết thúc mỗi 32 bit thì gán Base10 vào một phần tử của QFloat và bắt đầu Base10 lại từ đầu
		if (count == 32)
		{
			x.Data[index++] = Base10;
			count = 0;
			Base10 = 0;
		}

		// 32 bit đầu chia làm 2 phần, 16 bit phần bitSignAndExp và 16 bit phần bitFract
		if (i <= 15)
		{
			Base10 += pow(2, count) * bitSignAndExp[i];
			count++;
		}
		else
		{
			Base10 += pow(2, count) * bitFract[i - 16];
			count++;
		}
	}
}
