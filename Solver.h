#pragma once
#include "Stick.h"
#include <list>

class Solver
{
private:
	sf::Vector2f gravity = { 0.0f, 1000.0f };
	uint32_t                  sub_steps = 8;
	std::vector<VerletObject> objectList;
	std::list<Stick> stickList;

	float frame_dt = 0.01666666666f;
	float time = 0.0f;
	int CONSTRAINT_WIDTH = 880;
	int HEIGHT = 720;
	int START_X = 400;
	int START_Y = 0;
	bool checkForCollisions = true;

public:
	Solver();
	Solver(int SimulationUpdateRate, int subStepsCount);

	void update();

	void applyGravity();

	void updatePositions(float dt);

	void ConstrainObjects();

	void updateSticks();

	VerletObject& addObject(sf::Vector2f position, float radius);

	VerletObject& addObject(sf::Vector2f position, float radius, bool pinned);

	Stick& addStick(VerletObject& p1, VerletObject& p2);

	std::vector<VerletObject>& getObjects();

	std::list<Stick>& getSticks();

	void setSimulationUpdateRate(int rate);

	void solveCollisions();

	void setObjectVelocity(VerletObject& object, sf::Vector2f v);

	size_t getObjectsCount();

	float getTime() const;
	void setSubStepsCount(uint32_t sub_steps);
	float getStepDt() const;

	void setConstraint(int start_x, int start_y, int width, int height);

	void setCheckForCollisions(bool doCheck);

	void setGravity(sf::Vector2f gravity);
};