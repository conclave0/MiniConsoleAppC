#include "Source.h"

void main()
{

	node<int> *a;
	int n;
	int m;
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		fflush(stdin);
		cout << "Nhap phan tu thu " << i + 1 << ": ";
		cin >> m;
		if (i == 0)
			a = new node<int>(m);
		
		else a = insert(a, m);
	}
	int check;
	do
	{
		fflush(stdin);
		check = 0;
		cout << endl;
		cout << "1. Them mot phan tu vao cay." << endl;
		cout << "2. Xoa mot phan tu thuoc cay." << endl;
		cout << "3. Tim kiem phan tu trong cay." << endl;
		cout << "4. Duyet cay." << endl;
		cout << "5. Ket thuc." << endl << endl;
		cout << "Ban chon: ";
		cin >> check;

		switch (check)
		{
		case 1:
		{
			system("cls");
			fflush(stdin);
			int key;
			cout << "Nhap phan tu vao cay: ";
			cin >> key;
			a = insert(a, key);
			a = balance(a);
			break;
		}
		case 2:
		{
			system("cls");
			fflush(stdin);
			int key;
			cout << "Nhap phan tu can xoa: ";
			cin >> key;
			a = remove(a, key);
			a = balance(a);
			break;
		}
		case 3:
		{
			system("cls");
			fflush(stdin);
			int key;
			cout << "Nhap phan tu can tim: ";
			cin >> key;
			int count;
			count = find(key, a);
			if (count == -1)
				cout<< endl << "Khong ton tai" << endl;
			else cout << "Muc cua phan tu "<< key << ": " << count<< endl;
			a = balance(a);
			break;
		}
		case 4:
		{
			system("cls");
			cout<< endl << "Duyet giua: " << endl;
			inOrder(a);
			cout << endl << "Duyet truoc: " << endl;
			postOrder(a);
			cout << endl << "Duyet sau: " << endl;
			preOrder(a);
			break;
		}
		}

 	} while (check != 5);
}
