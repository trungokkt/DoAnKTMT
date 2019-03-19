#ifndef __QINT_H__
#define __QINT_H__
#define _BIT_UINT32_		32
#define _DEFAULT_SIZE	16	
#define _POSITION		((Binary.size() - 1 - i) / (sizeof(_Uint32t) * CHAR_BIT)) 
#define _SHIFT_OFFSET	(((Binary.size() - 1) % (CHAR_BIT * sizeof(_Uint32t))) - (i % (CHAR_BIT * sizeof(_Uint32t))))
#include <string>
#include <iostream>

using namespace std;

class QInt
{
protected:
	unsigned int data[4];

public:
	QInt();
	~QInt();
	QInt(const string&Binary);

	unsigned int getData(int i);
	void setData(int pos, unsigned int x);
	QInt operator & (const QInt &x) const;
	QInt operator << (const int &ShiftOffset);
	QInt operator ^ (const QInt &x) const;
	QInt operator + (QInt x) const;
	QInt operator - (QInt x) const;
	QInt& operator ~ ();

	QInt QInttoTwosComplement();

	bool checkIfZero();
};




#endif