#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <istream>
#include <fstream>

using namespace std;
// xap xep tang dan
int* CreateArray(int n, int lim)
{
	int *arr = new int [n];
	srand((unsigned int)time(NULL));
	for(int i = 0; i< n;i++)
		arr[i] = rand() % lim;
	return arr;
}

void Swap(int &a, int &b)
{
	a=a+b;
	b=a-b;
	a=a-b;
}

int* SelectionSort(int* a, int n)
{
	int *temp = a;
	int min;
	for(int i = 0;i < n -1; i++)
	{	min = i;
		for(int j = i+1; j<n;j++)
		{
			if(temp[j] < temp[min])
				min = j;
		}
		if(min != i)
			swap(temp[i], temp[min]);
	}
	return temp;
}

int* InterchangerSort(int* a, int n)
{	int* temp = a;
	for(int i = 0;i<n - 1;i++)
	for(int j = i+1;j<n;j++)
		if(temp[i]>temp[j])
			swap(temp[i],temp[j]);
return temp;
}

int* InsertionSort(int *a, int n)
{
	int *temp = a;
	int k = 1;
	int value;
	while( k < n )
	{
		int i = k-1;
		value = temp[k];
		while(i >= 0 && a[i] > value)
		{
			temp[i+1] = a[i];
			i = i-1;
		}
		temp[i+1] = value;
		k++;
	}
	return temp;
}

int* BubbleSort(int *a, int n)
{
	int *temp = a;
	int i = n ,c;
	while(i > 1 )
	{
		c = 0;
		for(int j = 0; j < i - 1; j++)
			if(temp[j] >= temp[j+1])
			{
				Swap(temp[j],temp[j+1]);
				c=1;
			}

		if(c!=0)	
			i--;
		else if(c == 0)	return temp;
	}
	return temp;
}

int* HeapSort(int *a, int n)
{
	int *temp = a;
	int end = n -1;
	//make heap
	int start = n/2;
	while(start >= 0)
	{
		int i = start;
		int j = i*2;
		while(j<n)
		{
			if( j+1 <= n && temp[j] < temp[j+1])
				j++;
			if(temp[i] < temp[j])
			{
				Swap(temp[i], temp[j]);
				i = j;
				j = j*2;
			}
			else break;
		}
		start --;
	}
	while(end >= 0)
	{
		Swap(temp[end],temp[0]);
		end--;
		int i = 0;
		int j = 0;
		while(j < end)
		{
			if ( j+1 < end && temp[j] < temp[j+1])
				j++;
			if(temp[i] < temp[j])
			{	
				Swap(temp[i], temp[j]);
				i = j ;
				j = j*2;
			}
			else break;
		}

	}
	return temp;
}

int getMax(int *array, int n)

{

	int max = array[0];

	for (int i = 1; i < n; i++)

		if (array[i] > max)

			max = array[i];

	return max;

}

void countSort(int *arr, int n, int exp)

{

	int *output;
	output = new int[n];

	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)

		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)

		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)

	{

		output[count[(arr[i] / exp) % 10] - 1] = arr[i];

		count[(arr[i] / exp) % 10]--;

	}

	for (i = 0; i < n; i++)

		arr[i] = output[i];

}

int* RadixSort(int *arr, int n)
{
	int *temp = arr;
	int m = getMax(temp, n);

	for (int exp = 1; m / exp > 0; exp *= 10)

		countSort(temp, n, exp);
	return temp;
}
// left, right la bien trai va bien phai cua mang
void Merge(int *a, int left, int mid, int right);
int* MergeSort(int *a, int left, int right)
{
	int *temp = a;
	if (right > left)
	{
		int mid; // Phan tu o giua
		mid = (left + right) / 2;
		MergeSort(temp , left, mid); // Goi de quy mang con ben trai
		MergeSort(temp , mid + 1, right); // Goi de quy mang con ben phai
		Merge(temp, left, mid, right); // Goi ham so sanh hai mang con
	}
	return temp;
}

