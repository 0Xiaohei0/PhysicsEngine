#include <SFML/Graphics.hpp>
#include "./VerletObject.cpp"

class Solver
{
	sf::Vector2f gravity = { 0.0f, 3000.0f };
	float frame_dt = 0.0f;
	float time = 0.0f;


public:
	void update()
	{
		time += frame_dt;
		const float step_dt = getStepDt();
		for (uint32_t i{ sub_steps }; i--;) {
			applyGravity();
			updatePositions(step_dt);
			solveCollisions();
		}
	}

	void applyGravity()
	{
		for (auto& obj : objectList)
		{
			obj.setAcceleration(gravity);
		}
	}

	void updatePositions(float dt)
	{
		for (auto& obj : objectList)
		{
			obj.updatePosition(dt);
		}
	}

	VerletObject& addObject(sf::Vector2f position, float radius)
	{
		objectList.emplace_back(position, radius);
		return objectList.back();
	}

	std::vector<VerletObject>& getObjects() {
		return objectList;
	}

	void setSimulationUpdateRate(int rate)
	{
		frame_dt = 1.0f / static_cast<float>(rate);
	}

	void solveCollisions()
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

	void setObjectVelocity(VerletObject& object, sf::Vector2f v)
	{
		object.setVelocity(v, getStepDt());
	}

	size_t getObjectsCount() {
		return objectList.size();
	}

	float getTime() const
	{
		return time;
	}
	void setSubStepsCount(uint32_t sub_steps)
	{
		this->sub_steps = sub_steps;
	}
	float getStepDt() const
	{
		return frame_dt / static_cast<float>(sub_steps);
	}

private:
	uint32_t                  sub_steps = 1;
	std::vector<VerletObject> objectList;
};