#include "Convert.h"

string Convert::BinToHex(bool *bit)
{
	string tempRes;
	string result;
	bool tempBit[128]; //do 16bytes nen chuoi bit dai nhat 128

	//dem do dai chuoi bit dau vao
	int dem = 0;
	for (int i = 0; i < 128; i++)
	{
		if (bit[i] == true || bit[i] == false)
		{
			dem++;
		}
		else break;
	}

	//lap 128 bit cho de thuc hien
	int tempSize = dem;
	if (tempSize < 128) //neu size cua chuoi bool <128 thi chuan bi chen` so 0 trong tat ca cac bit con lai
	{
		int tempSub = 128 - tempSize;
		for (int i = 127; i >= tempSub; i--) //push nguoc tu cuoi chuoi
		{
			tempBit[i] = bit[tempSize - 1];
			tempSize--;
		}
		for (int i = 0; i < tempSub; i++) // push lap day 28bit
		{
			tempBit[i] = false;
		}
	}
	else
	{
		for (int i = 0; i < 128; i++) // push lap day 28bit
		{
			tempBit[i] = bit[i];
		}
	}

	//chuan bi chuyen tu BIN -> HEX
	for (int i = 0; i < 128; i++)
	{
		if (tempBit[i] == true) //neu bool dung thi push 1
		{
			tempRes.push_back('1');
		}
		else tempRes.push_back('0'); //sai push 0

		if (i % 4 == 3) //lay ra 4bit de xu li
		{
			if (tempRes == "0000")//0
			{
				result.push_back('0');
			}
			else
			{
				if (tempRes == "0001")//1
				{
					result.push_back('1');
				}
				else
				{
					if (tempRes == "0010")//2
					{
						result.push_back('2');
					}
					else
					{
						if (tempRes == "0011")//3
						{
							result.push_back('3');
						}
						else
						{
							if (tempRes == "0100")//4
							{
								result.push_back('4');
							}
							else
							{
								if (tempRes == "0101")//5
								{
									result.push_back('5');
								}
								else
								{
									if (tempRes == "0110")//6
									{
										result.push_back('6');
									}
									else
									{
										if (tempRes == "0111")//7
										{
											result.push_back('7');
										}
										else
										{
											if (tempRes == "1000")//8
											{
												result.push_back('8');
											}
											else
											{
												if (tempRes == "1001")//9
												{
													result.push_back('9');
												}
												else
												{
													if (tempRes == "1010")//10
													{
														result.push_back('A');
													}
													else
													{
														if (tempRes == "1011")//11
														{
															result.push_back('B');
														}
														else
														{
															if (tempRes == "1100")//12
															{
																result.push_back('C');
															}
															else
															{
																if (tempRes == "1101")//13
																{
																	result.push_back('D');
																}
																else
																{
																	if (tempRes == "1110")//14
																	{
																		result.push_back('E');
																	}
																	else
																	{
																		if (tempRes == "1111")//15
																		{
																			result.push_back('F');
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			tempRes.clear();
		}
	}
	//xoa so 0 thua o dau chuoi hex 
	while (result.front() == '0')
	{
		result.erase(0, 1);
	}
	return result;
}

string Convert::StrDivTwo(const string &Str)
{
	string Result;
	int Temp = 0;

	for (int i = 0; i < Str.size(); i++)
	{
		Temp = Temp * 10 + (Str[i] - '0');

		if (i > 0 || (i == 0 && Temp >= 2))
		{
			Result.push_back((Temp / 2) + '0');
		}

		Temp = Temp % 2;
	}

	return Result;
}

bool* DecToBin32Bit(int Data32Bit) //ham ngoai chuyen 32bit cua tung data[]
{
	bool Res[32];
	int binaryNum[32]; //do 128/4 = 32bit

	// counter for binary array 
	int i = 0;
	while (Data32Bit > 0)
	{
		// storing remainder in binary array 
		binaryNum[i] = Data32Bit % 2;
		Data32Bit = Data32Bit / 2;
		i++;
	}
	if (i < 32)
	{
		for (int run = 31; run >= i; run--)
		{
			binaryNum[run] = 0;
		}
	}
	int temp = 31;
	for (int j = 0; j <32; j++)
	{
		Res[temp] = binaryNum[j];
		temp--;
	}

	return Res;
};

bool* Convert::DecToBin(QInt x)
{
	bool res[128];
	int temp[4];
	for (int i = 0; i < 4;i++)
	{
		temp[i] = x.getData(i);
	}
	//chuyen tat ca qua Bit;
	int dem = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (DecToBin32Bit(temp[i])[j] == true)
				res[dem] = true;
			else res[dem] = false;
			dem++;
		}
	}
	return res;
}

string Convert::DecToHex(QInt x)
{
	string Res;
	bool tempBit[128];
	for (int i = 0; i < 128; i++)
	{
		if (this->DecToBin(x)[i] == true)
		{
			tempBit[i] = true;
		}
		else
		{
			tempBit[i] = false;
		}
	}
	Res = BinToHex(tempBit);
	return Res;
}

