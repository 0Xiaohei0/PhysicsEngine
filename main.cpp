#include "particleImageDemo.h"
#include "BoxesDemo.h"
#include "ClothDemo.h"

enum CurrentDemo
{
	PARTICLE,
	BOX,
	CLOTH
};

int main()
{
	CurrentDemo currentDemo = CLOTH;

	if (currentDemo == PARTICLE) {
		ParticleImageDemo particleImageDemo;
		particleImageDemo.runParticleImageDemo();
	}
	else if (currentDemo == BOX) {
		BoxesDemo boxDemo;
		boxDemo.runDemo();
	}
	else if (currentDemo == CLOTH) {
		ClothDemo clothDemo;
		clothDemo.runDemo();
	}


	return 0;
}