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
	float		 bounce = 1.0f;
	float		 friction = 0.999f;

	VerletObject(sf::Vector2f position, float radius)
	{
		this->position = position;
		this->radius = radius;
		position_old = position - sf::Vector2f(0.0f, 0.0f);
		this->acceleration = { 0.0f, 0.0f };
	}

	void updatePosition(float dt)
	{
		sf::Vector2f velocity = position - position_old;
		velocity = velocity;
		position_old = position;
		// perform Verlet intergration
		position = position + velocity + acceleration * dt * dt;
		// Reset acceleration
		acceleration = {};

		// bound checking
		float width = 880;
		float height = 720;
		float startx = 400;
		float starty = 0;
		float rightbound = position.x + radius;
		float leftbound = position.x - radius;
		float topbound = position.y - radius;
		float bottombound = position.y + radius;
		if (rightbound > width) {
			position.x = width - radius;
			position_old.x = position.x + velocity.x * bounce;
		}
		else if (leftbound < startx) {
			position.x = startx + radius;
			position_old.x = position.x + velocity.x * bounce;
		}
		if (bottombound > height) {
			position.y = height - radius;
			position_old.y = position.y + velocity.y * bounce;
		}
		else if (topbound < starty) {
			position.y = starty + radius;
			position_old.y = position.y + velocity.y * bounce;
		}
	}

	void setVelocity(sf::Vector2f v, float dt)
	{
		position_old = position - (v * dt);
	}

	void setAcceleration(sf::Vector2f acc)
	{
		acceleration += acc;
	}

};