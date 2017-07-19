#include "QInt.h"

QInt QInt::BatBit(int i, int j)			//hàm bật bit 0->1
{
	//Cách sử dụng:
	//i là phần tử a[0] hay a[1]
	//j là bit m muon bat (0 <= j <= 63)
	unsigned __int64 mask = 0x0000000000000001;	//0000...001
	mask = mask << j;
	arrayBits[i] = arrayBits[i] | mask;

	return *this;
}

QInt QInt::TatBit(int i, int j)			//hàm tắt bit 1->0
{
	//Cách sử dụng:
	//i là phần tử a[0] hay a[1]
	//j là bit m muon tat (0 <= j <= 63)
	unsigned __int64 mask = 0x0000000000000001;	//000..001
	mask = ~(mask << j);
	arrayBits[i] = arrayBits[i] & mask;

	return *this;
}

int QInt::XemBit(int i, int j)			// hàm xem bit
{
	//Cách sử dụng:
	//i là phần tử a[0] hay a[1]
	//j là bit m muon xem (0 <= j <= 63)
	unsigned __int64 mask = 0x0000000000000001;	//0000...001
	mask = mask << j;
	if ((arrayBits[i] & mask) != 0)
		return 1;
	else
		return 0;
}

void QInt::WriteFileLessThan128Bits(string output)	//ghi QInt sang file nhung khong ghi het 128 bit
{
	fstream fOut;
	fOut.open("output.txt", ios::out | ios::app);

	int i, j, pos;
	pos = FindBit1();		//tim bit 1 dau tien tu trai qua
	if (pos == -1)			//neu khong tim thay xuat 0
	{
		fOut << "0";
		fOut << endl;
		return;
	}
	if (pos > 63)
	{
		i = 0;
		j = pos - 64;
	}
	else
	{
		i = 1;
		j = pos;
	}

	unsigned __int64 mask = 0x8000000000000000;	//tao mat na: 10000...00
	mask = mask >> (63 - j);					//de so 1 dung vi tri
	for (; i <= 1; i++)		//chep tu a[0] xong den a[1]
	{
		for (; j >= 0; j--)		//lan luot chep 64 bit cua a[0] va a[1]
		{
			if ((arrayBits[i] & mask) != 0)
				fOut << "1";
			else
				fOut << "0";

			mask = mask >> 1;
		}
		mask = 0x8000000000000000;
		j = 63;
	}
	fOut << endl;
}


int QInt::GetterDec()				// hàm lấy giá trị thap phan cua a[1]
{
	return arrayBits[1];
}

int QInt::FindBit1()					//ham tim bit 1
{
	int i, j;
	int pos = 127;
	for (i = 0; i <= 1; i++)		//duyet tu a[0] qua a[1]
	{
		for (j = 0; j <= 63; j++)
		{
			if ((XemBit(i, 63 - j) == 1))	//kiem duoc bit 1 roi thi dung va return
				return pos;
			pos--;
		}
	}

	return -1;	//neu khong tim duoc tra ve -1
}


//Các phép toán tử ==================================================================

//y tuong: cac phep and, or, xor, not 64 bit con duoc C ho tro nen tach ra 2 phan tu dem tinh toan voi nhau
QInt QInt::operator&(QInt b)	//toan tu and
{
	arrayBits[0] = arrayBits[0] & b.arrayBits[0];
	arrayBits[1] = arrayBits[1] & b.arrayBits[1];

	return *this;
}

QInt QInt::operator|(QInt b)	//toan tu or
{
	arrayBits[0] = arrayBits[0] | b.arrayBits[0];
	arrayBits[1] = arrayBits[1] | b.arrayBits[1];

	return *this;
}

QInt QInt::operator^(QInt b)	//toan tu xor
{
	arrayBits[0] = arrayBits[0] ^ b.arrayBits[0];
	arrayBits[1] = arrayBits[1] ^ b.arrayBits[1];

	return *this;
}

QInt QInt::operator~()			//toan tu not
{
	arrayBits[0] = ~arrayBits[0];
	arrayBits[1] = ~arrayBits[1];

	return *this;
}

