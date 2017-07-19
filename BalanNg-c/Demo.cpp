#include<iostream>
using namespace std;
#define NMAX 200

typedef char PhanTu[NMAX];
typedef PhanTu MangChuoi[NMAX];

void init(MangChuoi &BieuThuc);//khoi tao
void nhapBieuThuc(MangChuoi &bieuThuc, int &nBT);//nhap bieu thuc toan hoc
void push(MangChuoi &Stack, int &nStack, PhanTu x);//them pt vao stack
char* pop(MangChuoi &Stack, int &nStack);//lay pt ra khoi stack
int isEmpty(int nStack);//tra ve 1 neu sTack=0, neu ko tra ve 0
void taoBalanNguoc(MangChuoi &Balan, int &nBL, MangChuoi bieuThuc, int nBT);//tao bieu thuc Ba lan nguoc
int uuTienToanTu(char a, char b);//neu toan tu a uu tien hon b thi tra ve 1, neu ko tra ve 0
int ktToanTu(char a);//kt xem a co phai la toan tu (+ - * /) hay khong
float tinhBieuThucBalanNguoc(MangChuoi Balan, int nBL);//tinh gia tri bieu thuc tu bieu thuc Balan
//---------------------------------------------------------
int main()
{
    MangChuoi bieuThuc,Balan;
    int nBT, nBL=0;
    cout<<"Nhap bieu thuc (chi gom '+' '-' '*' '/' '(' ')' ):"<<endl<<"S = ";
    nhapBieuThuc(bieuThuc, nBT);
    taoBalanNguoc(Balan,nBL,bieuThuc,nBT);
    cout<<endl<<"Bieu thuc duoi dang Balan nguoc:"<<endl;
    for (int i=0; i<nBL; i++) cout<<Balan[i]<<" "; cout<<endl;
    cout<<endl<<"Gia tri bieu thuc: S = "<<tinhBieuThucBalanNguoc(Balan,nBL)<<endl;
    system("pause");
    return 0;
}
//---------------------------------------------------------
void init(MangChuoi &BieuThuc)
{
     for (int i=0; i<NMAX; i++)
         for (int j=0; j<NMAX; j++) BieuThuc[i][j]=0;
}

void nhapBieuThuc(MangChuoi &bieuThuc, int &nBT)//nhap bieu thuc toan hoc
{
     char s[NMAX]={0};
     cin.getline(s,NMAX);
     init(bieuThuc);
     int i;
     nBT=0;
     for (i=0; i<strlen(s); i++)
     {
         if ((s[i]<'0' || s[i]>'9') && s[i]!='.')
         {
            bieuThuc[nBT][strlen(bieuThuc[nBT])]=s[i];
            nBT++;
         }
         else
         {
             bieuThuc[nBT][strlen(bieuThuc[nBT])]=s[i];
             if ((s[i+1]<'0' || s[i+1]>'9') && s[i+1]!='.') nBT++;
         }
     }
}

void push(MangChuoi &Stack, int &nStack, PhanTu x)//thao tac push trong stack
{
     strcpy(Stack[nStack],x);
     nStack++;
}

char* pop(MangChuoi &Stack, int &nStack)//thao tac pop trong stack
{
      nStack--;
      return Stack[nStack];
}

int isEmpty(int nStack)//kiem tra stack co rong hay khong
{
    return (nStack==0?1:0);
}

int uuTienToanTu(char a, char b)//neu toan tu a uu tien hon b thi tra ve 1, neu ko tra ve 0
{
    if ((a=='*'||a=='/') && (b=='+'||b=='-')) return 1;
    if ((a=='*'||a=='/') && (b=='*'||b=='/')) return 1;
    if ((a=='+'||a=='-') && (b=='+'||b=='-')) return 1;
    return 0;   
}

int ktToanTu(char a)//a la toan tu tra ve 1, ko thi tra ve 0
{
    if ((a<'0' || a>'9') && a!='(' && a!=')') return 1;
    return 0;
}

void taoBalanNguoc(MangChuoi &Balan, int &nBL, MangChuoi bieuThuc, int nBT)//chuyen bieu thuc toan hoc thanh Ba lan nguoc
{
     MangChuoi stack;//khai bao stack
     int nS=0;
     nBL=0;
     
     for (int i=0; i<nBT; i++)//doc tung phan tu trong bieu thuc
     {
         if (bieuThuc[i][0]>='0' && bieuThuc[i][0]<='9')//neu phan tu la toan hang thi dua vao hang doi ket qua
            push(Balan,nBL,bieuThuc[i]);
         else
              if (bieuThuc[i][0]!='(' && bieuThuc[i][0]!=')')//neu phan tu la toan tu
              {
                 while (!isEmpty(nS))//push tat ca cac toan tu c� do uu tien cao hon toan tu hien thoi va cho vao hang doi ket qua
                 {
                       if (!ktToanTu(stack[nS-1][0])) break;
                       if (uuTienToanTu(stack[nS-1][0],bieuThuc[i][0]))
                          push(Balan,nBL,pop(stack,nS));
                       else break;
                 }
                 push(stack,nS,bieuThuc[i]);//dua toan tu dang xet vao stack
              }
         else
             if (bieuThuc[i][0]=='(')//neu phan tu la dau "(" thi cho vao stack
                push(stack,nS,bieuThuc[i]);
         else
             if (bieuThuc[i][0]==')')//neu phan tu la dau ngoac ")"
             {
                while (stack[nS-1][0]!='(')//lay tat ca cac phan tu cho den dau ngoac "(" trong stack cho vao hang doi ket qua
                      push(Balan,nBL,pop(stack,nS));
                pop(stack,nS);//xoa dau ngoac "(" khoi stack
             }
     }
     while (!isEmpty(nS))//neu con gia tri trong ngan xep thi dua tat ca cac gia tri nay vao hang doi ket qua
           push(Balan,nBL,pop(stack,nS));
}

float tinhBieuThucBalanNguoc(MangChuoi Balan, int nBL)//tinh gia tri bieu thuc Ba lan nguoc
{
      float stack[NMAX];//stack chua gia tri tinh toan
      int nS=0;
      float a,b,kq;
      for (int i=0; i<nBL; i++)//doc tung phan tu trong bieu thuc Ba lan nguoc
      {
          if (Balan[i][0]>='0' && Balan[i][0]<='9')//neu phan tu la toan hang
          {
             stack[nS]=atof(Balan[i]);//push toan hang vao stack
             nS++;
          }
          else//neu phan tu la toan tu
          {
              if (nS<2)//neu stack khong du toan hang de thuc hien phep tinh thi bieu thuc nhap sai
              {
                 cout<<"Bieu thuc bi loi"<<endl; return 0;
              }
              else//truong hop thuc hien duoc
              {
                  //lay 2 toan hang tu stack ra de thuc hien phep tinh
                  a=stack[nS-1]; nS--;
                  b=stack[nS-1]; nS--;
                  switch (Balan[i][0])
                  {
                         case '+':
                                  kq=a+b; break;//tinh cong
                         case '-':
                                  kq=b-a; break;//tru
                         case '*':
                                  kq=a*b; break;//nhan
                         case '/':
                                  kq=b/a; break;//chia
                  }
                  stack[nS]=kq; nS++;//dua gia tri vua tinh tro lai stack
              }
          }
      }
      if (nS==1) return stack[nS-1];//neu stack chi con 1 gia tri thi do la gia tri bieu thuc
      else cout<<"Bieu thuc nhap bi loi"<<endl;//neu stack con tu 2 gia tri tro len thi bieu thuc sai
}
