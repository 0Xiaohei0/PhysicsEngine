#pragma once
#include "Stick.h"

class Solver
{
private:
	sf::Vector2f gravity = { 0.0f, 1000.0f };
	uint32_t                  sub_steps = 8;
	std::vector<VerletObject> objectList;
	std::vector<Stick> stickList;
	float frame_dt = 0.01666666666f;
	float time = 0.0f;
	int CONSTRAINT_WIDTH = 880;
	int HEIGHT = 720;
	int START_X = 400;
	int START_Y = 0;

public:
	Solver();
	Solver(int SimulationUpdateRate, int subStepsCount);

	void update();

	void applyGravity();

	void updatePositions(float dt);

	void ConstrainObjects();

	void updateSticks();

	VerletObject& addObject(sf::Vector2f position, float radius);

	Stick& addStick(VerletObject& p1, VerletObject& p2);

	std::vector<VerletObject>& getObjects();
	std::vector<Stick>& getSticks();

	void setSimulationUpdateRate(int rate);

	void solveCollisions();

	void setObjectVelocity(VerletObject& object, sf::Vector2f v);

	size_t getObjectsCount();

	float getTime() const;
	void setSubStepsCount(uint32_t sub_steps);
	float getStepDt() const;

	void setGravity(sf::Vector2f gravity);
};