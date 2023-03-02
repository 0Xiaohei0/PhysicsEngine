#include <SFML/Graphics.hpp>
#include "./VerletObject.hpp"

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
			//applyConstraint();
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

	void applyConstraint()
	{
		const sf::Vector2f constraintPosition(300, 300);
		const float radius = 300.0f;
		for (VerletObject& obj : objectList) {
			const sf::Vector2f to_obj = obj.position - constraintPosition;
			const float dist = std::sqrt((to_obj.x * to_obj.x) + (to_obj.y * to_obj.y));
			if (dist > (radius - obj.radius)) {
				//std::cout << dist << ',' << radius - obj.radius << std::endl;
				//const sf::Vector2f normal = to_obj / dist;
				//std::cout << normal.x << ',' << normal.y << std::endl;
				//obj.position_old = obj.position;
				//const sf::Vector2f velocity = obj.position - obj.position_old;
				//obj.position = sf::Vector2f(300.0f, 300.0f) + normal * (radius - obj.radius);

				//const sf::Vector2f to_obj = obj.position - constraintPosition;;
				//const float dist = std::sqrt((to_obj.x * to_obj.x) + (to_obj.y * to_obj.y));
				//const sf::Vector2f newRelativePos = normal * (dist - obj.radius);
				//std::cout << (dist - obj.radius) << std::endl;




				//obj.position_old = obj.position + obj.position - obj.position_old;
				//obj.position_old = sf::Vector2f(300.0f, 300.0f) + normal * (dist + obj.radius);
				//std::cout << obj.position_old.x << ',' << obj.position_old.y << "          " << obj.position.x << ',' << obj.position.y << std::endl;
			}
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
		//std::cout << objectCount << std::endl;
		for (VerletObject& object_1 : objectList) {
			for (VerletObject& object_2 : objectList) {
				if (std::addressof(object_1) == std::addressof(object_2)) continue;
				const sf::Vector2f collision_axis = object_1.position - object_2.position;
				const float dist = std::sqrt((collision_axis.x * collision_axis.x) + (collision_axis.y * collision_axis.y));
				//std::cout << dist << std::endl;
				//std::cout << object_1.position.x << ',' << object_1.position.y << "          " << object_2.position.x << ',' << object_2.position.y << std::endl;
				if (dist <= (object_1.radius + object_2.radius)) {
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