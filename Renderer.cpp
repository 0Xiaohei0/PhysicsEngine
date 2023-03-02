#include "Renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderTarget& target) : m_target(target)
{
}

void Renderer::Render(Solver& solver)
{
	// Render sticks
	const auto& sticks = solver.getSticks();
	for (const Stick& stick : sticks) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = stick.point1.position;
		lines[1].position = stick.point2.position;
		m_target.draw(lines);
	}



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
