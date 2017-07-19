#include <iostream>

using namespace std;

template<typename N>
struct node		// struct cua cay AVL
{
	N key;
	unsigned char height;
	node<N>* left;
	node<N>* right;
	node<N>(N k) 
	{ key = k; left = right = 0; height = 1; }
};

template <typename N>
node<N>* newNode(N k)		//Tao node dau tien
{
	node<N>* a = (struct node<N>*)
		malloc(sizeof(struct node<N>));
	a->key = k;
	a->left = NULL;
	a->right = NULL;
	a->height = 1;  // new node is initially added at leaf
	return a;
}


template<typename N>
unsigned char height(node<N>* p)	//ham lay chieu cao cua cay
{
	if (p == NULL)
		return 0;
	else return p->height;
}


template<typename N>			//ham lay gia tri de kiem tra xem cay co can bang khong
int bfactor(node<N>* p)
{
	if (p == NULL)
		return 0;
	return height(p->right) - height(p->left);
}

template<typename N>
void fixheight(node<N>* p)		// ham sua lai chieu cao cua node
{
	if (p == NULL)
		return;
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

template <typename N>
node<N>* rotateright(node<N>* p)		// ham xoay phai
{

	node<N>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template <typename N>
node<N>* rotateleft(node<N>* q)			//ham xoay trai
{


	node<N>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template <typename N>
node<N>* balance(node<N>* p)		// ham can bang lai cay theo 4 truong hop
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		p = rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		p = rotateright(p);
	}
	return p;
}

template <typename N>	
node<N>* insert(node<N>* p, N k)		// chen phan tu moi vao cay
{
	if (!p) return new node<N>(k);
	else if (k < p->key)
		p->left = insert(p->left, k);
	else if (k >= p->key)
		p->right = insert(p->right, k);
	p = balance(p);
	return p;
}

template <typename N>
node<N>* findmin(node<N>* p)			// ham tim gia tri nho hon
{
	return p->left ? findmin(p->left) : p;
}

template <typename N>
node<N>* removemin(node<N>* p)			// ham xoa gia tri min
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

template <typename N>
node<N>* remove(node<N>* p, N k)		// ham xoa
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node<N>* q = p->left;
		node<N>* r = p->right;
		delete p;
		if (!r) return q;
		node<N>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	balance(p);
	return p;
}

template <typename N>
void preOrder(node<N> *p)		// ham duyet sau
{
	if (p != NULL) {
		cout << p->key << " ";
		preOrder(p->left);
		preOrder(p->right);
	}
}

template <typename N>
void inOrder(node<N> *p)		// ham duyet giua
{
	if (p != NULL) {
		inOrder(p->left);
		cout << p->key << " ";
		inOrder(p->right);
	}
}
template <typename N>
void postOrder(node<N> *p)		// ham duyet dau
{
	if (p != NULL) {
		postOrder(p->left);
		postOrder(p->right);
		cout << p->key << " ";
	}
}
template <typename N>
void find(N k, node<N> *aNode, int *s)	//ham tim kiem
{
	if (aNode != NULL) {
		if (aNode->left == aNode->right == NULL)
		*s = -1;
		else if (aNode->key < k ) {
			*s = (*s) + 1;
			find(k , aNode->right, s);
		}
		else if (aNode->key > k)
		{
			*s = (*s) + 1;
			find(k, aNode->left, s);
		}
		else if (aNode->key == k)
		{
			return;
		}

	}
}

template <typename N>
int find(N k, node<N> *aNode)		// ham lay ra muc cua phan tu
{
	int s = 0;
	find(k, aNode, &s);
	return s;
}