#include <SFML/Graphics.hpp>
#include "Fps.h"


FPS::FPS() : mFrame(0), mFps(0) {}
const unsigned int FPS::getFPS() const { return mFps; }

void FPS::update()
{
	if (mClock.getElapsedTime().asSeconds() >= 1.f)
	{
		mFps = mFrame;
		mFrame = 0;
		mClock.restart();
	}
	++mFrame;
}