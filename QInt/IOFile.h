#include "QInt.h"
#pragma once
class CIOFile
{
private:
	char cToanTu;								//chua toan tu
	string KetQua;								//chuoi luu ket qua
	int p1, p2;									//chi thi p1 va p2
public:
	void readFile(string, QInt &, QInt &);		//luu day string vao tung phan tu thich hop
	void CalAndWrite(string, QInt, QInt);		//ham tinh toan va xuat ket qua ra file
	CIOFile();
	~CIOFile();
};

