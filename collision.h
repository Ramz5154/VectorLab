#pragma once
#include "objects.h"
#include <vector>
class collision
{
public: 
	static void AABBAABBCollisionAction(std::vector<Cube*>&, std::vector<Cube*>&, float delta);
	static void SphereAABBCollisionAction(std::vector<Sphere*>&, std::vector<Cube*>&, std::vector<Cube*>&);
};

