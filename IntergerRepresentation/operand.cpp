#include "myLib.h"

//Phần tình toán số nguyên
//Thêm số 0 vào chuỗi ngắn hơn cho bằng nhau
void standard2String(string &s1, string &s2) 
{
	int l1 = s1.length(), l2 = s2.length();
	if (l1 > l2)
		s2.insert(0, l1 - l2, '0');
	else 
		s1.insert(0, l2 - l1, '0');
}

//So sánh 2 số dạng chuỗi
int compare2String(const string &s1, const string &s2)
{
	//-1 là bé hơn, 1 là lớn hơn, 0 là bằng nhau
	int n1 = s1.length(), n2 = s2.length();
	if (n1 < n2)
		return -1;
	else  if (n1 > n2)
		return 1;
	else
	{
		for (int i = 0; i < n1; i++)
			if (s1[i] < s2[i])
				return -1;
			else if (s1[i] > s2[i])
				return 1;

		return 0;
	}
}

//Phép cộng 2 số dạng chuỗi
string operator +(string num1, string num2)
{
	standard2String(num1, num2);
	char n1, n2;
	string sum;

	int i, mem = 0; //Phần nhớ khi cộng số lớn hơn 10

	for (i = num1.length() - 1; i >= 0; i--) //Chạy từ cuối lên đầu
	{
		n1 = num1[i];
		n2 = num2[i];
		//Cộng từng số hàng đơn vị với phần nhớ
		mem += (atoi(&n1) + atoi(&n2)); 
		//Chèn kết quả vào đầu chuỗi sum, nó sẽ lần lượt đẩy các số xuống cuối chuỗi
		//Nếu số lớn hơn mười thì chỉ lấy phần đơn vị
		sum.insert(0, 1, mem % 10 + '0'); 
		mem /= 10; 
	}

	if (mem != 0)
		sum.insert(0, 1, mem + '0');

	return sum;
}


//Phép trừ ra kết quả là số dương
string operator -(string num1, string num2) 
{
	standard2String(num1, num2);
	string sub;
	if (num1 == num2)
	{
		sub.insert(0, 1, '0');
		return sub;
	}

	char n1, n2;
	int a, b;

	//rs là kết quả phép trừ từng số, mem là phần nhớ
	int i, rs, mem = 0; 

	for (i = num1.length() - 1; i >= 0; i--) //Chạy từ cuối lên đầu
	{
		n1 = num1[i];
		n2 = num2[i];
		//Trường hợp số trừ là 9 và có nhớ
		if ((num2[i] == '9') && (mem == 1))
		{
			sub.insert(0, 1, num1[i]);
			continue;
		}

		a = atoi(&n1);
		b = atoi(&n2) + mem;
		//Nếu a>=b thì trừ bình thường, ngược lại mượn 1 để trừ sau đó nhớ 1
		if (a >= b)
		{
			rs = a - b;
			mem = 0;
		}
		else
		{
			rs = a + 10 - b;
			mem = 1;
		}

		if ((i == 0) && (rs == 0))
			continue;

		sub.insert(0, 1, rs + '0');
	}

	return sub;
}

//Chia lấy phần nguyên
string operator /(string num1, int num2)
{
	string div;
	int index = 0;
	//rs là kết quả từng phép chia nhỏ
	int rs = num1[index] - '0';
	while ((rs < num2) && (num1.length() != index))
		rs = rs * 10 + (num1[++index] - '0');

	//Chia lần lượt rs cho num2, sau một lần chia lấy thêm một đơn vị bên phải
	while (num1.length() > index) //Độ dài chuỗi 1 vẫn lớn hơn index thì tiếp tục chia
	{
		//Nối từng kết quả chia được vào chuỗi div
		div += (rs / num2) + '0';

		//Lấy đơn vị tiếp theo
		rs = (rs % num2) * 10 + (num1[++index] - '0');
	}

	if (div.length() == 0)
		return "0";
	
	return div;
}

//Chia lấy phần dư
int operator %(string num1, int num2)
{
	string mod = num1 / num2;
	char temp[3];
	_itoa(num2, temp, 10);
	mod = num1 - mod * temp;
	return atoi(mod.c_str());
}


//Phép nhân số nguyên
string mulWith1Int(string s1, int num)
{
	char n1;
	string mul;
	int i, mem = 0; //Phần nhớ

	for (i = s1.length() - 1; i >= 0; i--)
	{
		n1 = s1[i];
		mem = atoi(&n1)*num + mem; //Nhân từng chữ số của s1 với num cộng thêm phần nhớ
		mul.insert(0, 1, mem % 10 + '0'); //Chèn kết quả vào đầu chuỗi mul, nó sẽ lần lượt đẩy các số xuống cuối chuỗi
		mem /= 10;
	}

	if (mem != 0)
		mul.insert(0, 1, mem + '0');

	return mul;
}

string operator *(string num1, string num2)
{
	char n2;
	string mul, temp;

	for (int i = num2.length() - 1; i >= 0; i--)
	{
		n2 = num2[i];
		temp = mulWith1Int(num1, atoi(&n2));
		temp.insert(temp.length(), num2.length() - i - 1, '0'); //Thêm số chữ số 0 vào cuối chuỗi tương ứng với vị trí chữ số của num2 đang nhân
		mul = mul + temp;
	}

	return mul;
}

//Phần tính toán số thực
REALNUM convertToRealNum(const string &s)
{
	REALNUM value;
	int index = s.find('.');
	value.num = s;
	if (index != -1) //Khi có dâu thập phân mới xóa
	{
		value.point = s.length() - index - 1; //Lưu số chữ số thập phân.
		value.num.erase(index, 1);
	}
	else
		value.point = 0;
	return value;
}

string convertToString(const REALNUM &num)
{
	string s;
	s = num.num;
	if (num.point != 0)
	{
		int index = num.num.length() - num.point; //Vị trí dấu thập phân
		s.insert(index, 1, '.');
	}

	int n = s.length() - 1;
	int count = 0; //Đếm số chữ số 0 sau cùng
	while (s[n] == '0')
	{
		count++;
		n--;
	}

	if (count == num.point)
		s.erase(n + 1, count - 1);
	else
		s.erase(n + 1, count);

	return s;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void standardRealNum(REALNUM &num1, REALNUM &num2) //Thêm số 0 vào cuối phần thập phân cho độ dài bằng nhau
{
	int maxPoint = max(num1.point, num2.point); //Tìm phần thập phân dài nhất
	num1.num.insert(num1.num.length(), maxPoint - num1.point, '0'); //Chèn thêm số chữ số 0 cho bằng phần dài nhất
	num2.num.insert(num2.num.length(), maxPoint - num2.point, '0');
}

string subReal(string num1, string num2)
{
	REALNUM sub, a, b;
	a = convertToRealNum(num1);
	b = convertToRealNum(num2);
	standardRealNum(a, b);
	sub.num = a.num - b.num; // Trừ số nguyên bình thường
	sub.point = max(a.point, b.point); //phần thập phân của kết quả bằng phần thập phân lớn nhất trong 2 số
	return convertToString(sub);
}

string mulReal(string num1, int num2)
{
	REALNUM mul, a, b;
	char temp[3];
	_itoa(num2, temp, 10);
	a = convertToRealNum(num1);
	b = convertToRealNum(temp);
	mul.num = a.num*b.num; //Nhân số nguyên bình thường
	mul.point = a.point + b.point; //Phần thập phân của kết quả bằng tổng phần thập phân của phân số
	return convertToString(mul);
}
