#pragma once
#include <SFML/Graphics.hpp>
#include "Solver.h"

class Renderer {
public:
	Renderer(sf::RenderTarget& target);

	void Render(Solver& solver);

private:
	sf::RenderTarget& m_target;
};