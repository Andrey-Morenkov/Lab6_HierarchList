#pragma once

#include <string>

const int MaxLen = 81;


using namespace std;

class TLink
{
public:

	char   str[MaxLen]; // ������ � ������ ( ���������)
	TLink* pNext      ; // ��������� �� ��� �� �������
	TLink* pDown      ; // ��������� �� ����������

	TLink();
	TLink(char* _str, TLink* _pNext = NULL, TLink* _pDown = NULL);
	~TLink();
};







TLink:: TLink()
{
	pNext = NULL;
	pDown = NULL;
	str[0] = '\0';
}

TLink:: TLink(char* _str, TLink* _pNext, TLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;
	strcpy_s(str, _str);
}
