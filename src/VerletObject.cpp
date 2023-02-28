#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class VerletObject
{
public:
	sf::Vector2f position;
	sf::Vector2f position_old;
	sf::Vector2f acceleration;

	float        radius = 10.0f;
	sf::Color    color = sf::Color::White;

	VerletObject(sf::Vector2f position, float radius)
	{
		this->position = position;
		this->radius = radius;
		position_old = { 0.0f, 0.0f };
		this->acceleration = { 0.0f, 0.0f };
	}

	void updatePosition(float dt)
	{
		std::cout << position.x << ',' << position.y << std::endl;
		const sf::Vector2f velocity = position - position_old;
		// Save current position
		position_old = position;
		// perform Verlet intergration
		position = position + velocity + acceleration * dt * dt;
		// Reset acceleration
		acceleration = {};
	}

	void accelerate(sf::Vector2f acc)
	{
		acceleration += acc;
	}

};