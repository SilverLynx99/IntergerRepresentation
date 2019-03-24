#include <stdio.h>
#include <iostream>
#include <fstream>
#include "QInt.h"
#include "UtilityFunc.h"

// 0000‭0001 01100110 10101000 10100100		10011111 10000101 10101100 11101010‬ bit dương
// 11111110 10011001 01010111 01011011		01100000 01111010 01010011 00010110 bit âm
// ‭166 A8A4 9F85 ACEA
// ‬‭100953466666855658‬

// NOTE :
// 1.Chưa xử lý tràn số
// 2. Có thời gian sửa tiếp hàm chuyển đổi.
// 

using namespace std;

void inChuoiBitQInt(QInt a);

int main(int argc, char* argv[])
{
	QInt a, b;
	printf("Nhap so a: ");
	ScanQInt(a);
	printf("Nhap so b: ");
	ScanQInt(b);


	 

	// In ra chuỗi bit trong mảng bool
	//for (int i = 1; i <= 128; i++)
	//{
	//	ptrBool[i - 1] ? printf("1") : printf("0");
	//	if (i % 8 == 0) printf(" ");
	//}

	printf("\n");
	char * hexCode = DecToHex(b);
	printf("%s", hexCode);

	printf("\n");
	
	// QInt b = BinToDec(ptrBool);
	inChuoiBitQInt(BinToDec(DecToBin(a)));

	//delete[] ptrBool;
	delete[] hexCode;
	//// Kiểm tra đủ 3 tham số không. Nếu không --> báo lỗi
	//if (argc != 3) {
	//	cout << "Usage: file.exe input.txt output.txt";
	//	exit(1);
	//}

	//// Kiểm tra mở file input
	//ifstream inputFile;
	//inputFile.open(argv[1]);
	//if (!inputFile) {
	//	cout << "Cannot open the input file." << endl;
	//	return 1;
	//}

	//// Kiểm tra mở file output
	//ofstream outputFile;
	//outputFile.open(argv[2]);
	//if (!outputFile) {
	//	cout << "Cannot open the output file." << endl;
	//	return 1;
	//}

	//// Xử lý stream in và xuất ra stream out
	//processFileandOutput(inputFile, outputFile);

	// Đóng file
	//inputFile.close();
	//outputFile.close();

	system("pause");
	return 0;
}

void inChuoiBitQInt(QInt a)
{
	int temp;
	for (int j = 0; j < 4; j++) {
		for (int i = 31; i >= 0; i--)
		{
			temp = (a.data[j] >> i);
			printf("%d", temp & 1);
			if (i % 8 == 0)
				printf(" ");
		}
		printf("\n");
	}
	
}

//QInt a;
//a.data[0] = 0;
//a.data[1] = 0;
//a.data[2] = 23505060;
//a.data[3] = -1618629398;

//QInt c;
//c.data[0] = -1;
//c.data[1] = -1;
//c.data[2] = -23505061;
//c.data[3] = 1618629398;