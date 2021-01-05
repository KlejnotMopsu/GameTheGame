// GameTheGame.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <ctime>
#include "planet.h"
#include "plaszczak.h"
#include <Windows.h>


HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);
COLORREF color = RGB(250, 250, 250);




void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//==================================================
int main()
{
	hidecursor();
	Plaszczak *temp = nullptr;
	Planet *p;
	srand(time(NULL));

	int level = 1;

	SetPixel(mydc, 100, 100, color);

	while (1) {
		int w, h;
		w = (rand() % 15) + 5 + level * 2;
		h = (rand() % 15) + 5 + level * 2;

		p = new Planet(w, h);
		if (temp) {
			p->setPlayer(temp);
			p->calculatePlayerIndex();
		}
		p->clearConsoleForce();
		while (1) {
			hidecursor();
			int check = p->checkUp();
			switch (check) {
			case 0:
				break;

			case 1:
				p->clearConsoleForce();
				p->clearConsole();
				p->setCursorPosition(12, 5);
				std::cout << "LEVEL " << level+1 << "\n\n\n\n";
				Sleep(1000);
				break;
				
			case -1:
				p->deletePlayer();
				p->bringGameOver();
				delete p;
				return 0;
				break;

			default:
				exit(1);
				break;
			}
			if (check == 1)
				break;
			p->draw();
			//p.showPlayer();
			p->action();
			//system("cls");
		}
		temp = new Plaszczak( *(p->getPlayer()) );
		delete p;
		level++;
	}

	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
