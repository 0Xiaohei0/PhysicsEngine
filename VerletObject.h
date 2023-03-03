#pragma once
#include <SFML/Graphics.hpp>

class VerletObject
{
public:
	sf::Vector2f position;
	sf::Vector2f position_old;
	sf::Vector2f acceleration;

	float        radius = 10.0f;
	sf::Color    color = sf::Color::White;
	float		 bounce = 0.8f;
	float		 friction = 0.999f;

	VerletObject(sf::Vector2f position, float radius);

	void updatePosition(float dt);

	void setVelocity(sf::Vector2f v, float dt);

	void setAcceleration(sf::Vector2f acc);
};