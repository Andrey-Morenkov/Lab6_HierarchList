#pragma once

#include "stdafx.h"
#include <string>
#include "TLink.h"
#include "TStack.h"
#include "TText.h"
#include <iostream>
#include <conio.h>


using namespace std;

int mainmenu()
{
	int MenuLength = 2;         // ����� ����
	int line  = 0;        // �������� ������
	int idkey = 0;        // ������� �������

	while (idkey != 13)
	{
		line = (line + MenuLength) % MenuLength;
		
		system("cls");
			
		if (line == 0)
			cout << "* " << "��������� �����" << endl;
	    else
			cout << "  " << "��������� �����" << endl;
		if (line == 1)
			cout << "* " << "�����" << endl;
		else
		    cout << "  " << "�����" << endl;
		//if (line == 2)
			//cout << "* " << "��������� �����" << endl;
		//else
			//cout << "  " << "��������� �����" << endl;

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

int textmenu()
{
	system("cls");
	// PrintTextKeys();
	//Text.PrintTextNavigation();                         // ����� � ���� ����
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	//TText Text;
	char filename[] = "Text.txt";
	char savefile[] = "SavedText.txt";

	while (true)
	{
		int answer = mainmenu();
		switch (answer)
		{
		case 0:
			//Text.ReadFile(filename);
			//Text.PrintText();
			_getch();
			break;
		case 1:
			exit(0);
		}
		while (true)
		{
			int answer = mainmenu();
			switch (answer)
			{
			case 0:
				system("cls");
				//Text.ReadFile(filename);
				//Text.PrintText();
				_getch();
				break;
			case 1:
				system("cls");
				cout << "answer2" << endl;
				_getch();
				break;
			case 2:
				system("cls");
				//Text.SaveText(savefile);
				cout << "answer3" << endl;
				_getch();
				break;
			}
		}
	}
}