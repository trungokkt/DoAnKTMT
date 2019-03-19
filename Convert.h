#ifndef _CONVERT_H_
#define _CONVERT_H_
#include "QInt.h"

class Convert
{
public:
	string StrDectoBin(string Str);
	bool* DecToBin(QInt x);




	string BinToHex(bool* bit);
	string DecToHex(QInt x);


	string StrDivTwo(const string &Str);
	string sum(string a, string b);
	string Muti(string a, char b);
	string Power(int a, int n);
};

bool* DecToBin32Bit(int Data32Bit);
#endif