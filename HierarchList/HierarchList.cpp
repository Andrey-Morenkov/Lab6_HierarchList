#pragma once

#include "stdafx.h"
#include <string>
//#include "TLink.h"
#include "TStack.h"
#include "TText.h"
#include <iostream>
#include <conio.h>


using namespace std;

TTextMem TLink::TextMem;

int mainmenu(TText text, bool flag, int MenuLength)
{
	int line  = 0;        // Активная строка
	int idkey = 0;        // Нажатая клавиша

	while (idkey != 13)
	{
		line = (line + MenuLength) % MenuLength;
		
		system("cls");
			
		if (line == 0)
			cout << "* " << "Загрузить текст" << endl;
	    else
			cout << "  " << "Загрузить текст" << endl;
		if (line == 1)
			cout << "* " << "Сохранить текст" << endl;
		else
			cout << "  " << "Сохранить текст" << endl;
		if (line == 2)
		    cout << "* " << "Выход" << endl;
		else
			cout << "  " << "Выход" << endl;
		if (flag)
		{
			if (line == 3)
				cout << "* " << "Операции с текстом" << endl;
			else
				cout << "  " << "Операции с текстом" << endl;
			cout << endl;
			cout << endl;

			text.PrintText();
		}

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
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	TLink::InitMem(100);

	TText Text;
	bool flag = false;
	int MenuLength = 3;
	char filename[] = "Text.txt";
	char savefile[] = "SavedText.txt";

	while (true)
	{
		int answer = mainmenu(Text, flag, MenuLength);
		switch (answer)
		{
		case 0:
			Text.ReadFile(filename);
			flag = true;
			MenuLength = 4;
			//Text.PrintText();
			//system("cls");
			//textmenu(Text);
			break;
		case 1:
			Text.SaveText(savefile);
			system("cls");
			cout << "OK" << endl;
			_getch();
			break;
		case 2:
			exit(0);
		case 3:
			break;
			//textmenu;
		}
	}
}