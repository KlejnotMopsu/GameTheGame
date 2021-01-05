#include "pch.h"
#include "planet.h"
#include <iostream>
#include "plaszczak.h"
#include <conio.h>
#include "values.h"
#include <ctime>
#include <cstdlib>
#include <Windows.h>

Planet::Planet(int w, int h) {
	srand(time(NULL));
	width = w;
	height = h;
	encounters = 0;
	levelComplete = false;
	gameOver = false;

	//std::cout << "width = " << width << "  height = " << height << std::endl;
	//std::cout << "w * h = " << width * height << std::endl;

	bool shopRoll = false;
	if (rand() % 100 > 40) {
		shopRoll = true;
	}

	field = new char[width*height];
	for (int i = 0; i < height; i++) {
		for (int ii = 0; ii < width; ii++) {
			if ( (i == 0 || i == height -1)  || (ii == 0 || ii == width -1) ) {
				field[i*width + ii] = WALL;
			}
			else {
				field[i*width + ii] = EMPTY;
				int roll = rand() % 100;
				//std::cout << "ROLL:  " << roll << std::endl;
				if (roll > 95) {
					field[i*width + ii] = OPPORTUNITY;
				}
				if (roll > 96) {
					field[i*width + ii] = DANGER;
				}
			}

			/*std::cout << "i = " << i;
			std::cout << "  ii = " << ii;
			std::cout << "  i*width + ii = " << i*width + ii;
			std::cout << std::endl;*/
		}
	}

	//teleport
	int roll_1 = rand() % ( (width-2)/2) + 1;
	int roll_2 = rand() % (height-2) + 1;
	teleport1.X = roll_1; teleport1.Y = roll_2;

	roll_1 = rand() % ( (width-2)/2) + width/2;
	roll_2 = rand() % (height - 2) + 1;
	teleport2.X = roll_1; teleport2.Y = roll_2;

	field[teleport1.Y*width + teleport1.X] = TELEPORT;
	field[teleport2.Y*width + teleport2.X] = TELEPORT;

	//shop
	roll_1 = rand() % (width - 3) + 1;
	roll_2 = rand() % (height - 3) + 1;
	field[roll_2*width + roll_1] = SHOP;

	//starting point
	int startX, startY;
	startX = startY = 1;
	int index;
	index = startY * width + startX;
	player = new Plaszczak(index);

	for (int i = 0; i <= height * width; i++) {
		if (field[i] == DANGER)
			encounters++;
	}
}
Planet::~Planet() {
	delete[] field;
}

void Planet::draw() {
	setCursorPosition(0, 0);
	for (int i = 0; i < height; i++) {
		for (int ii = 0; ii < width; ii++) {
			
			if ((i*width + ii) == player->getIndex()) {
				std::cout << player->getLook();
			}
			else {
				std::cout << field[i*width + ii];
			}
		}
		std::cout << std::endl;
	}
	player->showHUD();
	setCursorPosition(26, height);
	std::cout << "X: " << encounters;
}

