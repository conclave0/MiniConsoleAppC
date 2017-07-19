#include "iostream"
#include "Trie.h"
#include "time.h"
#include "stdio.h"
#include "conio.h"
#include "stack"
#include "windows.h"
using namespace std;
INPUT ip;
bool capslockState = false;
void setINPUT()
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
}
void XuatKey(WORD key)
{
	// Press key
	ip.ki.wVk = key; // virtual-key code for  key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}
void XuatString(string key)
{
	for (int i = 0; i < key.size(); i++)
	{
		XuatKey(key[i]);
	}
}
void XuatChar(char tmp)
{
	keybd_event((unsigned char)VkKeyScan(tmp), 0, 0, 0);
	keybd_event((unsigned char)VkKeyScan(tmp), 0, KEYEVENTF_KEYUP, 0);
}
void xuat(string input)
{
	//for (string::iterator it = input.begin() + 1; it != input.end(); ++it)
	for (int it = 1; it < input.size();it++)
	{
		if ((input[it]) != 13)
			std::cout << input[it];
		else
			std::cout << endl;
	}

}
//#pragma comment(linker, "/HEAP:0x8000000000000000000000")
/*
string keyboard(CTrie& dic)
{
	bool flag = true;//co phai nhap tu moi hay khong?
	vector<string> collect;
	clock_t start, finish;
	string input;
	input.push_back(' ');//
	stack<CTrie_Node*> posStack;
	posStack.push(NULL);//
	string word;
	CTrie_Node* pos = NULL;
	char ctmp = ' ';
	while (true)
	{
		
		ctmp = _getch();
		//fflush(stdin);
		if (ctmp == 27)//ESC de thoat
			break;
		else if (checkDau(ctmp))
		{	
			input.push_back(ctmp);
			if ((word.size() != 0) && flag)
			{
				dic.Insert(word, 1);//hoc tu moi
				//cout << "+" << word << endl;
				//system("pause");
			}
			posStack.push(pos);//
			pos = NULL;
			word.clear();
			flag = true;
		}
		else if (ctmp == '\t')//choose word
		{
			if (collect.size() == 0)
			{
				pos = NULL;
				posStack.push(NULL);
				input.push_back(' ');
				if (flag)
				{
					dic.Insert(word, 1);//hoc tu moi
					//cout << "+" << word << endl;
					//system("pause");
				}
			}
			else
			{

				dic.Insert(collect.front(), 1);//hoc tu co san
				
				for (int i = input.size() - 1; i >= 0; i--)
					if (!checkDau(input[i]))
					{
						input.pop_back();
						posStack.pop();
					}
					else
						break;
				pos = NULL;
				posStack.push(NULL);
				for (int i = 0; i < collect.front().size(); i++)
				{
					dic.FindWordCont(collect.front().at(i), pos);
					posStack.push(pos);
					input.push_back(collect.front().at(i));
				}
				input.push_back(' ');
				ctmp = ' ';
				pos = NULL;
				

			}

			word.clear();
			flag = true;
		}
		else if (ctmp == 8) //backspace
		{
			if (input.size() == 1)
				continue;
			flag = false;
			input.pop_back();
			ctmp = input.back();
			posStack.pop();
			pos = posStack.top();
			word.clear();
		}
		else
		{
			word.push_back(ctmp);
			input.push_back(ctmp);
			posStack.push(pos);
		}
		system("cls");
		cout << "---NOTEPAD---" << endl; 
		xuat(input);
		cout << (char)219 << endl;
		cout << "-------------" << endl;
		start = clock();
		collect = dic.FindWordCont(ctmp, pos);
		//xem lai du doan tu
		finish = clock();
		cout << "Co " << collect.size() << " ket qua, trong vong " << (double)(finish - start) / CLOCKS_PER_SEC << " giay:" << endl;
		for (int i = 0; i < collect.size(); i++)
			cout << collect[i] << endl;
	}
	return input;
}
*/
bool garbageChar(int key)
{
	switch (key)
	{
	case VK_LBUTTON:case VK_CONTROL:case VK_SHIFT:
		return true;
	default:
		return false;
	}
}
string input;
vector<string> keyboard(CTrie& dic, char ctmp)
{
	bool flag = true;//co phai nhap tu moi hay khong?
	vector<string> collect;
	
	//input.push_back();//
	stack<CTrie_Node*> posStack;
	posStack.push(NULL);//
	string word;
	CTrie_Node* pos = NULL;
	word.push_back(ctmp);
	input.push_back(ctmp);
	posStack.push(pos);
	collect = dic.FindWordCont(ctmp, pos);
	return collect;
}

void main()
{

	CTrie dic;
	clock_t start, finish;
	std::cout << "---NOTEPAD---" << endl;
	std::cout << (char)219 << endl;
	std::cout << "-------------" << endl;
	std::cout << "Loading..." << endl;
	
	//ImportDic
	start = clock();
	dic.ImportDic(DIC_NAME);
	finish = clock();
	//EndImportDic
	
	std::cout << "Thoi gian import: " <<double(finish - start) / CLOCKS_PER_SEC << endl;
	//learn new word
	//dic.LearnWordFromSentence(BOOK_NAME);
	
	//keyboardEmulator
	setINPUT();//kich hoat keyboard;
	char temp = ' ';
	while (true)
	{
		for (temp = 8; temp <= 190; temp++){
			if (GetAsyncKeyState(temp) != -32767)//if key have not pressed
				continue;
			else{
				vector<string> result = keyboard(dic, temp);

				system("cls");
				std::cout << "---NOTEPAD---" << endl;
				xuat(input);
				std::cout << (char)219 << endl;
				std::cout << "-------------" << endl;
				start = clock();
				//xem lai du doan tu
				finish = clock();
				std::cout << "Co " << result.size() << " ket qua, trong vong " << (double)(finish - start) / CLOCKS_PER_SEC << " giay:" << endl;
				for (int i = 0; i < result.size(); i++)
					std::cout << result[i] << endl;
			}
		}
	}
	//EndKeyBoardEmulator
	
	//testZone

	//endtestZone
	
	

	

	
	
	//test tim kiem
	/*
	vector<string> collect;
	start = clock();
	collect = dic.FindWordFromKey("ki");
	finish = clock();
	cout << "Co " << collect.size() << " ket qua, trong vong " << (double)(finish - start) / CLOCKS_PER_SEC << " giay:" << endl;
	for (int i = 0; i < collect.size();i++)
		cout << collect[i]<<endl;
	*/
	//dic.Insert("agent");//insert thi prior = 0
	//dic.EraseWord("agent");
	//dic.Insert("agent");
	//dic.LearnWord("adult");//learnword thi prior = 1
	//dic.LearnWord("adult");
	//dic.LearnWord("address");
	
	//gia lap keyboard
	
	/*
	vector<string> collect;
	string input;
	stack<CTrie_Node*> posStack;
	string word;
	CTrie_Node* pos = NULL;
	char ctmp=' ';
	while (true)
	{
		fflush(stdin);
		ctmp = _getch();
		if (ctmp == 27)//ESC de thoat
			break;
		else if (ctmp == ' ' || ctmp == '\n' || ctmp == '.')
		{
			pos = NULL;
			input.push_back(ctmp);
			dic.Insert(word, 1);//hoc tu moi
			word.clear();
		}
		else if (ctmp == '\t')
		{
			if (collect.size() == 0)
			{
				pos = NULL;
				input.push_back(' ');
				dic.Insert(word, 1);//hoc tu moi
			}
			else
			{
				pos = NULL;
				dic.Insert(collect.front(), 1);
				for (int i = input.size() - 1; i >= 0; i--)
					if (input[i] != ' ')//&& input[i] != '.')
					{
						input.erase(input.end() - 1);
						posStack.pop();
					}
					else
						break;
				input.append(collect.front());
				input.append(" ");
			}

			word.clear();
		}
		else if (ctmp == 8) //backspace
		{
			if (input.size() > 1)
			{
				posStack.pop();
				pos = posStack.top();
				input.pop_back();
				ctmp = input.back();
			}
			else
			{
				posStack.pop();
				pos = NULL;
				input.pop_back();
				ctmp = ' ';
			}
		}
		else
		{
			word.push_back(ctmp);
			input.push_back(ctmp);
			posStack.push(pos);
		}
		system("cls");
		cout << "Nhap: " << input << endl;
		start = clock();
		collect = dic.FindWordCont(ctmp, pos);
		finish = clock();
		cout << "Co " << collect.size() << " ket qua, trong vong " << (double)(finish - start) / CLOCKS_PER_SEC << " giay:" << endl;
		for (int i = 0; i < collect.size(); i++)
			cout << collect[i] << endl;
	}
	*/
	/*
	start = clock();
	collect = dic.FindWordCont('d',pos);
	finish = clock();
	cout << "Co " << collect.size() << " ket qua, trong vong " << (double)(finish - start) / CLOCKS_PER_SEC << " giay:" << endl;
	for (int i = 0; i < collect.size(); i++)
		cout << collect[i] << endl;
	
	start = clock();
	collect = dic.FindWordCont('d',pos);
	finish = clock();
	cout << "Co " << collect.size() << " ket qua, trong vong " << (double)(finish - start) / CLOCKS_PER_SEC << " giay:" << endl;
	for (int i = 0; i < collect.size(); i++)
		cout << collect[i] << endl;
	//cout << "Co " << collect.size() << " ket qua:" << endl;
	//for (int i = 0; i < collect.size(); i++)
		//cout << collect[i] << endl;
	*/
}

/*

*/
