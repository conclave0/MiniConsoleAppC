#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <stdlib.h>

#pragma once
class QInt
{
private:
	__int64 arrayBits[2];		//so nguyen lon: mang 2 phan tu co do lon 16 bytes
public:
	QInt BatBit(int, int);		//ham bật bit  (0 -> 1)
	QInt TatBit(int, int);		//hàm tắt bit  (1 -> 0)
	int XemBit(int, int);		//hàm xem bit đó là 0 hay 1
	QInt SaveTo(int, string);	//luu dãy vao bien QInt
	QInt SaveBinary(string);	//luu nhi phan vao QInt
	QInt SaveHexa(string);		//luu thap luc phan vao QInt
	void QIntToHexa();			//chuyen tu QInt sang thap luc phan
	QInt SaveDecimal(string);	//luu thap phan vao QInt
	string QIntToDecimal();		//chuyen tu QInt sang thap phan
	int FindBit1();				//tim bit cuoi cung la 1
	int GetterDec();			//lay so thap phan trong QInt.arrayBits[1]
	//void WriteFile(string);		//chep QInt sang file du 128 bit
	void WriteFileLessThan128Bits(string);		//chep QInt sang file nhung khong chep het 128 bit

	//toán tử cộng trừ nhân chia, input là kiểu QInt đã có đủ 128 bit, output là return QInt;
	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt Bu2();				//hàm chuyển dãy bit sang bù 2
	QInt operator*(QInt);
	QInt operator/(QInt);

	//các toán tử cơ bản
	QInt operator&(QInt);	//toan tu and
	QInt operator|(QInt);	//toan tu or
	QInt operator^(QInt);	//toan tu xor
	QInt operator~();		//toan tu not
	QInt operator=(QInt);	//toan tu gan
	QInt operator<<(int);	//toan tu dich trai
	QInt operator>>(int);	//toan tu dich phai
	QInt rol();				//rotate left
	QInt ror();				//rotate right

	QInt();
	QInt(int, int);
	~QInt();
};

int BangMa(char c);
string divide2(string);				//ham chia 2
string Multiply2(string KetQua);	//ham nhan 2
string Plus1(string KetQua);		//ham cong 1
void TinhToanQInt(QInt &QInt1, QInt QInt2, char cToanTu);	//ham xu ly cac truong hop ma de bai yeu cau