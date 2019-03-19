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