#include "pch.h"
#include "plaszczak.h"

Plaszczak::Plaszczak(int ind, char l) {
	x = 1;
	y = 1;
	look = l;
	lives = 3;
	index = ind;
	bombs = 0;
	upgrade = false;
	money = 0;
	rays = 0;
}
Plaszczak::Plaszczak(int px, int py, char l) {
	x = px;
	y = py;
	look = l;
	lives = 3;
	index = -1;
	bombs = 0;
	upgrade = false;
	money = 0;
	rays = 0;
}
Plaszczak::Plaszczak(const Plaszczak &p2) {
	x = 1;
	y = 1;
	lives = p2.lives;
	bombs = p2.bombs;
	money = p2.money;
	rays = p2.rays;
	look = p2.look;
	upgrade = p2.upgrade;
}


void Plaszczak::showHUD() const{
	std::cout << "Lives: " << lives << "  $" << money << "  B: " << bombs << "  R: " << rays;
}

void Plaszczak::goUp() {
	y--;
}
void Plaszczak::goDown() {
	y++;
}
void Plaszczak::goLeft() {
	x--;
}
void Plaszczak::goRight() {
	x++;
}
int Plaszczak::getX() const {
	return x;
}
int Plaszczak::getY() const {
	return y;
}
char Plaszczak::getLook() const{
	return look;
}
int Plaszczak::getIndex() const {
	return index;
}
bool Plaszczak::getUpgrade() const {
	return upgrade;
}
int Plaszczak::getMoney() const {
	return money;
}
int Plaszczak::getLives() const {
	return lives;
}
int Plaszczak::getBombs() const {
	return bombs;
}
int Plaszczak::getRays() const {
	return rays;
}


void Plaszczak::goUpIndex(int xx) {
	y--;
	index -= xx;
}
void Plaszczak::goDownIndex(int xx) {
	y++;
	index += xx;
}
void Plaszczak::goLeftIndex(int xx) {
	x--;
	index -= xx;
}
void Plaszczak::goRightIndex(int xx) {
	x++;
	index += xx;
}

void Plaszczak::setIndex(int xx) {
	index = xx;
}
void Plaszczak::setX(int xx) {
	x = xx;
}
void Plaszczak::setY(int xx) {
	y = xx;
}
void Plaszczak::setLook(char xx) {
	look = xx;
}
void Plaszczak::setUpgrade(bool xx) {
	upgrade = xx;
}
void Plaszczak::addLife(int xx) {
	lives += xx;
}
void Plaszczak::addMoney(int xx) {
	money += xx;
}
void Plaszczak::addBomb(int xx) {
	bombs += xx;
}
void Plaszczak::addRays(int xx) {
	rays += xx;
}