#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "VerletObject.h"
#include "Solver.h"
#include "FPS.h"

class BoxesDemo
{
public:
	void runDemo();
private:
	const int WINDOW_SIZE_X = 1280;
	const int WINDOW_SIZE_Y = 720;

	const int frame_rate = 144;

	FPS fps;
	sf::Font font;

	Solver solver;
};


