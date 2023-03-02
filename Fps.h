#pragma once
#include <SFML/Graphics.hpp>

class FPS
{
public:
	FPS();
	const unsigned int getFPS() const;
	void update();

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;
};