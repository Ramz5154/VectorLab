#include "collision.h"
#include <algorithm>

using namespace glm;


bool collision::collisionDetection(const Sphere& object1, const Sphere& object2)
{
	float distance = glm::length(object1.trans.Position - object2.trans.Position);
	float radius1 = std::max({ object1.trans.Scale.x, object1.trans.Scale.y, object1.trans.Scale.z });
	float radius2 = std::max({ object2.trans.Scale.x, object2.trans.Scale.y, object2.trans.Scale.z });
	if (distance <= radius1 + radius2) {
		return true;
	} 
	return false;
} 
