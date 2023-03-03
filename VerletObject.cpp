#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "VerletObject.h"




VerletObject::VerletObject(sf::Vector2f position, float radius)
{
	this->position = position;
	this->radius = radius;
	position_old = position - sf::Vector2f(0.0f, 0.0f);
	this->acceleration = { 0.0f, 0.0f };
}

void VerletObject::updatePosition(float dt)
{
	sf::Vector2f velocity = position - position_old;
	velocity = velocity;
	position_old = position;
	// perform Verlet intergration
	position = position + velocity + acceleration * dt * dt;
	// Reset acceleration
	acceleration = {};
}

void VerletObject::setVelocity(sf::Vector2f v, float dt)
{
	position_old = position - (v * dt);
}

void VerletObject::setAcceleration(sf::Vector2f acc)
{
	acceleration += acc;
}