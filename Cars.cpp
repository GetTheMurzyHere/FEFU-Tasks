#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <math.h>
#include <string>

using namespace std;

void setCursor(int x, int y)
{
	HANDLE hCon;
	COORD cPos = { x, y };
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, cPos);
}

class Road {
public:
	Road(float length0, int width0) {
		this->length = length0;
		this->width = width0;
	}

	Road() {

	}

	float getLength() {
		return length;
	}

private:
	float length;
	int width;
};

class Car {
public:
	Car(float v0, int line, Road rd) {
		this->speed = v0;
		this->carLine = line;
		this->road = rd;
	}

	void move() {
		if (this->x+this->speed > this->road.getLength()) {
			setCursor(this->x+1, getY());
			cout << "\b" << " ";
			this->x = 0;
		}
		else {
			this->x += this->speed;
		}
	}

	float getSpeed() {
		return speed;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	void setY(float nextY) {
		y = nextY;
	}

	void setX(float nextX) {
		x = nextX;
	}

private:
	float x = 0, y = 0, speed;
	int carLine;
	Road road;

};

int main() {

	setCursor(0, 0);
	int i = 0;
	setlocale(LC_ALL, "Russian");
	while (true) {
		setCursor(i, 0);
		cout << " Keep it strange";
		i++;
		Sleep(30);
	}
	return 0;
}