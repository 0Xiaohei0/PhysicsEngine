#include "ClothDemo.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <list>
#include "Renderer.h"


void ClothDemo::runDemo() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Cloth Simulation");
	Renderer renderer(window);
	sf::Text FPSCounterText;

	if (!font.loadFromFile("OpenSans-Light.ttf"))
	{
		std::cout << "error loading font" << std::endl;
	}

	FPSCounterText.setFont(font);
	FPSCounterText.setCharacterSize(24);
	FPSCounterText.setFillColor(sf::Color::Red);
	window.setFramerateLimit(frame_rate);
	//solver.setGravity(sf::Vector2f(0.0f, 0.0f));
	solver.setConstraint(0, 0, 1280, 720);

	//setup Objects
	std::vector< std::reference_wrapper<VerletObject>> points;
	int rowCount = (int)(CLOTH_HEIGHT / CLOTH_HOLE_SIZE);
	int colCount = (int)(CLOTH_WIDTH / CLOTH_HOLE_SIZE);
	std::cout << "Generating a " << rowCount << " x " << colCount << " cloth.";
	//std::cout << (CLOTH_HEIGHT / CLOTH_HOLE_SIZE) << std::endl;
	for (int pos_y = CLOTH_START_Y; pos_y <= CLOTH_START_Y + CLOTH_HEIGHT - CLOTH_HOLE_SIZE; pos_y += CLOTH_HOLE_SIZE) {
		for (int pos_x = CLOTH_START_X; pos_x <= CLOTH_START_X + CLOTH_WIDTH - CLOTH_HOLE_SIZE; pos_x += CLOTH_HOLE_SIZE) {
			points.push_back(solver.addObject(sf::Vector2f(pos_x, pos_y), 2.0f, pos_y == CLOTH_START_Y));
		}
	}

	for (int i = 0; i < points.size(); i++) {
		int bottomIdx = i + colCount;
		int rightIdx = i + 1;
		if (rightIdx % colCount == 0)
			rightIdx = -1;

		if (bottomIdx >= 0 && bottomIdx < points.size()) {
			solver.addStick(points.at(i), points.at(bottomIdx));
		}
		if (rightIdx >= 0 && rightIdx < points.size()) {
			solver.addStick(points.at(i), points.at(rightIdx));
		}
	}
	solver.setObjectVelocity(points.back(), sf::Vector2f(300.0f, 0.0f));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		renderer.Render(solver);

		// Draw fps text
		fps.update();
		FPSCounterText.setString(std::to_string(fps.getFPS()));
		window.draw(FPSCounterText);


		window.display();
		solver.update();
	}
}