void Planet::action() {
	char k, l;
	l = _getch();

	if (l && l != -32){
		switch (l) {
		case 'b':
			bringStore();
			break;

		case 32:
			useBomb();
			break;

		case 'v':
			useRay();
			break;

		case 'p':
			player->addMoney(1000);
			break;

		default:
			break;
		}
		if (l == 27)
			exit(0);
	}
	else {
		int destination = ERROR;
		k = _getch();
		switch (k) {
		case KEY_UP:
			destination = checkField('u');
			if (destination != WALL) {
				COORD tile;
				tile.X = player->getX();
				tile.Y = player->getY();
				player->goUpIndex(width);

				COORD playa;
				playa.X = player->getX();
				playa.Y = player->getY();

				setCursorPosition(tile.X, tile.Y);
				std::cout << field[tile.Y * width + tile.X];
				setCursorPosition(playa.X, playa.Y);
				std::cout << player->getLook();
			}
			else if (player->getUpgrade()) {
				int x, y;
				x = player->getX();
				y = player->getY();
				player->setY(height - 2);
				player->setIndex((height-2)*width + x);
			}
			break;

		case KEY_DOWN:
			destination = checkField('d');
			if (destination != WALL) {
				COORD tile;
				tile.X = player->getX();
				tile.Y = player->getY();
				player->goDownIndex(width);

				COORD playa;
				playa.X = player->getX();
				playa.Y = player->getY();

				setCursorPosition(tile.X, tile.Y);
				std::cout << field[tile.Y * width + tile.X];
				setCursorPosition(playa.X, playa.Y);
				std::cout << player->getLook();
			}
			else if (player->getUpgrade()) {
				int x, y;
				x = player->getX();
				y = player->getY();
				player->setY(1);
				player->setIndex((1)*width + x);
			}
			break;

		case KEY_LEFT:
			destination = checkField('l');
			if (destination != WALL) {
				COORD tile;
				tile.X = player->getX();
				tile.Y = player->getY();
				player->goLeftIndex(1);

				COORD playa;
				playa.X = player->getX();
				playa.Y = player->getY();

				setCursorPosition(tile.X, tile.Y);
				std::cout << field[tile.Y * width + tile.X];
				setCursorPosition(playa.X, playa.Y);
				std::cout << player->getLook();
			}
			else if (player->getUpgrade()) {
				int x, y;
				x = player->getX();
				y = player->getY();
				player->setX(width - 2);
				player->setIndex(y*width + width-2);
			}
			break;

		case KEY_RIGHT:
			destination = checkField('r');
			if (destination != WALL) {
				COORD tile;
				tile.X = player->getX();
				tile.Y = player->getY();
				player->goRightIndex(1);

				COORD playa;
				playa.X = player->getX();
				playa.Y = player->getY();

				setCursorPosition(tile.X, tile.Y);
				std::cout << field[tile.Y * width + tile.X];
				setCursorPosition(playa.X, playa.Y);
				std::cout << player->getLook();
			}
			else if (player->getUpgrade()) {
				int x, y;
				x = player->getX();
				y = player->getY();
				player->setX(1);
				player->setIndex(y*width + 1);
			}
			break;

		case 't':
			setCursorPosition(0, 0);
			std::cout << 't';
			break;
		case 'y':
			setCursorPosition(0, 0);
			std::cout << 'y';
			break;
		default:
			break;
		}
		
		switch (destination) {
		case TELEPORT:
			if (player->getIndex() == (teleport1.Y*width + teleport1.X)) {
				player->setX(teleport2.X);
				player->setY(teleport2.Y);
				player->setIndex(teleport2.Y*width + teleport2.X);
			}
			else if (player->getIndex() == (teleport2.Y*width + teleport2.X)) {
				player->setX(teleport1.X);
				player->setY(teleport1.Y);
				player->setIndex(teleport1.Y*width + teleport1.X);
			}
			break;

		case DANGER:
			encounter();
			field[player->getIndex()] = EMPTY;
			encounters--;
			if (encounters <= 0) {
				spawnGateway();
			}
			break;

		case OPPORTUNITY:
			field[player->getIndex()] = EMPTY;
			opportunity();
			break;

		case SHOP:
			bringStore();
			break;

		case GATEWAY:
			levelComplete = true;
			break;

		default:
			break;
		}

	}

	

}

void Planet::showPlayer() const {
	std::cout << *player;
}

char Planet::checkField(char k) {
	int out = ERROR;

	switch (k) {
	case 'u':
		out = field[(player->getY() - 1) * width + player->getX()];
		break;

	case 'd':
		out = field[(player->getY() + 1) * width + player->getX()];
		break;

	case 'l':
		out = field[player->getY() * width + player->getX() - 1];
		break;

	case 'r':
		out = field[player->getY() * width + player->getX() + 1];
		break;

	default:
		return ERROR;
		break;
	}

	return out;
}

