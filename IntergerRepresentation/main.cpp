#include <stdio.h>
#include <iostream>
#include <fstream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*// Kiểm tra đủ 3 tham số không. Nếu không --> báo lỗi
	if (argc != 3) {
		cout << "Usage: file.exe input.txt output.txt";
		exit(1);
	}

	// Kiểm tra mở file input
	ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile) {
		cout << "Cannot open the input file." << endl;
		return 1;
	}

	// Kiểm tra mở file output
	ofstream outputFile;
	outputFile.open(argv[2]);
	if (!outputFile) {
		cout << "Cannot open the output file." << endl;
		return 1;
	}

	// Xử lý stream in và xuất ra stream out
	processFileandOutput(inputFile, outputFile);

	// Đóng file
	inputFile.close();
	outputFile.close();
	*/
	QInt a, b;
	a.data[3] =-1;
	a.data[2] = -1;
	a.data[1] = -1;
	a.data[0] = -1;
	//a.data[3] = 1234;
	b.data[3] = 3;

	QInt k;

	k =a*b;
	
	cout << k.data[3] << endl;
	cout << k.data[2]<<endl;
	cout << k.data[1] << endl;
	cout << k.data[0]<<endl;
	for (int i = 1; i <=32 ; i++)
	{
		cout << ((k.data[3] >> 32 - i)&1);
	}
	system("pause");
	return 0;
}