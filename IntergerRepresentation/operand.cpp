﻿#include "UtilityFunc.h"

//-------------- UTILITY FUNCTION --------------
//Thêm số 0 vào chuỗi ngắn hơn cho bằng nhau
void standard2String(string &s1, string &s2) 
{
	int l1 = s1.length(), l2 = s2.length();
	if (l1 > l2)
		s2.insert(0, l1 - l2, '0');
	else 
		s1.insert(0, l2 - l1, '0');
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
//--------------


//-------------- BASIC FUNCTION --------------
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

string operator /(string num1, int num2)
{
	string div; // Chuỗi chứa kq
	int index = 0; // Vị trí duyệt trên mảng num1

	//rs là kết quả từng phép chia nhỏ
	// Bước khởi đầu: Lấy đủ ký tự lớn có giá trị lớn hơn số bị chia
	// Nếu k đúng điều kiện, ta đến thẳng trường hợp div.length() = 0
	int rs = num1[index] - '0';
	while ((rs < num2) && (num1.length() != index))
		rs = rs * 10 + (num1[++index] - '0');

	//Chia lần lượt rs cho num2, sau một lần chia lấy thêm một đơn vị bên phải
	while (num1.length() > index) // Dùng index để duyệt hết chuỗi.
	{
		//Nối từng kết quả chia được vào chuỗi div
		// Dùng phép chia của C để lấy phần nguyên
		div += (rs / num2) + '0';

		//Lấy đơn vị tiếp theo
		rs = (rs % num2) * 10 + (num1[++index] - '0');
	}

	// Trường hợp 
	if (div.length() == 0)
		return "0";
	
	return div;
}

int operator %(string num1, int num2)
{
	string mod = num1 / num2;

	// CẦN COMMENT
	char temp[3];
	_itoa(num2, temp, 10);

	mod = num1 - (mod * temp);

	// CẦN COMMENT
	return atoi(mod.c_str());
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
//--------------