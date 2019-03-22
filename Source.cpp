#include "Qfloat.h"


unsigned int* Qfloat::getData() const
{
	unsigned int* Result = new unsigned int[4];
	for (int i = 0; i < 4; i++)
		Result[i] = this->data[i];
	return Result;
}

void Qfloat::setData(int viTrim, unsigned int Data)
{
	this->data[viTrim] = Data;
}

bool* DecToBin15Bit(int Data15Bit, int &size, bool want) //ham chuyen dec to bin max la 15 bit
{
	string temp;
	if (want == false)
	{
		int binaryNum[15];
		int i = 0;
		while (Data15Bit > 0)
		{
			binaryNum[i] = Data15Bit % 2;
			temp.push_back(binaryNum[i]);
			Data15Bit = Data15Bit / 2;
			i++;
		}
		int chay = i;
		size = chay;
		bool *Res = new bool[temp.size()];
		for (int j = 0; j < chay; j++)
		{
			Res[i - 1] = binaryNum[j];
			i--;
		}
		return Res;
		delete[]Res;
	}
	else
	{
		bool Res[15];
		int binaryNum[15]; 

		// counter for binary array 
		int i = 0;
		while (Data15Bit > 0)
		{
			// storing remainder in binary array 
			binaryNum[i] = Data15Bit % 2;
			Data15Bit = Data15Bit / 2;
			i++;
		}
		if (i < 15)
		{
			for (int run = 14; run >= i; run--)
			{
				binaryNum[run] = 0;
			}
		}
		int temp = 14;
		for (int j = 0; j <15; j++)
		{
			Res[temp] = binaryNum[j];
			temp--;
		}
		return Res;
	}
};

unsigned long long int NguyenSangSo(string x)
{
	int l1 = x.length();
	unsigned long long int num1 = 0;
	for (int i = l1 - 1; i >= 0; --i)
	{
		num1 += (int)(x[i] - '0') * pow(10, l1 - i - 1);
	}
	return num1;
}

bool* StrDecToBin(string Dec)
{
	bool res[128];
	string tempDec = Dec;
	bool Negative = false;
	if (tempDec[0] == '-') //kiem tra so am
	{
		tempDec.erase(tempDec.begin());
		Negative = true;
		res[127] = 1;
	}
	else res[127] = 0;


	//tach phan nguyen va frac khoi chuoi
	bool resFrac[112];
	string tempRes15Bit;
	string tempFrac;
	int size = 0;
	int run = 0;
	while (tempDec[run] != '.')
	{
		tempRes15Bit.push_back(tempDec[run]);
		run++;
	}
	while (tempDec[run] != '\0')
	{
		tempFrac.push_back(tempDec[run]);
		run++;
	}
	if (tempFrac[0] == '.') //kiem tra coi co dau cham dau chuoi khong neu co thi xoa
	{
		tempFrac.erase(tempFrac.begin());
	}

	//doi phan so nguyen tu string sang so;
	int nguyen = NguyenSangSo(tempRes15Bit);

	//doi phan Frac tu string sang so
	int sizeFrac = tempFrac.size();
	long double frac = NguyenSangSo(tempFrac) / pow(10, sizeFrac);


	int dichNguyen;
	DecToBin15Bit(nguyen, dichNguyen, false); //dich qua bao nhieu bit
	bool* res15Bit = new bool[dichNguyen];

	//doi phan nguyen sang bin

	for (int i = 0; i < dichNguyen; i++)
	{
		if (DecToBin15Bit(nguyen, dichNguyen, false)[i] == true)
		{
			res15Bit[i] = true;
		}
		else res15Bit[i] = false;
	}
	dichNguyen--;
	int soMuE = 16383 + dichNguyen; //so mu E


	//chuyen phan da dich (cua nguyen) sang frac
	int lapDayFrac = 111 - dichNguyen + 1;
	run = 1;
	if (lapDayFrac != 111)
	{
		for (int i = 111; i > lapDayFrac-1; i--)
		{
			
			if (res15Bit[run] == true)
			{
				resFrac[i] = true;
			}
			else resFrac[i] = false;
			run++;
		}
	}


	//doi frac sang bin
	int dem = 0;
	while (lapDayFrac!=0)
	{
		lapDayFrac--;
		frac = frac * 2;
		int fract_bit = frac;

		if (fract_bit == 1)
		{
			frac = frac - fract_bit;
			resFrac[lapDayFrac] = true;
		}
		else
			resFrac[lapDayFrac] = false;
	}
	
	//doi so so mu E
	for (int i = 0; i < 15; i++)
	{
		if (DecToBin15Bit(soMuE, dichNguyen, true)[i] == true)
		{
			res15Bit[i] = true;
		}
		else res15Bit[i] = false;
	}	

	//dua so mu E vao trong chuoi ket qua
	run = 0;
	for (int i = 126; i >= 112; i--)
	{
		if (res15Bit[run] == true)
		{
			res[i] = true;
		}
		else res[i] = false;
		run++;

	}
	// dua so frac vao ket qua
	run = 0;
	for (int i = 0; i < 112; i++)
	{
		if (resFrac[run] == true)
		{
			res[i] = true;
		}
		else res[i] = false;
		run++;
	}
	
	return res;
}

