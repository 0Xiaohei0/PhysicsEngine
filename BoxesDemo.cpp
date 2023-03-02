#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <list>
#include "BoxesDemo.h"


void BoxesDemo::runDemo() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "anime physics");
	sf::Text FPSCounterText;

	if (!font.loadFromFile("OpenSans-Light.ttf"))
	{
		std::cout << "error loading font" << std::endl;
	}

	FPSCounterText.setFont(font);
	FPSCounterText.setCharacterSize(24);
	FPSCounterText.setFillColor(sf::Color::Red);
	window.setFramerateLimit(frame_rate);

	VerletObject& p1 = solver.addObject(sf::Vector2f(200.0f, 200.0f), 10.0f);
	VerletObject& p2 = solver.addObject(sf::Vector2f(220.0f, 200.0f), 10.0f);
	solver.addStick(p1, p2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();


		// Draw fps text
		fps.update();
		FPSCounterText.setString(std::to_string(fps.getFPS()));
		window.draw(FPSCounterText);


		window.display();
	}
}