void Planet::useBomb() {
	if (player->getBombs() <= 0) {
		return;
	}
	else {
		COORD temp = { player->getX(), player->getY() };
		field[temp.Y*width + temp.X] = DEBRIS;
		if (field[(temp.Y + 1)*width + temp.X] != WALL) {
			if (field[(temp.Y + 1)*width + temp.X] == DANGER)
				encounters--;
			field[(temp.Y + 1)*width + temp.X] = DEBRIS;
		}
		if (field[(temp.Y - 1)*width + temp.X] != WALL) {
			if (field[(temp.Y - 1)*width + temp.X] == DANGER)
				encounters--;
			field[(temp.Y - 1)*width + temp.X] = DEBRIS;
		}
		if (field[temp.Y*width + temp.X + 1] != WALL) {
			if (field[temp.Y*width + temp.X + 1] == DANGER)
				encounters--;
			field[temp.Y*width + temp.X + 1] = DEBRIS;
		}
		if (field[temp.Y*width + temp.X - 1] != WALL) {
			if (field[temp.Y*width + temp.X - 1] == DANGER)
				encounters--;
			field[temp.Y*width + temp.X - 1] = DEBRIS;
		}
		player->addBomb(-1);
		Beep(500, 200);
	}
}

void Planet::useRay() {
	if (player->getRays() <= 0) {
		return;
	}
	else {
		char check, dir;
		check = _getch();

		if (check && check != -32) {

		}
		else {
			dir = _getch();
			int x, y;
			x = player->getX();
			y = player->getY();

			char desField = ERROR;
			switch (dir) {

			case KEY_UP:
				do {
					if (field[(y-1)*width + x] == DANGER)
						encounters--;
					field[(--y)*width + x] = RAY_DEBRIS;
					desField = field[(y - 1)*width + x];
				} while (desField != WALL);
				break;

			case KEY_DOWN:
				do {
					if (field[(y+1)*width + x] == DANGER)
						encounters--;
					field[(++y)*width + x] = RAY_DEBRIS;
					desField = field[(y + 1)*width + x];
				} while (desField != WALL);
				break;

			case KEY_LEFT:
				do {
					if (field[y*width + (x - 1)] == DANGER)
						encounters--;
					field[y*width + (--x)] = RAY_DEBRIS;
					desField = field[y*width + x-1];
				} while (desField != WALL);
				break;

			case KEY_RIGHT:
				do {
					if (field[y*width + (x + 1)] == DANGER)
						encounters--;
					field[y*width + (++x)] = RAY_DEBRIS;
					desField = field[y*width + x + 1];
				} while (desField != WALL);


			default:
				break;
			}
		}

	}
		player->addRays(-1);
		Beep(1000, 100);
}

void Planet::setLevelComplete(bool xx) {
	levelComplete = xx;
}

void Planet::setGameOver(bool xx) {
	gameOver = xx;
}

void Planet::deletePlayer() {
	delete player;
}


bool Planet::getGameOver() {
	return gameOver;
}

bool Planet::getLevelComplete() {
	return levelComplete;
}

void Planet::encounter(int xx) {
	const char tb[] = { 'Q', 'W', 'E', 'R',
					'A', 'S', 'D', 'F' };
	const short ind = 8;
	int profit = 0;
	srand(time(NULL));
	bool win;
	char qte,
		prev = 'P';
	int maxRounds = xx;
	if (player->getUpgrade())
		maxRounds--;
	setCursorPosition(0, height + 1);
	std::cout << "                         ";

	for (short round = 0; round < maxRounds; round++) {
		win = false;
		do {
			qte = tb[rand() % ind];
		} while (qte == prev);
		prev = qte;
		setCursorPosition(10, height+1);
		std::cout << "PRESS "<<  qte << "!\n";
		setCursorPosition(0, round+2 + height);
		std::cout << '|';
		setCursorPosition(22, round+2 + height);
		std::cout << '|';
		setCursorPosition(1, round+2 + height);
	
		for (int i = 0; i <= 500000; i++) {
			if (i % 25000 == 0) std::cout << '-';
			if (GetKeyState(qte) & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
				win = true;
				profit += rand() % 30;
				break;
			}
		}
		if (win == false)
			break;

		Sleep(100);
	}	
	if (win == false) {
		setCursorPosition(1, height + 1);
		std::cout << "FAILURE";
		player->addLife(-1);
	}
	else {
		profit += 100;
		setCursorPosition(1, height + 1);
		std::cout << "SUCCES";
		//Beep(700, 200);
		Beep(900, 300);
	}
	
	player->addMoney(profit);

	//Sleep(500);
	clearConsoleForce();
}

