#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <math.h>

using namespace std;

void setCursor(int x, int y)
{
    HANDLE hCon;
    COORD cPos = { x, y };
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, cPos);
}

class Road
{
public:
    Road(float length0, int width0)
    {
        this->length = length0;
        this->width = width0;
    }

    Road()
    {
    }

    float getLength()
    {
        return length;
    }

private:
    float length;
    int width;
};

class Car
{
public:
    Car(float v0, int line, Road rd)
    {
        this->speed = v0;
        this->carLine = line;
        this->road = rd;
    }

    void move()
    {
        if (this->x + this->speed > this->road.getLength())
        {
            setCursor(this->x + 1, getY());
            cout « "\b" « " ";
            this->x = 0;
        }
        else
        {
            this->x += this->speed;
        }
    }

    float getSpeed()
    {
        return speed;
    }

    float getX()
    {
        return x;
    }

    float getY()
    {
        return y;
    }

    void setY(float nextY)
    {
        y = nextY;
    }

    void setX(float nextX)
    {
        x = nextX;
    }

private:
    float x = 0, y = 0, speed;
    int carLine;
    Road road;
};

int main()
{
    setlocale(LC_ALL, "Russian");

    int width;
    float length;

    vector<Car> cars;

    cout « "Введите длину и ширину дороги: ";
    cin » length » width;
    cout « endl;
    Road road = Road(length, width);

    cout « "Поочерёдно вводите скорость каждой машины: " « endl;
    float currentCarSpeed;

    for (int i = 0; i < width; i++)
    {
        cin » currentCarSpeed;
        Car car = Car(currentCarSpeed, i, road);
        car.setY(float(i * 2 + 4 + width));
        cars.push_back(car);
    }

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width + 1; j++)
        {
            setCursor(i, j * 2 + 3 + width);
            cout « "_";
        }
    }

    while (!_kbhit())
    {
        for (int i = 0; i < width; i++)
        {
            cars[i].move();
            setCursor(cars[i].getX(), i * 2 + 4 + width);
            cout « "*" « '\b';
        }
        for (int i = 0; i < width; i++)
        {
            setCursor(cars[i].getX() - cars[i].getSpeed(), i * 2 + 4 + width);
            cout « " ";
        }
        Sleep(25);
    }

    return 0;
}
