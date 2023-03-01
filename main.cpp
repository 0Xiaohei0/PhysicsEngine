#include <SFML/Graphics.hpp>
#include "VerletObject.cpp"
#include "Solver.cpp"


const int WINDOW_SIZE_X = 1280;

const int WINDOW_SIZE_Y = 720;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");

	Solver solver;

	const int frame_rate = 144;
	window.setFramerateLimit(frame_rate);

	//solver configuration
	solver.setSimulationUpdateRate(frame_rate);

	//add objects to solver
	const sf::Vector2f object_spawn_position = { 400.0f, 300.0f };
	solver.addObject(object_spawn_position, 30.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		solver.update();


		//const sf::Vector2f position(0, 0.0f);
		//const float radius = 300.0f;
		//sf::CircleShape constriant{ radius };
		//constriant.setFillColor(sf::Color::Green);
		//constriant.setPosition(position);
		//window.draw(constriant);

		//render objects

		const std::vector<VerletObject> objects = solver.getObjects();
		for (const VerletObject& obj : objects) {
			sf::CircleShape circle{ 1.0f };
			circle.setPointCount(32);
			circle.setOrigin(1.0f, 1.0f);
			circle.setPosition(obj.position_old);
			circle.setScale(obj.radius, obj.radius);
			circle.setFillColor(sf::Color::Magenta);
			window.draw(circle);

			sf::CircleShape circle2{ 1.0f };
			circle2.setPointCount(32);
			circle2.setOrigin(1.0f, 1.0f);
			circle2.setPosition(obj.position);
			circle2.setScale(obj.radius, obj.radius);
			circle2.setFillColor(obj.color);
			window.draw(circle2);
		}




		window.display();
	}

	return 0;
}