void Merge(int *a, int left, int mid, int right)
{
	int *temp; // Khoi tao mang tam de sap xep
	int i = left; // Vi tri phan tu dau tien cua mang con ben trai
	int j = mid + 1; // Vi tri phan tu dau tien cua mang con ben phai

	temp = new int[right - left + 1]; // Khoi tao so luong phan tu cua mang tam

	for (int k = 0; k <= right - left; k++)
	{
		// Kiem phan tu cua mang con ben trai va ben phai
		if (a[i] < a[j])
		{
			// Neu a[i] < a[j] thi copy phan tu ben trai vao mang tam
			temp[k] = a[i];
			i++; // Vi tri phan tu tiep theo cua mang
		}
		else // Nguoc lai copy phan tu cua mang con ben phai vao mang tam
		{
			temp[k] = a[j];
			j++; // Vi tri phan tu tiep theo cua mang
		}

		// Kiem tra mang con ben trai con phan tu nao khong
		if (i == mid + 1)
		{
			// Nguoc lai dua cac phan tu con lai cua mang con ben phai vao mang tam
			while (j <= right)
			{
				k++;
				temp[k] = a[j];
				j++;
			}
			break;
		}

		// Kiem tra mang con ben phai con phan tu nao khong
		if (j == right + 1)
		{
			// Nguoc lai dua cac phan tu con lai cua mang con ben phai vao mang tam
			while (i <= mid)
			{
				k++;
				temp[k] = a[i];
				i++;
			}
			break;
		}
	}

	for (int k = 0; k <= right - left; k++) // Chep mang tam vao mang chinh
		a[left + k] = temp[k];
	delete temp;
}

int* QuickSort(int *a, int n)		//khong de quy
{
	int *temp = a;
	int *Sl, *Sr, l, r;
	Sl = new int[n];
	Sr = new int[n];
	//Sl ,Sr :Mang dung nhu Stack luu tru vi tri ben trai, ben phai
	unsigned long Sp = 1;//So phan tu cua Stack
	Sl[Sp - 1] = 0; Sr[Sp - 1] = n - 1;
	while (Sp > 0)//2 Stack khac rong
	{
		l = Sl[Sp - 1]; r = Sr[Sp - 1];
		Sp--;
		while (l<r)
		{
			long i = l, j = r, x = abs(temp[(i + j) / 2]);
			while (i <= j)
			{
				while (abs(temp[i]) < x)
					i++;
				while (abs(temp[j]) > x)
					j--;
				if (i <= j)
					swap(temp[i++], temp[j--]);
			}
			if (i<r)
			{
				Sp++;
				Sl[Sp - 1] = i;  Sr[Sp - 1] = r;
			}
			r = j;
		}
	}
	return temp;
}

int* QuickSortRecursion(int *a, int m, int n)//m = 0, n = n-1, co de quy
{
	int *temp = a;
	int mid;
	int  i = m, j = n;
	mid = temp[(m + n) / 2];//gia tri lam moc de so sanh, khong nhat thiet la gia tri o giua
	while (i < j)
	{
		while (temp[i] < mid) i++;//tim vi tri nho hon gtri moc
		while (temp[j] > mid) j--;//tim vi tri lon hon gtri moc
		//hoan doi 2 vi tri do cho nhau
		if (i <= j)
		{
			Swap(temp[i], temp[j]);
			i++; j--;//sau khi doi cho, tang giam i,j den vi tri tiep theo
		}
	}
	//goi de quy de phan hoach thanh vung sap xep so voi vi tri moc
	if (m<i)
		QuickSortRecursion(temp, m, j);
	if (i<n)
		QuickSortRecursion(temp, i, n);

	return temp;
}

void Print(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}cout << endl;
}

void main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return;
	}

	freopen(argv[1], "wt", stdout);
	double result = 0;
	int *temp1, *temp2, *temp3, *temp4, *temp5, *temp6, *temp7, *temp8, *temp9;
	clock_t start, end;

	int *a;
	int n = atoi(argv[2]);
	int b = 30001;
	for (int i = 0; i < 50; i++)
	{
		a = CreateArray(n, b);
		temp1 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp1[i] = a[i];
		}

		temp2 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp2[i] = a[i];
		}

		temp3 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp3[i] = a[i];
		}
		temp4 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp4[i] = a[i];
		}
		temp5 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp5[i] = a[i];
		}
		temp6 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp6[i] = a[i];
		}
		temp7 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp7[i] = a[i];
		}
		temp8 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp8[i] = a[i];
		}
		temp9 = new int[n];
		for (int i = 0; i < n; i++)
		{
			temp9[i] = a[i];
		}

		start = clock();
		temp1 = SelectionSort(temp1, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result<< "	";

		start = clock();
		temp2 = InsertionSort(temp2, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";
		
		temp3 = a;
		start = clock();
		temp3 = InterchangerSort(a, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";

		start = clock();
		temp4 = BubbleSort(temp4, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";

		start = clock();
		temp5 = HeapSort(temp5, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";

		start = clock();
		temp6 = QuickSortRecursion(temp6,0 , n-1);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";

		start = clock();
		temp7 = QuickSort(temp7, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";

		start = clock();
		temp8 = MergeSort(temp8,0,n-1);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << "	";

		start = clock();
		temp9 = RadixSort(temp9, n);
		end = clock();
		result = (double)(end - start) / CLOCKS_PER_SEC;
		cout << result << endl;
	}
}
