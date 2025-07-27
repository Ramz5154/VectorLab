#pragma once
#include "objects.h"
#include <vector>
class collision
{
public: 
	static bool SphereSphereCollisionDetection(const Sphere& object1, const Sphere& object2);
	static void SphereSphereCollisionAction(Sphere& object1, Sphere& Object2, float delta);
	static void AABBAABBCollisionAction(std::vector<Cube*>&, float delta);
	static bool AABBAABBCollisionDetection(const Cube& object1, const Cube& object2);
};

