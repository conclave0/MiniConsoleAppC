#include    <stdio.h>
#include    <stdlib.h>
#include    <conio.h>
#include    <dos.h>
#include    <string.h>
#include    <math.h>
#include <alloc.h>
#define TRUE 1
#define FALSE 0
typedef struct {
	int masv;
	char hoten[20];
} sinhvien;
typedef struct node{
	sinhvien infor;
	struct node *next;
} *NODEPTR;
void Initialize(NODEPTR *plist){
	*plist = NULL;
}
NODEPTR Getnode(void){
	NODEPTR p;
	p = (NODEPTR)malloc(sizeof(struct node));
	return(p);
}
void Freenode(NODEPTR p){
	free(p);
}
int Emptynode(NODEPTR *plist){
	if (*plist == NULL)
		return(TRUE);
	return(FALSE);
}
NODEPTR Inserttop(NODEPTR *plist, sinhvien x){
	NODEPTR p;
	p = Getnode();
	p->infor = x;
	if (Emptynode(plist)){
		p->next = NULL;
		*plist = p;
		return(p);
	}
	p->next = *plist;
	*plist = p;
	return(p);
}
int Bottomnode(NODEPTR *plist){
	int i; NODEPTR p;
	if (Emptynode(plist))
		return(-1);
	p = *plist; i = 0;
	while (p != NULL){
		i = i + 1;
		p = p->next;
	}
	return(i);
}
NODEPTR Insertbottom(NODEPTR *plist, sinhvien x){
	NODEPTR p, q; int n, i;
	n = Bottomnode(plist);
	if (n == -1){
		Inserttop(plist, x);
		return(*plist);
	}
	p = *plist; i = 0; q = Getnode(); q->infor = x;
	while (i<n - 1){
		p = p->next;
		i = i + 1;
	}
	p->next = q; q->next = NULL;
	delay(2000); return(q);
}
NODEPTR Insertafter(NODEPTR *plist, sinhvien x, int n){
	NODEPTR p, q; int i;
	if (n<0){
		printf("\n Vi tri khong hop le");
		delay(2000); return(NULL);
	}
	p = *plist; i = 0;
	while (p != NULL && i<n){
		i = i + 1;
		p = p->next;
	}
	if (p == NULL){
		printf("\n Vi tri khong hop le");
		delay(2000); return(NULL);
	}
	q = Getnode(); q->infor = x;
	q->next = p->next;
	p->next = q;
	return(q);
}
void Deltop(NODEPTR *plist){
	NODEPTR p, q;
	p = *plist;
	if (Emptynode(plist)){
		printf("\n Danh sach rong");
		delay(2000); return;
	}
	q = p; p = p->next; *plist = p;
	printf("\n Node bi loai bo");
	printf("\n%-5d%-20s", q->infor.masv, q->infor.hoten);
	delay(2000); Freenode(q);
}
void Delbottom(NODEPTR *plist){
	NODEPTR p, q; int i, n;
	n = Bottomnode(plist);
	if (n == -1){
		printf("\n Danh sach rong");
		delay(2000); return;
	}
	if (n == 1){
		Deltop(plist); return;
	}
	p = *plist; i = 0;
	while (i<n - 2){
		p = p->next;
		i = i + 1;
	}
	q = p->next; p->next = NULL;
	printf("\n Node duoc loai bo");
	printf("\n %-5d%-20s", q->infor.masv, q->infor.hoten);
	delay(2000); Freenode(q);
}
void Delcurrent(NODEPTR *plist, int n){
	NODEPTR p, q; int i;
	if (Emptynode(plist)){
		printf("\n Danh sach rong");
		delay(2000); return;
	}
	if (n == 0){
		Deltop(plist); return;
	}
	p = *plist; i = 0;
	while (p != NULL && i<n - 1){
		i = i + 1;
		p = p->next;
	}
	if (p->next == NULL){
		printf("\n Node khong hop le");
		delay(2000); return;
	}
	q = p->next; p->next = q->next;
	printf("\n Node duoc loai bo");
	printf("\n %-5d%-20s", q->infor.masv, q->infor.hoten);
	delay(2000); Freenode(q);
}
void Travenode(NODEPTR *plist){
	NODEPTR p;
	if (Emptynode(plist)){
		printf("\n Danh sach rong");
		delay(2000); return;
	}
	p = *plist;
	while (p != NULL){
		printf("\n %-5d%-20s", p->infor.masv, p->infor.hoten);
		p = p->next;
	}
	delay(2000);
}
void Sortnode(NODEPTR *plist){
	NODEPTR p, q; sinhvien temp;
	for (p = *plist; p != NULL; p = p->next){
		for (q = p->next; q != NULL; q = q->next){
			if (p->infor.masv>q->infor.masv){
				temp = p->infor; p->infor = q->infor;
				q->infor = temp;
			}
		}
	}
	printf("\n Danh sach duoc sap xep");
	for (p = *plist; p != NULL; p = p->next){
		printf("\n %-5d%-20s", p->infor.masv, p->infor.hoten);
	}
	delay(2000);
}
void Searchnode(NODEPTR *plist, int masv){
	NODEPTR p;
	p = *plist;
	while (p != NULL && p->infor.masv != masv)
		p = p->next;
	if (p == NULL)
		printf("\n Node khong ton tai");
	else {
		printf("\n Node can tim");
		printf("\n %-5d%-20s", p->infor.masv, p->infor.hoten);
	}
	delay(2000);
}

void Thuchien(void){
	NODEPTR plist; sinhvien x, y; int vitri; char c;
	Initialize(&plist);
	do {
		clrscr();
		printf("\n THAO TAC VOI SINGLE LINK LIST");
		printf("\n 1- Them node dau danh sach");
		printf("\n 2- Them node cuoi danh sach");
		printf("\n 3- Them node giua danh sach");
		printf("\n 4- Loai bo node dau danh sach");
		printf("\n 5- Loai bo node cuoi danh sach");
		printf("\n 6- Loai node giua danh sach");
		printf("\n 7- Duyet danh sach");
		printf("\n 8- Sap xep danh sach");
		printf("\n 9- Tim kiem danh sach");
		printf("\n 0- Tro ve");
		c = getch();
		switch (c){
		case '1':
			printf("\n Ma sinh vien:"); scanf("%d", &x.masv);
			fflush(stdin); printf("\n Ho va ten:"); gets(x.hoten);
			Inserttop(&plist, x); break;
		case '2':
			printf("\n Ma sinh vien:"); scanf("%d", &x.masv);
			fflush(stdin); printf("\n Ho va ten:"); gets(x.hoten);
			Insertbottom(&plist, x); break;
		case '3':
			printf("\n Vi tri tren:"); scanf("%d", &vitri);
			printf("\n Ma sinh vien:"); scanf("%d", &x.masv);
			fflush(stdin); printf("\n Ho va ten:"); gets(x.hoten);
			Insertafter(&plist, x, vitri - 1); break;
		case '4': Deltop(&plist); break;
		case '5': Delbottom(&plist); break;
		case '6':
			fflush(stdin); printf("\n Vi tri loai bo:");
			scanf("%d", &vitri);
			Delcurrent(&plist, vitri - 1); break;
		case '7': Travenode(&plist); break;
		case '8': Sortnode(&plist); break;
		case '9':
			fflush(stdin); printf("\n Ma sinh vien:");
			scanf("%d", &vitri);
			Searchnode(&plist, vitri); break;
		}
	} while (c != '0');
}
void main(void){
	Thuchien();
}
