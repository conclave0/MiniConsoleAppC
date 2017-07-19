#include "QInt.h"

int BangMa(char c)	//chỉ ra các con số cúa A,B..F trong kieu hex
{
	switch (c)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;

	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	}
}

string divide2(string s)			//ham chia kieu string cho 2
{
	int temp, count = 0, carry = 0;
	char c;
	string KetQua;

	while (1)
	{
		c = s[count];
		temp = c - 48 + carry;
		if ((temp / 2 != 0) || ((temp / 2 == 0) && (count != 0)))
		{
			c = temp / 2 + 48;
			KetQua.insert(KetQua.size(), 1, c);
		}
		if (temp % 2 == 1)
			carry = 10;
		else carry = 0;
		count++;
		if (count == s.size())		//lam den khi bien count = do dai cua s
			break;
	}

	return KetQua;
}

string Plus1(string KetQua)				//ham cong 1
{
	int carry = 0, temp, pos;
	pos = KetQua.size() - 1;		//lay so dau tien tu phai qua
	temp = KetQua[pos] - 48 + 1;
	do
	{
		if (temp == 10)				//neu cong xong = 10 thi se co bien nho
		{
			KetQua[pos] = 48;
			carry = 1;
		}
		else//nguoc lai thi khong co bien nho
		{
			KetQua[pos] = temp + 48;
			carry = 0;
			break;
		}
		pos--;
		temp = KetQua[pos] - 48 + carry;
	} while (carry != 1);			//lam cho den khi het bien nho

	return KetQua;
}

string Multiply2(string KetQua)			//ham nhan 2
{
	string temp;
	int multi, carry = 0;	//multi: lay tung so nhan 2, carry: bien nho
	int pos = KetQua.size() - 1;
	while (pos >= 0)		//lam cho toi khi het pos
	{
		multi = (KetQua[pos] - 48) * 2 + carry;
		if (multi >= 10)	//neu nhan xong ma >= 10 thi phai co bien nho
		{
			carry = 1;
			multi -= 10;
		}
		else                //nguoc lai thi het bien nho
		{
			carry = 0;
		}
		temp.insert(0, 1, multi + 48);

		pos--;
	}
	if (carry == 1)			//TH van con bien nho thi phai them 1 vao
	{
		temp.insert(0, 1, 49);
	}

	return temp;
}

void TinhToanQInt(QInt &QInt1, QInt QInt2, char cToanTu)		//tuy theo tung truong hop ma tinh toan QInt
{
	if (cToanTu == '+')						//toan tu cong
		QInt1 = QInt1 + QInt2;
	else if (cToanTu == '-')				//toan tu tru
		QInt1 = QInt1 - QInt2;
	else if (cToanTu == '*')				//toan tu nhan
		QInt1 = QInt1 * QInt2;
	else if (cToanTu == '/')				//toan tu chia
		QInt1 = QInt1 / QInt2;
	else if (cToanTu == '&')				//toan tu &
		QInt1 = QInt1 & QInt2;
	else if (cToanTu == '|')				//toan tu |
		QInt1 = QInt1 | QInt2;
	else if (cToanTu == '^')				//toan tu ^
		QInt1 = QInt1 ^ QInt2;
	else if (cToanTu == '~')				//toan tu ~
		QInt1 = ~QInt1;
	else if (cToanTu == '=')				//operator gan
		QInt1 = QInt2;
	else if (cToanTu == '<')				//toan tu dich trai
		QInt1 = QInt1 << QInt2.GetterDec();
	else if (cToanTu == '>')				//toan tu dich phai
		QInt1 = QInt1 >> QInt2.GetterDec();
	else if (cToanTu == 'r')				//rotate right 1 lan
		QInt1.ror();
	else if (cToanTu == 'l')				//rotate left 1 lan
		QInt1.rol();
}