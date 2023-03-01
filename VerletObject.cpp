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
	float		 bounce = 0.5f;
	float		 friction = 0.999;

	VerletObject(sf::Vector2f position, float radius)
	{
		this->position = position;
		this->radius = radius;
		position_old = position - sf::Vector2f(-3.0f, -3.0f);
		this->acceleration = { 0.0f, 0.0f };
	}

	void updatePosition(float dt)
	{
		sf::Vector2f velocity = position - position_old;
		velocity = velocity * friction;
		//std::cout << position.x << ',' << position.y << ' ' << position_old.x << ',' << position_old.y << "        ";
		//std::cout << velocity.x << ',' << velocity.y << std::endl;
		// Save current position
		position_old = position;
		// perform Verlet intergration
		position = position + velocity + acceleration * dt * dt;
		// Reset acceleration
		acceleration = {};

		float width = 1280;
		float height = 720;
		float rightbound = position.x + radius;
		float leftbound = position.x - radius;
		float topbound = position.y - radius;
		float bottombound = position.y + radius;
		if (rightbound > width) {
			position.x = width - radius;
			position_old.x = position.x + velocity.x * bounce;
		}
		else if (leftbound < 0) {
			position.x = 0 + radius;
			position_old.x = position.x + velocity.x * bounce;
		}
		if (bottombound > height) {
			position.y = height - radius;
			position_old.y = position.y + velocity.y * bounce;
		}
		else if (topbound < 0) {
			position.y = 0 + radius;
			position_old.y = position.y + velocity.y * bounce;
		}
	}

	void setAcceleration(sf::Vector2f acc)
	{
		acceleration += acc;
	}

};