QInt QInt::operator=(QInt other)	//toan tu gan
{
	this->arrayBits[0] = other.arrayBits[0];
	this->arrayBits[1] = other.arrayBits[1];

	return *this;
}

QInt QInt::operator << (int n)		//dich trái
{
	int i;
	for (i = 0; i < n; i++)		//dich lan luot cho toi n lan
	{
		arrayBits[0] = arrayBits[0] << 1;	//dich trai a[0] truoc
		if (XemBit(1, 63) == 1)	//neu o giua la 1 thi khi dich trai ben kia cung se la 1
			BatBit(0, 0);
		arrayBits[1] = arrayBits[1] << 1;
	}

	return *this;
}

QInt QInt::operator >> (int n)		//dịch phải
{
	int i;
	for (i = 0; i < n; i++)	//dich lan luot cho toi n lan
	{
		arrayBits[1] = arrayBits[1] >> 1;
		if (XemBit(0, 0) == 1)
			BatBit(1, 63);
		else
			TatBit(1, 63);

		arrayBits[0] = arrayBits[0] >> 1;
	}

	return *this;
}

QInt QInt::rol() // rotate left 1 lần
{
	int i, j, temp;
	temp = XemBit(0, 63);
	arrayBits[0] = arrayBits[0] << 1;		//dịch trái a[0] trước
	if (XemBit(1, 63) == 1)					// kiểm tra bit thứ 63 của a[1] có phải là bit 1 hay không để nhét vào bit cuối cùng của a[0]
		BatBit(0, 0);
	arrayBits[1] = arrayBits[1] << 1;		// dịch trái a[1] bình thường

	if (temp == 1)		// trường hợp bit đầu tiên trái cùng là 1
		BatBit(1, 0);	// bit dau bang 1 thì đem bit này xuống bit cuối cùng bằng cách bật bit cuối cùng lên
	else
		TatBit(1, 0);	// bit dau bang 0 thì đem bit này xuống bit cuối cùng bằng cách bật bit cuối cùng lên

	return *this;

}

QInt QInt::ror()		//rotate right 1 lan
{
	int temp;
	temp = XemBit(1, 0);;
	arrayBits[1] = arrayBits[1] >> 1;		// dịch phải a[1] trước
	if (XemBit(0, 0) == 1)				//kiểm tra bit cuối của a[0] có phải là bit 0 hay 1
		BatBit(1, 63);		// trường hợp số âm (bit =1), khi dịch phải thêm bit 1 vao dau cua a[1]
	else
		TatBit(1, 63);		// trường hợp số dương (bit =0), khi dịch phải thêm bit 0 vao dau cua a[1]

	arrayBits[0] = arrayBits[0] >> 1;	// dịch phải a[0] bình thường

	if (temp == 1)
		BatBit(0, 63);	// dời bit 1 cuối cùng sang bit đầu tiên của a[0]
	else
		TatBit(0, 63);	// dời bit 0 cuối cùng sang bit đầu tiên của a[0]

	return *this;
}

//Các toán tử tính toán===============================================================

QInt QInt::operator+(QInt a)		// toán tử cộng
{
	int tam = 0;
	int bit;
	QInt output;
	//cong tung bit roi xem truong hop cu the
	for (int j = 1; j >= 0; j--)
	{
		for (int i = 0; i < 64; i++)
		{
			bit = XemBit(j, i) + a.XemBit(j, i) + tam;
			tam = 0;
			if (bit == 3)				//bit = 3: bien nho = 1, bat bit
			{
				tam = 1;
				output.BatBit(j, i);
			}

			if (bit == 2)				//bit = 2: bien nho = 1, tat bit
			{
				tam = 1;
				output.TatBit(j, i);
			}

			if (bit == 1)				//bit = 1: bien nho = 0, bat bit
			{
				tam = 0;
				output.BatBit(j, i);
			}

			if (bit == 0)				//bit = 0: bien nho = 0, tat bit
			{
				tam = 0;
				output.TatBit(j, i);
			}

		}
	}
	return output;
}



QInt QInt::operator-(QInt a)		// toán tử trừ
{
	QInt output;
	a.Bu2();	// b - a nghĩa là b + Bu2(a);
	output = *this + a;
	return output;
}

