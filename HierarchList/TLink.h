#pragma once

#include <string>

const int MaxLen = 81;

using namespace std;

class TLink;
class TText;

const int MaxArrSize = 100;

struct TTextMem
{
	TLink* pFirst;
	TLink* pFree;
	TLink* pLast;
};


class TLink
{
public:

	char   str[MaxLen]; // ������ � ������ ( ���������)
	TLink* pNext      ; // ��������� �� ��� �� �������
	TLink* pDown      ; // ��������� �� ����������

	TLink();
	TLink(const char* _str, TLink* _pNext = NULL, TLink* _pDown = NULL);
	~TLink(){	}
	
	static TTextMem TextMem;
	void* operator new(size_t size);
	void operator delete (void* p);
	static void InitMem(int size);
	static void ClearMem(TText txt);
	//void PrintFreeLinks();

};

TLink:: TLink()
{
	pNext = NULL;
	pDown = NULL;
	str[0] = '\0';
}

TLink:: TLink(const char* _str, TLink* _pNext, TLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;
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
	tmp->TextMem.pFree = TextMem.pFree;                                       // ???????????
	TextMem.pFree = tmp;
}

void TLink::InitMem(int size)
{
	TextMem.pFirst = (TLink*) new char[sizeof (TLink)* size];
	TextMem.pFree = TextMem.pFirst;
	TextMem.pLast = TextMem.pFirst + (size - 1);
	TLink* tmp = TextMem.pFirst;
	for (int i = 0; i < size - 1; i++)
	{
		tmp->pNext = tmp + 1;                    // ������ ������
		tmp++;
	}
	tmp->pNext = NULL;
}

void TLink::ClearMem(TText txt)
{
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
	{
		string s = "+";
		s += txt.GetLine();
		txt.GetLine(s);
	}
	TLink* pTmp = TextMem.pFree;
	while (pTmp != NULL)
	{
		pTmp->str[0] = '+';
		pTmp->str[1] = '\0';
	}
	pTmp = TextMem.pFirst;
	for (int i = 0; i < MaxArrSize; i++)
	{
		if (pTmp->str[0] == '+')
			pTmp->str[0] = '_';
		else
		{
			delete pTmp;
			pTmp++;
		}
	}
}
