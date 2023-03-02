#include "Stick.h"

Stick::Stick(VerletObject& p1, VerletObject& p2) : point1(p1), point2(p2), length(std::hypot(p1.position.x - p2.position.x, p1.position.y - p2.position.y))
{
}

void Stick::updatePosition()
{
	sf::Vector2f distanceVec = point1.position - point2.position;
	float distance = std::hypot(distanceVec.x, distanceVec.y);
	float difference = length - distance;
	float percent = difference / distance / 2;
	sf::Vector2f offset = distanceVec * percent;

	point1.position -= offset;
	point2.position += offset;
}
