#include <SFML/Graphics.hpp>
#include "VerletObject.hpp"
#include "Solver.hpp"


const int WINDOW_SIZE_X = 1280;

const int WINDOW_SIZE_Y = 720;

const uint32_t     max_objects_count = 100;
const float        object_spawn_delay = 0.025f;
const float        object_spawn_speed = 1200.0f;
const sf::Vector2f object_spawn_position = { 500.0f, 200.0f };
const float        object_min_radius = 10.0f;
const float        object_max_radius = 30.0f;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");

	Solver solver;

	const int frame_rate = 144;
	window.setFramerateLimit(frame_rate);

	//solver configuration
	solver.setSimulationUpdateRate(frame_rate);

	sf::Clock clock;



	//add objects to solver
	//solver.addObject({ 310.0f, 330.0f }, 10.f);
	//solver.addObject({ 300.0f, 300.0f }, 10.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (solver.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
			clock.restart();
			auto& object = solver.addObject(object_spawn_position, ((float)rand() / (RAND_MAX + 1)) * (object_max_radius - object_min_radius + 1) + object_min_radius);
			const float t = solver.getTime();
			//const float angle = max_angle * sin(t) + Math::PI * 0.5f;
			//solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{ cos(angle), sin(angle) });
			//object.color = getRainbow(t);
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
			//sf::CircleShape circle{ 1.0f };
			//circle.setPointCount(32);
			//circle.setOrigin(1.0f, 1.0f);
			//circle.setPosition(obj.position_old);
			//circle.setScale(obj.radius, obj.radius);
			//circle.setFillColor(sf::Color::Magenta);
			//window.draw(circle);

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