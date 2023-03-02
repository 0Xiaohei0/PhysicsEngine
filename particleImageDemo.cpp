#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <list>
#include "VerletObject.cpp"
#include "Solver.cpp"
#include "FPS.cpp"

class ParticleImageDemo
{


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

	void reset() {
		std::vector<VerletObject>& objects = solver.getObjects();
		size_t objectsSize = objects.size();
		for (std::list<VerletObject>& snapshot : playbackBuffer) {
			size_t idx = 0;
			for (VerletObject& obj : snapshot) {
				if (idx < objectsSize) {
					obj.color = objects.at(idx).color;
					idx++;
				}
			}
		}
	}

public:
	int runParticleImageDemo()
	{
		sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "anime physics");

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

			// spawn objects
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
				}
				if (mainclock.getElapsedTime().asSeconds() >= snapshotDelay) {
					state = DISPLAY;
					displayClock.restart();
				}
			}
			// assign color to objects
			if (state == DISPLAY) {
				for (VerletObject& obj : objects) {
					obj.color = image.getPixel((int)obj.position.x, (int)obj.position.y);
				}
				if (displayClock.getElapsedTime().asSeconds() >= displayDelay) {
					state = PLAYBACK;
					reset();
				}
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
			// Draw fps text
			fps.update();
			FPSCounterText.setString(std::to_string(fps.getFPS()));
			window.draw(FPSCounterText);

			if (state != PLAYBACK)
				solver.update();


			window.display();
		}

		return 0;
	}
};