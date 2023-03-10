#include "Stick.h"
#include <iostream>

Stick::Stick(VerletObject& p1, VerletObject& p2) : point1(p1), point2(p2), length(std::hypot(p1.position.x - p2.position.x, p1.position.y - p2.position.y))
{
}

void Stick::updatePosition()
{
	sf::Vector2f distanceVec = point2.position - point1.position;
	float distance = std::hypot(distanceVec.x, distanceVec.y);
	//std::cout << distance << std::endl;
	float difference = length - distance;
	float percent = difference / distance / 2;
	sf::Vector2f offset = distanceVec * percent;

	if (!point1.pinned)
		point1.position -= offset;
	if (!point2.pinned)
		point2.position += offset;
}
