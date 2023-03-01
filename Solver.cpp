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
		//applyConstraint();
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