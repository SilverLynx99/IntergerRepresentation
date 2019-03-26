#include "QFloat.h"

void ScanQfloat(Qfloat &x)
{
	string NumberFloat = "-5.25";
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
	while ((DECfloat != "0.0") && (DECfloat.size() != 0))
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

void PrintQfloat(Qfloat x)
{
	int i, exp = 0, temp1, temp2;
	bool sign = false;
	//Lấy phần mũ và dấu
	//Lấy phần mũ
	temp1 = x.Data[0] >> 16;
	for (i = 0; i <= 14; i++)
	{
		temp2 = (temp1 >> i) & 1;
		if (temp2 == 1)
			exp |= (temp2 << i);
	}
	exp -= 16383; //Trừ đi 2^14-1 để ra được số E
	//Lấy phần dấu
	temp1 >>= 15;
	if ((temp1 & 1) == 1)
		sign = true;

	////////////////////////////////////////
	//Lấy phần nguyên và thập phân
	//Lấy phần nguyên
	string dec = "0"; //Chuỗi chứa phần nguyên
	string add = "1"; //Chuỗi tính phép 2 mũ 
	int count = 0; //Tính vị trí của bit
	int countExp = 0; //Tính mũ để nhân 2
	int bit; //Lấy bit
	bool check = false; //Nếu phần nguyên = 0 thì phần thập phân sẽ có thêm một bit 1 ở đầu
	int j, index, moveBit;
	if (exp == 0) //Khi mũ = 0
	{
		dec = "1";
		index = 0;
		temp1 = x.Data[0] >> 16;
	}
	else if (exp > 0) //Khi mũ > 0, nếu mũ < 0 thì phần nguyên = 0
	{
		int max;
		index = 3 - (112 - exp) / 32; //Lấy vị trí mảng Qfloat
		moveBit = (112 - exp) % 32; //Tính số bit cần dịch phải
		temp1 = x.Data[index] << (32 - moveBit); //Dịch trái để lấy phần thập phân 
		temp2 = x.Data[index] >> moveBit; //Dịch bit sang phải để lấy bit phần nguyên
	
		if (index != 0) //Tính lượng bit cần duyệt ở mỗi ô Qfloat
			max = 32 - moveBit;
		else
			max = 16 - moveBit;

		for (i = index; i >= 0; i--) //Duyết từ phải qua trái
		{
			if (i != index)
			{
				temp2 = x.Data[i]; //Gán ô tiếp theo
				if (i == 0) //Cập nhật max sau mỗi vòng lặp
					max = 16;
				else
					max = 32;
			}

			for (j = 0; j < max; j++)
			{
				bit = (temp2 >> j) & 1; //Lấy bit tại vị trí j
				if (bit == 1) //Đồng nghĩa bit cuối là 1
				{
					while (countExp < count) //Tương đương phép tính 2^countExp
					{
						add = add * "2";
						countExp++;
					}
					dec = dec + add;
				}
				count++;
			}
		}

		while (countExp < count) //Thêm một bit 1 ở đầu bị bỏ khi chuyển sang chấm động
		{
			add = add * "2"; 
			countExp++;
		}
		dec = dec + add;
	}
	else
	{
		index = 0;
		moveBit = 16;
		temp1 = x.Data[0] << moveBit;
		check = true;
	}

	//Lấy phần thập phân
	string fract = "0"; //Chuỗi chưa phần thập phân
	string div2 = "1"; //Chuỗi thực hiện phép tính 2^âm
	count = countExp = 0;
	if (check) //Cộng thêm bit đầu ở thập phân nếu mũ âm
	{
		while (exp < 0)
		{
			div2 = divReal(div2, 2);
			exp++;
		}
		fract = addReal(fract, div2);
	}
	
	for (i = index; i <= 3; i++)
	{
		if (x.Data[i] == 0)
			break;

		if (i != index)
		{
			moveBit = 32;
			temp1 = x.Data[i];
		}

		for (j = 0; j < moveBit; j++)
		{
			bit = (temp1 << j) & (1 << 31); //Lấy bit tại vị trí j
			if (bit == (1 << 31)) //Đồng nghĩa bit đầu là 1
			{
				while (countExp < count + 1) //Tương đương phép tính 2^-countExp
				{
					div2 = divReal(div2, 2);
					countExp++;
				}
				fract = addReal(fract, div2);
			}
			count++;
		}
	}

	//Nối phần nguyên và thập phân sau đó thêm dâu âm (nếu có)
	fract.erase(0, 1);
	dec += fract;
	if (sign) //Thêm dấu âm
		dec.insert(0, 1, '-');

	cout << dec << endl;
}