QInt QInt::operator*(QInt M)		// toán tử nhân
{
	QInt Q = *this;
	QInt A;
	int Q1 = 0;
	A.arrayBits[1] = A.arrayBits[0] = 0;	//Gán A trong toán tử * booth bằng 0
	for (int j = 0; j < 128; j++)			// Xét tổng n = 128 bit
	{
		if (Q1 == 0 && (Q.XemBit(1, 0) == 1)) //các hàm if và else if là để dịch phải theo như booth
		{
			Q1 = Q.XemBit(1, 0);			//Sau khi dịch phải Q thì giá trị Q1 là bit phải nhất của Q
			Q >> 1;							//Sau đó bắt đầu dịch phải Q để tránh trường hợp mất bit cuối để gán vào Q1
			A = A - M;						//Lấy A trừ giá trị M như trong thuật toán booth
		}
		else if (Q1 == 1 && (Q.XemBit(1, 0) == 0))	//Tương tự như hàm if ở trên
		{
			Q1 = Q.XemBit(1, 0);
			Q >> 1;
			A = A + M;						// Lấy A + M như trong thuật toán booth
		}
		else if ((Q1 == 0 && (Q.XemBit(1, 0) == 0)) || (Q1 == 1 && (Q.XemBit(1, 0) == 1))) //Đây là trường hợp không thay đổi giá trị của A
		{
			Q1 = Q.XemBit(1, 0);
			Q >> 1;
		}
		if (A.XemBit(1, 0) == 0)		//Sau đó như trên, nếu dịch phải A thì bit phải nhất của Q chính là bit trái nhất của A 
			Q.TatBit(0, 63);
		if (A.XemBit(1, 0) == 1)		//Phần if else này dùng để bật hoặc tắt bit phải nhất của Q và khiến Q như là đang dịch phải
			Q.BatBit(0, 63);
		A >> 1;		//Sau khi bật bit Q thì mới bắt đầu dịch trái A
	}
	return Q;
}

QInt QInt::operator/(QInt M)			// toán tử chia
{
	QInt Q = *this;
	QInt A;
	int flag = 0; // Nếu flag là 0 thì không cần đổi dấu kết quả, nếu flag là 1 thì phải đổi dấu kết quả.

	if (XemBit(0, 63) == 1 || M.XemBit(0, 63) == 1) //Hàm kiểm tra nếu số chia và số bị chia có giá trị âm
	{
		if (XemBit(0, 63) == 1 && M.XemBit(0, 63) == 1) //Nếu cả 2 số chia và số bị chia đều âm thì bù 2 cả 2 số
		{
			Q.Bu2();
			M.Bu2();
		}
		else if (XemBit(0, 63) == 1 && M.XemBit(0, 63) == 0) //Nếu Q là số âm 
		{
			Q.Bu2();
			flag = 1;
		}
		else if (XemBit(0, 63) == 0 && M.XemBit(0, 63) == 1) //Nếu M là số âm
		{
			M.Bu2();
			flag = 1;
		}
	}

	int k = 128;		//k: so bit cua Q va M	
	while (k > 0)
	{
		A << 1;	//Dịch bit A

		if (Q.XemBit(0, 63) == 1)	//Vì dịch trái nên bit phải nhất của Q là bit trái nhất của A
			A.BatBit(1, 0);
		Q << 1;
		A = A - M;					//Luôn lấy A - M ở mỗi vòng lặp

		if (A.XemBit(0, 63) == 1)	//Kiểm tra A dương hay âm và xử lý tùy trường hợp 
		{
			A = A + M;
			Q.TatBit(1, 0);
		}

		else
			Q.BatBit(1, 0);

		k--;
	}

	if (flag == 1)	//Nếu flag = 1 thì kết quả phép chia là số âm
		Q.Bu2();

	return Q;	//Do Q là thương và A là số dư nên ta chỉ cần Q

}


//=================================================================