void Planet::opportunity() {
	srand(time(NULL));
	short roll = rand() % 8;

	setCursorPosition(0, height + 1);
	std::cout << "                           ";
	setCursorPosition(0, height + 1);
	if (roll == 7) {
		player->addMoney(rand() % 600 + 1100);
		std::cout << "You found treasure!";
	}
	else if (roll == 6) {
		player->addBomb(1);
		std::cout << "You found bomb.";
	}
	else if (roll == 5) {
		player->addLife(1);
		std::cout << "You found 1Up";
	}
	else if (roll == 4) {
		player->addMoney(rand() % 100 + 50);
		std::cout << "You found some money.";
	}
	else {
		std::cout << "Nothing interesting...";
	}
}

int Planet::checkUp() {
	if (encounters <= 0)
		spawnGateway();

	if (gameOver == true  ||  player->getLives() <= 0)
		return -1;
	if (levelComplete)
		return 1;

	return 0;
}

void Planet::spawnGateway() {
	field[(height / 2) * width + (width / 2)] = GATEWAY;
}

void Planet::calculatePlayerIndex() {
	player->setIndex( player->getX() * width + player->getY() );
}

void Planet::setCursorPosition(int x, int y){
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Planet::clearConsole() {
	
	for (int i = 0; i < height+15; i++) {
		setCursorPosition(0, i);
		for (int ii = 0; ii < width + 15; ii++) {
			std::cout << ' ';
		}
	}
}

void Planet::clearConsoleForce() {

	for (int i = 0; i < 100; i++) {
		setCursorPosition(0, i);
		for (int ii = 0; ii < 100; ii++) {
			std::cout << ' ';
		}
	}
}

void Planet::bringMenu() {
	clearConsole();
}

void Planet::bringStore() {
	clearConsoleForce();
	setCursorPosition(11, 4);
	std::cout << "STORE";
	setCursorPosition(5, 5);
	std::cout << " <3  " << "  <U>    " << " B  " << "           R        ";
	setCursorPosition(5, 6);
	std::cout << "1Up  " << "Upgrade  " << "Bomb" << "  Disintegration Ray";
	setCursorPosition(5, 7);
	std::cout << "200$ " << " 1500$   " << "250$" << "         750$       ";
	setCursorPosition(5, 8);
	std::cout << "  1  " << "   2     " << " 3  " << "           4        ";
	
	char choice;
	do {
		setCursorPosition(5, 2);
		std::cout << "                            ";
		setCursorPosition(5, 2);
		player->showHUD();

		choice = _getch();
		setCursorPosition(5, 10);
		std::cout << "                            ";
		setCursorPosition(5, 10);

		switch (choice) {
		case 27:
			break;

		case '1':
			if (player->getMoney() < 200) {
				std::cout << "Insufficient funds.";
			}
			else {
				player->addMoney(-200);
				player->addLife(1);
				std::cout << "You bought 1Up.";
			}
			break;

		case '2':
			if (player->getMoney() < 1500) {
				std::cout << "Insufficient funds.";
			}
			else {
				player->addMoney(-1500);
				player->setLook(UPGRADED);
				player->setUpgrade(true);
				std::cout << "You bought upgrade.";
			}
			break;

		case '3':
			if (player->getMoney() < 250) {
				std::cout << "Insufficient funds.";
			}
			else {
				player->addMoney(-250);
				player->addBomb(1);
				std::cout << "You bought bomb.";
			}
			break;

		case '4':
			if (player->getMoney() < 750) {
				std::cout << "Insufficient funds.";
			}
			else {
				player->addMoney(-750);
				player->addRays(1);
				std::cout << "You bought disintegration ray.";
			}
			break; 

		default:
			break;
		}
	} while (choice != 27);

	clearConsoleForce();
	draw();
}

void Planet::bringGameOver() {
	if (player->getLives() <= 0) {
		clearConsole();
		setCursorPosition(12, 5);
		std::cout << "GAME OVER\n\n\n\n";
	}
}

Plaszczak* Planet::getPlayer() {
	return player;
}

void Planet::setPlayer(Plaszczak *xx) {
	player = xx;
}