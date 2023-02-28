#include <SFML/Graphics.hpp>
#include "./VerletObject.cpp"

class Solver
{
	sf::Vector2f gravity = { 0.0f, 1000.0f };
	float frame_dt = 0.0f;

public:
	void update()
	{
		applyGravity();
		updatePositions(frame_dt);
	}

	void applyGravity()
	{
		for (auto& obj : objectList)
		{
			obj.accelerate(gravity);
		}
	}

	void updatePositions(float dt)
	{
		for (auto& obj : objectList)
		{
			obj.updatePosition(dt);
		}
	}

	void addObject(sf::Vector2f position, float radius)
	{
		objectList.emplace_back(position, radius);
	}

	std::vector<VerletObject> getObjects() {
		return objectList;
	}

	void setSimulationUpdateRate(int rate)
	{
		frame_dt = 1.0f / static_cast<float>(rate);
	}


private:
	std::vector<VerletObject> objectList;
};