QInt QInt::Bu2()			// hàm lấy bù 2
{
	int i, j, flag;
	//bù 2 là duyệt dãy bit từ phải qua. Gặp số 1 đầu tiên bỏ, còn lại đảo bit.
	//kiếm số 1 đầu tiên
	for (i = 1, flag = 0; i >= 0; i--)
	{
		for (j = 63; j >= 0; j--)
		{
			if (XemBit(i, 63 - j) == 1)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
	}

	if (j == 0 && i == 0)		//neu bit 1 nam o vi tri cuoi cung thi return
		return *this;

	if (j == 0)		//TH gặp số 1 ngay tai vi trí bit 63 của a[1]
	{
		j = 63;
		i = 0;
	}
	else
		j--;

	//bit 1: j = 62
	//dao bit bat dau tu sau so 1 dau tien kiem duoc tu phai qua
	for (; i >= 0; i--)
	{
		for (; j >= 0; j--)
		{
			if (XemBit(i, 63 - j) == 1)
				TatBit(i, 63 - j);
			else
				BatBit(i, 63 - j);
		}
		j = 63;
	}

	return *this;
}



QInt QInt::SaveTo(int p, string s)		// hàm lưu vào chuỗi
{
	if (p == 2)
		this->SaveBinary(s);	//luu nhi phan
	else if (p == 10)
		this->SaveDecimal(s);//luu thap phan
	else if (p == 16)
		this->SaveHexa(s);	//luu thap luc phan

	return *this;
}

QInt QInt::SaveBinary(string s)			// hàm lưu dãy nhị phân vào QInt
{
	int i, j, count;
	i = 1;
	count = 0;
	//chep tung bit cua string sang QInt
	for (j = s.size() - 1; j >= 0; j--)
	{
		//do cac bit khi tao deu la 0 nen chi khi gap bit 0 thi moi can bat bit
		if (s[j] == '1')
			BatBit(i, count);
		count++;
		//TH count > 63 thi phai qua a[0]
		if (count > 63)
		{
			count = 0;
			i = 0;
		}
	}

	return *this;
}

QInt QInt::SaveHexa(string s)		// hàm lưu dãy thập lục vào QInt
{
	int i, j, count, temp, bit;
	unsigned char mask = 0x01;		//0000 0001
	temp = 0;
	j = s.size() - 1;	//j: do dai cua s
	i = 1;
	bit = 0;
	//doc day thap luc phan trong de thanh day bit luu vao QInt
	for (; j >= 0; j--)
	{
		temp = BangMa(s[j]);	//đổi ra int
		for (count = 0; count < 4; count++)
		{
			//doi 1 lan 4 bit xem trong 4 bit do bit nao se bat
			if ((mask & temp) != 0)
				BatBit(i, bit + count);
			mask = mask << 1;
		}
		mask = 0x01;
		bit += 4;
		if (bit > 60)
		{
			bit = 0;
			i = 0;
		}
	}

	return *this;
}

void QInt::QIntToHexa()				//hàm chuyen tu QInt sang thap luc phan
{
	fstream fOut;
	fOut.open("output.txt", ios::out | ios::app);
	int temp, i, j, count, pos;
	//y tưởng: lưu trực tiếp kết quả vào file luôn không cần qua biến
	pos = FindBit1();	//vi tri xuat hien bit 1 dau tien
	if (pos == -1)		//TH khong tim thay bit 1
	{
		fOut << "0" << endl;	//xuat 0 va ket thuc
		return;
	}
	if (pos > 63)		//neu bit 1 nam o vi tri > 63
	{
		i = 0;
		pos = pos + (3 - pos % 4);	//dung de xac dinh 4 bit 1 lan
		j = pos - 64;
	}
	else
	{
		i = 1;
		pos = pos + (3 - pos % 4);
		j = pos;
	}
	for (temp = 0; i <= 1; i++)	//duyet từ bit 127 về 0
	{
		for (; j >= 0;)
		{
			for (count = 3, temp = 0; count >= 0; count--, j--)	//mỗi lần đếm 4 bit để cộng
			{
				if (XemBit(i, j) == 1)
					temp += (1 << count);
			}
			switch (temp)	//sau khi cộng xem truong hop cụ the de ghi vao file
			{
			case 10: {
				fOut << "A";
				break;
			}
			case 11: {
				fOut << "B";
				break;
			}
			case 12:
			{
				fOut << "C";
				break;
			}
			case 13: {
				fOut << "D";
				break;
			}
			case 14: {
				fOut << "E";
				break;
			}
			case 15: {
				fOut << "F";
				break;
			}
			default: fOut << temp;
			}
		}
		j = 63;
	}
	fOut << endl;

	fOut.close();
}

QInt QInt::SaveDecimal(string s)				// hàm luu thap phan vao QInt
{
	//y tuong: chia s lon de lay phan du cho vao QInt, phan nguyen dem chia tiep
	int i, bit, flag;	//flag: kiem tra xem chuoi string co dau '-' ko
	i = 1;
	flag = 0;
	bit = 0;
	if (s[0] == '-')	//neu day la so am
	{
		flag = 1;
		s.erase(0, 1);
	}
	while (1)
	{
		if ((s[s.size() - 1] - 48) % 2 == 1)	//neu nhu phan tu cuoi cung cua chuoi la so le thi bat bit
			BatBit(i, bit);
		bit++;
		if (bit > 63)	//TH đã xet het a[1]
		{
			bit = 0;
			i = 0;
		}

		s = divide2(s);	//chia s cho 2
		if (s == "")
			break;
	}

	if (flag == 1)	//TH string nhap vao la so am
		Bu2();

	return *this;

}

string QInt::QIntToDecimal()					// chuyển từ QInt sang thập phân
{
	string KetQua;
	//cac TH mot minh a[1] cung co the bieu dien duoc so nguyen lon
	if (arrayBits[1] > 0 && arrayBits[0] == 0)	//a[1] > 0 dong thoi a[0] = 0 thi so nay duong va chi can a[1] bieu dien
	{
		while (arrayBits[1] > 0)
		{
			KetQua.insert(0, 1, arrayBits[1] % 10 + 48);
			arrayBits[1] /= 10;
		}
		return KetQua;
	}
	if (arrayBits[1] < 0 && arrayBits[0] == -1)	//a[1] < 0 dong thoi a[0] = -1 thi so nay am va chi can a[1] bieu dien
	{
		arrayBits[1] = -arrayBits[1];
		while (arrayBits[1] > 0)
		{
			KetQua.insert(0, 1, arrayBits[1] % 10 + 48);
			arrayBits[1] /= 10;
		}
		return KetQua.insert(0, 1, '-');
	}

	//TH vuot qua pham vi co the chua cua a[1]
	int sign = 0;	//bit dau
	if (XemBit(0, 63) == 1)	//neu la am
	{
		sign = 1;	//bit dau bat len
		Bu2();		//lay bu 2 cua QInt
	}
	//y tuong: di tu trai qua thay bit 1 thi bat dau lay temp = 0 * 2 + 1 = 1. Tu sau do neu gap 0 thi chi x2. gap 1 thi x2 + 1
	int pos = FindBit1();
	if (pos < 0)
		return "0";
	KetQua = "0";
	while (pos >= 0)
	{
		if (pos > 63)	//voi bit >= 63
		{
			if (XemBit(0, pos - 64) == 1)	//khi gap bit 1
			{
				KetQua = Multiply2(KetQua);	//x2
				KetQua = Plus1(KetQua);		//+ 1 
			}
			else
				KetQua = Multiply2(KetQua);	//gap bit 0 thi chi nhan 2
		}
		else//voi bit <= 63
		{
			if (XemBit(1, pos) == 1)
			{
				KetQua = Multiply2(KetQua);
				KetQua = Plus1(KetQua);
			}
			else
				KetQua = Multiply2(KetQua);
		}
		pos--;
	}

	if (sign == 1)				//neu am thi them dau tru phia truoc
		KetQua.insert(0, 1, '-');

	return KetQua;
}

QInt::QInt()			//ham khoi tao gia tri mac dinh cho QInt
{
	arrayBits[0] = 0;	//khi khoi tao thi a[0] và a[1] cùng bang 0
	arrayBits[1] = 0;
}

QInt::QInt(int a, int b)//ham khoi tao khi co tham so truyen vao cho QInt
{
	arrayBits[0] = a;
	arrayBits[1] = b;
}

QInt::~QInt()
{
}
