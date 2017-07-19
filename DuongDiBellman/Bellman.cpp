#include <iostream>
#define MAX 100
#define VoCuc 32767
using namespace std;
struct graph
{
	int n;
	int a[MAX][MAX];
};
graph g;
int LastV[MAX];
int dau, cuoi;
int P_truoc[MAX], P_hientai[MAX];

bool DuongDiNganNhat_Bellman(int dinhDau)
{
	int k = 0,i,j,v;
	for (int i = 0; i < g.n; i++)
	{
		P_hientai[i] = VoCuc;
	}
	P_hientai[dinhDau] = 0;

	while (true)
	{
		for (i = 0; i < g.n; i++)
			P_truoc[i] = P_hientai[i];

		for (i = 0; i < g.n; i++)
		{
			v = -1;
			for (j = 0; j < g.n;j++)
				if (g.a[i][j] != 0 && P_truoc[j] != VoCuc &&(v == -1 || P_truoc[j] + g.a[j][i] < P_truoc[v] + g.a[v][i]))
					v = j;
			if (v != -1 && (P_truoc[i] == VoCuc || P_truoc[i] > P_truoc[v] + g.a[v][i]))
			{
				LastV[i] = v;
				P_hientai[i] = P_truoc[v] + g.a[v][i];
			}
		}
		bool trung_nhau = true;
		for (i = 1; i <= g.n; i++)
		{
			if (P_truoc[i] != P_hientai[i])
			{
				trung_nhau = false;
				break;
			}
		}

		if (trung_nhau == true)
			return true;
		else
		{
			if (k < g.n - 1)
				k += 1;
			else return false;
		}
	}
}

void main()
{
	dau = 2;
	freopen("dothi.txt", "rt", stdin);
	cin >> g.n;
	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++)
			cin >> g.a[i][j];
	cin.clear();
	bool Ketqua;
	Ketqua = DuongDiNganNhat_Bellman(dau);
	freopen("duongdi.txt", "wt", stdout);
	if (Ketqua == true)
	{
		for (int i = 0; i < g.n; i++)
		{
			if (i != dau && LastV[i] != 0)
			{
				cout << "Duong di tu " << dau << " toi " << i << " la: ";
				int t = i;
				while (t != dau)
				{
					cout << t << "<--";
					t = LastV[t];
				}
				cout << t << endl;
			}
		}

	}
	else cout << "Ton tai mach am" << endl;
	cout.clear();
	getchar();
	getchar();
}
