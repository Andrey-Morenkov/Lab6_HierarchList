
#pragma once

#pragma warning(disable:4996)

#include <string>
#include <iostream>
#include "TText.h"
#include "TStack.h"
#include <fstream>
#include <conio.h>


const int MaxLen = 81;

using namespace std;

const int MaxArrSize = 100;

class TLink;
class TText
{
public:

	TLink*         pFirst;
	TLink*         pCurr;
	TStack<TLink*> path;

	TText(TLink* _pFirst = NULL);
	~TText(){};

	void GoNextLink();
	void GoDownLink();
	void GoPrevLink();
	void GoFirstLink();

	void InsNextLine(char* _str);
	void InsNextSection(char* _str);
	void InsDownLine(char* _str);
	void InsDownSection(char* _str);

	void DelNextLine();
	void DelDownLine();

	void Reset();
	void GoNext();
	bool IsEnd();

	string GetLine();
	void SetLine(string str);

	TLink* ReadSection(ifstream& ifs);
	void   ReadFile(char* fname);
	void   PrintSection(TLink* p, int level);
	void   PrintText();
	void   SaveText(char* fname);
	void   SaveSection(TLink* p, ofstream& ofs);
};
class TLink;

struct TTextMem
{
	TLink* pFirst;
	TLink* pFree;
	TLink* pLast;
};


class TLink
{
public:

	char   str[MaxLen]; // Строка в списке ( заголовок)
	TLink* pNext      ; // Указатель на тот же уровень
	TLink* pDown      ; // Указатель на подуровень
	int    level      ; // Уровень текста
	

	TLink();
	TLink(const char* _str, TLink* _pNext = NULL, TLink* _pDown = NULL);
	~TLink(){	}
	
	static TTextMem TextMem;                        // поле где выделяем память
	       void*    operator new(size_t size);      
	       void     operator delete (void* p);
	static void     InitMem(int size);
	static void     ClearMem(TText& txt);
	static void     PrintFreeLinks();

};

TLink:: TLink()
{
	pNext = NULL;
	pDown = NULL;
	level = 0;
	str[0] = '\0';
}

TLink:: TLink(const char* _str, TLink* _pNext, TLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;
	level = 0;
	strcpy_s(str, _str);
}

void* TLink:: operator new(size_t size)
{
	TLink* tmp = TextMem.pFree;
	TextMem.pFree = TextMem.pFree->pNext;
	return tmp;
}

void TLink:: operator delete (void* p)
{
	TLink* tmp = (TLink*) p;
	tmp->TextMem.pFree = TextMem.pFree;
	tmp->pNext = TextMem.pFree;
	TextMem.pFree = tmp;
}

void TLink::InitMem(int size)
{
	TextMem.pFirst = (TLink*) new char[sizeof (TLink)*size];
	TextMem.pFree  = TextMem.pFirst;
	TextMem.pLast  = TextMem.pFirst + (size - 1);
	TLink* tmp = TextMem.pFirst;
	tmp->str[0] = '\0';
	for (int i = 0; i < size - 1; i++)
	{
		tmp->str[0] = '\0';
		tmp->pNext = tmp + 1;                                            // начало связки
		tmp++;
	}
	tmp->str[0] = '\0';
	tmp->pNext = NULL;
}

void TLink::ClearMem(TText& txt)
{
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
	{
		string s = "+";
		s += txt.GetLine();
		txt.SetLine(s.c_str());
	}
	string s1 = "+";
	s1 += txt.GetLine();
	txt.SetLine(s1.c_str());

	TLink* pTmp = TextMem.pFree;
	while (pTmp != NULL)
	{
		pTmp->str[0] = '+';
		pTmp->str[1] = '\0';
		pTmp = pTmp->pNext;
	}
	pTmp = TextMem.pFirst;
	while (true)
	{
		if (pTmp->str[0] == '+')
			strcpy(pTmp->str, pTmp->str + 1);
		else
			delete pTmp;
		if (pTmp == TextMem.pLast)
			break;
		pTmp = pTmp + 1;
	}
}


//---------------------------------------------------------

TText::TText(TLink* _pFirst) : path(100)
{
	if (_pFirst == NULL)
	{
		pFirst = new TLink;
		pCurr = pFirst;
	}
	else
	{
		pFirst = _pFirst;
		pCurr = pFirst;
	}
}

