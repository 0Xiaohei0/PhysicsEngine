#include <SFML/Graphics.hpp>
#include "src/VerletObject.cpp"
#include "src/Solver.cpp"


const int WINDOW_SIZE_X = 1280;
const int WINDOW_SIZE_Y = 720;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");

	Solver solver;

	const int frame_rate = 60;
	window.setFramerateLimit(frame_rate);

	//solver configuration
	solver.setSimulationUpdateRate(frame_rate);

	//add objects to solver
	const sf::Vector2f object_spawn_position = { 500.0f, 200.0f };
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
		//render objects
		sf::CircleShape circle{ 1.0f };
		circle.setPointCount(32);
		circle.setOrigin(1.0f, 1.0f);
		const std::vector<VerletObject> objects = solver.getObjects();
		for (const VerletObject& obj : objects) {
			circle.setPosition(obj.position);
			circle.setScale(obj.radius, obj.radius);
			circle.setFillColor(obj.color);
			window.draw(circle);
		}


		window.display();
	}

	return 0;
}