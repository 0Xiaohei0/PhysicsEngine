#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <list>
#include "VerletObject.h"
#include "Solver.h"
#include "FPS.h"

class ParticleImageDemo
{
	const int WINDOW_SIZE_X = 1280;
	const int WINDOW_SIZE_Y = 720;

	const int frame_rate = 144;
	const uint32_t     max_objects_count = 2100;
	const float        object_spawn_delay = 0.025f;
	const float        snapshotDelay = 15.0f;
	const float        displayDelay = 10.0f;
	const float        object_spawn_speed = 1200.0f;
	const sf::Vector2f object_spawn_position = { 500.0f, 50.0f };
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

	void reset();

public:
	ParticleImageDemo();
	int runParticleImageDemo();
};