void TText::GoNextLink()
{
	if (pCurr != NULL)
	{
		if (pCurr->pNext != NULL)
		{
			path.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}
}

void TText::GoDownLink()
{
	if (pCurr != NULL)
	{
		if (pCurr->pDown != NULL)
		{
			path.Push(pCurr);
			pCurr = pCurr->pDown;
		}
	}
}

void TText::GoPrevLink()
{
	if (!path.IsEmpty())
	{
		pCurr = path.Pop();
	}
}

void TText::GoFirstLink()
{
	pCurr = pFirst;
	path.Clear();
}

void TText::InsNextLine(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pNext = pCurr->pNext;
		pCurr->pNext = tmp;
	}
}

void TText::InsNextSection(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pDown = pCurr->pNext;
		pCurr->pNext = tmp;
	}
}

void TText::InsDownLine(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pNext = pCurr->pDown;
		pCurr->pDown = tmp;
	}
}

void TText::InsDownSection(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pDown = pCurr->pDown;
		pCurr->pDown = tmp;
	}
}

void TText::DelNextLine()
{
	if (pCurr != NULL)
	{
		TLink* tmp = pCurr->pNext;
		pCurr->pNext = pCurr->pNext->pNext;
		delete tmp;
	}
}

void TText::DelDownLine()
{
	if (pCurr != NULL)
	{
		TLink* tmp = pCurr->pDown;
		pCurr->pDown = pCurr->pDown->pNext;
		delete tmp;
	}
}

void TText::Reset()
{
	pCurr = pFirst;
	path.Clear();

	if (pCurr->pNext != NULL)
		path.Push(pCurr->pNext);
	if (pCurr->pDown != NULL)
		path.Push(pCurr->pDown);
}

void TText::GoNext()
{
	if (!path.IsEmpty())
	{
		pCurr = path.Pop();
		if (pCurr->pNext != NULL)
			path.Push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			path.Push(pCurr->pDown);
	}
}

bool TText::IsEnd()
{
	return (path.IsEmpty());
}

TLink* TText::ReadSection(ifstream& ifs)
{
	TLink* pHead = new TLink();
	TLink* pTmp = pHead;
	string str;
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str[0] == '}')
			break;
		else
		{
			if (str[0] == '{')
				pTmp->pDown = ReadSection(ifs);
			else
			{
				//char   str1[100] = str.c_str();
				TLink* q = new TLink(str.c_str());
				pTmp->pNext = q;
				pTmp = q;
			}
		}
	}

	if (pHead->pDown == NULL)
	{
		TLink* tmp = pHead->pNext;
		delete pHead;
		pHead = tmp;
	}
	return pHead;
}

void TText::ReadFile(char* fname)
{
	ifstream ifs;// (fname);
	ifs.open(fname);
	pFirst = ReadSection(ifs);
	pCurr = pFirst;
	ifs.close();
}

string voids(int _level)
{
	int i = _level;
	string str;
	//str[0] = '\0';
	while (i != 0)
	{
		str += "   ";
		i--;
	}
	return str;
}

void TText::PrintSection(TLink* p, int level)
{
	if (p != NULL)
	{
		if (p == pCurr)
			cout << "*" << voids(level) << p->str << endl;
		else
		{
			cout << " " << voids(level) << p->str << endl;
		}
		if (p->pDown != NULL)
		{
			level++;
			p->pDown->level = level;
			PrintSection(p->pDown, level);
			level--;
			//p->level = level;
		}
		PrintSection(p->pNext, level);
	}
}

void TText::PrintText()
{
	PrintSection(pFirst, pFirst->level);
}

void TText::SaveText(char* fname)
{
	ofstream ofs;
	ofs.open(fname);
	SaveSection(pFirst, ofs);
	ofs.close();
}

void TText::SaveSection(TLink* p, ofstream& ofs)
{
	if (p != NULL)
	{
		ofs << p->str << endl;
		if (p->pDown != NULL)
		{
			ofs << "{" << endl;
			SaveSection(p->pDown, ofs);
			ofs << "}" << endl;

		}
		SaveSection(p->pNext, ofs);
	}
}

string TText::GetLine()
{
	return this->pCurr->str;
}

void TText::SetLine(string str)
{
	*this->pCurr->str = *str.c_str();
}

void TLink::PrintFreeLinks()
{
	setlocale(LC_CTYPE, "Russian");
	TLink* tmp = TextMem.pFree;
	if (tmp == NULL)
		cout << "Нет свободных звеньев" << endl;
	else
	{
		int c = 0;
		cout << "Список свободных звеньев:" << endl;
		while (tmp != NULL)
		{
			if (tmp->str[0] != '\0')
				cout << tmp->str << endl;
			tmp = tmp->pNext;
			c++;
		}
		cout << "Всего " << c << " свободных звеньев" << endl;
	}
}