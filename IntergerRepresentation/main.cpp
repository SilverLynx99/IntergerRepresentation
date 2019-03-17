#include <stdio.h>
#include <iostream>
#include <fstream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Kiểm tra đủ 3 tham số không. Nếu không --> báo lỗi
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

	system("pause");
	return 0;
}