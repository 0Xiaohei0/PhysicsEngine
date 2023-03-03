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

	const int CLOTH_WIDTH = 820;
	const int CLOTH_HEIGHT = 620;
	const int CLOTH_HOLE_SIZE = 10;
	const int CLOTH_START_X = 200;
	const int CLOTH_START_Y = 0;

	const int frame_rate = 144;

	FPS fps;
	sf::Font font;
	Solver solver;

	sf::Vector2i lastMousePosition;
};


