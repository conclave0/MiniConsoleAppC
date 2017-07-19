#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "fstream"
#define MAX_WORD 8
#define STD_DIC_NAME "stddic.txt"
#define DIC_NAME "dictionary2.txt"
#define BOOK_NAME "Book.txt"
using namespace std;
class CTrie_Node
{
private:
	char key;
	bool leaf;
public:	vector<CTrie_Node*> children;
	string word;//
	int prior;//
public:
	//cai tien
	//tang prior cho child key, sap xep lai children, su dung insertsort
	CTrie_Node* UpdatePriorNode(char key,int point=1)
	{
		for (int i = 0; i < children.size();i++)
			if (children[i]->GetKey() == key)
			{
				children[i]->prior += point;//tang prior
				CTrie_Node* tmp = children[i];//luu dia chi child key
				if (i != 0)
				{
					int j;
					for (j = i-1; j >= 0;j--)
						if (tmp->prior > children[j]->prior)
						{
							children[j + 1] = children[j];
						}
						else break;
					children[j + 1] = tmp;
				}
				return tmp;//tra ve dia chi cua child key
			}
		
	}
	char GetKey(){
		return key;
	}

	void SetKey(char ch){
		key = ch;
	}

	void SetWord(string Word)//
	{
		word = Word;
	}

	string GetWord(string Word)//
	{
		return word;
	}

	bool CheckLeaf(){
		return leaf;
	}

	void SetLeaf(bool status = true){
		leaf = status;
	}

	CTrie_Node* FindChild(char ch){
		CTrie_Node* temp;
		for (int i = 0; i < children.size(); i++){
			temp = children[i];
			if (temp->key == ch){
				return temp;
			}
		}
		return NULL;
	}

	void AppendChild(CTrie_Node* child){
		children.push_back(child);
	}

	vector<CTrie_Node*> GetChildren(){
		return children;
	}

	CTrie_Node(){
		key = ' ';
		leaf = false;
		prior = 0;
	};
	~CTrie_Node(){};
};

//check dau
bool checkDau(char key)
{
	switch (key)
	{
	case ' ':case 13: case '.':case ',':return true;
	default:
		return false;
		break;
	}
}


class CTrie
{
private:
	CTrie_Node* root;
public:
	void Insert(string& key,int point=0);
	void InsertDic(string fileIn);//tu dien ngoai bo, chi co word
	void ImportDic(string fileIn);//tu dien noi bo, word+prior
	void ExportDic(string fileOut);//xuat danh sach ra file, word+prior
	vector<string> FindWordFromKey(string key,CTrie_Node* pos = NULL);
	void LearnWord(string& key,int point=1);
	vector<string> FindHighPriorWord();//tim cac tu co prior cao nhat //goi y dau tien
	void LearnWordFromSentence(string fileIn);//hoc them tu moi tu doan van
	void LearnSentenceFromPara(string fileIn);//hoc cau
	void EraseWord(string key);//xoa mot tu

	vector<string> FindWordCont(char key, CTrie_Node* &pos);//tim tu lien tuc
	CTrie();
	~CTrie();
};

void CTrie::LearnWordFromSentence(string fileIn)
{
	fstream fi;
	fi.open(fileIn, ios::in);
	string tmp;
	while (!fi.eof())
	{
		fi >> tmp;
		for (int i = tmp.size() - 1; i >= 0; i--)
			if (((tmp[i] >= 'a' && tmp[i] <= 'z') || (tmp[i] >= 'A' && tmp[i] <= 'Z')))
				break;
			else
				tmp.erase(tmp.end()-1);

		for (int i = 0; i < tmp.size(); i++)
			if (((tmp[i] >= 'a' && tmp[i] <= 'z') || (tmp[i] >= 'A' && tmp[i] <= 'Z')))
				break;
			else
			{
				tmp.erase(tmp.begin());
				i--;
			}

		if (tmp.size() == 0)
			continue;
		//for (int i = 0; i < tmp.size(); i++)
			//if (!((tmp[i] >= 'a' && tmp[i] <= 'z') || (tmp[i] >='A' && tmp[i] <='Z')))
				//continue;
		Insert(tmp,1);
	}
	fi.close();
}

void CTrie::EraseWord(string key)
{
	CTrie_Node* cur = root;
	vector<CTrie_Node*> bucket;
	for (int i = 0; i < key.size(); i++)
	{
		cur = cur->FindChild(key[i]);
		bucket.push_back(cur);
	}
	cur->SetLeaf(false);
	for (int i = 0; i < bucket.size(); i++)
	{
		bucket[i]->prior -= cur->prior;
	}
}


