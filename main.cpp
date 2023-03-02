#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <list>
#include "VerletObject.hpp"
#include "Solver.hpp"
#include "FPS.cpp"


const int WINDOW_SIZE_X = 1280;
const int WINDOW_SIZE_Y = 720;

const int frame_rate = 60;
const uint32_t     max_objects_count = 2100;
const float        object_spawn_delay = 0.002f;
const float        snapshotDelay = 15.0f;
const float        displayDelay = 10.0f;
const float        object_spawn_speed = 1200.0f;
const sf::Vector2f object_spawn_position = { 500.0f, 200.0f };
const float        object_min_radius = 3.0f;
const float        object_max_radius = 8.0f;
const float		   PI = 3.1415926535897932386f;
const float        max_angle = 1.0f;
FPS fps;
sf::Font font;
std::list<sf::Color> colorSnapshot;
Solver solver;
sf::Image image;

std::list<std::list<VerletObject>> playbackBuffer;


enum State
{
	SIMULATION,
	DISPLAY,
	PLAYBACK,
};

State state = SIMULATION;



static sf::Color getRainbow(float t)
{
	const float r = sin(t);
	const float g = sin(t + 0.33f * 2.0f * PI);
	const float b = sin(t + 0.66f * 2.0f * PI);
	return { static_cast<uint8_t>(255.0f * r * r),
			static_cast<uint8_t>(255.0f * g * g),
			static_cast<uint8_t>(255.0f * b * b) };
}

void reset() {
	std::vector<VerletObject>& objects = solver.getObjects();
	int objectsSize = objects.size();
	for (std::list<VerletObject>& snapshot : playbackBuffer) {
		int idx = 0;
		for (VerletObject& obj : snapshot) {
			if (idx < objectsSize) {
				obj.color = objects.at(idx).color;
				idx++;
			}
		}
	}

	//auto& objects = solver.getObjects();
	//for (VerletObject& obj : objects) {
	//	colorSnapshot.push_back(image.getPixel((int)obj.position.x, (int)obj.position.y));
	//}
	//solver = Solver();
	////solver configuration
	//solver.setSimulationUpdateRate(frame_rate);
	//solver.getObjects().reserve(1000000);
	//solver.setSubStepsCount(8);
	//srand(10);
	/*std::cout << "Pass2: " << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << rand() << std::endl;
	}*/
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");


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

	window.setFramerateLimit(frame_rate);

	//solver configuration
	solver.setSimulationUpdateRate(frame_rate);
	solver.getObjects().reserve(1000000);
	solver.setSubStepsCount(8);

	sf::Clock clock;
	sf::Clock mainclock;
	sf::Clock displayClock;
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
	/*std::cout << "Pass1: " << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << rand() << std::endl;
	}*/
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();



		std::vector<VerletObject>& objects = solver.getObjects();
		if (state == SIMULATION) {
			if (solver.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
				clock.restart();
				for (int i = 0; i < 4; i++) {
					auto& object = solver.addObject(object_spawn_position + sf::Vector2f(i * 100.0f, 0.0f), ((float)rand() / (RAND_MAX + 1)) * (object_max_radius - object_min_radius + 1) + object_min_radius);
					const float t = solver.getTime();
					const float angle = max_angle * sin(t) + PI * 0.5f;
					solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{ cos(angle), sin(angle) });
				}
				//object.color = image.getPixel((int)object.position.x, (int)object.position.y);
			}
			//std::cout << solver.getObjectsCount() << std::endl;
			if (mainclock.getElapsedTime().asSeconds() >= snapshotDelay) {
				state = DISPLAY;
				displayClock.restart();
			}
			//for (VerletObject& obj : objects) {
			//	if ((int)obj.position.x <= 0 || (int)obj.position.x >= WINDOW_SIZE_X ||
			//		(int)obj.position.y <= 0 || (int)obj.position.y <= WINDOW_SIZE_Y)
			//		continue;
			//	obj.color = image.getPixel((int)obj.position.x, (int)obj.position.y);
			//}

			//const sf::Vector2f position(0, 0.0f);
			//const float radius = 300.0f;
			//sf::CircleShape constriant{ radius };
			//constriant.setFillColor(sf::Color::Green);
			//constriant.setPosition(position);
			//window.draw(constriant);
		}
		if (state == DISPLAY) {
			for (VerletObject& obj : objects) {
				obj.color = image.getPixel((int)obj.position.x, (int)obj.position.y);
			}
			if (displayClock.getElapsedTime().asSeconds() >= displayDelay) {
				state = PLAYBACK;
				reset();
			}


		}
		if (state == PLAYBACK) {
			//if (solver.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
			//	clock.restart();
			//	auto& object = solver.addObject(object_spawn_position, ((float)rand() / (RAND_MAX + 1)) * (object_max_radius - object_min_radius + 1) + object_min_radius);
			//	const float t = solver.getTime();
			//	const float angle = max_angle * sin(t) + PI * 0.5f;
			//	solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{ cos(angle), sin(angle) });
			//	if (!colorSnapshot.empty())
			//	{
			//		object.color = colorSnapshot.front();
			//		colorSnapshot.pop_front();
			//	}
			//	//object.color = image.getPixel((int)object.position.x, (int)object.position.y);
			//}
			////std::cout << solver.getObjectsCount() << std::endl;
		}

		//render objects
		if (state == SIMULATION || state == DISPLAY) {
			std::list<VerletObject> currentSnapshot;
			for (VerletObject& obj : objects) {

				sf::CircleShape circle2{ 1.0f };
				circle2.setPointCount(32);
				circle2.setOrigin(1.0f, 1.0f);
				circle2.setPosition(obj.position);
				circle2.setScale(obj.radius, obj.radius);
				circle2.setFillColor(obj.color);
				window.draw(circle2);
				currentSnapshot.push_back(obj);
			}
			playbackBuffer.push_back(currentSnapshot);
			std::cout << playbackBuffer.back().size() << std::endl;
		}
		else if (state == PLAYBACK) {
			std::cout << playbackBuffer.size() << std::endl;
			if (!playbackBuffer.empty()) {
				std::list<VerletObject> snapshot = playbackBuffer.front();
				for (const VerletObject& obj : snapshot) {
					sf::CircleShape circle2{ 1.0f };
					circle2.setPointCount(32);
					circle2.setOrigin(1.0f, 1.0f);
					circle2.setPosition(obj.position);
					circle2.setScale(obj.radius, obj.radius);
					circle2.setFillColor(obj.color);
					window.draw(circle2);
				}
				playbackBuffer.pop_front();
			}
		}
		fps.update();
		FPSCounterText.setString(std::to_string(fps.getFPS()));
		window.draw(FPSCounterText);

		if (state != PLAYBACK)
			solver.update();


		window.display();
	}

	return 0;
}