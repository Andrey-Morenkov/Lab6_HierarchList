#pragma once

#include "stdafx.h"
#include <string>
#include "TLink.h"
#include "TStack.h"
#include "TText.h"
#include <iostream>
#include <conio.h>


using namespace std;

int menu()
{
	int line  = 0;        // �������� ������
	int idkey = 0;        // ������� �������
	int MenuLength = 3;   // ����� ����

	while (idkey != 13)
	{
		line = (line + MenuLength) % MenuLength;
		
		system("cls");

		if (line == 0)
			cout << "* " << "��������� �����" << endl;
		else
			cout << "  " << "��������� �����" << endl;
		if (line == 1)
			cout << "* " << "�������� � �������" << endl;
		else
		    cout << "  " << "�������� � �������" << endl;
		if (line == 2)
			cout << "* " << "��������� �����" << endl;
		else
			cout << "  " << "��������� �����" << endl;

		idkey = _getch();
		switch (idkey)
		{
		case 72: 
			line--;
			break;
		case 80: 
			line++;
			break;
		}
	}
	return line;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	char file[] = "Text.txt";

	while (true)
	{
		int answer = menu();
		switch (answer)
		{
		case 0:
			system("cls");
			ReadFile(file);
			_getch();
			break;
		case 1:
			system("cls");
			cout << "answer2" << endl;
			_getch();
			break;
		case 2:
			system("cls");
			cout << "answer3" << endl;
			_getch();
			break;
		}
	}
}

