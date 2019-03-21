#include <stdio.h>
#include <iostream>
#include <fstream>
#include "QInt.h"
#include "UtilityFunc.h"

// 0000‭0001 01100110 10101000 10100100		10011111 10000101 10101100 11101010‬ bit dương
// 11111110 10011001 01010111 01011011		01100000 01111010 01010011 00010110 bit âm
// ‭166 A8A4 9F85 ACEA
// ‬‭100 953 466 666 855 658‬
//string Number = "123564687923134646";
//string NumberBit = "10110001100100011110011110011111000111110001111110000111100001";

using namespace std;

int main(int argc, char* argv[])
{
	string test = "1335";

	cout << test / 2;
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

	//bool *ptrBool = DecToBin(c);
	//char * hexCode = DecToHex(c);
	//printf("%d", sizeof(float));

	//delete[] ptrBool;
	//delete[] hexCode;

	// // In ra chuỗi bit trong mảng bool
	//for (int i = 1; i <= 128; i++)
	//{
	//	ptrBool[i - 1] ? printf("1") : printf("0");
	//	if (i % 8 == 0) printf(" ");
	//}

	// QInt b = BinToDec(ptrBool);
	printf("\n");

	QInt b;
	ScanQInt(b);

	int temp;
	for (int i = 31; i >= 0; i--)
	{
		temp = (b.data[0] >> i);
		printf("%d", temp & 1);
		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");

	for (int i = 31; i >= 0; i--)
	{
		temp = (b.data[1] >> i);
		printf("%d", temp & 1);
		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");

	for (int i = 31; i >= 0; i--)
	{
		temp = (b.data[2] >> i);
		printf("%d", temp & 1);
		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");

	for (int i = 31; i >= 0; i--)
	{
		temp = (b.data[3] >> i);
		printf("%d", temp & 1);
		if (i % 8 == 0)
			printf(" ");
	}
	


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

	//// Đóng file
	//inputFile.close();
	//outputFile.close();

	printf("\n");
	system("pause");
	return 0;
}