void CTrie::LearnWord(string& key,int point)//su dung de tang prior mot tu da co
{
	CTrie_Node* cur = root;
	for (int i = 0; i < key.size(); i++)
	{
		cur = cur->UpdatePriorNode(key[i],point);
	}
}

//tim word tu subtree va push vao collect
vector<string> FindWord(CTrie_Node* subtree,vector<string>& collect){
	for (int i = 0; i < subtree->children.size(); i++)
	{
		if (subtree->children[i]->CheckLeaf())
		{
			collect.push_back(subtree->children[i]->word);
			if (collect.size() == MAX_WORD)//dung de gioi han ket qua tim kiem
				return collect;
		}
		FindWord((*subtree).children[i],collect);
		if (collect.size() == MAX_WORD)//
			return collect;
	}
	return collect;
}

vector<string> CTrie::FindWordFromKey(string key,CTrie_Node* pos)
{
	CTrie_Node* subtree = root;
	vector<string> collect;
	if (pos != NULL)
		subtree = pos;
	if (subtree->CheckLeaf())
		collect.push_back(subtree->word);
	//tim cay con
	CTrie_Node* child;
	for (int i = 0; i < key.size(); i++)
	{
		child = subtree->FindChild(key[i]);
		if (child != NULL)
			subtree = child;
		else
		{
			pos = NULL;//
			return collect;
		}
	}
	pos = subtree; //dung de luu lai vi tri cay con truoc do
	//gom tu
	FindWord(subtree,collect);
	return collect;
}

vector<string> CTrie::FindWordCont(char key, CTrie_Node* &pos)
{
	CTrie_Node* subtree = root;
	vector<string> collect;
	if (pos != NULL)
		subtree = pos;

	//tim cay con
	subtree = subtree->FindChild(key);
	//neu ko co thi thoat
	if (subtree == NULL)
	{
		if (checkDau(key))//
			pos = NULL;
		return collect;
	}
	pos = subtree; //dung de luu lai vi tri cay con truoc do
	//gom tu vao collect
	FindWord(subtree, collect);
	return collect;
}

int countWordEx = 0;
vector<CTrie_Node*> bucket;
void Export(CTrie_Node* subtree,fstream& fo)
{
	
	for (int i = 0; i < subtree->children.size(); i++)
	{
		bucket.push_back(subtree->children[i]);
		Export(subtree->children[i],fo);
		bucket.pop_back();
	}
	if (subtree->CheckLeaf())
	{
		fo << subtree->word << endl << subtree->prior << endl;
		countWordEx++;
		for (int j = 0; j < bucket.size(); j++)
			bucket[j]->prior -= subtree->prior;
	}
}

void CTrie::ExportDic(string fileOut)
{
	fstream fo;
	fo.open(fileOut, ios::out);

	Export(root,fo);
	std::cout << "Co " << countWordEx << " tu" << endl;
	fo.close();
}

int countWordIm = 0;
void CTrie::ImportDic(string fileIn)
{
	fstream fi;
	fi.open(fileIn, ios::in);
	string tmp;
	string tmpPoint;
	getline(fi, tmp);
	while (!tmp.empty())
	{
		countWordIm++;
		getline(fi, tmpPoint);
		this->Insert(tmp,stoi(tmpPoint));
		getline(fi, tmp);
	}
	std::cout << "Co " << countWordIm << " tu" << endl;
	fi.close();
}

void CTrie::InsertDic(string fileIn)
{
	fstream fi;
	fi.open(fileIn, ios::in);
	string tmp;
	getline(fi, tmp);
	while (!tmp.empty())
	{
		this->Insert(tmp);
		getline(fi, tmp);
	}
	fi.close();
}


void CTrie::Insert(string& str, int point){
	CTrie_Node* current = root;
	//truong hop chuoi rong, co the can hoac khong 
	if (str.length() == 0){
		current->SetLeaf();
		return;
	}

	CTrie_Node* child;
	CTrie_Node* temp;
	for (int i = 0; i < str.length(); i++){
		//tim phan giong nhau da co
		child = current->FindChild(str[i]);
		if (child != NULL)
			current = child;
		//truong hop tao moi 1 node de chen vao trie
		else
		{
			temp = new CTrie_Node();
			//if (temp == NULL)
				//countWord--;
			temp->SetKey(str[i]);
			current->AppendChild(temp);
			current = temp;
		}
		current->prior += point;//
		//khi het chuoi thi dat 1 cai bool
		if (i == (str.length() - 1))
		{
			current->SetLeaf();
			current->SetWord(str);
		}
	}

	if (point!=0)
		LearnWord(str, 0);//dung de dieu chinh thu tu prior cua cac children
}

CTrie::CTrie()
{
	root = new CTrie_Node();
	root->SetKey(0);
}

CTrie::~CTrie()
{
}

