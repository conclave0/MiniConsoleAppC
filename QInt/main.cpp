#include "QInt.h"
#include "IOFile.h"

void main(int argc, char *argv[])
{
	if (argc != 3)		//neu nhu tham so vao khac 3
	{
		fstream fOut;
		fOut.open("output.txt", ios::out);	//tao 1 file output va xuat khong du so phan tu
		fOut << "Khong du so phan tu.";
		fOut.close();
		return;
	}
	ifstream fIn(argv[1]);
	fstream fOut;
	fOut.open(argv[2], ios::out);
	string big;
	while (!fIn.eof())				//doc cho den khi het file
	{
		CIOFile RW;
		QInt QInt1, QInt2;
		big.clear();
		getline(fIn, big);							//chep 1 dong cua file vao big
		RW.readFile(big, QInt1, QInt2);				//doc file va luu gia tri vao bien
		RW.CalAndWrite(argv[2], QInt1, QInt2);		//tinh toan va chep ket qua ra file output
	}

	fIn.close();
	fOut.close();
}