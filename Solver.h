#pragma once

class Solver
{
private:
	sf::Vector2f gravity = { 0.0f, 3000.0f };
	uint32_t                  sub_steps = 1;
	std::vector<VerletObject> objectList;
	float frame_dt = 0.0f;
	float time = 0.0f;

public:
	void update();

	void applyGravity();

	void updatePositions(float dt);

	VerletObject& addObject(sf::Vector2f position, float radius);

	std::vector<VerletObject>& getObjects();

	void setSimulationUpdateRate(int rate);

	void solveCollisions();

	void setObjectVelocity(VerletObject& object, sf::Vector2f v);

	size_t getObjectsCount();

	float getTime() const;
	void setSubStepsCount(uint32_t sub_steps);
	float getStepDt() const;
};