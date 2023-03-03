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
	points.push_back(solver.addObject(sf::Vector2f(500.0f, 400.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(550.0f, 400.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(550.0f, 450.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(500.0f, 450.0f), 2.0f));

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

