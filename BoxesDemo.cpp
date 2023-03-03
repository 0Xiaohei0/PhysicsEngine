#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <list>
#include "BoxesDemo.h"
#include "Renderer.h"


void BoxesDemo::runDemo() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "anime physics");
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


	points.push_back(solver.addObject(sf::Vector2f(500.0f, 350.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(500.0f, 300.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(500.0f, 250.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(500.0f, 200.0f), 2.0f, true));
	solver.setObjectVelocity(points.at(4), sf::Vector2f(300.0f, 0.3f));

	points.push_back(solver.addObject(sf::Vector2f(800.0f, 350.0f), 10.0f));
	points.push_back(solver.addObject(sf::Vector2f(800.0f, 300.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(800.0f, 250.0f), 2.0f));
	points.push_back(solver.addObject(sf::Vector2f(800.0f, 200.0f), 2.0f, true));
	solver.setObjectVelocity(points.at(8), sf::Vector2f(300.0f, 0.3f));



	solver.addStick(points.at(0), points.at(1));
	solver.addStick(points.at(1), points.at(2));
	solver.addStick(points.at(2), points.at(3));
	solver.addStick(points.at(3), points.at(0));
	solver.addStick(points.at(0), points.at(2));
	solver.addStick(points.at(1), points.at(3));

	solver.addStick(points.at(0), points.at(4));
	solver.addStick(points.at(4), points.at(5));
	solver.addStick(points.at(5), points.at(6));
	solver.addStick(points.at(6), points.at(7));

	solver.addStick(points.at(8), points.at(9));
	solver.addStick(points.at(9), points.at(10));
	solver.addStick(points.at(10), points.at(11));

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

