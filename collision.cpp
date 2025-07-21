#include "collision.h"

using namespace glm;


bool collision::collisionDetection(const Sphere& object1, const Sphere& object2)
{
	float distance = glm::distance(object1.center, object2.center);
	if (distance < object1.radius + object2.radius) {
		return true;
	} 
	return false;
} 
