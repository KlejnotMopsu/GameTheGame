#pragma once
#include "plaszczak.h"
#include <Windows.h>

class Planet {
private:
	char *field;
	int width,
		height,
		encounters;
	Plaszczak *player;
	COORD teleport1,
		teleport2;
	bool levelComplete,
		gameOver;

public:
	Planet(int, int);
	~Planet();

	void draw();
	void action();
	void showPlayer() const;
	char checkField(char);
	void useBomb();
	void useRay();
	void setLevelComplete(bool);
	void setGameOver(bool);
	bool getLevelComplete();
	bool getGameOver();
	void deletePlayer();

	void encounter(int = 3);
	void opportunity();
	int checkUp();
	void spawnGateway();
	void calculatePlayerIndex();

	void setCursorPosition(int x, int y);
	void clearConsole();
	void clearConsoleForce();
	void bringMenu();
	void bringStore();
	void bringGameOver();

	Plaszczak* getPlayer();
	void setPlayer(Plaszczak*);
};