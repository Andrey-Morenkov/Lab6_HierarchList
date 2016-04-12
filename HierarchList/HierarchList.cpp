#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <string>
#include "TLink.h"
#include "TStack.h"
//#include "TText.h"
#include <iostream>
#include <conio.h>


using namespace std;

TTextMem TLink::TextMem;


//--------------------------------------------------------------------------------------------------------
int mainmenu(TText text, int MenuLength)
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
		    cout << "* " << "Выход" << endl;
		else
			cout << "  " << "Выход" << endl;

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
//--------------------------------------------------------------------------------------------------------
int MenuWithText(TText text, int MenuLength)
{
	int line = 0;        // Активная строка
	int idkey = 0;       // Нажатая клавиша

	while (idkey != 13)
	{
		system("cls");
		line = (line + MenuLength) % MenuLength;
		if (line == 0)
			cout << "* " << "Операции с текстом" << endl;
		else
			cout << "  " << "Операции с текстом" << endl;
		if (line == 1)
			cout << "* " << "Cохранить текст" << endl;
		else
			cout << "  " << "Cохранить текст" << endl;
		if (line == 2)
			cout << "* " << "Выход" << endl;
		else
			cout << "  " << "Выход" << endl;
		cout << endl;
		cout << endl;

		text.PrintText();


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

//--------------------------------------------------------------------------------------------------------
int MenuWithText(TText& text)
{
	int idkey = 0;       // Нажатая клавиша
	int flag  = 1;       // 1 - enter 0 - exit

	while ((idkey != 13) && (idkey != 231))
	{
		system("cls");

		cout << "^          |                           |                     " << endl;
		cout << "| - Prev   | - Next   --> - Down    <--| - Action   x - exit " << endl;
		cout << "|          V                                                 " << endl;

		cout << endl;
		cout << endl;

		text.PrintText();

		idkey = _getch();
		switch (idkey)
		{
		case 72:                  // prev
			text.GoPrevLink();
			break;
		case 80:                  // next
			text.GoNextLink();
			break;
		case 77:                  // down
			text.GoDownLink();
			break;
		}
	}
	if (idkey == 231)
	{
		flag = 0;
	}
	return flag;
}
//--------------------------------------------------------------------------------------------------------
void MenuAction(TText& text)
{
	int idkey = 0;       // Нажатая клавиша
	char str_[20];
	system("cls");

	cout << "Ins                                       Del                                      " << endl;
	cout << "     Next: -Line <Ф>  Down: -Line <Я>          Next: -Line <Ж>  Down: -Line <Ю>    " << endl;
	cout << "           -Sect <Ы>        -Sect <Ч>                                              " << endl;
	
	cout << endl;
	cout << endl;
	
	idkey = _getch();
	switch (idkey)
	{
	case 228:                  // InsNextLine
		cout << "Введи строку" << endl;
		cin >> str_;
		text.InsNextLine(str_);
		break;
	case 235:                  // InsNextSect
		cout << "Введи строку" << endl;
		cin >> str_;
		text.InsNextSection(str_);
		break;
	case 239:                  // InsDownLine
		cout << "Введи строку" << endl;
		cin >> str_;
		text.InsDownLine(str_);
		break;
	case 231:                  // InsDownSect
		cout << "Введи строку" << endl;
		cin >> str_;
		text.InsDownSection(str_);
		break;
	case 166:                  // DelNextLine
		text.DelNextLine();
		TLink::PrintFreeLinks();
		getch();
		break;
	case 238:                  //  DelDownLine
		text.DelDownLine();
		TLink::PrintFreeLinks();
		getch();
		break;
	}
}

//--------------------------------------------------------------------------------------------------------
//----------------------------------------------Программа-------------------------------------------------
//--------------------------------------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	TLink::InitMem(100);

	TText Text;
	int MenuLength = 2;
	char filename[] = "Text.txt";
	char savefile[] = "SavedText.txt";


	int answer_main = mainmenu(Text, MenuLength);
	switch (answer_main)
	{
	case 0:
	{
			  Text.ReadFile(filename);
			  while (true)
			  {
				  MenuLength = 3;
				  int answer_text_menu = MenuWithText(Text, MenuLength);
				  switch (answer_text_menu)
				  {
				  case 0:
				  {
							system("cls");
														
							while (MenuWithText(Text))
								MenuAction(Text);
							break;
				  }
				  case 1:
				  {
							Text.SaveText(savefile);
							system("cls");
							cout << "OK" << endl;
							cout << "Нажмите клавижу" << endl;
							_getch();
							break;
				  }
				  case 2:
				  {
							system("cls");
							TLink::ClearMem(Text);
							TLink::PrintFreeLinks();
							cout << endl;
							int i = _getch();
							exit(0);

				  }
				  }
				  Text.PrintText();
			  }
			  break;
	}
	case 1:
	{
			  exit(0);
			  break;
	}
	}
}