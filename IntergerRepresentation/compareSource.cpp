#include "phatLib.h"

void CopyBitHexaToBin(string &bit, string bitOfHexCode, int pos)
{
	int i;
	for (i = 3; i >= 0; i--)
	{
		bit[pos] = bitOfHexCode[i];
		pos--;
	}
}

string HexToBin(string hex)
{
	string bit;
	bit.resize(128);
	int i;
	for (i = 0; i < 128; i++)
	{
		bit[i] = '0';
	}
	vector<string> listBitOfHexCode;
	listBitOfHexCode.push_back("0000");
	listBitOfHexCode.push_back("0001");
	listBitOfHexCode.push_back("0010");
	listBitOfHexCode.push_back("0011");
	listBitOfHexCode.push_back("0100");
	listBitOfHexCode.push_back("0101");
	listBitOfHexCode.push_back("0110");
	listBitOfHexCode.push_back("0111");
	listBitOfHexCode.push_back("1000");
	listBitOfHexCode.push_back("1001");
	listBitOfHexCode.push_back("1010");
	listBitOfHexCode.push_back("1011");
	listBitOfHexCode.push_back("1100");
	listBitOfHexCode.push_back("1101");
	listBitOfHexCode.push_back("1110");
	listBitOfHexCode.push_back("1111");

	int j = hex.length() - 1;
	int lenOfBitHex = 128 - 4 * hex.length();
	for (i = 127; i >= lenOfBitHex; i -= 4)
	{
		if (hex[j] >= 48 && hex[j] <= 57)
		{
			CopyBitHexaToBin(bit, listBitOfHexCode[hex[j] - 48], i);
		}
		else if (hex[j] >= 65 && hex[j] <= 70)
		{
			CopyBitHexaToBin(bit, listBitOfHexCode[hex[j] - 55], i);
		}
		j = j - 1;
	}

	return bit;
}

void ConvertBinToString(bool *bit, string &x)
{
	x.resize(128);
	int i;
	for (i = 0; i < 128; i++)
	{
		if (bit[i] == false)
			x[i] = '0';
		else x[i] = '1';
	}
}

bool operator<(string s1, string s2)
{
	if (s1[0] == '1' && s2[0] == '0')
		return true;
	else if (s1[0] == '0' && s2[0] == '1')
		return false;
	else if (s1[0] == '0' && s2[0] == '0')
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return true;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return false;
			}
			cnt1++;
		}
	}
	else if (s1[0] == '1' && s2[0] == '1')
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return false;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return true;
			}
			cnt1++;
		}
	}
}

bool operator>(string s1, string s2)
{
	if (s1[0] == '1' && s2[0] == '0')
		return false;
	else if (s1[0] == '0' && s2[0] == '1')
		return true;
	else if (s1[0] == '0' && s2[0] == '0') //TH: 2 so DUONG
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return false;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return true;
			}
			cnt1++;
		}
	}
	else if (s1[0] == '1' && s2[0] == '1') //TH: 2 so AM
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return true;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return false;
			}
			cnt1++;
		}
	}
}

bool operator<=(string s1, string s2)
{
	if (s1[0] == '1' && s2[0] == '0')
		return true;
	else if (s1[0] == '0' && s2[0] == '1')
		return false;
	else if (s1[0] == '0' && s2[0] == '0')
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return true;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return false;
			}
			cnt1++;
		}
		return true;
	}
	else if (s1[0] == '1' && s2[0] == '1')
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return false;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return true;
			}
			cnt1++;
		}
		return true;
	}
}

bool operator>=(string s1, string s2)
{
	if (s1[0] == '1' && s2[0] == '0')
		return false;
	else if (s1[0] == '0' && s2[0] == '1')
		return true;
	else if (s1[0] == '0' && s2[0] == '0')
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return false;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return true;
			}
			cnt1++;
		}
		return true;
	}
	else if (s1[0] == '1' && s2[0] == '1')
	{
		int cnt1 = 1;
		while (cnt1 < 128)
		{
			if (s1[cnt1] == '0' && s2[cnt1] == '1') {
				return true;
			}
			else if (s1[cnt1] == '1' && s2[cnt1] == '0') {
				return false;
			}
			cnt1++;
		}
		return true;
	}
}

bool operator==(string s1, string s2)
{
	if (s1[0] == '1' && s2[0] == '0')
		return false;
	else if (s1[0] == '0' && s2[0] == '1')
		return false;
	else
	{
		int cnt = 1;
		while (cnt < 128)
		{
			if (s1[cnt] != s2[cnt])
				return false;
			cnt++;
		}
		return true;
	}
}

/*const string operator=(const string &s1)
{

}*/