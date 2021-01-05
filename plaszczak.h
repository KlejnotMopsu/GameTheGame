#pragma once
#include <iostream>
#include "values.h"


class Plaszczak {
private:
	int x, y, index,
		lives,
		bombs,
		money,
		rays;
	char look;
	bool upgrade;

public:
	Plaszczak(int, char = REGULAR);
	Plaszczak(int, int, char = REGULAR);
	Plaszczak(const Plaszczak &p2);

	friend std::ostream &operator<<(std::ostream& os, const Plaszczak& p) {
		os << p.look << " - (" << p.x << ',' << p.y << ')' << "I: " << p.index;
		return os;
	}

	void showHUD() const;

	void goUp();
	void goDown();
	void goLeft();
	void goRight();
	void goUpIndex(int xx);
	void goDownIndex(int xx);
	void goLeftIndex(int xx);
	void goRightIndex(int xx);

	int getX() const;
	int getY() const;
	char getLook() const;
	int getIndex() const;
	bool getUpgrade() const;
	int getMoney() const;
	int getLives() const;
	int getBombs() const;
	int getRays() const;

	void setIndex(int);
	void setX(int);
	void setY(int);
	void setLook(char);
	void setUpgrade(bool);
	void addLife(int);
	void addMoney(int);
	void addBomb(int);
	void addRays(int);
};