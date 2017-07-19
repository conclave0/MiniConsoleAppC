#include "IOFile.h"

void CIOFile::readFile(string big, QInt &QInt1, QInt &QInt2)		//ham doc file va luu gia tri vao bien
{

	string small;
	int count = 0;
	while (!big.empty())	//lam cho den khi het string big
	{
		//chep file vao bien de su dung
		small = big.substr(0, big.find(" "));

		if (count == 0)			//phan tu 0
		{
			p1 = atoi(small.c_str());	//chuyen tu string sang int
		}
		else if (count == 1)	//phan tu 1
		{
			if (small.size() == 1 && small[0] == '~')		//TH gap toan tu not
			{
				cToanTu = small[0];
			}
			else if (small.size() == 3 && small[0] == 'r')	//TH gap ror hoac rol
			{
				cToanTu = small[2];
			}
			else if (small.size() == 2 && (small[0] == '1' && small[1] == '0') || (small[0] == '1' && small[1] == '6'))	//TH: phan tu <= 2 va bat dau bang 0 hoac 1
			{
				p2 = atoi(small.c_str());	//chuyen string thanh int p2
			}
			else if (small.size() == 1 && (small[0] == '2'))
			{
				p2 = atoi(small.c_str());	//chuyen string thanh int p2 (p2 = 2)
			}
			else
				QInt1.SaveTo(p1, small);
		}

		else if (count == 2)	//phan tu 2
		{
			if (cToanTu == '~' || cToanTu == 'r' || cToanTu == 'l')		//TH co cac toan tu: ~, ror, rol
			{
				QInt1.SaveTo(p1, small);
			}
			else if (small.size() <= 2 && ((small[0] < 48) || small[0] > 57) && (small[0] < 65 || small[0] > 80) && small[0] != '-')	//TH: cac toan tu &, |, xor, not, ~, shl, shr
			{
				cToanTu = small[0];
				if (p2 != 0)	//TH p2 nhan nham vi khi co toan tu thi se khong co chuyen doi
				{
					small.clear();
					small = p2 + 48;
					QInt1.SaveTo(p1, small);
					p2 = 0;
				}
			}
			else if (small[0] == '-' && small.size() == 1)		//TH: dau '-'
			{
				cToanTu = small[0];
				if (p2 != 0)	//TH p2 nhan nham vi khi co toan tu thi se khong co chuyen doi
				{
					small.clear();
					small = p2 + 48;
					QInt1.SaveTo(p1, small);
					p2 = 0;
				}
			}
			else if (p2 != 0)
			{
				QInt1.SaveTo(p1, small);
			}
		}

		else
		{
			//lan nay chac chan la chi co QInt 2
			QInt2.SaveTo(p1, small);
		}

		if (big.find(" ") > big.size()) //kiem tra neu tim thay khoang trang ngoai pham vi big.size
		{
			break;
		}
		else
		{
			big.erase(0, big.find(" ") + 1); //xoa string big tu dau den khi gap khoang trang dau tien
		}

		count++;
	}
}

void CIOFile::CalAndWrite(string output, QInt QInt1, QInt QInt2)	//ham tinh toan va xuat ket qua ra file
{
	fstream fOut;
	fOut.open(output, ios::out | ios::app);
	//tu cac input o tren bat dau xu ly de xuat ra file output luon
	if (p1 == 2)	//voi p1 = 2
	{
		if (p2 != 0)//p2 khac 0
		{
			if (p2 == 10)	//chuyen tu 2 sang 10
			{
				KetQua = QInt1.QIntToDecimal();
				fOut << KetQua << endl;
			}
			else if (p2 == 16)	//chuyen tu 2 sang 16
				QInt1.QIntToHexa();
		}
		else
		{
			//cac phep tinh toan QInt1 va QInt2
			TinhToanQInt(QInt1, QInt2, cToanTu);		//lua chon phep tinh phu hop
			QInt1.WriteFileLessThan128Bits(output);		//luu ket qua QInt sang file					
		}
	}

	else if (p1 == 10)	//bieu dien thap phan
	{
		if (p2 == 2)	//bieu dien 10 sang 2
		{
			QInt1.WriteFileLessThan128Bits(output);		//luu ket qua QInt sang file
		}
		else if (p2 == 16)	//bieu dien 10 sang 16
			QInt1.QIntToHexa();
		else
		{
			//cac phep tinh toan
			TinhToanQInt(QInt1, QInt2, cToanTu);
			KetQua = QInt1.QIntToDecimal();
			fOut << KetQua << endl;
		}
	}

	else if (p1 == 16)	//bieu dien tren he 16
	{
		if (p2 == 2)	//bieu dien 16 sang 2
		{
			QInt1.WriteFileLessThan128Bits(output);	//luu ket qua QInt sang file
		}
		else if (p2 == 10)//bieu dien 16 sang 10
		{
			KetQua = QInt1.QIntToDecimal();
			fOut << KetQua << endl;
		}
		else
		{
			//cac phep tinh toan
			TinhToanQInt(QInt1, QInt2, cToanTu);
			QInt1.QIntToHexa();
		}
	}
}
CIOFile::CIOFile()			//ham khoi tao mac dinh
{
	p1 = 0;
	p2 = 0;
	KetQua.clear();
	cToanTu = '0';
}

CIOFile::~CIOFile()
{
}
