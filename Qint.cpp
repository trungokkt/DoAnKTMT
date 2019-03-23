#include "Qint.h"
#include "Convert.h"

QInt::QInt(){};

QInt::~QInt(){};

QInt::QInt(const string &Binary)
{
	memset(this->data, 0, 16);
	for (size_t i = 0; i < Binary.size(); i++)
	{
		if (Binary[i] == '1')
		{
			this->data[3 - (Binary.size() - 1 - i) / 32] = this->data[3 - (Binary.size() - 1 - i) / 32] | ((1 << ((Binary.size() - 1 - i) % 32)));
		}
	}
}

unsigned int QInt::getData(int i)
{
	return this->data[i];
};

void QInt::setData(int pos, unsigned int x)
{
	this->data[pos] = x;
}

bool QInt::checkIfZero()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->data[i] != 0)
		{
			return false;
		}
	}
	return true;
}


QInt QInt::operator << (const int&shift)
{
	QInt Result;
	memset(Result.data, 0, 16);

	unsigned int SignBit = (1 << 31) & this->data[0];
	Result.data[0] = this->data[0] << shift;
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < shift; j++)
		{
			Result.data[i - 1] = Result.data[i - 1] | (((1 << (31 - j)) & this->data[i]) >> (32 - shift));
		}

		Result.data[i] = this->data[i] << shift;
	}

	return Result;
}

QInt QInt::operator & (const QInt&x) const
{
	QInt Result;
	memset(Result.data, 0, 16);

	for (int i = 0; i < 4; i++)
	{
		Result.data[i] = this->data[i] & x.data[i];
	}

	return Result;
}

QInt QInt::operator ^ (const QInt&x) const
{
	QInt Result;
	memset(Result.data, 0, 16);

	for (int i = 0; i < 4; i++)
	{
		Result.data[i] = this->data[i] ^ x.data[i];
	}

	return Result;
}

QInt QInt::operator + (QInt x) const
{
	QInt res = *this;
	QInt tempCarr;

	while (!(x.checkIfZero()))
	{
		tempCarr = res & x;

		res = res ^ x;

		x = tempCarr << 1;
	}
	return res;
}

QInt& QInt::operator ~ ()
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = ~this->data[i];
	}

	return *this;
}

QInt QInt::QInttoTwosComplement()
{
	return (~*this + QInt("1"));
}

QInt QInt::operator - (QInt x) const
{
	return (*this + x.QInttoTwosComplement());
}
QInt QInt::operator * (QInt x) const
{
	QInt Result;

	QInt Temp = *this;

	QInt ONE("1"); // 1
	bool Negative = false; //kiem tra so am

	if ((Temp.isNegative() && !x.isNegative()) || (!Temp.isNegative() && x.isNegative()))//kiem tra trai dau
	{
		Negative = true;
	}
	if (x.isNegative())
	{
		x = ~(x - ONE); //neu am thi chuyen sang dang so duong
	}
	if (Temp.isNegative())
	{
		Temp = ~(Temp - ONE); //neu am thi chuyen sang dang so duong
	}
	//nhan 2 so
	while (!(x.isNegative() || x.isEqualZero()))
	{
		if (((x & ONE)- ONE).isEqualZero()) //x le thi cong ket qua voi Temp
		{

			Result = Result + Temp;
		}

		Temp = Temp << 1; //nhan temp cho 2;
		x = x >> 1; //chia x cho 2.
	}
	Result = Temp;
	// neu 2 so trai dau
	if (Negative == true)
	{
		Result = ~Result + ONE; //chuyet ket qua ve dang bu 2.
	}

	return Result;
}
// toan tu /
QInt QInt::operator / (QInt x)
{
	QInt Result("1");
	if (this->isEqualZero() || x.isEqualZero()) // kiem tra kq va x co bang 0 khong
	{
		return Result;
	}
	else
	{
		QInt One("1");

		if ((x - One).isEqualZero())
		{
			Result = *this;
		}
		else
		{
			QInt Temp = *this;
			int k = 128;
			bool Negative = false;

			if ((Temp.isNegative() && !x.isNegative()) || (!Temp.isNegative() && x.isNegative()))//neu 2 so trai dau
			{
				Negative = true;
			}

			if (x.isNegative())
			{
				x = ~(x - One); //am thi chuyen ve so duong
			}
			if (Temp.isNegative())
			{
				Temp = ~(Temp - One); //am thi chuyen ve so duong
			}

			while (k > 0)
			{
				Result = Result << 1;
				Result.Data[3] = Result.Data[3] | ((Temp.Data[3] & (1 << 31)) >> 31);
				Temp = Temp << 1;

				Result = Result - x;
				if (Result.isNegative())
				{
					Result = Result + x;
				}
				else
				{
					Temp.Data[3] = Temp.Data[3] | 1;
				}

				--k;
			}

			Result = Temp;
			if (Negative == true)
			{
				Result = ~Result + One;
			}
		}
	}
	return Result;
}
bool QInt::operator == (QInt x) {
	if (this != &x)
	{
		for (int i = 0; i < x.size(); i++)
		{
			if (this->Data[i] != x.Data[i])
				return false;
		}
	}
	return true;
}
//Toán tử <.
bool  QInt::operator < (QInt x) {
	if (this->isNegative() && !x.isNegative())
		return true;
	if (!this->isNegative() && x.isNegative())
		return false;
	if (this->isNegative() && x.isNegative()){
		QInt One("1");
		x = ~(x - One); //doi ve so duong
		*this = ~(*this - One);
		if (this != &x)
		{
			for (int i = 0; i < x.size(); i++)
			{
				if (this->Data[i] < x.Data[i])
					return false;
			}
		}
		return true;
	}

	if (!this->isNegative() && !x.isNegative()) {
		if (this != &x)
		{
			for (int i = 0; i < x.size(); i++)
			{
				if (this->Data[i] > x.Data[i])
					return false;
			}
		}
		return true;
	}
}
//Toán tử >.
bool  QInt::operator > (QInt x) {
	return !(*this < x);
}
//Toán tử >=.
bool  QInt::operator >= (QInt x) {
	return (*this > x || *this == x);
}
/*Toán tử <=*/
bool  QInt::operator <= (QInt x) {
	return (*this < x || *this == x);
}
//Hàm kiếm tra bằng không.
bool QInt::isEqualZero()
{
	for (int i = 0; i < this->size(); i++)
	{
		if (this->Data[i] != 0)
		{
			return false;
		}
	}

	return true;
}

//Hàm kiểm tra số âm.
bool QInt::isNegative()
{
	if ((this->Data[0] & (1 << (_SIZE_INT_ - 1))) >> (_SIZE_INT_ - 1) == 1)
	{
		return true;
	}

	return false;
}
