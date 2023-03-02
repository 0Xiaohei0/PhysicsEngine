#pragma once
#include "VerletObject.h"

class Stick
{
public:
	Stick(VerletObject& point1, VerletObject& point2);
	void updatePosition();

private:
	VerletObject& point1;
	VerletObject& point2;
	float length;
};
