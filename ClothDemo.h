#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "VerletObject.h"
#include "Solver.h"
#include "FPS.h"

class ClothDemo
{
public:
	void runDemo();
private:
	const int WINDOW_SIZE_X = 1280;
	const int WINDOW_SIZE_Y = 720;

	const float CLOTH_WIDTH = 620;
	const float CLOTH_HEIGHT = 620;
	const float CLOTH_HOLE_SIZE = 100;
	const float CLOTH_START_X = 200;
	const float CLOTH_START_Y = 0;

	const int frame_rate = 144;

	FPS fps;
	sf::Font font;
	Solver solver;
};


