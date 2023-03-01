#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include "VerletObject.hpp"
#include "Solver.hpp"
#include "FPS.cpp"


const int WINDOW_SIZE_X = 1280;

const int WINDOW_SIZE_Y = 720;

const uint32_t     max_objects_count = 300;
const float        object_spawn_delay = 0.025f;
const float        object_spawn_speed = 1200.0f;
const sf::Vector2f object_spawn_position = { 500.0f, 200.0f };
const float        object_min_radius = 20.0f;
const float        object_max_radius = 35.0f;
const float		   PI = 3.1415926535897932386f;
const float        max_angle = 1.0f;
FPS fps;
sf::Font font;

static sf::Color getRainbow(float t)
{
	const float r = sin(t);
	const float g = sin(t + 0.33f * 2.0f * PI);
	const float b = sin(t + 0.66f * 2.0f * PI);
	return { static_cast<uint8_t>(255.0f * r * r),
			static_cast<uint8_t>(255.0f * g * g),
			static_cast<uint8_t>(255.0f * b * b) };
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");

	sf::Image image;
	if (!image.loadFromFile("bocchi.jpg"))
	{
		std::cout << "Error loading image." << std::endl;
	}
	if (!font.loadFromFile("OpenSans-Light.ttf"))
	{
		std::cout << "error loading font" << std::endl;
	}

	sf::Text FPSCounterText;
	FPSCounterText.setFont(font);
	FPSCounterText.setCharacterSize(24);
	FPSCounterText.setFillColor(sf::Color::Red);

	Solver solver;

	const int frame_rate = 144;
	window.setFramerateLimit(frame_rate);

	//solver configuration
	solver.setSimulationUpdateRate(frame_rate);

	sf::Clock clock;


	//add objects to solver
	//solver.addObject({ 310.0f, 330.0f }, 10.f);
	//solver.addObject({ 300.0f, 300.0f }, 10.f);

	//for (int i = 0; i < WINDOW_SIZE_X; i += 30) {
	//	for (int j = 0; j < WINDOW_SIZE_Y; j += 30) {
	//		auto& reference = solver.addObject(sf::Vector2f(i, j), 10);
	//		reference.color = sf::Color::Blue;
	//	}
	//}

	//std::cout << "Pass1: " << std::endl;
	//srand(10);
	//for (int i = 0; i < 10; i++) {

	//	std::cout << rand() << std::endl;
	//}
	//srand(10);
	//std::cout << "Pass2: " << std::endl;
	//for (int i = 0; i < 10; i++) {

	//	std::cout << rand() << std::endl;
	//}
	srand(10);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		fps.update();
		FPSCounterText.setString(std::to_string(fps.getFPS()));
		window.draw(FPSCounterText);

		std::vector<VerletObject>& objects = solver.getObjects();

		if (solver.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
			clock.restart();
			auto& object = solver.addObject(object_spawn_position, ((float)rand() / (RAND_MAX + 1)) * (object_max_radius - object_min_radius + 1) + object_min_radius);
			const float t = solver.getTime();
			const float angle = max_angle * sin(t) + PI * 0.5f;
			solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{ cos(angle), sin(angle) });
			//object.color = image.getPixel((int)object.position.x, (int)object.position.y);
		}

		for (VerletObject& obj : objects) {
			obj.color = image.getPixel((int)obj.position.x, (int)obj.position.y);;
		}


		solver.update();


		//const sf::Vector2f position(0, 0.0f);
		//const float radius = 300.0f;
		//sf::CircleShape constriant{ radius };
		//constriant.setFillColor(sf::Color::Green);
		//constriant.setPosition(position);
		//window.draw(constriant);

		//render objects

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