#include "Renderer.h"

Renderer::Renderer(sf::RenderTarget& target) : m_target(target)
{
}

void Renderer::Render(Solver& solver)
{
	// Render circles
	sf::CircleShape circle{ 1.0f };
	circle.setPointCount(32);
	circle.setOrigin(1.0f, 1.0f);
	const auto& objects = solver.getObjects();
	for (const auto& obj : objects) {
		circle.setPosition(obj.position);
		circle.setScale(obj.radius, obj.radius);
		circle.setFillColor(obj.color);
		m_target.draw(circle);
	}
}
