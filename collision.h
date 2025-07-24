#pragma once
#include "objects.h"

class collision
{
public: 
	static bool SphereSphereCollisionDetection(const Sphere& object1, const Sphere& object2);
	static void SphereSphereCollisionAction(Sphere& object1, Sphere& Object2, float delta);
};

