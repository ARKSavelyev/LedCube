// LedCubeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cmath>
class Point
{
public:
	//координаты x height y width z depth, верхний левый передний угол будет 0 0 0
	int8_t x;
	int8_t y;
	int8_t z;
	bool Equals(Point otherPoint);
};
bool Point::Equals(Point otherPoint)//сравнение одной точки с другой
{
	if ((x == otherPoint.x) && (y == otherPoint.y) && (z == otherPoint.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}



class Cube
{
public:
	Point points[4]; //точки - 4 из восьми - передний левый верхний угол, передний верхний правый, задний нижний левый, задний нижний правый
	Cube(Point newPoints[2]); //передаешь верхний передний левый и задний нижний правый
	Cube(Point newPoints[4]); //передаешь все точки
	bool Equals(Cube cube);
	int8_t getSide();
private:
	int8_t side;
};
Cube::Cube(Point newPoints[2]) //передаешь верхний передний левый и задний нижний правый
{
	side = abs(newPoints[1].x - newPoints[0].x);
	points[0] = newPoints[0];
	points[3] = newPoints[1];

	points[1].x = newPoints[0].x;
	points[1].y = newPoints[1].y;
	points[1].z = newPoints[0].z;

	points[2].x = newPoints[1].x;
	points[2].y = newPoints[0].y;
	points[2].z = newPoints[1].z;
}
Cube::Cube(Point newPoints[4]) //передаешь все точки
{
	side = abs(newPoints[3].x - newPoints[1].x);
	for (int i = 0; i < 4; i++)
	{
		points[i] = newPoints[i];
	}
}
bool Cube::Equals(Cube cube) //Сравнение кубов
{
	if (points[0].Equals(cube.points[0]) && side == cube.getSide())
	{
		return true;
	}
	else
	{
		return false;
	}
}
int8_t Cube::getSide()
{
	return side;
}



class LedCube
{
public:
	int8_t leds[4][4][4];
	LedCube();
	void Woop(Cube cubes[2]);
private:
	void init();
	Point litLeds[64];
	int8_t litLedsCount;
	int8_t findCorner(Cube cubes[2]);
	void lightCube(Cube cube);
	void lightLed(int8_t x, int8_t y, int8_t z);
	void addLitLed(int8_t x, int8_t y, int8_t z);
	void clearLitLeds();
};
void LedCube::clearLitLeds() //иду по списку горящих ледов и выключаю их
{
	for (int i = 0; i < litLedsCount; i++)
	{
		leds[litLeds[i].x][litLeds[i].y][litLeds[i].z] = 0;
		litLedsCount = 0;
	}
}
void LedCube::addLitLed(int8_t x, int8_t y, int8_t z)//добавляю точку в список горящих ледов
{
	litLeds[litLedsCount].x = x;
	litLeds[litLedsCount].y = y;
	litLeds[litLedsCount++].z = z;
}
void LedCube::lightLed(int8_t x, int8_t y, int8_t z)
{
	leds[x][y][z] = 1;
	addLitLed(x,y,z);
}
void LedCube::lightCube(Cube cube) //зажигаю куб
{
	int8_t side = cube.getSide();
	if (side = 0)
	{
		lightLed(cube.points[0].x, cube.points[0].y, cube.points[0].z);
	}
	else
	{
		Point FTL = cube.points[0];
		//верхние грани
		for (int i = 0; i <= side;i++)
		{
			lightLed(FTL.x, FTL.y + i, FTL.z);
			lightLed(FTL.x, FTL.y + i, FTL.z + side);
		}
		for (int i = 1;i < side; i++)
		{
			lightLed(FTL.x, FTL.y, FTL.z + i);
			lightLed(FTL.x, FTL.y+side, FTL.z + i);
		}
		//Вертикальные грани

		//нижние грани
	}
}
int8_t LedCube::findCorner(Cube cubes[2])//нахожу общий угл, точку которая будет гореть в любом случае
{
	int8_t corN = 4;
	for (int i = 0;i < 4;i++)
	{
		if (cubes[0].points[i].Equals(cubes[1].points[i]))
		{
			corN = i;
		}
	}
	return corN;
}
void LedCube::init()//
{
	for (int x = 0; x < 4;x++)
	{
		for (int y = 0; y < 4;y++)
		{
			for (int z = 0; z < 4;z++)
			{
				leds[x][y][z] = 0;
			}
		}
	}
	litLedsCount = 0;
}
LedCube::LedCube()
{
	init();
}
void LedCube::Woop(Cube cubes[2])
{
	
}



int main()
{
    
}
