#include <SFML/Graphics.hpp>
#include "VerletObject.h"
#include "Solver.h"
#include <iostream>

Solver::Solver() {
	objectList.reserve(10000);
	stickList.reserve(10000);
}

Solver::Solver(int SimulationUpdateRate, int subStepsCount)
{
	objectList.reserve(10000);
	stickList.reserve(10000);
	setSimulationUpdateRate(SimulationUpdateRate);
	setSubStepsCount(subStepsCount);
}

void Solver::update()
{
	time += frame_dt;
	const float step_dt = getStepDt();
	for (uint32_t i{ sub_steps }; i--;) {
		applyGravity();
		updatePositions(step_dt);
		solveCollisions();
		updateSticks();
		ConstrainObjects();
	}
}

void Solver::applyGravity()
{
	for (auto& obj : objectList)
	{
		obj.setAcceleration(gravity);
	}
}

void Solver::updatePositions(float dt)
{
	for (auto& obj : objectList)
	{
		if (!obj.pinned)
		{
			obj.updatePosition(dt);
		}
	}
}

void Solver::updateSticks()
{
	for (size_t i = 0; i < stickList.size(); i++) {
		Stick& s = stickList.at(i);
		s.updatePosition();
	}
}

void Solver::ConstrainObjects() {

	for (auto& obj : objectList)
	{
		sf::Vector2f& position = obj.position;
		sf::Vector2f& position_old = obj.position_old;
		float& bounce = obj.bounce;
		float& radius = obj.radius;
		sf::Vector2f velocity = position - position_old;

		float rightbound = position.x + radius;
		float leftbound = position.x - radius;
		float topbound = position.y - radius;
		float bottombound = position.y + radius;
		if (rightbound > CONSTRAINT_WIDTH) {
			position.x = CONSTRAINT_WIDTH - radius;
			position_old.x = position.x + velocity.x * bounce;
		}
		else if (leftbound < START_X) {
			position.x = START_X + radius;
			position_old.x = position.x + velocity.x * bounce;
		}
		if (bottombound > HEIGHT) {
			position.y = HEIGHT - radius;
			position_old.y = position.y + velocity.y * bounce;
		}
		else if (topbound < START_Y) {
			position.y = START_Y + radius;
			position_old.y = position.y + velocity.y * bounce;
		}
	}
}

VerletObject& Solver::addObject(sf::Vector2f position, float radius)
{
	objectList.emplace_back(position, radius);
	return objectList.back();
}

VerletObject& Solver::addObject(sf::Vector2f position, float radius, bool pinned)
{
	objectList.emplace_back(position, radius, pinned);
	return objectList.back();
}

Stick& Solver::addStick(VerletObject& p1, VerletObject& p2)
{
	stickList.emplace_back(p1, p2);
	return stickList.back();
}

std::vector<VerletObject>& Solver::getObjects() {
	return objectList;
}

std::vector<Stick>& Solver::getSticks()
{
	return stickList;
}

void Solver::setSimulationUpdateRate(int rate)
{
	frame_dt = 1.0f / static_cast<float>(rate);
}

void Solver::solveCollisions()
{
	const auto objectCount = objectList.size();
	for (uint64_t i{ 0 }; i < objectCount; ++i) {
		VerletObject& object_1 = objectList[i];
		for (uint64_t j{ i + 1 }; j < objectCount; ++j) {
			VerletObject& object_2 = objectList[j];
			//if (std::addressof(object_1) == std::addressof(object_2)) continue;
			const sf::Vector2f collision_axis = object_1.position - object_2.position;
			const float dist2 = (collision_axis.x * collision_axis.x) + (collision_axis.y * collision_axis.y);
			const float min_dist = object_1.radius + object_2.radius;
			if (dist2 < min_dist * min_dist) {
				const float dist = sqrt(dist2);
				const sf::Vector2f n = collision_axis / dist;
				const float delta = (object_1.radius + object_2.radius) - dist;
				object_1.position += 0.5f * delta * n;
				object_2.position -= 0.5f * delta * n;
			}
		}
	}
}

void Solver::setObjectVelocity(VerletObject& object, sf::Vector2f v)
{
	object.setVelocity(v, getStepDt());
}

size_t Solver::getObjectsCount() {
	return objectList.size();
}

float Solver::getTime() const
{
	return time;
}
void Solver::setSubStepsCount(uint32_t sub_steps)
{
	this->sub_steps = sub_steps;
}
float Solver::getStepDt() const
{
	return frame_dt / static_cast<float>(sub_steps);
}

void Solver::setConstraint(int start_x, int start_y, int width, int height)
{
	START_X = start_x;
	START_Y = start_y;
	CONSTRAINT_WIDTH = width;
	HEIGHT = height;
}

void Solver::setGravity(sf::Vector2f gravity)
{
	this->gravity = gravity;
}
